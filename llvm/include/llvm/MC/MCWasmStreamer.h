//===- MCWasmStreamer.h - MCStreamer Wasm Object File Interface -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCWASMSTREAMER_H
#define LLVM_MC_MCWASMSTREAMER_H

#include "MCAsmBackend.h"
#include "MCCodeEmitter.h"
#include "llvm/MC/MCConfig.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCExpr;
class MCInst;

class MCWasmStreamer : public MCObjectStreamer {
public:
  MCWasmStreamer(MCContext &Context, std::unique_ptr<MCAsmBackend> TAB,
                 std::unique_ptr<MCObjectWriter> OW,
                 std::unique_ptr<MCCodeEmitter> Emitter)
      : MCObjectStreamer(Context, std::move(TAB), std::move(OW),
                         std::move(Emitter)),
        SeenIdent(false) {}

  LLVM_MC_ABI ~MCWasmStreamer() override;

  /// state management
  void reset() override {
    SeenIdent = false;
    MCObjectStreamer::reset();
  }

  /// \name MCStreamer Interface
  /// @{

  LLVM_MC_ABI void changeSection(MCSection *Section,
                                 uint32_t Subsection) override;
  LLVM_MC_ABI void emitLabel(MCSymbol *Symbol, SMLoc Loc = SMLoc()) override;
  LLVM_MC_ABI void emitLabelAtPos(MCSymbol *Symbol, SMLoc Loc,
                                  MCDataFragment &F, uint64_t Offset) override;
  LLVM_MC_ABI void emitAssemblerFlag(MCAssemblerFlag Flag) override;
  LLVM_MC_ABI void emitThumbFunc(MCSymbol *Func) override;
  LLVM_MC_ABI void emitWeakReference(MCSymbol *Alias,
                                     const MCSymbol *Symbol) override;
  LLVM_MC_ABI bool emitSymbolAttribute(MCSymbol *Symbol,
                                       MCSymbolAttr Attribute) override;
  LLVM_MC_ABI void emitSymbolDesc(MCSymbol *Symbol,
                                  unsigned DescValue) override;
  LLVM_MC_ABI void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                    Align ByteAlignment) override;

  LLVM_MC_ABI void emitELFSize(MCSymbol *Symbol, const MCExpr *Value) override;

  LLVM_MC_ABI void emitLocalCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                         Align ByteAlignment) override;

  LLVM_MC_ABI void emitZerofill(MCSection *Section, MCSymbol *Symbol = nullptr,
                                uint64_t Size = 0,
                                Align ByteAlignment = Align(1),
                                SMLoc Loc = SMLoc()) override;
  LLVM_MC_ABI void emitTBSSSymbol(MCSection *Section, MCSymbol *Symbol,
                                  uint64_t Size,
                                  Align ByteAlignment = Align(1)) override;

  LLVM_MC_ABI void emitIdent(StringRef IdentString) override;

  LLVM_MC_ABI void finishImpl() override;

private:
  LLVM_MC_ABI void emitInstToFragment(const MCInst &Inst,
                                      const MCSubtargetInfo &) override;
  LLVM_MC_ABI void emitInstToData(const MCInst &Inst,
                                  const MCSubtargetInfo &) override;

  LLVM_MC_ABI void fixSymbolsInTLSFixups(const MCExpr *expr);

  bool SeenIdent;
};

} // end namespace llvm

#endif
