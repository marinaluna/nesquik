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
#pragma once
#include <memory>
#include <vector>

#include "../../common/Common.h"
#include "../PPU.h"
#include "MemoryComponent.h"


namespace Memory {
	class Mapper;

	class Cart : public MemoryComponent
	{
	private:
		std::vector<u8> raw;

		struct
		{
			char magicNumbers[4]; // Should be 'N, E, S, 0x1A'
			u8 prgRomBanks; // Total size is 16KB * prgRomBanks
			u8 chrRomBanks; // Total size is 8KB * chrRomBanks, if 0 then the game uses CHR RAM
			MirroringType mirrorType; // 0 for horizontal, 1 for vertical
			bool hasPersistantRAM; // Such as PRG RAM @ $6000-$7FFF
			bool hasTrainer; // 512 bytes @ $7000-$71FF
			bool use4ScreenVRAM; // Ignore mirroring bit
			u8 mapper;
		} header;

		Mapper* mapper;
		
		std::vector<u8> prgRom;
		std::vector<u8> chrRom;
		std::vector<u8> expRom;
		std::vector<u8> sram;

		bool parseiNESHeader();
		bool parseNES2Header();

		bool setMapper(u8 mapperType);

		std::vector<u8>& getCartSection(u16& addr);

	public:

		Cart(std::vector<u8>& rawBytes): raw(rawBytes) {}

		bool load();

		virtual void write8(u16 addr, u8 byte) override;
		virtual u8 read8(u16 addr) override;
		virtual void write16(u16 addr, u16 word) override;
		virtual u16 read16(u16 addr) override;
		virtual void writeBytes(const std::vector<u8>& bytes, u16 addr) override;
		virtual void readBytes(u16 addr, std::vector<u8>& dest, int bytes) override;
	};

} // namespace Memory
