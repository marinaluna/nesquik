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


namespace Core
{
	namespace Memory {
		class RAM;
	}


	class Cpu
	{
	private:
		std::shared_ptr<Bus> bus;
		// General purpose registers
		u8 reg_X, reg_Y, reg_A;
		// Special purpose registers
		u8 reg_SP;
		u8 reg_P;
		u16 reg_PC;
		// System RAM
		Memory::RAM* ram;

	public:
		Cpu(std::shared_ptr<Bus>& _bus);

		bool reset();
		void run(int cycles);

		Memory::RAM* getRAM();
	};

} // namespace Core
