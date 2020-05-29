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

#include <cstdint>


using u8 = uint8_t;
using u16 = uint16_t;

using s8 = int8_t;
using s16 = int16_t;


///////////////////////////////
// Bits of the status register
///////////////////////////////
#define STATUS_NEGATIVE   0x80
#define STATUS_OVERFLOW   0x40
#define STATUS_BREAKCMD   0x10
#define STATUS_DECIMAL    0x08 // Unused by the NES
#define STATUS_DISABLEINT 0x04
#define STATUS_ZERO       0x02
#define STATUS_CARRY      0x01
