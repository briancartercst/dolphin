// Copyright 2010 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>
#include <vector>

#include "Common/CommonTypes.h"

namespace Gecko
{
class GeckoCode
{
public:
  GeckoCode() : enabled(false) {}
  struct Code
  {
    u32 address = 0;
    u32 data = 0;
    std::string original_line;
  };

  std::vector<Code> codes;
  std::string name, creator;
  std::vector<std::string> notes;

  bool enabled;
  bool user_defined;

  bool Compare(const GeckoCode& compare) const;
  bool Exist(u32 address, u32 data) const;
};

// Installation address for codehandler.bin in the Game's RAM
constexpr u32 INSTALLER_BASE_ADDRESS = 0x80001800;
constexpr u32 ENTRY_POINT = 0x800018A8;

// This forms part of a communication protocol with HLE_Misc::HLEGeckoCodehandler.
// Basically, codehandleronly.s doesn't use ICBI like it's supposed to when patching the
// game's code. This results in the JIT happily ignoring all code patches for blocks that
// are already compiled. The hack for getting around that is that the first 5 frames after
// the handler is installed (0xD01F1BAD -> +5 -> 0xD01F1BB2) cause full ICache resets.
//
// HLEGeckoCodehandler will increment this value 5 times then cease flushing the ICache to
// preserve the emulation performance.
constexpr u32 MAGIC_GAMEID = 0xD01F1BAD;

void SetActiveCodes(const std::vector<GeckoCode>& gcodes);
void RunCodeHandler();

}  // namespace Gecko
