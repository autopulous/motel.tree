/*----------------------------------------------------------------------------
  Motel Pool

  application programmer's types (APT) header file 
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

#ifndef MOTEL_POOL_T_H
#define MOTEL_POOL_T_H

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public Pool members
*/

typedef enum motelPoolMember
{
    motelPoolMember_Bytes,        /*!< Data type:   (size_t *)
                                       Description: Memory currently allocated to the memory manager */

    motelPoolMember_BytesUsed,    /*!< Data type:   (size_t *)
                                       Description: Memory currently used of those allocated to the memory manager */

    motelPoolMember_BlockSize,    /*!< Data type:   (size_t *)
                                       Description: The amount of memory allocated as a unit by the memory manager */

    motelPoolMember_PoolCount,    /*!< Data type:   (size_t *)
                                       Description: The number of pools created by the memory manager */

    motelPoolMember_BlockCount,   /*!< Data type:   (size_t *)
                                       Description: The number of blocks allocated by the memory manager */

    motelPoolMember_Segments,     /*!< Data type:   (size_t *)
                                       Description: Blocks segments currently allocated to the memory manager */

    motelPoolMember_SegmentsUsed, /*!< Data type:   (size_t *)
                                       Description: Block segments currently used of those allocated to the memory manager */

    motelPoolMember_
} motelPoolMember;

#ifndef MOTEL_POOL_H

/*----------------------------------------------------------------------------
  Abstracted MotelPool object handle data types
  ----------------------------------------------------------------------------*/

typedef void * motelMemoryHandle;

typedef void * motelMemoryObjectHandle;

#endif

#endif
