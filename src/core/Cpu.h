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

#include "../common/Common.h"
#include "Bus.h"

namespace Memory {
	class RAM;
}

struct Registers {
	// General purpose regs
	u8 X, Y, A;
	// Stack pointer
	u8 SP;
	// Status register
	u8 P;
	// Program counter
	u16 PC;
};

namespace Core
{

	class Cpu
	{
	private:
		std::shared_ptr<Bus> bus;

		Registers regs;
		// System RAM
		Memory::RAM* ram;

	public:
		Cpu();

		bool reset();
		void run(int cycles);

		void setBus(std::shared_ptr<Bus>& _bus);

		Memory::RAM* getRAM();
	};

} // namespace Core
