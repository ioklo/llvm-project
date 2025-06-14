//===-- MCTargetOptionsCommandFlags.h --------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains machine code-specific flags that are shared between
// different command line tools.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCTARGETOPTIONSCOMMANDFLAGS_H
#define LLVM_MC_MCTARGETOPTIONSCOMMANDFLAGS_H

#include "llvm/MC/MCConfig.h"
#include <optional>
#include <string>

namespace llvm {

class MCTargetOptions;
enum class EmitDwarfUnwindType;

namespace mc {

LLVM_MC_ABI bool getRelaxAll();
LLVM_MC_ABI std::optional<bool> getExplicitRelaxAll();

LLVM_MC_ABI bool getIncrementalLinkerCompatible();

LLVM_MC_ABI bool getFDPIC();

LLVM_MC_ABI int getDwarfVersion();

LLVM_MC_ABI bool getDwarf64();

LLVM_MC_ABI EmitDwarfUnwindType getEmitDwarfUnwind();

LLVM_MC_ABI bool getEmitCompactUnwindNonCanonical();

LLVM_MC_ABI bool getShowMCInst();

LLVM_MC_ABI bool getFatalWarnings();

LLVM_MC_ABI bool getNoWarn();

LLVM_MC_ABI bool getNoDeprecatedWarn();

LLVM_MC_ABI bool getNoTypeCheck();

LLVM_MC_ABI bool getSaveTempLabels();

LLVM_MC_ABI bool getCrel();

LLVM_MC_ABI bool getImplicitMapSyms();

LLVM_MC_ABI bool getX86RelaxRelocations();

LLVM_MC_ABI bool getX86Sse2Avx();

LLVM_MC_ABI std::string getABIName();

LLVM_MC_ABI std::string getAsSecureLogFile();

/// Create this object with static storage to register mc-related command
/// line options.
struct RegisterMCTargetOptionsFlags {
  LLVM_MC_ABI RegisterMCTargetOptionsFlags();
};

LLVM_MC_ABI MCTargetOptions InitMCTargetOptionsFromFlags();

} // namespace mc

} // namespace llvm

#endif
