/*----------------------------------------------------------------------------
  Motel Pool
 
  application programmer's interface (API) header file
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

#ifndef MOTEL_POOL_I_H
#define MOTEL_POOL_I_H

#include <stddef.h>

/*----------------------------------------------------------------------------
  ValidatePool()
  ----------------------------------------------------------------------------
  Test every object within a pool to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:
  
  pMemoryHandle - (I) Handle to the motel memory manager to validate
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory pool passed the validity check

  False - Memory pool did not pass the validity check due to:

          1. Internal error
          2. The free segment list was overwriten by the calling application.
             This is caused when a memory object's bounds are exceeded (e.g.
             strcpy() buffer overrun).
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelPool module.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidatePool
(
    motelMemoryHandle pMemoryHandle
);

/*----------------------------------------------------------------------------
  ConstructPool()
  ----------------------------------------------------------------------------
  Construct the memory manager.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle   - (O) Handle to the motel memory manager
  pAllocationSize - (I) Block size (in bytes) to be allocated as a unit
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory manger was succesfully constructed

  False - Memory manger was not successfully constructed due to:

          1. The allocation of the memory manager failed
          2. The memory manger already exists
  ----------------------------------------------------------------------------
  Notes:

  The maximum memory paramter may be set to zero to allow the pool to grow to
  the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructPool
(
    motelMemoryHandle * pMemoryHandle,
    size_t pAllocationSize
);

/*----------------------------------------------------------------------------
  DestructPool()
  ----------------------------------------------------------------------------
  Destruct the memory manager and release all memory associated with it.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle - (I) Handle to the motel memory manager
  ----------------------------------------------------------------------------
  Return Values:

  True  - Memory pool was succesfully destructed

  False - Memory pool was not successfully destructed due to:

          1. The deallocation of a pool or block failed
          2. The deallocation of the memory pool failed
          3. The memory pool does not exist
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructPool
(
    motelMemoryHandle * pMemoryHandle
);

/*----------------------------------------------------------------------------
  SetPoolMember()
  ----------------------------------------------------------------------------
  Set the value of a published memory control member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle - (I) The memory manager handle
  pMember       - (I) The member to retrieve
  pValue        - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. The pMemory handle was invalid
          2. pValue was NULL
          3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.pool.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided
  by the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetPoolMember
(
    motelMemoryHandle pMemoryHandle,
    motelPoolMember pMember,
    const void * pValue
);

/*----------------------------------------------------------------------------
  GetPoolMember()
  ----------------------------------------------------------------------------
  Get the value of a published Memory member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle - (I) The memory manager handle
  pMember       - (I) The member variable to retrieve
  pValue        - (O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. The pMemory handle was invalid
          2. pValue was NULL
          3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.pool.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided by
  the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetPoolMember
(
    motelMemoryHandle pMemoryHandle,
    motelPoolMember pMember,
    void * pValue
);

/*----------------------------------------------------------------------------
  AllocatePoolMemory()
  ----------------------------------------------------------------------------
  Get object memory from the memory pool.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle       - (I) The memory manager handle
  pObjectHandleHandle - (O) Object handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully gotten from the memory pool

  False - Object was not successfully gotten from the memory pool due to:

          1. The pObjectHandleHandle handle was NULL
          2. The pObjectHandleHandle handle contents were not NULL
          3. System memory could not be allocated
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AllocatePoolMemory
(
    motelMemoryHandle pMemoryHandle,
    motelMemoryObjectHandle * pObjectHandleHandle,
    size_t pObjectSize
);

/*----------------------------------------------------------------------------
  DeallocatePoolMemory()
  ----------------------------------------------------------------------------
  Return object memory to the memory pool.
  ----------------------------------------------------------------------------
  Parameters:

  pMemoryHandle       - (I) The memory manager handle
  pObjectHandleHandle - (I) Object handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully returned to the memory pool

  False - Object was not successfully returned to the memory pool due to:

          1. The pObjectHandleHandle handle was NULL
          1. The pObjectHandleHandle handle contents were NULL
          2. The object doesn't belong to the memory pool
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeallocatePoolMemory
(
    motelMemoryHandle pMemoryHandle,
    motelMemoryObjectHandle * pObjectHandleHandle
);

#endif