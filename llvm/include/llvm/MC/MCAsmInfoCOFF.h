//===- MCAsmInfoCOFF.h - COFF asm properties --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCASMINFOCOFF_H
#define LLVM_MC_MCASMINFOCOFF_H

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCConfig.h"

namespace llvm {

class MCAsmInfoCOFF : public MCAsmInfo {
  virtual void anchor();

protected:
  LLVM_MC_ABI explicit MCAsmInfoCOFF();
};

class MCAsmInfoMicrosoft : public MCAsmInfoCOFF {
  LLVM_MC_ABI void anchor() override;

protected:
  LLVM_MC_ABI explicit MCAsmInfoMicrosoft();
};

class MCAsmInfoGNUCOFF : public MCAsmInfoCOFF {
  LLVM_MC_ABI void anchor() override;

protected:
  LLVM_MC_ABI explicit MCAsmInfoGNUCOFF();
};

} // end namespace llvm

#endif // LLVM_MC_MCASMINFOCOFF_H
