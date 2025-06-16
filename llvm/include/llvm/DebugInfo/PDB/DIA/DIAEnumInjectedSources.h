//==- DIAEnumInjectedSources.h - DIA Injected Sources Enumerator -*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIAENUMINJECTEDSOURCES_H
#define LLVM_DEBUGINFO_PDB_DIA_DIAENUMINJECTEDSOURCES_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBEnumChildren.h"
#include "llvm/DebugInfo/PDB/IPDBInjectedSource.h"

namespace llvm {
namespace pdb {

class DIAEnumInjectedSources : public IPDBEnumChildren<IPDBInjectedSource> {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIAEnumInjectedSources(
      CComPtr<IDiaEnumInjectedSources> DiaEnumerator);

  LLVM_DEBUGINFOPDB_ABI uint32_t getChildCount() const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr
  getChildAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr getNext() override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  CComPtr<IDiaEnumInjectedSources> Enumerator;
};
} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_DIA_DIAENUMINJECTEDSOURCES_H
