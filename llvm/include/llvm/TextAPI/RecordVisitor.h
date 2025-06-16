//===- llvm/TextAPI/RecordSlice.h - TAPI RecordSlice ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// Defines the TAPI Record Visitor.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_TEXTAPI_RECORDVISITOR_H
#define LLVM_TEXTAPI_RECORDVISITOR_H

#include "llvm/TextAPI/Record.h"
#include "llvm/TextAPI/SymbolSet.h"
#include "llvm/TextAPI/TextAPIConfig.h"

namespace llvm {
namespace MachO {

/// Base class for any usage of traversing over collected Records.
class RecordVisitor {
public:
  LLVM_TEXTAPI_ABI virtual ~RecordVisitor();

  virtual void visitGlobal(const GlobalRecord &) = 0;
  LLVM_TEXTAPI_ABI virtual void visitObjCInterface(const ObjCInterfaceRecord &);
  LLVM_TEXTAPI_ABI virtual void visitObjCCategory(const ObjCCategoryRecord &);
};

/// Specialized RecordVisitor for collecting exported symbols
/// and undefined symbols if RecordSlice being visited represents a
/// flat-namespaced library.
class SymbolConverter : public RecordVisitor {
public:
  SymbolConverter(SymbolSet *Symbols, const Target &T,
                  const bool RecordUndefs = false)
      : Symbols(Symbols), Targ(T), RecordUndefs(RecordUndefs) {}
  LLVM_TEXTAPI_ABI void visitGlobal(const GlobalRecord &) override;
  LLVM_TEXTAPI_ABI void
  visitObjCInterface(const ObjCInterfaceRecord &) override;
  LLVM_TEXTAPI_ABI void visitObjCCategory(const ObjCCategoryRecord &) override;

private:
  void addIVars(const ArrayRef<ObjCIVarRecord *>, StringRef ContainerName);
  SymbolSet *Symbols;
  const Target Targ;
  const bool RecordUndefs;
};

} // end namespace MachO.
} // end namespace llvm.

#endif // LLVM_TEXTAPI_RECORDVISITOR_H
