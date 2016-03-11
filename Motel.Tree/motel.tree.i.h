/*----------------------------------------------------------------------------
  Motel Tree
 
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

#ifndef MOTEL_TREE_I_H
#define MOTEL_TREE_I_H

/*----------------------------------------------------------------------------
  ValidateTree()
  ----------------------------------------------------------------------------
  Test every node within a tree to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) The tree handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Tree passed the validity check

  False - Tree did not pass the validity check due to:

          1. A node had a greater value located on a lesser branch
          2. A node had a lesser value located on a greater branch
          3. A node had branch weight that was incorrect
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelTree module. A
  validity check failure suggests a bug in the motelTree implementation.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateTree
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  ConstructTree()
  ----------------------------------------------------------------------------
  Construct an empty tree.
  ----------------------------------------------------------------------------
  Parameters:

  pTree               - (I/O) Pointer to recieve the tree handle
  pCompareKeyFunction - (I)   Pointer to the node key comparison function
  pTreeMaximumSize    - (I)   The maximum number of bytes used by the tree
  ----------------------------------------------------------------------------
  Return Values:

  True  - Tree was succesfully constructed

  False - Tree was not successfully constructed due to:

          1. The ComparisonKeyFunction was NULL
          2. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  This function requires the contents of the pTree handle to be initialized
  to NULL prior to calling this function because this function assumes that 
  a pointer with value represents an unfreed memory block and therefore
  overwritting this pointer with a new value would orphan the previously
  allocated memory block.

  The key comparison function is required. This function must adhere to the
  behavior of the standard C function strcmp(), mathematically returning
  (pKey1 - pKey2) where:

                  <  0   means pKey1 is less than pKey2
                  == 0   means pKey1 is equal to pKey2
                  >  0   means pKey1 is greater than pKey2

  The maximum memory paramter may be set to zero to allow the tree to grow to
  the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructTree
(
    motelTreeHandle * pTree,
    size_t pTreeMaximumSize,
    size_t pDataSize,
    size_t pKeySize,
    long (* pCompareKeyFunction)(const void * pKey1, const void * pKey2)
);

/*----------------------------------------------------------------------------
  DestructTree()
  ----------------------------------------------------------------------------
  Destruct a tree by removing all nodes.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I/O) Pointer to the tree handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Tree was succesfully destructed

  False - Tree was not successfully destructed due to:

          1. The pTree handle pointer was NULL
          2. The destruction of a node key object failed
          3. The destruction of a node data object failed
          4. The SafeFreeBlock() of a node failed
          5. The SafeFreeBlock() of the tree failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructTree
(
    motelTreeHandle * pTree
);

/*----------------------------------------------------------------------------
  SetTreeMember()
  ----------------------------------------------------------------------------
  Set the value of a published tree member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pTree   - (I) A tree handle
  pMember - (I) The member to retrieve
  pValue  - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
          2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.tree.t.h of the member variable to learn
  the memory and data type requirements of each.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetTreeMember
(
    motelTreeHandle pTree,
    motelTreeMember pMember,
    const void * pValue
);

/*----------------------------------------------------------------------------
  GetTreeMember()
  ----------------------------------------------------------------------------
  Get the value of a published tree member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pTree   - (I)   A tree handle
  pMember - (I)   The member variable to retrieve
  pValue  - (I/O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
          2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.tree.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided by
  the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetTreeMember
(
    motelTreeHandle pTree,
    motelTreeMember pMember,
    void * pValue
);

/*----------------------------------------------------------------------------
  InsertTreeNode()
  ----------------------------------------------------------------------------
  Insert a node into the tree at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  pData - (I) Pointer to the data object handle
  pKey  - (I) Pointer to the key object handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully inserted

  False - Node was not successfully inserted due to:

          1. The pTree handle was NULL.
          2. The pNode handle was NULL.
          3. The pKey handle was NULL.
  ----------------------------------------------------------------------------
  Operational Note:
  
  Self balancing is an intrinsic (single pass) effect of both the insert and
  delete operations with node rebalancing occuring according to the computed
  relative weight of the lesser and greater branches of each node considered
  during traversal of the tree for insertion or deletion. A maximum 3 to 1
  ratio of "lesser to greater" or "greater to lesser" branch weights is
  permitted before rebalancing.

  Usage Note:

  The MotelTree supports insertion of duplicate key values. Differentiation of
  duplicates within the tree is achieved by an instance counter that acts as a
  version number for duplicate keys. Calling applications that wish to handle
  duplicate key insertion as an error, a data overwrite or as ingorable are
  responsible for searching for duplicates prior to attempting an insert.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION InsertTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey
);

/*----------------------------------------------------------------------------
  SelectTreeNode()
  ----------------------------------------------------------------------------
  Select (find) a node within the tree - changing the cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Tree handle
  pKey      - (I) Pointer to the key object handle
  pInstance - (I) The instance of the key object in the tree
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully selected

  False - Node was not successfully selected due to:

          1. The pTree handle was NULL.
          2. The pKey handle was NULL.
  ----------------------------------------------------------------------------
  Usage Note:

  The MotelTree supports insertion of duplicate key values. Differentiation of
  duplicates within the tree is achieved by an instance counter that acts as a
  version number for duplicate keys. Calling applications that wish to handle
  duplicate key insertion as an error, a data overwrite or as ingorable are
  responsible for searching for duplicates prior to attempting an insert.

  Passing 0 as pInstance will cause the an aribtrary instance of the node to
  the returned (e.g. the one presently nearest the tree root).
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SelectTreeNode
(
    motelTreeHandle pTree,
    void * pKey,
    unsigned long pInstance
);

/*----------------------------------------------------------------------------
  FetchTreeNode()
  ----------------------------------------------------------------------------
  Fetch a node from the tree at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Tree handle
  pData     - (O) Pointer to the data object handle (may be NULL)
  pKey      - (O) Pointer to the key object handle (may be NULL)
  pInstance - (O) Pointer to the node instance (may be NULL)
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully fetched

  False - Node was not successfully fetched due to:

          1. The pTree handle is NULL.
          2. The tree is empty
          3. The tree cursor is NULL
  ----------------------------------------------------------------------------
  Usage Note:

  The MotelTree supports insertion of duplicate key values. Differentiation of
  duplicates within the tree is achieved by an instance counter that acts as a
  version number for duplicate keys.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION FetchTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
);

/*----------------------------------------------------------------------------
  UpdateTreeNode()
  ----------------------------------------------------------------------------
  Update a node in the tree at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  pData - (I) Pointer to the data object handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully updated

  False - Node was not successfully updated due to:

          1. The pTree handle was NULL.
          2. The pData handle was NULL.
          3. The tree cursor was NULL
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION UpdateTreeNode
(
    motelTreeHandle pTree,
    void * pData
);

/*----------------------------------------------------------------------------
  DeleteTreeNode()
  ----------------------------------------------------------------------------
  Delete a node from the tree at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree in which the node to delete exists
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully deleted

  False - Node was not successfully deleted due to:

          1. The pTree handle was NULL
          2. The tree is empty
          3. The tree cursor was NULL
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeleteTreeNode
(
    motelTreeHandle pTree
);

/*****************************************************************************
                           Tree traversal operations
  *****************************************************************************/

/*----------------------------------------------------------------------------
  PeekLeastTreeNode()
  ----------------------------------------------------------------------------
  Move the cursor to the node with the lowest key value and copy the key and
  data values from the node.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Handle of the tree
  pData     - (O) Pointer to the data object handle (may be NULL)
  pKey      - (O) Pointer to the key object handle (may be NULL)
  pInstance - (O) Pointer to the node instance (may be NULL)
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully peeked

  False - Node was not successfully peeked due to:

          1. The pTree handle was NULL
          2. The tree is empty
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekLeastTreeNode(pTree, pData)                                       \
        (SetTreeMember(pTree, motelTreeMember_Least, NULL) ?                  \
        (FetchTreeNode(pTree, pData) :                                        \
        FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekLeastTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
);

/*----------------------------------------------------------------------------
  PeekGreatestTreeNode()
  ----------------------------------------------------------------------------
  Move the cursor to the node with the highest key value and copy the key and
  data values from the node.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Handle of the tree
  pData     - (O) Pointer to the data object handle (may be NULL)
  pKey      - (O) Pointer to the key object handle (may be NULL)
  pInstance - (O) Pointer to the node instance (may be NULL)
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully peeked

  False - Node was not successfully peeked due to:

          1. The pTree handle was NULL
          2. The tree is empty
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekGreatestTreeNode(pTree, pData)                                    \
        (SetTreeMember(pTree, motelTreeMember_Greatest, NULL) ?               \
        (FetchTreeNode(pTree, pData) :                                        \
        FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekGreatestTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
);

/*----------------------------------------------------------------------------
  PeekLesserTreeNode()
  ----------------------------------------------------------------------------
  Move the cursor to the node with the next lower key value and copy the key
  and data values from the node.
  
  Calling this function when the cursor is not set will result in the Greatest
  node being returned; thus permitting wrap-around traversal of the values in
  the tree.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Handle of the tree
  pData     - (O) Pointer to the data object handle (may be NULL)
  pKey      - (O) Pointer to the key object handle (may be NULL)
  pInstance - (O) Pointer to the node instance (may be NULL)
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully peeked

  False - Node was not successfully peeked due to:

          1. The pTree handle was NULL
          2. The pData handle pointer was NULL
          3. The tree is empty
          4. There is no lower node
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekLesserTreeNode(pTree, pData)                                      \
        (SetTreeMember(pTree, motelTreeMember_Lesser, NULL) ?             \
        (FetchTreeNode(pTree, pData) :                                        \
        FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekLesserTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
);

/*----------------------------------------------------------------------------
  PeekGreaterTreeNode()
  ----------------------------------------------------------------------------
  Move the cursor to the node with the next higher key value and copy the
  key and data values from the node.

  Calling this function when the cursor is not set will result in the Least
  node being returned; thus permitting wrap-around traversal of the values in
  the tree.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Handle of the tree
  pData     - (O) Pointer to the data object handle (may be NULL)
  pKey      - (O) Pointer to the key object handle (may be NULL)
  pInstance - (O) Pointer to the node instance (may be NULL)
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully peeked

  False - Node was not successfully peeked due to:

          1. The pTree handle was NULL
          2. The pData handle pointer was NULL
          3. The tree is empty
          4. There is no higher node
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekGreaterTreeNode(pTree, pData)                                     \
        (SetTreeMember(pTree, motelTreeMember_Higher, NULL) ?             \
        (FetchTreeNode(pTree, pData) :                                        \
        FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekGreaterTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
);

#endif
