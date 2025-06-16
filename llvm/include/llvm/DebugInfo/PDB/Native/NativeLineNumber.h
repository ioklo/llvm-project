//===- NativeLineNumber.h - Native line number implementation ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVELINENUMBER_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVELINENUMBER_H

#include "llvm/DebugInfo/CodeView/Line.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBLineNumber.h"

namespace llvm {
namespace pdb {

class NativeSession;

class NativeLineNumber : public IPDBLineNumber {
public:
  LLVM_DEBUGINFOPDB_ABI explicit NativeLineNumber(
      const NativeSession &Session, const codeview::LineInfo Line,
      uint32_t ColumnNumber, uint32_t Length, uint32_t Section, uint32_t Offset,
      uint32_t SrcFileId, uint32_t CompilandId);

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
  const NativeSession &Session;
  const codeview::LineInfo Line;
  uint32_t ColumnNumber;
  uint32_t Section;
  uint32_t Offset;
  uint32_t Length;
  uint32_t SrcFileId;
  uint32_t CompilandId;
};
} // namespace pdb
} // namespace llvm
#endif
