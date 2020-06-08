// Copyright (C) 2020 Marina Terry
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "Cart.h"

#include "../../debug/Log.h"
#include "mappers/MapperNROM.h"


const u8 iNESMagic[4] = {
	0x4E, 0x45, 0x53, 0x1A
};

namespace Memory {

bool Cart::load()
{
	if(memcmp(raw.data(), iNESMagic, 4) == 0) {
		Debug::LogInfo("Detected iNES ROM!");

		if((raw.at(0x07) & 0x0C) == 0x08) {
			Debug::LogInfo("Detected NES2.0 ROM!");
			return parseiNESHeader() && parseNES2Header();
		}
		return parseiNESHeader();
	} else {
		Debug::LogError("Rom format unsupported!");
		return false;
	}
}

bool Cart::parseiNESHeader()
{
	memcpy(header.magicNumbers, raw.data(), 4);

	header.hasTrainer = raw.at(6) & 0x04;
	if(header.hasTrainer) {
		Debug::LogError("Trainer support not implemented!");
		return false;
	}

	header.prgRomBanks = raw.at(0x04);
	Debug::LogHex("PRG banks: ", 2, header.prgRomBanks);
	header.chrRomBanks = raw.at(0x05);
	Debug::LogHex("CHR banks: ", 2, header.chrRomBanks);

	unsigned int prgSize = 0x4000 * header.prgRomBanks;
	unsigned int chrSize = 0x2000 * header.chrRomBanks;

	if(raw.size() < 0x10 + prgSize + chrSize) {
		Debug::LogError("Rom smaller than specified in header! Aborting!");
		return false;
	}

	prgRom.resize(prgSize);
	chrRom.resize(chrSize);

	for(int i = 0x0000; i < prgSize; i++) {
		prgRom.at(i) = raw.at(0x10 + i);
	}
	for(int i = 0x0000; i < chrSize; i++) {
		chrRom.at(i) = raw.at(0x10 + prgSize + i);
	}

	header.mirrorType = (raw.at(0x06) & 0x01)? MirroringType::VERTICAL : MirroringType::HORIZONTAL;
	header.hasPersistantRAM = raw.at(0x06) & 0x02;
	header.use4ScreenVRAM = raw.at(0x06) & 0x08;

	return setMapper(((raw.at(0x06) & 0xF0) >> 4) | (raw.at(0x07) & 0xF0));
}

bool Cart::parseNES2Header()
{
	// TODO
	Debug::LogError("NES2 not implemented!");
	return false;
}

bool Cart::setMapper(u8 mapperType)
{
	Debug::LogHex("ROM Mapper Type: ", 2, mapperType);

	switch(mapperType)
	{
		case 0x00:
			mapper = new MapperNROM(this);
			break;
		default:
			Debug::LogError("Mapper not supported!");
			return false;
	}
	return true;
}

void Cart::write8(u16 addr, u8 byte)
{
	getCartSection(addr).at(addr) = byte;
}

u8 Cart::read8(u16 addr)
{
	return getCartSection(addr).at(addr);
}

void Cart::write16(u16 addr, u16 word)
{
	std::vector<u8>& cartSect = getCartSection(addr);
	cartSect.at(addr) = word & 0xFF;
	cartSect.at(addr + 1) = (word & 0xFF00) >> 8;
}

u16 Cart::read16(u16 addr)
{
	std::vector<u8>& cartSect = getCartSection(addr);
	return cartSect.at(addr) | (cartSect.at(addr + 1) << 8);
}

void Cart::writeBytes(const std::vector<u8>& bytes, u16 addr)
{

}

void Cart::readBytes(u16 addr, std::vector<u8>& dest, int bytes)
{
	std::vector<u8>& cartSect = getCartSection(addr);
	for(int i = 0; i < bytes; i++) {
		dest.at(i) = cartSect.at(addr + i);
	}
}

std::vector<u8>& Cart::getCartSection(u16& addr)
{
	if(addr >= 0x0000 && addr < 0x1FE0) { // Expansion ROM: 0x4020 - 0x5FFF
		return expRom;
	} else if(addr >= 0x1FE0 && addr < 0x3FE0) { // SRAM: 0x6000 - 0x7FFF
		addr -= 0x1FE0;
		return sram;
	} else {		  					  // Else, use PRG ROM: 0x8000 - 0xFFFF
		addr -= 0x3FE0;
		return prgRom;
	}
}

} // namespace Memory
