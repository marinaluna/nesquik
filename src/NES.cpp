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
#include "NES.h"

#include "core/memory/MemoryComponent.h"
#include "core/memory/RAM.h"
#include "core/memory/Cart.h"
#include "core/Cpu.h"


NES::NES(std::vector<u8>& romBytes)
{
	cpu = std::make_unique<Core::Cpu>();
	cart = new Memory::Cart(romBytes);

	bus = std::make_shared<Core::Bus>(cpu->getRAM(), cart);

	cpu->setBus(bus);
}

/////////////////////////
// Returns true if boots
// successfully
/////////////////////////
bool NES::boot()
{
	bool success = false;

	success = cart->load() && cpu->reset();
	
	running = success;
	return success;
}

void NES::stop()
{
	running = false;
}

void NES::tick()
{
	cpu->step(1);
}

bool NES::isRunning()
{
	return running;
}
