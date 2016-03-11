/*----------------------------------------------------------------------------
  Motel Pool
 
  library implementation file
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

#include "motel.pool.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.pool.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidatePool
(
    motelMemoryHandle pMemoryHandle
)
{
    segmentHandle * lFreeSegment;

    poolIndexHandle lPoolIndexHandle;
    blockIndexHandle lBlockIndexHandle;

    size_t lPoolIndex_1, lPoolIndex_2;
    size_t lBlockIndex_1, lBlockIndex_2;

    size_t lCount;

    size_t lSize;

    /*
    ** there is no memory manager
    */

    if (NULL == pMemoryHandle)
    {
        return (TRUE);
    }

    /*
    ** dereference the pool and block index handles
    */

    lPoolIndexHandle = pMemoryHandle->poolIndexHandle;
    lBlockIndexHandle = pMemoryHandle->blockIndexHandle;

    /*
    ** make sure the pools are unique
    */

    lPoolIndex_1 = pMemoryHandle->poolCount;

    while (0 < lPoolIndex_1)
    {
        lPoolIndex_1--;

        lPoolIndex_2 = lPoolIndex_1;

        while (0 < lPoolIndex_2)
        {
            lPoolIndex_2--;

            if (lPoolIndexHandle[lPoolIndex_1].freeSegmentsHandleHandle == lPoolIndexHandle[lPoolIndex_2].freeSegmentsHandleHandle)
            {
                return (FALSE);
            }

            if (lPoolIndexHandle[lPoolIndex_1].segmentSize == lPoolIndexHandle[lPoolIndex_2].segmentSize)
            {
                return (FALSE);
            }
        }
    }

    /*
    ** make sure the blocks do not overlap
    */

    lBlockIndex_1 = pMemoryHandle->blockCount;

    while (0 < lBlockIndex_1)
    {
        lBlockIndex_1--;

        lBlockIndex_2 = lBlockIndex_1;

        while (0 < lBlockIndex_2)
        {
            lBlockIndex_2--;

            if (lBlockIndexHandle[lBlockIndex_1].firstSegment >= lBlockIndexHandle[lBlockIndex_2].firstSegment &&
                lBlockIndexHandle[lBlockIndex_1].firstSegment <= lBlockIndexHandle[lBlockIndex_2].lastSegment)
            {
                return (FALSE);
            }

            if (lBlockIndexHandle[lBlockIndex_1].lastSegment >= lBlockIndexHandle[lBlockIndex_2].firstSegment &&
                lBlockIndexHandle[lBlockIndex_1].lastSegment <= lBlockIndexHandle[lBlockIndex_2].lastSegment)
            {
                return (FALSE);
            }
        }
    }

    /*
    ** make sure the pool and block free segment handle handles match
    */

    lCount = 0;

    lPoolIndex_1 = pMemoryHandle->poolCount;

    while (0 < lPoolIndex_1)
    {
        lPoolIndex_1--;

        lBlockIndex_1 = pMemoryHandle->blockCount;

        while (0 < lBlockIndex_1)
        {
            lBlockIndex_1--;

            if (lPoolIndexHandle[lPoolIndex_1].freeSegmentsHandleHandle == lBlockIndexHandle[lBlockIndex_1].freeSegmentsHandleHandle)
            {
                lCount++;
            }
        }
    }

    if (pMemoryHandle->blockCount != lCount)
    {
        return (FALSE);
    }

    /*
    ** check the consistency of the free segment lists
    */

    lCount = 0;

    lPoolIndex_1 = pMemoryHandle->poolCount;

    while (0 < lPoolIndex_1)
    {
        lPoolIndex_1--;

        lFreeSegment = pMemoryHandle->poolIndexHandle[lPoolIndex_1].freeSegmentsHandleHandle;

        while (NULL != lFreeSegment)
        {
            lCount++;

            /*
            ** circular reference test
            */

            if (lFreeSegment == (segmentHandle *) * lFreeSegment)
            {
                return (FALSE);
            }

            lFreeSegment = (segmentHandle *) * lFreeSegment;
        }
         
        /*
        ** don't count the traversal to the NULL at the end of the free segment list
        */

        lCount--;

        /*
        ** cannot be more segments than were allocated within the blocks
        */

        if (pMemoryHandle->segments < lCount)
        {
            return (FALSE);
        }
    }

    /*
    ** account for the memory used by the blocks
    */

    lSize = 0;

    lBlockIndex_1 = pMemoryHandle->blockCount;

    while (0 < lBlockIndex_1)
    {
        lBlockIndex_1--;

        lSize += lBlockIndexHandle[lBlockIndex_1].blockSize;
    }

    /*
    ** account for the memory used for the block list
    */

    lSize += sizeof(block) * pMemoryHandle->blockCount;

    /*
    ** account for the memory used for the pool list
    */

    lSize += sizeof(pool) * pMemoryHandle->poolCount;

    /*
    ** account for the memory used by the free segment list root handles
    */

    lSize += sizeof(segmentHandle *) * pMemoryHandle->poolCount;

    /*
    ** account for the memory used by the memory manager
    */

    lSize += sizeof(motelMemory);

    /*
    ** memory accounting is not correct
    */
    
    if (pMemoryHandle->bytes != lSize)
    {
        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructPool
(
    motelMemoryHandle * pMemoryHandleHandle,
    size_t pAllocationSize
)
{
    /*
    ** allocate the memory manager
    */

    if (!SafeMallocBlock((void **) pMemoryHandleHandle, sizeof(motelMemory)))
    {
        return (FALSE);
    }

    /*
    ** initialize memory manager
    */

    (* pMemoryHandleHandle)->blockSize = pAllocationSize < sizeof(freeSegmentHandle) ? sizeof(freeSegmentHandle) : pAllocationSize;

    (* pMemoryHandleHandle)->bytes = sizeof(motelMemory);
    (* pMemoryHandleHandle)->bytesUsed = sizeof(motelMemory);

    (* pMemoryHandleHandle)->poolIndexHandle = (poolIndexHandle) NULL;
    (* pMemoryHandleHandle)->poolCount = 0;

    (* pMemoryHandleHandle)->blockIndexHandle = (blockIndexHandle) NULL;
    (* pMemoryHandleHandle)->blockCount = 0;

    (* pMemoryHandleHandle)->segments = 0;
    (* pMemoryHandleHandle)->segmentsUsed = 0;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructPool
(
    motelMemoryHandle * pMemoryHandleHandle
)
{
    motelMemoryHandle lMemoryHandle;

    blockIndexHandle lBlockIndexHandle;

    size_t lBlockCount;

    poolIndexHandle lPoolIndexHandle;

    size_t lPoolCount;

    /*
    ** there is no memory manager
    */

    if (NULL == pMemoryHandleHandle || NULL == * pMemoryHandleHandle)
    {
        return (FALSE);
    }

    /*
    ** dereference the memory handle handle
    */

    lMemoryHandle = * pMemoryHandleHandle;

    lBlockIndexHandle = lMemoryHandle->blockIndexHandle;

    lBlockCount = lMemoryHandle->blockCount;

    lPoolIndexHandle = lMemoryHandle->poolIndexHandle;

    lPoolCount = lMemoryHandle->poolCount;

    /*
    ** free the blocks
    */

    while (0 < lBlockCount)
    {
        lBlockCount--;

        if (!ManagedFreeBlock((void **) &lBlockIndexHandle[lBlockCount].firstSegment, lBlockIndexHandle[lBlockCount].blockSize, &lMemoryHandle->bytes))
        {
            return (FALSE);
        }

        lMemoryHandle->segments -= lBlockIndexHandle[lBlockCount].blockSize / lBlockIndexHandle[lBlockCount].segmentSize;
    }

    if (0 != lMemoryHandle->segments)
    {
        return (FALSE);
    }

    lMemoryHandle->segmentsUsed = 0;

    /*
    ** free the block list
    */

    if (NULL != lMemoryHandle->blockIndexHandle)
    {
        if (!ManagedFreeBlock((void **) &lMemoryHandle->blockIndexHandle, sizeof(block) * lMemoryHandle->blockCount, &lMemoryHandle->bytes))
        {
            return (FALSE);
        }
    }

    lMemoryHandle->blockCount = 0;

    /*  
    ** free the free segment list root handles
    */

    while (0 < lPoolCount)
    {
        lPoolCount--;

        if (!ManagedFreeBlock((void **) &lPoolIndexHandle[lPoolCount].freeSegmentsHandleHandle, sizeof(segmentHandle *), &lMemoryHandle->bytes))
        {
            return (FALSE);
        }
    }

    /*
    ** free the pool list
    */

    if (NULL != lMemoryHandle->poolIndexHandle)
    {
        if (!ManagedFreeBlock((void **) &lMemoryHandle->poolIndexHandle, sizeof(pool) * lMemoryHandle->poolCount, &lMemoryHandle->bytes))
        {
            return (FALSE);
        }
    }

    lMemoryHandle->poolCount = 0;

    /*
    ** everything except the memory manager control structure should have been freed
    */

    if (sizeof(motelMemory) != lMemoryHandle->bytes)
    {
        return (FALSE);
    }

    /*
    ** free the memory manager control structure
    */

    if (!SafeFreeBlock((void **) pMemoryHandleHandle))
    {
        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetPoolMember
(
    motelMemoryHandle pMemoryHandle,
    motelPoolMember pMember,
    const void * pValue
)
{
    /*
    ** set member values
    */

    switch (pMember)
    {
        case motelPoolMember_BlockSize:

            pMemoryHandle->blockSize = * (size_t *) pValue;

            return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetPoolMember
(
    motelMemoryHandle pMemoryHandle,
    motelPoolMember pMember,
    void * pValue
)
{
    /*
    ** no return parameter
    */

    if (NULL == pValue)
    {
        return (FALSE);
    }

    /*
    ** get member
    */

    switch (pMember)
    {
        case motelPoolMember_Bytes:

            * (size_t *) pValue = pMemoryHandle->bytes;

            return (TRUE);

        case motelPoolMember_BytesUsed:

            * (size_t *) pValue = pMemoryHandle->bytesUsed;

            return (TRUE);

        case motelPoolMember_PoolCount:

            * (size_t *) pValue = pMemoryHandle->poolCount;

            return (TRUE);

        case motelPoolMember_BlockCount:

            * (size_t *) pValue = pMemoryHandle->blockCount;

            return (TRUE);

        case motelPoolMember_Segments:

            * (size_t *) pValue = pMemoryHandle->segments;

            return (TRUE);

        case motelPoolMember_SegmentsUsed:

            * (size_t *) pValue = pMemoryHandle->segmentsUsed;

            return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AllocatePoolMemory
(
    motelMemoryHandle pMemoryHandle,
    motelMemoryObjectHandle * pObjectHandleHandle,
    size_t pObjectSize
)
{
    poolIndexHandle lPoolIndexHandle;

    size_t lSegmentSize;

    if (NULL == pObjectHandleHandle || NULL != * pObjectHandleHandle)
    {
        return (FALSE);
    }
    
    if (0 == pObjectSize)
    {
        return (FALSE);
    }

    /*
    ** segments within a pool must at least be large enough to hold the free
    ** segment list objects
    */

    lSegmentSize = sizeof(freeSegment) > pObjectSize ? sizeof(freeSegment) : pObjectSize;

    /*
    ** select or create a pool for this segment size
    */

    lPoolIndexHandle = bsearch((void *) &lSegmentSize, (const void *) pMemoryHandle->poolIndexHandle, (size_t) pMemoryHandle->poolCount, sizeof(pool), (int (*)(const void *, const void *)) _segmentInPool);

    if (NULL == lPoolIndexHandle)
    {
        if (!ExtendPoolIndex(pMemoryHandle, &lPoolIndexHandle, lSegmentSize))
        {
            return (FALSE);
        }
    }

    /*
    ** select or create a block from which to allocate a segment for the object
    */

    if (NULL == lPoolIndexHandle->freeSegmentsHandleHandle || NULL == * lPoolIndexHandle->freeSegmentsHandleHandle)
    {
        if (!ExtendBlockIndex(pMemoryHandle, lPoolIndexHandle))
        {
            return (FALSE);
        }
    }
    
    /*
    ** assign a segment to store the object
    */

    * pObjectHandleHandle = * lPoolIndexHandle->freeSegmentsHandleHandle;

    /*
    ** update the free segment list
    */

    * lPoolIndexHandle->freeSegmentsHandleHandle = ((freeSegmentHandle) * (lPoolIndexHandle->freeSegmentsHandleHandle))->segmentHandle;

    /*
    ** update utilization statistics
    */

    pMemoryHandle->segmentsUsed++;

    pMemoryHandle->bytesUsed += lSegmentSize;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeallocatePoolMemory
(
    motelMemoryHandle pMemoryHandle,
    motelMemoryObjectHandle * pObjectHandleHandle
)
{
    blockIndexHandle lBlockIndexHandle;

    segmentHandle lSegmentHandle;

    if (NULL == pObjectHandleHandle || NULL == * pObjectHandleHandle)
    {
        return (FALSE);
    }

    lSegmentHandle = * pObjectHandleHandle;

    lBlockIndexHandle = bsearch(lSegmentHandle, pMemoryHandle->blockIndexHandle, pMemoryHandle->blockCount, sizeof(block), (int (*)(const void *, const void *)) _segmentInBlock);

    if (NULL == lBlockIndexHandle)
    {
        return (FALSE);
    }

    /*
    ** make the segment point to the previous top of the free segment list
    */

    ** (segmentHandle **) pObjectHandleHandle = * lBlockIndexHandle->freeSegmentsHandleHandle;

    /*
    ** make the free segment list point to the segment of the object being deallocated
    */

    * lBlockIndexHandle->freeSegmentsHandleHandle = * (segmentHandle *) pObjectHandleHandle;

    /*
    ** disconnect the pointer to the segment
    */

    * pObjectHandleHandle = (motelMemoryObjectHandle) NULL;

    /*
    ** update utilization statistics
    */

    pMemoryHandle->segmentsUsed--;

    pMemoryHandle->bytesUsed -= lBlockIndexHandle->segmentSize;

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

boolean ExtendPoolIndex
(
    motelMemoryHandle pMemoryHandle,
    poolIndexHandle * pPoolIndexHandleHandle,
    size_t pSegmentSize
)
{
    poolIndexHandle lPoolIndexHandle;

    /*
    ** allocate or grow the list of pools
    */

    if (NULL == pMemoryHandle->poolIndexHandle)
    {
        if (!SafeMallocBlock((void **) &pMemoryHandle->poolIndexHandle, sizeof(pool)))
        {
            return (FALSE);
        }
    }
    else 
    {
        if (!SafeReallocBlock((void **) &pMemoryHandle->poolIndexHandle, (pMemoryHandle->poolCount + 1) * sizeof(pool)))
        {
            return (FALSE);
        }
    }

    pMemoryHandle->bytes += sizeof(pool);
    pMemoryHandle->bytesUsed += sizeof(pool);

    /*
    ** create a local reference to the allocated pool handle
    */

    lPoolIndexHandle = &pMemoryHandle->poolIndexHandle[pMemoryHandle->poolCount];
    
    /*
    ** allocate a free segment handle handle for the pool
    */

    lPoolIndexHandle->freeSegmentsHandleHandle = (segmentHandle *) NULL;

    if (!ManagedMallocBlock((void **) &lPoolIndexHandle->freeSegmentsHandleHandle, sizeof(segmentHandle *), &pMemoryHandle->bytes))
    {
        return (FALSE);
    }

    /*
    ** a block will need to be allocated to build the free segment list
    */

    * lPoolIndexHandle->freeSegmentsHandleHandle = (segmentHandle) NULL;

    /*
    ** initialize the pool handle
    */

    lPoolIndexHandle->segmentSize = pSegmentSize;
    
    /*
    ** increment the pool count
    */

    pMemoryHandle->poolCount++;

    /*
    ** order the pools by segment size so these can be quickly found by bsearch()
    */

    qsort((void *) pMemoryHandle->poolIndexHandle, (size_t) pMemoryHandle->poolCount, sizeof(pool), (int (*)(const void *, const void *)) _comparePools);

    /*
    ** return the allocated pool handle
    */

    * pPoolIndexHandleHandle = lPoolIndexHandle;

    return (TRUE);
}

boolean ExtendBlockIndex
(
    motelMemoryHandle pMemoryHandle,
    poolIndexHandle pPoolIndexHandle
)
{
    size_t lSegmentSize = pPoolIndexHandle->segmentSize;
    size_t lSegments;

    blockIndexHandle lBlockIndexHandle;

    size_t lSegmentIndex;

    freeSegment lFreeSegment;

    /*
    ** allocate or grow the list of blocks
    */

    if (NULL == pMemoryHandle->blockIndexHandle)
    {
        if (!SafeMallocBlock((void **) &pMemoryHandle->blockIndexHandle, sizeof(block)))
        {
            return (FALSE);
        }
    }
    else 
    {
        if (!SafeReallocBlock((void **) &pMemoryHandle->blockIndexHandle, (pMemoryHandle->blockCount + 1) * sizeof(block)))
        {
            return (FALSE);
        }
    }

    pMemoryHandle->bytes += sizeof(block);
    pMemoryHandle->bytesUsed += sizeof(block);

    /*
    ** simplify the reference to the new block list entry
    */

    lBlockIndexHandle = &pMemoryHandle->blockIndexHandle[pMemoryHandle->blockCount];

    /*
    ** calculate the block allocation size as a multiple of the object size
    */

    lSegments = pMemoryHandle->blockSize / lSegmentSize;

    lBlockIndexHandle->blockSize = lSegments * lSegmentSize;

    /*
    ** allocate a new block
    */

    lBlockIndexHandle->firstSegment = (segmentHandle) NULL;

    if (!ManagedMallocBlock((void **) &lBlockIndexHandle->firstSegment, lBlockIndexHandle->blockSize, &pMemoryHandle->bytes))
    {
        return (FALSE);
    }

    lBlockIndexHandle->lastSegment = lBlockIndexHandle->firstSegment + (lBlockIndexHandle->blockSize - lSegmentSize);

    pMemoryHandle->segments += lSegments;

    /*
    ** associate the pool with the new block
    */

    lBlockIndexHandle->segmentSize = pPoolIndexHandle->segmentSize;

    lBlockIndexHandle->freeSegmentsHandleHandle = pPoolIndexHandle->freeSegmentsHandleHandle;

    /*
    ** construct the free segment list
    */

    * lBlockIndexHandle->freeSegmentsHandleHandle = lBlockIndexHandle->firstSegment;

    lFreeSegment.segmentHandle = lBlockIndexHandle->firstSegment;

    for (lSegmentIndex = lSegments; 1 < lSegmentIndex; lSegmentIndex--)
    {
        /*
        ** assign the address of the next free segment in the free list
        */

        * lFreeSegment.segmentHandleHandle = (segmentHandle)(lFreeSegment.segmentHandle + lSegmentSize);

        /*
        ** bump the segment handle handle to the next segment
        */

        lFreeSegment.segmentHandle += lSegmentSize;
    }

    /*
    ** terminate the free segment list
    */

    * lFreeSegment.segmentHandleHandle = (segmentHandle) NULL;
    
    /*
    ** increment the block count
    */

    pMemoryHandle->blockCount++;

    /*
    ** order the blocks by address range so these can be quickly found by bsearch()
    */

    qsort((void *) pMemoryHandle->blockIndexHandle, (size_t) pMemoryHandle->blockCount, sizeof(block), (int (*)(const void *, const void *)) _compareBlocks);

    return (TRUE);
}

int _comparePools
(
    const poolIndexHandle pPoolIndexHandle_1,
    const poolIndexHandle pPoolIndexHandle_2
)
{
    return ((int) pPoolIndexHandle_1->segmentSize - (int) pPoolIndexHandle_2->segmentSize);
}

int _segmentInPool
(
    const size_t * pSegmentSize,
    const poolIndexHandle pPoolIndexHandle
)
{
    return ((int) * pSegmentSize - (int) pPoolIndexHandle->segmentSize);
}

int _compareBlocks
(
    const blockIndexHandle pBlockIndexHandle_1,
    const blockIndexHandle pBlockIndexHandle_2
)
{
    if (pBlockIndexHandle_1->firstSegment < pBlockIndexHandle_2->firstSegment)
    {
        return (-1);
    }

    if (pBlockIndexHandle_1->firstSegment > pBlockIndexHandle_2->firstSegment)
    {
        return (1);
    }

    return (0);
}

int _segmentInBlock
(
    const segmentHandle pSegmentHandle,
    const blockIndexHandle pBlockIndexHandle
)
{
    if (pSegmentHandle < pBlockIndexHandle->firstSegment)
    {
        return (-1);
    }

    if (pSegmentHandle > pBlockIndexHandle->lastSegment)
    {
        return (1);
    }

    return (0);
}
