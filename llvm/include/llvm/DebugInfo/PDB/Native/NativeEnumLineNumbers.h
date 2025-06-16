//==- NativeEnumLineNumbers.h - Native Line Number Enumerator ------------*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMLINENUMBERS_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMLINENUMBERS_H

#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBEnumChildren.h"
#include "llvm/DebugInfo/PDB/IPDBLineNumber.h"
#include "llvm/DebugInfo/PDB/Native/NativeLineNumber.h"
#include <vector>

namespace llvm {
namespace pdb {

class NativeEnumLineNumbers : public IPDBEnumChildren<IPDBLineNumber> {
public:
  LLVM_DEBUGINFOPDB_ABI explicit NativeEnumLineNumbers(
      std::vector<NativeLineNumber> LineNums);

  LLVM_DEBUGINFOPDB_ABI uint32_t getChildCount() const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr
  getChildAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr getNext() override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  std::vector<NativeLineNumber> Lines;
  uint32_t Index;
};
} // namespace pdb
} // namespace llvm

#endif
