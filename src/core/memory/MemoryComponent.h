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

#include "../../common/Common.h"


namespace Memory {

	class MemoryComponent
	{
	public:
		MemoryComponent() {}

		virtual void write8(u16 addr, u8 byte) = 0;
		virtual u8 read8(u16 addr) = 0;
		virtual void write16(u16 addr, u16 word) = 0;
		virtual u16 read16(u16 addr) = 0;
		virtual void writeBytes(const std::vector<u8>& bytes, u16 addr) = 0;
		virtual void readBytes(u16 addr, std::vector<u8>& dest, int bytes) = 0;
	};

} // namespace Memory
