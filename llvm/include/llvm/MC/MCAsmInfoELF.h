//===- llvm/MC/MCAsmInfoELF.h - ELF Asm info --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCASMINFOELF_H
#define LLVM_MC_MCASMINFOELF_H

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCConfig.h"

namespace llvm {

class MCAsmInfoELF : public MCAsmInfo {
  LLVM_MC_ABI virtual void anchor();
  LLVM_MC_ABI MCSection *
  getNonexecutableStackSection(MCContext &Ctx) const final;

protected:
  LLVM_MC_ABI MCAsmInfoELF();
};

} // end namespace llvm

#endif // LLVM_MC_MCASMINFOELF_H
