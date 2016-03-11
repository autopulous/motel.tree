/*----------------------------------------------------------------------------
  Motel Compilation
  
  application programmer's types (APT) header file
  ----------------------------------------------------------------------------
  Copyright 2010-2012 John L. Hart IV. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain all copyright notices,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce all copyright
     notices, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY John L. Hart IV "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
  NO EVENT SHALL John L. Hart IV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.

  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of John L Hart IV.
  ----------------------------------------------------------------------------*/

#ifndef MOTEL_COMPILATION_T_H
#define MOTEL_COMPILATION_T_H

/*----------------------------------------------------------------------------
  Platform specific storage class and calling convention
  ----------------------------------------------------------------------------*/

#if defined _WIN32 || defined _WIN64

#include <windows.h>

#if defined _M_IX86 || _M_X64
#define MOTEL_LITTLE_ENDIAN
#else
#error need to defeine the endian of this architecture
#endif

/* Place EXPORT_STORAGE_CLASS before the type of a public/exported function or data object. */

#define EXPORT_STORAGE_CLASS __declspec(dllexport)
#define IMPORT_STORAGE_CLASS __declspec(dllimport)

/* Place CALLING_CONVENTION before the name of a public/exported function. */

#define CALLING_CONVENTION __stdcall

#else

/* Place EXPORT_STORAGE_CLASS before the type of a public function. */

#define EXPORT_STORAGE_CLASS

#define EXPORT_STORAGE_CLASS
#define IMPORT_STORAGE_CLASS

/* Place CALLING_CONVENTION before the name of a public function. */

#define CALLING_CONVENTION

#endif

/*----------------------------------------------------------------------------
  Compiler specific macros
  ----------------------------------------------------------------------------*/

#if defined __GNUC__

#define UNUSED __attribute__ ((unused))

#else

#define UNUSED

#endif

#endif
