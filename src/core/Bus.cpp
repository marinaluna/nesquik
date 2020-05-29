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
#include "Bus.h"

#include <iostream>
namespace Core
{

Bus::Bus()
{
	memSys.resize(0x10000);
	memset(memSys.data(), 0x00, memSys.size());
	memPPU.resize(0x10000);
	memset(memPPU.data(), 0x00, memPPU.size());
}

u8 Bus::read8(u16 addr, MemorySpace memspace)
{
	if(memspace == MemorySpace::SYS)
		return memSys.at(addr);
	else
		return memPPU.at(addr);
}

void Bus::write8(u16 addr, u8 byte, MemorySpace memspace)
{
	if(memspace == MemorySpace::SYS)
		memSys.at(addr) = byte;
	else
		memPPU.at(addr) = byte;
}

u16 Bus::read16(u16 addr, MemorySpace memspace)
{
	if(memspace == MemorySpace::SYS)
		return memSys.at(addr) | (memSys.at(addr + 1) << 8);
	else
		return memPPU.at(addr) | (memPPU.at(addr + 1) << 8);
}

void Bus::write16(u16 addr, u16 word, MemorySpace memspace)
{
	if(memspace == MemorySpace::SYS) {
		memSys.at(addr) = word & 0xFF;
		memSys.at(addr + 1) = (word & 0xFF00) >> 8;
	} else {
		memPPU.at(addr) = word & 0xFF;
		memPPU.at(addr + 1) = (word & 0xFF00) >> 8;
	}
}

void Bus::writeBytes(const std::vector<u8>& src, u16 addr, MemorySpace memspace)
{
	u16 counter = 0;
	for(u8 byte : src) {
		write8(addr + counter, byte, memspace);
		counter++;
	}
}

} // namespace Core
