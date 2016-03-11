/*----------------------------------------------------------------------------
  Motel Tree

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

#ifndef MOTEL_TREE_H
#define MOTEL_TREE_H

#define MUTABILITY

#include <memory.h>

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.Memory/motel.memory.i.h"

/*----------------------------------------------------------------------------
  Public macros and data types
  ----------------------------------------------------------------------------*/

#include "motel.tree.t.h"

/*----------------------------------------------------------------------------
  Private macros
  ----------------------------------------------------------------------------*/

#define REBALANCE_THRESHOLD 3

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.tree.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  ConstructNode()
  ----------------------------------------------------------------------------
  Construct a tree node.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I)   Tree handle
  pKey  - (I/O) Pointer to the key object handle
  pData - (I/O) Pointer to the data object handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully constructed

  False - Node was not successfully constructed due to:

          1. The tree handle was invalid
          2. The pointer to the key object handle was invalid
          3. The pointer to the data object handle was invalid
          4. ManagedMallocBlock() failed
          5. Would make the tree exceed its maximum number of bytes
  ----------------------------------------------------------------------------*/

static boolean ConstructNode
(
    motelTreeHandle pTree,
    void * pKey,
    void * pData,
    motelTreeNodeHandle * pNode
);

/*----------------------------------------------------------------------------
  DestructNode()
  ----------------------------------------------------------------------------
  Destruct the current node.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree in which the node exists
  ----------------------------------------------------------------------------
  Return Values:

  True  - Node was succesfully destructed

  False - Node was not successfully destructed due to:

          1. The pTree handle was NULL
          2. No current node was set
          3. The node data destruction failed
          4. The node key destruction failed
          5. The node destruction failed
  ----------------------------------------------------------------------------*/

static boolean DestructNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetEqualNode()
  ----------------------------------------------------------------------------
  Get a node that matches the provided key object from the tree.
  ----------------------------------------------------------------------------
  Parameters:

  pTree     - (I) Tree handle
  pKey      - (I) The key object to use to find a node in the tree
  pInstance - (I) The instance of the key object in the tree
  ----------------------------------------------------------------------------
  Return Values:

  NULL - No node was found that matched the value of the key object

  motelTreeNodeHandle - A node from the tree that matched the value of the
                        provided key object
  ----------------------------------------------------------------------------
  Note:

  For nodes with duplicated key values the eariliest entered instance of the
  node will be returned from the tree.
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetEqualNode
(
    motelTreeHandle pTree,
    const void * pKey,
    unsigned long pInstance
);

/*----------------------------------------------------------------------------
  NodeCompare()
  ----------------------------------------------------------------------------
  Compare the key values of a pair of nodes
  ----------------------------------------------------------------------------
  Parameters:

  pTree  - (I) The tree handle
  pNode1 - (I) The first node to compare
  pNode2 - (I) The second node to compare
  ----------------------------------------------------------------------------
  Return Values:

  < 0   means pNode1->key is less than pNode2->key
  > 0   means pNode1->key is greater than pNode2->key
  
  ----------------------------------------------------------------------------
  Notes:

  This function uses the key comparison function established by the calling
  system when the tree that the node resides in was constructed. By definition
  this function must adhere to the behavior of the standard C function
  strcmp(), mathematically returning (pNode1->key - pNode2->key).

  In the case where node keys are duplicated within the tree (e.g. logically 
  pNode1->key == pNode2->key) the node instance values are compared to
  distinguish the relative value of the nodes.
  ----------------------------------------------------------------------------*/

static long NodeCompare
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pNode1,
    motelTreeNodeHandle pNode2
);

/*----------------------------------------------------------------------------
  GetLeastNode()
  ----------------------------------------------------------------------------
  Get the node with the lowest key value from the tree without altering
  the node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  ----------------------------------------------------------------------------
  Return Values:

  NULL - There is no tree or there are no nodes are in the tree

  motelTreeNodeHandle - The lowest key valued node in the tree
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetLeastNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetGreatestNode()
  ----------------------------------------------------------------------------
  Get the node with the highest key value from the tree without altering
  the node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  ----------------------------------------------------------------------------
  Return Values:

  NULL - There is no tree or there are no nodes are in the tree

  motelTreeNodeHandle - The highest key valued node in the tree
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetGreatestNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetLesserNode()
  ----------------------------------------------------------------------------
  Get the node with the next lower key value in the tree without altering
  the node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  ----------------------------------------------------------------------------
  Return Values:

  NULL - There is no tree or there is no lower node in the tree

  motelTreeNodeHandle - The next lower key valued node in the tree
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetLesserNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetGreaterNode()
  ----------------------------------------------------------------------------
  Get the node with the next higher key value in the tree without altering
  the node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  ----------------------------------------------------------------------------
  Return Values:

  NULL - There is no tree or there is no higher node in the tree

  motelTreeNodeHandle - The next higher key valued node in the tree
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetGreaterNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetRootNode()
  ----------------------------------------------------------------------------
  Get the root node of the tree without altering the node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Tree handle
  ----------------------------------------------------------------------------
  Return Values:

  NULL - There is no tree or there is no root node in the tree

  motelTreeNodeHandle - The root node of the tree
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetRootNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetParentNode()
  ----------------------------------------------------------------------------
  Get the physical parent node of the passed node without altering the node
  cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree in which the node exists
  ----------------------------------------------------------------------------
  Return Values:

  NULL - The current node is NULL or it is the root node of the tree

  motelTreeNodeHandle - The parent node of the node passed
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetParentNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetLesserChildNode()
  ----------------------------------------------------------------------------
  Get the physical lesser child node of the passed node without altering the
  node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree in which the node exists
  ----------------------------------------------------------------------------
  Return Values:

  NULL - The current node is NULL or it is a leaf node in the tree

  motelTreeNodeHandle - The lesser child node of the node passed
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetLesserChildNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetGreaterChildNode()
  ----------------------------------------------------------------------------
  Get the physical greater child node of the passed node without altering the
  node cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree in which the node exists
  ----------------------------------------------------------------------------
  Return Values:

  NULL - The current node is NULL or it is a leaf node in the tree

  motelTreeNodeHandle - The greater child node of the node passed
  ----------------------------------------------------------------------------*/

static motelTreeNodeHandle GetGreaterChildNode
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetTreeLevelCount()
  ----------------------------------------------------------------------------
  Determine the maximum level depth of a tree.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) Handle of the tree
  ----------------------------------------------------------------------------
  Return Values:

  unsigned long - The maximum level depth within the tree
  ----------------------------------------------------------------------------
  Note:

  This function determines the branch length of the longest route from the
  root to a leaf node. Each node within the longest route from the root to
  a leaf node is considered a level within the tree.
  ----------------------------------------------------------------------------*/

static unsigned long GetTreeLevelCount
(
    motelTreeHandle pTree
);

/*----------------------------------------------------------------------------
  GetSubtreeLevelCount()
  ----------------------------------------------------------------------------
  Determine the maximum level depth of a subtree.
  ----------------------------------------------------------------------------
  Parameters:

  pRoot - (I) The root of the subtree to measure
  ----------------------------------------------------------------------------
  Return Values:

  unsigned long - The maximum level depth within the subtree
  ----------------------------------------------------------------------------
  Note:

  This function determines the branch length of the longest route from the
  subtree root to a leaf node. Each node within the longest route from the
  subtree root to a leaf node is considered a level within the subtree.
  ----------------------------------------------------------------------------*/

static unsigned long GetSubtreeLevelCount
(
    motelTreeNodeHandle pRoot
);

/*----------------------------------------------------------------------------
  PivotLesserToGreater()
  ----------------------------------------------------------------------------
  Pivot a subtree moving nodes from the lesser side of the subtree to the
  greater side of the subtree
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) The tree handle
  pRoot - (I) The root of the subtree to rebalance
  ----------------------------------------------------------------------------
  Return Values:

  None
  ----------------------------------------------------------------------------
  Notes:

  1. Make the lesser child of the old root the new root
  2. Make the old root the greater child of the new root
  3. Make the greater child of the new root the lesser child of the old root

                 Old                           New

                  Y                             W.
                 / \                          /   \
                W   Z     -- Becomes ->     U       Y.
               / \                         / \     / \     
              U   X                       T   V   X.  Z
             / \               
            T   V               Altered nodes denoted with a period

  The old root's (Y) lesser and new root's (W) greater children were altered
  as a result weights on these branches must be recalculated
  ----------------------------------------------------------------------------*/

static void PivotLesserToGreater
(
    motelTreeHandle pTree, 
    motelTreeNodeHandle * pRoot
);

/*----------------------------------------------------------------------------
  PivotGreaterToLesser()
  ----------------------------------------------------------------------------
  Pivot a subtree moving nodes from the greater side of the subtree to the
  lesser side of the subtree
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) The tree handle
  pRoot - (I) The root of the subtree to rebalance
  ----------------------------------------------------------------------------
  Return Values:

  None
  ----------------------------------------------------------------------------
  Notes:

  1. Make the greater child of the old root the new root
  2. Make the old root the lesser child of the new root
  3. Make the lesser child of the new root the greater child of the old root

                 Old                           New

                  B                             D.
                 / \                          /   \
                A   D     -- Becomes ->     B.      F
                   / \                     / \     / \     
                  C   F                   A   C.  E   G
                     / \               
                    E   G       Altered nodes denoted with a period

  The old root's (B) greater and new root's (D) lesser children were altered
  as a result weights on these branches must be recalculated
  ----------------------------------------------------------------------------*/

static void PivotGreaterToLesser
(
    motelTreeHandle pTree, 
    motelTreeNodeHandle * pRoot
);

/*----------------------------------------------------------------------------
  PruneSubtree()
  ----------------------------------------------------------------------------
  Delete all nodes from a subtree 
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) The tree handle
  pRoot - (I) The root of the subtree to prune
  ----------------------------------------------------------------------------
  Return Values:

  True  - Subtree was succesfully pruned

  False - Subtree was not successfully pruned due to one of the following:

          1. A node destruction failed
          2. A SafeFreeBlock() failed
  ----------------------------------------------------------------------------*/

static boolean PruneSubtree
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pRoot
);

/*----------------------------------------------------------------------------
  ValidateSubtree()
  ----------------------------------------------------------------------------
  Test every node within a subtree to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:

  pTree - (I) The tree handle
  pRoot - (I) The root of the subtree to check
  ----------------------------------------------------------------------------
  Return Values:

  True  - Subtree passed the validity check

  False - Subtree did not pass the validity check due to one of the following:

          1. A node had a greater value that is located on a lesser branch
          2. A node had a lesser value that is located on a greater branch
          3. A node had branch weight that was incorrect
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelTree module. A
  validity check failure suggests a bug in the motelTree implementation.
  ----------------------------------------------------------------------------*/

static boolean ValidateSubtree
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pRoot
);

#endif
