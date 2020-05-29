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
#include <vector>

#include "../common/Common.h"


enum MemorySpace
{
	SYS, PPU
};

namespace Core
{

	class Bus
	{
	private:
		// General system memory and graphics memory
		// For some reason these don't share the same memory space
		std::vector<u8> memSys;
		std::vector<u8> memPPU;
	public:
		u8 read8(u16 addr, MemorySpace memspace);
		void write8(u16 addr, u8 byte, MemorySpace memspace);
		u16 read16(u16 addr, MemorySpace memspace);
		void write16(u16 addr, u16 word, MemorySpace memspace);
		void writeBytes(const std::vector<u8>& src, u16 addr, MemorySpace memspace);

		Bus();
	};

} // namespace Core
