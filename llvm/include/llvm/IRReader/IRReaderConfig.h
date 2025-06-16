//===- BinaryFormatConfig.h - Compiler abstraction support ---*- C++ -*----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_IRREADER_IRREADERCONFIG_H
#define LLVM_IRREADER_IRREADERCONFIG_H

#include "llvm/Config/llvm-config.h"

#ifndef LLVM_ABI_GENERATING_ANNOTATIONS
// Marker to add to classes or functions in public headers that should not have
// export macros added to them by the clang tool
  #define LLVM_ABI_NOT_EXPORTED
  #if defined(LLVM_BUILD_LLVM_DYLIB) || defined(LLVM_BUILD_SHARED_LIBS) ||       \
      defined(LLVM_ENABLE_PLUGINS)
// Some libraries like those for tablegen are linked in to tools that used
// in the build so can't depend on the llvm shared library. If export macros
// were left enabled when building these we would get duplicate or
// missing symbol linker errors on windows.
    #if defined(LLVM_BUILD_STATIC)
      #define LLVM_IRREADER_ABI
      #define LLVM_IRREADER_TEMPLATE_ABI
      #define LLVM_IRREADER_EXPORT_TEMPLATE
      #define LLVM_IRREADER_ABI_EXPORT
    #elif defined(_WIN32) && !defined(__MINGW32__)
      #if defined(LLVM_IRREADER_EXPORTS)
        #define LLVM_IRREADER_ABI __declspec(dllexport)
        #define LLVM_IRREADER_TEMPLATE_ABI
        #define LLVM_IRREADER_EXPORT_TEMPLATE __declspec(dllexport)
      #else
        #define LLVM_IRREADER_ABI __declspec(dllimport)
        #define LLVM_IRREADER_TEMPLATE_ABI __declspec(dllimport)
        #define LLVM_IRREADER_EXPORT_TEMPLATE
      #endif
      #define LLVM_IRREADER_ABI_EXPORT __declspec(dllexport)
    #elif defined(__ELF__) || defined(__MINGW32__) || defined(_AIX) ||             \
          defined(__MVS__)
      #define LLVM_IRREADER_ABI LLVM_ATTRIBUTE_VISIBILITY_DEFAULT
      #define LLVM_IRREADER_TEMPLATE_ABI LLVM_ATTRIBUTE_VISIBILITY_DEFAULT
      #define LLVM_IRREADER_EXPORT_TEMPLATE
      #define LLVM_IRREADER_ABI_EXPORT LLVM_ATTRIBUTE_VISIBILITY_DEFAULT
    #elif defined(__MACH__) || defined(__WASM__) || defined(__EMSCRIPTEN__)
      #define LLVM_IRREADER_ABI LLVM_ATTRIBUTE_VISIBILITY_DEFAULT
      #define LLVM_IRREADER_TEMPLATE_ABI
      #define LLVM_IRREADER_EXPORT_TEMPLATE
      #define LLVM_IRREADER_ABI_EXPORT LLVM_ATTRIBUTE_VISIBILITY_DEFAULT
    #endif
  #else
    #define LLVM_IRREADER_ABI
    #define LLVM_IRREADER_TEMPLATE_ABI
    #define LLVM_IRREADER_EXPORT_TEMPLATE
    #define LLVM_IRREADER_ABI_EXPORT
  #endif
  #define LLVM_IRREADER_C_ABI LLVM_IRREADER_ABI
#endif

#endif // LLVM_IRREADER_IRREADERCONFIG_H