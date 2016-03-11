/*----------------------------------------------------------------------------
  Motel Memory
 
  application programmer's interface (API) header file
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

#ifndef MOTEL_MEMORY_I_H
#define MOTEL_MEMORY_I_H

/*----------------------------------------------------------------------------
  Includes required to compile the contents of this source file
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"

/*----------------------------------------------------------------------------
  SizeOfObject()
  ----------------------------------------------------------------------------
  Determine the number of bytes to store an object.
  ----------------------------------------------------------------------------
  Parameters:

  tObject - (I) Object type
  pSize   - (O) Object size
  ----------------------------------------------------------------------------*/

#define SizeOfObject(tObject, pSize) {struct _z_{tObject _a_; tObject _b_;}; pSize = offsetof(struct _z_, _b_) - offsetof(struct _z_, _a_);}

/*----------------------------------------------------------------------------
  SafeMallocBlock()
  ----------------------------------------------------------------------------
  Allocates a block of memory.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer     - (I/O) The address of a memory pointer to hold the result of
                      the Malloc()
  pSize       - (I)   The number of bytes to allocate.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully allocated

  False - Memory was not successfully allocated due to one of the following:

          1. The buffer pointer pointer was NULL.
          2. The buffer pointer pointed to be the buffer pointer pointer was
             not initialized to NULL.
          3. Zero or fewer bytes were requested to be allocated.
          4. Alloc() failed.
  ----------------------------------------------------------------------------
  Notes:

  This function requires the contents of the pBuffer pointer to be initialized
  to NULL prior to calling this function because this function assumes that 
  a pointer with value represents an unfreed memory block and therefore
  overwriting this pointer with a new value would orphan the previously
  allocated memory block.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeMallocBlock
(
    void ** pBuffer,
    size_t  pSize
);

/*----------------------------------------------------------------------------
  SafeCallocBlock()
  ----------------------------------------------------------------------------
  Allocates and initializes a block of memory to zeros.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer     - (I/O) The address of a memory pointer to hold the result of
                      the Calloc()
  pSize       - (I)   The number of bytes to allocate.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully allocated

  False - Memory was not successfully allocated due to one of the following:

          1. The buffer pointer pointer was NULL.
          2. The buffer pointer pointed to be the buffer pointer pointer was
             not initialized to NULL.
          3. Zero or fewer bytes were requested to be allocated.
          4. Alloc() failed.
  ----------------------------------------------------------------------------
  Notes:

  This function requires the contents of the pBuffer pointer to be initialized
  to NULL prior to calling this function because this function assumes that 
  a pointer with value represents an unfreed memory block and therefore
  overwriting this pointer with a new value would orphan the previously
  allocated memory block.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeCallocBlock
(
    void ** pBuffer,
    size_t  pSize
);

/*----------------------------------------------------------------------------
  SafeReallocBlock()
  ----------------------------------------------------------------------------
  Reallocates a block of memory leaving the current contents unchanged.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer     - (I/O) The address of a memory pointer to hold the result of
                      the Realloc()
  pSize       - (I)   The number of bytes to allocate.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully allocated

  False - Memory was not successfully allocated due to one of the following:

          1. The buffer pointer pointer was NULL.
          2. Zero or fewer bytes were requested to be allocated.
          3. Realloc() failed.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeReallocBlock
(
    void ** pBuffer,
    size_t  pSize
);

/*----------------------------------------------------------------------------
  SafeFreeBlock()
  ----------------------------------------------------------------------------
  Deallocates a block of memory, setting the memory pointer to NULL.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer     - (I/O) The address of a memory pointer to the memory block
                      being deallocated by Free().
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully deallocated

  False - Memory was not successfully deallocated due to one of the following:

          1. The buffer pointer pointer was NULL.
          2. The buffer pointer pointed to be the buffer pointer pointer was
             not initialized to NULL.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeFreeBlock
(
    void ** pBuffer
);

/*----------------------------------------------------------------------------
  ManagedMallocBlock()
  ----------------------------------------------------------------------------
  Allocates a block of memory and then adds the size value to a memory
  management variable. This function is designed for use with a cache or other
  data structure where the total number of bytes in use needs to be managed.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer    - (I/O) The address of a memory pointer to hold the result of
                     the SafeMallocBlock()
  pSize      - (I)   The number of bytes to allocate.
  pAllocated - (I/O) A pointer to a memory management variable.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully allocated

  False - Memory was not successfully allocated due to one of the following:

          1. The memory management variable pointer was NULL.
          2. Zero or fewer bytes were requested to be allocated.
          3. SafeAlloc() failed.
  ----------------------------------------------------------------------------
  Notes:

  Because this function uses SafeMallocBlock() it requires the contents of the
  pBuffer pointer to be initialized to NULL prior to calling this function
  because the SafeAlloc function assumes that a pointer with value
  represents an unfreed memory block and therefore overwriting this pointer
  with a new value would orphan the previously allocated memory block.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedMallocBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
);

/*----------------------------------------------------------------------------
  ManagedCallocBlock()
  ----------------------------------------------------------------------------
  Allocates and initializes a block of memory to zeros and then adds the size
  value to a memory management variable. This function is designed for use
  with a cache or other data structure where the total number of bytes in use
  needs to be managed.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer    - (I/O) The address of a memory pointer to hold the result of
                     the SafeCallocBlock()
  pSize      - (I)   The number of bytes to allocate.
  pAllocated - (I/O) A pointer to a memory management variable.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully allocated

  False - Memory was not successfully allocated due to one of the following:

          1. The memory management variable pointer was NULL.
          2. Zero or fewer bytes were requested to be allocated.
          3. SafeAlloc() failed.
  ----------------------------------------------------------------------------
  Notes:

  Because this function uses SafeCallocBlock() it requires the contents of the
  pBuffer pointer to be initialized to NULL prior to calling this function
  because the SafeAlloc function assumes that a pointer with value
  represents an unfreed memory block and therefore overwriting this pointer
  with a new value would orphan the previously allocated memory block.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedCallocBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
);

/*----------------------------------------------------------------------------
  ManagedFreeBlock()
  ----------------------------------------------------------------------------
  Deallocates a block of memory, setting the memory pointer to NULL and then
  subtracts the passed size value from the memory management variable. This
  function is designed for use with a cache or other data structure where the
  total number of bytes in use needs to be managed.
  ----------------------------------------------------------------------------
  Parameters:
  
  pBuffer    - (I/O) The address of a memory pointer to the memory block
                     being deallocated by SafeFreeBlock().
  pSize      - (I)   The number of bytes being deallocate.
  pAllocated - (I/O) A pointer to a memory management variable.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory was successfully deallocated

  False - Memory was not successfully deallocated due to one of the following:

          1. The memory management variable pointer was NULL.
          2. Zero or fewer bytes were requested to be deallocated.
          3. SafeFreeBlock() failed.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedFreeBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
);

/*----------------------------------------------------------------------------
  CopyBlock()
  ----------------------------------------------------------------------------
  Copies a block of memory.
  ----------------------------------------------------------------------------
  Parameters:
  
  pDestination     - (I) pointer to the block being copied into.
  pDestinationSize - (I) The size of the Destination block.
  pSource          - (I) pointer to the block being copied from.
  pSourceSize      - (I) The size of the Source block.
  pBytesToCopy     - (I) The number of bytes requested to be copied.
  ----------------------------------------------------------------------------
  Return Values:

  True  - Block was successfully copied

  False - Block was not successfully copied due to one of the following:

          1. The pointer to the destination block was NULL.
          2. The pointer to the source block was NULL.
  ----------------------------------------------------------------------------
  Notes: Safely copies overlapping blocks as follows.

  Case 1 (Source greater than Destination, Bytes to copy = 17 (or greater)):
  --------------------------------------------------------------------------

  ABCDEFGHIJKLMOPQRSTUVWXYZ
  ^       ^
  To      From

  IJKLMOPQRSTUVWXYZSTUVWXYZ

  Case 2 (Destination greater than Source, Bytes to copy = 17 (or greater)):
  --------------------------------------------------------------------------

  ABCDEFGHIJKLMOPQRSTUVWXYZ
  ^       ^
  From    To

  ABCDEFGHABCDEFGHIJKLMOPQR

  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyBlock
(
    void * pDestination,
    size_t pDestinationSize,
    void * pSource,
    size_t pSourceSize,
    size_t pBytesToCopy
);

/*----------------------------------------------------------------------------
  CompareBlocks()
  ----------------------------------------------------------------------------
  Memory comparison
  ----------------------------------------------------------------------------
  Parameters:

  pBlock1          - (I) Pointer to memory block
  pBytesToCompare1 - (I) Number of bytes in the block to compare
  pBlock2          - (I) Pointer to memory block
  pBytesToCompare1 - (I) Number of bytes in the block to compare

  ----------------------------------------------------------------------------
  Notes: Nominally the pBytesToCompare paramters reflect the size of their
         respective blocks, but if a comparison of fewer bytes is desired
         these parameters may be set lower
  ----------------------------------------------------------------------------
  Returns:

  lem (LESS_THAN, EQUAL_TO, MORE_THAN) value
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareBlocks
(
   const byte * pBlock1,
   size_t pBytesToCompare1,
   const byte * pBlock2,
   size_t pBytesToCompare2
);

#endif
