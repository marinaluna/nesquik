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

namespace Core {
namespace Memory {

bool Cart::load()
{
	if(memcmp(raw.data(), iNESMagic, 4) == 0) {
		LOG_INFO("Detected iNES ROM!");

		if((raw.at(0x07) & 0x0C) == 0x08) {
			LOG_INFO("Detected NES2.0 ROM!");
			return parseiNESHeader() && parseNES2Header();
		}
		return parseiNESHeader();
	} else {
		LOG_ERR("Rom format unsupported!");
		return false;
	}
}

bool Cart::parseiNESHeader()
{
	memcpy(header.magicNumbers, raw.data(), 4);

	header.hasTrainer = raw.at(6) & 0x04;
	if(header.hasTrainer) {
		LOG_ERR("Trainer support not implemented!");
		return false;
	}

	header.prgRomBanks = raw.at(0x04);
	LOG_HEX("PRG banks: ", 2, header.prgRomBanks);

	uint prgSize = 0x4000 * header.prgRomBanks;
	prgRom.resize(prgSize);
	if(raw.size() < 0x10 + prgSize) {
		LOG_ERR("Rom smaller than specified in header! Aborting!");
		return false;
	}
	for(int i = 0x0000; i < prgSize; i++){
		prgRom.at(i) = raw.at(0x10 + i);
	}

	header.chrRomBanks = raw.at(0x05);
	LOG_HEX("CHR banks: ", 2, header.chrRomBanks);
	chrRom.resize(0x2000 * header.chrRomBanks);

	header.mirrorType = (raw.at(0x06) & 0x01)? MirroringType::VERTICAL : MirroringType::HORIZONTAL;
	header.hasPersistantRAM = raw.at(0x06) & 0x02;
	header.use4ScreenVRAM = raw.at(0x06) & 0x08;

	return setMapper(((raw.at(0x06) & 0xF0) >> 4) | (raw.at(0x07) & 0xF0));
}

bool Cart::parseNES2Header()
{
	// TODO
	LOG_ERR("NES2 not implemented!");
	return false;
}

bool Cart::setMapper(u8 mapperType)
{
	LOG_HEX("ROM Mapper Type: ", 2, mapperType);

	switch(mapperType)
	{
		case 0x00:
			mapper = new MapperNROM(this);
			break;
		default:
			LOG_ERR("Mapper not supported!");
			return false;
	}
	return true;
}

void Cart::write8(u16 addr, u8 byte)
{

}

u8 Cart::read8(u16 addr)
{
	return 0xFF;
}

} // namespace Memory
} // namespace Core