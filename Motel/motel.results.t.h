/*----------------------------------------------------------------------------
  Motel Result
  
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

#ifndef MOTEL_RESULT_T_H
#define MOTEL_RESULT_T_H

#include <stdlib.h>
#include <assert.h>

/* debug only error testing */

#define ASSERT(booleanExpression)                \
{                                                \
    assert(!booleanExpression);                  \
}

/* release and debug error testing */

#define CONFIRM(booleanExpression, failureCode)  \
{                                                \
    if (!(booleanExpression)) exit(failureCode); \
}

/*
** motel function/method result/exception codes
*/

typedef enum motelResult motelResult;
typedef motelResult * motelResultHandle;

enum motelResult
{
    motelResult_OK = 0,
    motelResult_Deprecated,
    motelResult_Unimplemented,
    motelResult_Undefined,

    motelResult_Incompatible,

    motelResult_NullPointer,
    motelResult_OutOfBounds,
    motelResult_NodeError,

    motelResult_MaximumSize,
    motelResult_MemoryAllocation,
    motelResult_MemoryDeallocation,
    motelResult_MemoryLeak,

    motelResult_Opening,
    motelResult_Reading,
    motelResult_Writing,
    motelResult_Closing,

    motelResult_File,
    motelResult_FileEmpty,
    
    motelResult_Cursor,
    motelResult_StreamEnd,

    motelResult_Socket,

    motelResult_NoSource,

    motelResult_NotFound,

    motelResult_NoData,
    motelResult_NoNode,

    motelResult_NodeDestruction,

    motelResult_NodeCount,

    motelResult_Structure,

    motelResult_UnknownMember,
    motelResult_InvalidMember,
    motelResult_RequiredMember,
    motelResult_DependentMember,

    motelResult_UndefinedDelimiter,
    motelResult_Uninitialized,
    motelResult_Corrupted,

    motelResult_ConfiguringEnvironment,
    motelResult_ConfiguringConnection,
    motelResult_ConfiguringStatement,

    motelResult_InvalidValue,
    motelResult_InvalidState,

    motelResult_
};

#endif
