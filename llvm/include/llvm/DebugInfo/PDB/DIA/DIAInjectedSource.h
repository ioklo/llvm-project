//===- DIAInjectedSource.h - DIA impl for IPDBInjectedSource ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIAINJECTEDSOURCE_H
#define LLVM_DEBUGINFO_PDB_DIA_DIAINJECTEDSOURCE_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBInjectedSource.h"

namespace llvm {
namespace pdb {
class DIASession;

class DIAInjectedSource : public IPDBInjectedSource {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIAInjectedSource(
      CComPtr<IDiaInjectedSource> DiaSourceFile);

  LLVM_DEBUGINFOPDB_ABI uint32_t getCrc32() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getCodeByteSize() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getFileName() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getObjectFileName() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getVirtualFileName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCompression() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getCode() const override;

private:
  CComPtr<IDiaInjectedSource> SourceFile;
};
} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_DIA_DIAINJECTEDSOURCE_H
