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
#include <memory>

#include "common/Common.h"
#include "core/Cpu.h"
#include "core/Bus.h"

namespace Core {
	namespace Memory {
		class Cart;
	}

	class Cpu;
}

 
class NES
{
private:
	Core::Memory::Cart* cart;

	std::unique_ptr<Core::Cpu> cpu;
	//std::unique_ptr<Core::PPU> ppu;
	std::shared_ptr<Core::Bus> bus;

	bool isRunning;

public:
	NES(std::vector<u8>& romBytes);

	bool boot();
	void stop();

	void tick();
};
