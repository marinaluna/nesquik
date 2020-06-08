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

#include "memory/MemoryComponent.h"
#include "memory/Cart.h"
#include "memory/RAM.h"

namespace Core
{

Bus::Bus(Memory::RAM* _cpuRam, Memory::Cart* _cart)
:	cpuRam(_cpuRam),
	cart(_cart)
{}

u8 Bus::read8(u16 addr) {
	return getComponentForAddr(addr)->read8(addr);
}

void Bus::write8(u16 addr, u8 byte) {
	getComponentForAddr(addr)->write8(addr, byte);
}

u16 Bus::read16(u16 addr) {
	return getComponentForAddr(addr)->read16(addr);
}

void Bus::write16(u16 addr, u16 word) {
	getComponentForAddr(addr)->write16(addr, word);
}

void Bus::writeBytes(const std::vector<u8>& src, u16 addr) {
	getComponentForAddr(addr)->writeBytes(src, addr);
}

void Bus::readBytes(u16 addr, std::vector<u8>& dest, int bytes) {
	getComponentForAddr(addr)->readBytes(addr, dest, bytes);
}

//////////////////////////////
// Returns Component and
// offsets the address to
// the component's base addr
//////////////////////////////
Memory::MemoryComponent* Bus::getComponentForAddr(u16& addr)
{
	// TODO: Separate IO regs
	if(addr >= 0x0000 && addr < 0x4020) {
		return cpuRam;
	} else if(addr >= 0x4020 && addr <= 0xFFFF) {
		addr -= 0x4020;
		return cart;
	}
	// TODO: Error handling
	return cpuRam;
}

} // namespace Core
