/*----------------------------------------------------------------------------
  Motel Memory
 
  library implementation file
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

#include "motel.memory.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.memory.c - Copyright 2010-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeMallocBlock
(
    void ** pBuffer,
    size_t  pSize
)
{
    if (0 < pSize && NULL != pBuffer && NULL == * pBuffer)
    {
        * pBuffer = Malloc(pSize);

        if (NULL != * pBuffer) 
        {
            return (TRUE);
        }
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeCallocBlock
(
    void ** pBuffer,
    size_t  pSize
)
{
    if (0 < pSize && NULL != pBuffer && NULL == * pBuffer)
    {
        * pBuffer = Calloc(pSize);

        if (NULL != * pBuffer) 
        {
            return (TRUE);
        }
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeReallocBlock
(
    void ** pBuffer,
    size_t  pSize
)
{
    if (0 < pSize && NULL != pBuffer)
    {
        * pBuffer = Realloc(* pBuffer, pSize);

        if (NULL != * pBuffer) 
        {
            return (TRUE);
        }
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SafeFreeBlock
(
    void ** pBuffer
)
{
    if (NULL != pBuffer && NULL != * pBuffer)
    {
        Free(* pBuffer);

        * pBuffer = (void **) NULL;

        return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedMallocBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
)
{
    if (NULL != pAllocated && 0 < pSize && SafeMallocBlock((void **) pBuffer, pSize))
    {
        * pAllocated += pSize;

        return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedCallocBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
)
{
    if (NULL != pAllocated && 0 < pSize && SafeCallocBlock((void **) pBuffer, pSize))
    {
        * pAllocated += pSize;

        return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ManagedFreeBlock
(
    void **  pBuffer,
    size_t   pSize,
    size_t * pAllocated
)
{
    if (NULL != pAllocated && 0 < pSize && SafeFreeBlock((void **) pBuffer))
    {
        * pAllocated -= pSize;

        return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyBlock
(
    void * pDestination,
    size_t pDestinationSize,
    void * pSource,
    size_t pSourceSize,
    size_t pBytesToCopy
)
{

// parameter validation

{
    if (NULL == pDestination || NULL == pSource)
    {
        return (FALSE);
    }
}

// function body

{
    /*
    ** prevent source buffer out of bounds access and destination buffer overrun
    */

    pBytesToCopy = (pSourceSize < pBytesToCopy ? pSourceSize : pBytesToCopy);
    pBytesToCopy = (pDestinationSize < pBytesToCopy ? pDestinationSize : pBytesToCopy);

    if (0 != pBytesToCopy)
    {
        byte * lDestination = (byte *) pDestination;
        byte * lSource = (byte *) pSource;

        if (pSource > pDestination)
        {
            /*
            ** copy bytes (going forward)
            */

            loop
            {
                *lDestination = *lSource;

                escape(1 == pBytesToCopy);

                pBytesToCopy--;

                lDestination++, lSource++;
            }
        }
        else
        {
            /*
            ** copy bytes (going backward) - in case the buffers overlap
            */

            lDestination += pBytesToCopy;
            lSource += pBytesToCopy;

            loop
            {
                lDestination--, lSource--;

                *lDestination = *lSource;

                escape(1 == pBytesToCopy);

                pBytesToCopy--;
            }
        }
    }

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareBlocks
(
   const byte * pBlock1,
   size_t pBytesToCompare1,
   const byte * pBlock2,
   size_t pBytesToCompare2
)
{
lem lResult;
size_t lBytesToCompare;


// function initialization

{
    if (NULL == pBlock1)
    {
        pBytesToCompare1 = 0;
    }

    if (NULL == pBlock2)
    {
        pBytesToCompare2 = 0;
    }

    if (pBytesToCompare1 < pBytesToCompare2)
    {
        lBytesToCompare = pBytesToCompare1;
        lResult = LESS_THAN;
    }
    else if (pBytesToCompare1 == pBytesToCompare2)
    {
        lBytesToCompare = pBytesToCompare1;
        lResult = EQUAL_TO;
    }
    else
    {
        lBytesToCompare = pBytesToCompare2;
        lResult = MORE_THAN;
    }
}

// function body

{
    loop
    {
        escape (0 == lBytesToCompare);

        lResult = (lem) (* pBlock1 - * pBlock2);

        escape (EQUAL_TO != lResult);

        pBlock1++;
        pBlock2++;

        lBytesToCompare--;
    }

    return (EQUAL_TO > lResult ? LESS_THAN : EQUAL_TO == lResult ? EQUAL_TO : MORE_THAN);
}
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/
