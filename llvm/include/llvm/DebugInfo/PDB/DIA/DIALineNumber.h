//===- DIALineNumber.h - DIA implementation of IPDBLineNumber ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIALINENUMBER_H
#define LLVM_DEBUGINFO_PDB_DIA_DIALINENUMBER_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBLineNumber.h"

namespace llvm {
namespace pdb {
class DIALineNumber : public IPDBLineNumber {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIALineNumber(
      CComPtr<IDiaLineNumber> DiaLineNumber);

  LLVM_DEBUGINFOPDB_ABI uint32_t getLineNumber() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getLineNumberEnd() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getColumnNumber() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getColumnNumberEnd() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSourceFileId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCompilandId() const override;
  LLVM_DEBUGINFOPDB_ABI bool isStatement() const override;

private:
  CComPtr<IDiaLineNumber> LineNumber;
};
} // namespace pdb
} // namespace llvm
#endif
