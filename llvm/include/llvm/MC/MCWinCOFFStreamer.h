//===- MCWinCOFFStreamer.h - COFF Object File Interface ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCWINCOFFSTREAMER_H
#define LLVM_MC_MCWINCOFFSTREAMER_H

#include "llvm/MC/MCConfig.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCObjectStreamer.h"

namespace llvm {

class MCAsmBackend;
class MCContext;
class MCCodeEmitter;
class MCInst;
class MCSection;
class MCSubtargetInfo;
class MCSymbol;
class StringRef;
class WinCOFFObjectWriter;
class raw_pwrite_stream;

class MCWinCOFFStreamer : public MCObjectStreamer {
public:
  LLVM_MC_ABI MCWinCOFFStreamer(MCContext &Context,
                                std::unique_ptr<MCAsmBackend> MAB,
                                std::unique_ptr<MCCodeEmitter> CE,
                                std::unique_ptr<MCObjectWriter> OW);

  /// state management
  void reset() override {
    CurSymbol = nullptr;
    MCObjectStreamer::reset();
  }

  LLVM_MC_ABI WinCOFFObjectWriter &getWriter();

  /// \name MCStreamer interface
  /// \{

  LLVM_MC_ABI void initSections(bool NoExecStack,
                                const MCSubtargetInfo &STI) override;
  LLVM_MC_ABI void changeSection(MCSection *Section,
                                 uint32_t Subsection = 0) override;
  LLVM_MC_ABI void emitLabel(MCSymbol *Symbol, SMLoc Loc = SMLoc()) override;
  LLVM_MC_ABI void emitAssemblerFlag(MCAssemblerFlag Flag) override;
  LLVM_MC_ABI void emitThumbFunc(MCSymbol *Func) override;
  LLVM_MC_ABI bool emitSymbolAttribute(MCSymbol *Symbol,
                                       MCSymbolAttr Attribute) override;
  LLVM_MC_ABI void emitSymbolDesc(MCSymbol *Symbol,
                                  unsigned DescValue) override;
  LLVM_MC_ABI void beginCOFFSymbolDef(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCOFFSymbolStorageClass(int StorageClass) override;
  LLVM_MC_ABI void emitCOFFSymbolType(int Type) override;
  LLVM_MC_ABI void endCOFFSymbolDef() override;
  LLVM_MC_ABI void emitCOFFSafeSEH(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCOFFSymbolIndex(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCOFFSectionIndex(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCOFFSecRel32(MCSymbol const *Symbol,
                                    uint64_t Offset) override;
  LLVM_MC_ABI void emitCOFFImgRel32(MCSymbol const *Symbol,
                                    int64_t Offset) override;
  LLVM_MC_ABI void emitCOFFSecNumber(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCOFFSecOffset(MCSymbol const *Symbol) override;
  LLVM_MC_ABI void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                    Align ByteAlignment) override;
  LLVM_MC_ABI void emitLocalCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                         Align ByteAlignment) override;
  LLVM_MC_ABI void emitWeakReference(MCSymbol *Alias,
                                     const MCSymbol *Symbol) override;
  LLVM_MC_ABI void emitZerofill(MCSection *Section, MCSymbol *Symbol,
                                uint64_t Size, Align ByteAlignment,
                                SMLoc Loc = SMLoc()) override;
  LLVM_MC_ABI void emitTBSSSymbol(MCSection *Section, MCSymbol *Symbol,
                                  uint64_t Size, Align ByteAlignment) override;
  LLVM_MC_ABI void emitIdent(StringRef IdentString) override;
  LLVM_MC_ABI void emitWinEHHandlerData(SMLoc Loc) override;
  LLVM_MC_ABI void emitCGProfileEntry(const MCSymbolRefExpr *From,
                                      const MCSymbolRefExpr *To,
                                      uint64_t Count) override;
  LLVM_MC_ABI void finishImpl() override;

  /// \}

protected:
  const MCSymbol *CurSymbol;

  LLVM_MC_ABI void emitInstToData(const MCInst &Inst,
                                  const MCSubtargetInfo &STI) override;

  LLVM_MC_ABI void finalizeCGProfileEntry(const MCSymbolRefExpr *&S);

private:
  LLVM_MC_ABI void Error(const Twine &Msg) const;
};

} // end namespace llvm

#endif // LLVM_MC_MCWINCOFFSTREAMER_H
