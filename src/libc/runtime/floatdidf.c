//===-- floatdidf.c - Implement __floatdidf -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __floatdidf for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include "int_lib.h"

// Returns: convert a to a double, rounding toward even.

// Assumption: double is a IEEE 64 bit floating point type
//             di_int is a 64 bit integral type

// seee eeee eeee mmmm mmmm mmmm mmmm mmmm | mmmm mmmm mmmm mmmm mmmm mmmm mmmm
// mmmm


// Support for systems that don't have hardware floating-point; there are no
// flags to set, and we don't want to code-gen to an unknown soft-float
// implementation.

#define SRC_I64
#define DST_DOUBLE
#include "int_to_fp_impl.inc"

COMPILER_RT_ABI double __floatdidf(di_int a) { return __floatXiYf__(a); }

#if defined(__ARM_EABI__)
#if defined(COMPILER_RT_ARMHF_TARGET)
AEABI_RTABI double __aeabi_l2d(di_int a) { return __floatdidf(a); }
#else
COMPILER_RT_ALIAS(__floatdidf, __aeabi_l2d)
#endif
#endif

#if defined(__MINGW32__) && defined(__arm__)
COMPILER_RT_ALIAS(__floatdidf, __i64tod)
#endif
