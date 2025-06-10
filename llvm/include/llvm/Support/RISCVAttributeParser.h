//===-- RISCVAttributeParser.h - RISCV Attribute Parser ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_RISCVATTRIBUTEPARSER_H
#define LLVM_SUPPORT_RISCVATTRIBUTEPARSER_H

#include "llvm/Support/Compiler.h"
#include "llvm/Support/ELFAttributeParser.h"
#include "llvm/Support/RISCVAttributes.h"

namespace llvm {
class RISCVAttributeParser : public ELFAttributeParser {
  struct DisplayHandler {
    RISCVAttrs::AttrType attribute;
    Error (RISCVAttributeParser::*routine)(unsigned);
  };
  LLVM_SUPPORT_ABI static const DisplayHandler displayRoutines[];

  LLVM_SUPPORT_ABI Error handler(uint64_t tag, bool &handled) override;

  LLVM_SUPPORT_ABI Error unalignedAccess(unsigned tag);
  LLVM_SUPPORT_ABI Error stackAlign(unsigned tag);
  LLVM_SUPPORT_ABI Error atomicAbi(unsigned tag);

public:
  RISCVAttributeParser(ScopedPrinter *sw)
      : ELFAttributeParser(sw, RISCVAttrs::getRISCVAttributeTags(), "riscv") {}
  RISCVAttributeParser()
      : ELFAttributeParser(RISCVAttrs::getRISCVAttributeTags(), "riscv") {}
};

} // namespace llvm

#endif
