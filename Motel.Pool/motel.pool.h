/*----------------------------------------------------------------------------
  Motel Pool
 
  private header file
  ----------------------------------------------------------------------------
  Copyright 2010-2011 John L. Hart IV. All rights reserved.
 
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

#ifndef MOTEL_POOL_H
#define MOTEL_POOL_H

#define MUTABILITY

#include <stdlib.h>

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.Memory/motel.memory.i.h"

#include "motel.pool.t.h"

/*----------------------------------------------------------------------------
  Public macros and data types
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

typedef void * motelMemoryObjectHandle;

typedef byte * segmentHandle;

typedef union freeSegment freeSegment;
typedef freeSegment * freeSegmentHandle;

union freeSegment
{
    segmentHandle segmentHandle;

    segmentHandle * segmentHandleHandle;
};

typedef freeSegment * freeSegmentHandle;

typedef struct pool pool;
typedef pool * poolIndexHandle;

struct pool
{
    size_t segmentSize;                       // size of the segments within this pool

    segmentHandle * freeSegmentsHandleHandle; // the free handle handle associated to this pool
};

typedef struct block block;
typedef block * blockIndexHandle;

struct block
{
    segmentHandle firstSegment;               // the first segment within the block

    segmentHandle lastSegment;                // the last segment within the block

    size_t blockSize;                         // bytes allocated to this block

    size_t segmentSize;                       // size of the segments within this block

    segmentHandle * freeSegmentsHandleHandle; // the free handle handle associated to this block

};

typedef struct motelMemory  motelMemory;
typedef motelMemory * motelMemoryHandle;

struct motelMemory
{
    size_t bytes;                      // bytes allocated to the memory manager
    size_t bytesUsed;                  // bytes used of those allocated to the memory manager

    poolIndexHandle poolIndexHandle;   // a dynamically allocated array of pool handles

    size_t poolCount;                  // sizes the pool handle array

    blockIndexHandle blockIndexHandle; // a dynamically allocated array of block handles

    size_t blockCount;                 // sizes the block handle array

    size_t blockSize;                  // bytes allocated per request to the system by the memory manager

    size_t segments;                   // number of segments allocated to the memory manager
    size_t segmentsUsed;               // number of segments used of those allocated to the memory manager
};

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.pool.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

boolean ExtendPoolIndex
(
    motelMemoryHandle pMemoryHandle,
    poolIndexHandle * pPoolIndexHandleHandle,
    size_t pSegmentSize
);

boolean ExtendBlockIndex
(
    motelMemoryHandle pMemoryHandle,
    poolIndexHandle pPoolIndexHandle
);

int _comparePools
(
    const poolIndexHandle pPoolIndexHandle_1,
    const poolIndexHandle pPoolIndexHandle_2
);

int _segmentInPool
(
    const size_t * pSegmentSize,
    const poolIndexHandle pPoolIndexHandle
);

int _compareBlocks
(
    const blockIndexHandle pBlockIndexHandle_1,
    const blockIndexHandle pBlockIndexHandle_2
);

int _segmentInBlock
(
    const segmentHandle pSegmentHandle,
    const blockIndexHandle pBlockIndexHandle
);

#endif