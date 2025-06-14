//===- MCXCOFFObjectStreamer.h - MCStreamer XCOFF Object File Interface ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCXCOFFSTREAMER_H
#define LLVM_MC_MCXCOFFSTREAMER_H

#include "llvm/MC/MCConfig.h"
#include "llvm/MC/MCObjectStreamer.h"

namespace llvm {
class XCOFFObjectWriter;

class MCXCOFFStreamer : public MCObjectStreamer {
public:
  LLVM_MC_ABI MCXCOFFStreamer(MCContext &Context,
                              std::unique_ptr<MCAsmBackend> MAB,
                              std::unique_ptr<MCObjectWriter> OW,
                              std::unique_ptr<MCCodeEmitter> Emitter);

  LLVM_MC_ABI XCOFFObjectWriter &getWriter();

  LLVM_MC_ABI bool emitSymbolAttribute(MCSymbol *Symbol,
                                       MCSymbolAttr Attribute) override;
  LLVM_MC_ABI void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                    Align ByteAlignment) override;
  LLVM_MC_ABI void emitZerofill(MCSection *Section, MCSymbol *Symbol = nullptr,
                                uint64_t Size = 0,
                                Align ByteAlignment = Align(1),
                                SMLoc Loc = SMLoc()) override;
  LLVM_MC_ABI void emitInstToData(const MCInst &Inst,
                                  const MCSubtargetInfo &) override;
  LLVM_MC_ABI void emitXCOFFLocalCommonSymbol(MCSymbol *LabelSym, uint64_t Size,
                                              MCSymbol *CsectSym,
                                              Align Alignment) override;
  LLVM_MC_ABI void
  emitXCOFFSymbolLinkageWithVisibility(MCSymbol *Symbol, MCSymbolAttr Linkage,
                                       MCSymbolAttr Visibility) override;
  LLVM_MC_ABI void emitXCOFFRefDirective(const MCSymbol *Symbol) override;
  LLVM_MC_ABI void emitXCOFFRenameDirective(const MCSymbol *Name,
                                            StringRef Rename) override;
  LLVM_MC_ABI void emitXCOFFExceptDirective(const MCSymbol *Symbol,
                                            const MCSymbol *Trap, unsigned Lang,
                                            unsigned Reason,
                                            unsigned FunctionSize,
                                            bool hasDebug) override;
  LLVM_MC_ABI void emitXCOFFCInfoSym(StringRef Name,
                                     StringRef Metadata) override;
};

} // end namespace llvm

#endif // LLVM_MC_MCXCOFFSTREAMER_H
