//===- IRObjectFile.h - LLVM IR object file implementation ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the IRObjectFile template class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_OBJECT_IROBJECTFILE_H
#define LLVM_OBJECT_IROBJECTFILE_H

#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/Object/IRSymtab.h"
#include "llvm/Object/ModuleSymbolTable.h"
#include "llvm/Object/ObjectConfig.h"
#include "llvm/Object/SymbolicFile.h"

namespace llvm {
class Module;

namespace object {
class ObjectFile;

class IRObjectFile : public SymbolicFile {
  std::vector<std::unique_ptr<Module>> Mods;
  ModuleSymbolTable SymTab;
  LLVM_OBJECT_ABI IRObjectFile(MemoryBufferRef Object,
                               std::vector<std::unique_ptr<Module>> Mods);

public:
  LLVM_OBJECT_ABI ~IRObjectFile() override;
  LLVM_OBJECT_ABI void moveSymbolNext(DataRefImpl &Symb) const override;
  LLVM_OBJECT_ABI Error printSymbolName(raw_ostream &OS,
                                        DataRefImpl Symb) const override;
  LLVM_OBJECT_ABI Expected<uint32_t>
  getSymbolFlags(DataRefImpl Symb) const override;
  LLVM_OBJECT_ABI basic_symbol_iterator symbol_begin() const override;
  LLVM_OBJECT_ABI basic_symbol_iterator symbol_end() const override;
  bool is64Bit() const override {
    return Triple(getTargetTriple()).isArch64Bit();
  }
  LLVM_OBJECT_ABI StringRef getTargetTriple() const;

  static bool classof(const Binary *v) { return v->isIR(); }

  using module_iterator =
      pointee_iterator<std::vector<std::unique_ptr<Module>>::const_iterator,
                       const Module>;

  module_iterator module_begin() const { return module_iterator(Mods.begin()); }
  module_iterator module_end() const { return module_iterator(Mods.end()); }

  iterator_range<module_iterator> modules() const {
    return make_range(module_begin(), module_end());
  }

  /// Finds and returns bitcode embedded in the given object file, or an
  /// error code if not found.
  LLVM_OBJECT_ABI static Expected<MemoryBufferRef>
  findBitcodeInObject(const ObjectFile &Obj);

  /// Finds and returns bitcode in the given memory buffer (which may
  /// be either a bitcode file or a native object file with embedded bitcode),
  /// or an error code if not found.
  LLVM_OBJECT_ABI static Expected<MemoryBufferRef>
  findBitcodeInMemBuffer(MemoryBufferRef Object);

  LLVM_OBJECT_ABI static Expected<std::unique_ptr<IRObjectFile>>
  create(MemoryBufferRef Object, LLVMContext &Context);
};

/// The contents of a bitcode file and its irsymtab. Any underlying data
/// for the irsymtab are owned by Symtab and Strtab.
struct IRSymtabFile {
  std::vector<BitcodeModule> Mods;
  SmallVector<char, 0> Symtab, Strtab;
  irsymtab::Reader TheReader;
};

/// Reads a bitcode file, creating its irsymtab if necessary.
LLVM_OBJECT_ABI Expected<IRSymtabFile> readIRSymtab(MemoryBufferRef MBRef);

} // namespace object

} // namespace llvm

#endif
