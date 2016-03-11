/*----------------------------------------------------------------------------
  Motel Tree
 
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

/*----------------------------------------------------------------------------
   Terms:

   - A root node with no children is called a sprout node
   - A root node with one child is called a sapling node
   - A root node with two children is called a trunk node
   - A non-root node with two children is called a fork node
   - A non-root node with one child is called a twig node
   - A non-root node with no children is called a leaf node
  ----------------------------------------------------------------------------*/

#include "motel.tree.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.tree.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateTree
(
    motelTreeHandle pTree
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (TRUE);
    }

    pTree->result = motelResult_OK;

    /*
    ** there are no nodes in the tree
    */

    if (NULL == pTree->root)
    {
        return (TRUE);
    }

    /*
    ** validate the root subtree
    */

    if (!ValidateSubtree(pTree, pTree->root))
    {
        return (FALSE); // pass through result code
    }

    /*
    ** the tree is valid
    */

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructTree
(
    motelTreeHandle * pTree,
    size_t pTreeMaximumSize,
    size_t pDataSize,
    size_t pKeySize,
    long (* pCompareKeyFunction)(const void * pKey1, const void * pKey2)
)
{
    /*
    ** no key comparision function was provided
    */

    if (NULL == pCompareKeyFunction)
    {
        return (FALSE);
    }

    /*
    ** the maximum size is too small to even create the tree control structure
    */

    if (0 != pTreeMaximumSize && sizeof(motelTree) > pTreeMaximumSize)
    {
        return (FALSE);
    }
    
    /*
    ** allocate the tree control structure
    */

    if (!SafeMallocBlock((void **) pTree, sizeof(motelTree)))
    {
        return (FALSE);
    }

    /*
    ** initialize the tree control structure
    */

    (* pTree)->result = motelResult_OK;

    (* pTree)->compareKeyFunction = pCompareKeyFunction;

    (* pTree)->maximumSize = pTreeMaximumSize;
    (* pTree)->size = sizeof(motelTree);

    (* pTree)->keySize = pKeySize;
    (* pTree)->dataSize = pDataSize;

    (* pTree)->root = (motelTreeNodeHandle) NULL;

    (* pTree)->cursor = (motelTreeNodeHandle) NULL;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructTree
(
    motelTreeHandle * pTree
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree || NULL == * pTree)
    {
        return (FALSE);
    }

    if (!PruneSubtree(* pTree, (* pTree)->root))
    {
        (* pTree)->result = motelResult_NodeDestruction;

        return (FALSE);
    }

    if (!SafeFreeBlock((void **) pTree))
    {
        (* pTree)->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetTreeMember
(
    motelTreeHandle pTree,
    motelTreeMember pMember,
    const void * pValue
)
{
    /*
    ** there is no tree object
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** node cursor navigation
    */

    switch (pMember)
    {
        motelTreeNodeHandle lCurrentNode;

        case motelTreeMember_Lesser:

            lCurrentNode = GetLesserNode(pTree);

            if (NULL == lCurrentNode)
            {
                return (FALSE);
            }

            pTree->cursor = lCurrentNode;

            return (TRUE);

        case motelTreeMember_Least:

            pTree->cursor = GetLeastNode(pTree);

            if (NULL == pTree->cursor)
            {
                return (FALSE);
            }

            return (TRUE);

        case motelTreeMember_Greatest:

            pTree->cursor = GetGreatestNode(pTree);

            if (NULL == pTree->cursor)
            {
                return (FALSE);
            }

            return (TRUE);

        case motelTreeMember_Greater:

            lCurrentNode = GetGreaterNode(pTree);

            if (NULL == lCurrentNode)
            {
                return (FALSE);
            }

            pTree->cursor = lCurrentNode;

            return (TRUE);

        case motelTreeMember_Root:

            pTree->cursor = GetRootNode(pTree);

            if (NULL == pTree->cursor)
            {
                return (FALSE);
            }

            return (TRUE);

        case motelTreeMember_Parent:

            lCurrentNode = GetParentNode(pTree);

            if (NULL == lCurrentNode)
            {
                return (FALSE);
            }

            pTree->cursor = lCurrentNode;

            return (TRUE);

        case motelTreeMember_LesserChild:

            lCurrentNode = GetLesserChildNode(pTree);

            if (NULL == lCurrentNode)
            {
                return (FALSE);
            }

            pTree->cursor = lCurrentNode;

            return (TRUE);

        case motelTreeMember_GreaterChild:

            lCurrentNode = GetGreaterChildNode(pTree);

            if (NULL == lCurrentNode)
            {
                return (FALSE);
            }

            pTree->cursor = lCurrentNode;

            return (TRUE);
    }

    if (NULL == pValue)
    {
        pTree->result = motelResult_NullPointer;

        return (FALSE);
    }

    switch (pMember)
    {
    }

    pTree->result = motelResult_InvalidMember;

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetTreeMember
(
    motelTreeHandle pTree,
    motelTreeMember pMember,
    void * pValue
)
{
    motelTreeNodeHandle lRoot;

    /*
    ** there is no tree object
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** no return parameter
    */

    if (NULL == pValue)
    {
        return (FALSE);
    }

    /*
    ** result code is a special case because we want to set a result code for GetTreeMember()
    */

    if (motelTreeMember_Result == pMember)
    {
        * (motelResult *) pValue = pTree->result;

        return (TRUE);
    }

    /*
    ** get member
    */

    pTree->result = motelResult_OK;

    switch (pMember)
    {
        case motelTreeMember_Size:

            * (size_t *) pValue = pTree->size;

            return (TRUE);

        case motelTreeMember_Nodes:

            lRoot = pTree->root;

            if (NULL == lRoot)
            {
                * (unsigned long *) pValue = 0L;
            }
            else
            {
                * (unsigned long *) pValue = lRoot->lesserNullNodes + lRoot->greaterNullNodes - 1L;
            }

            return (TRUE);

        case motelTreeMember_LevelCount:

            * (unsigned long *) pValue = GetTreeLevelCount(pTree);

            return (TRUE);
    }

    pTree->result = motelResult_InvalidMember;

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION InsertTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey
)
{
    motelTreeNodeHandle lInsertNode;

    motelTreeNodeHandle lNode;
    motelTreeNodeHandle lChild;

    long lComparisonResult;

    unsigned int lRebalanceThreshold = REBALANCE_THRESHOLD;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** there is no data object
    */

    if (NULL == pData)
    {
        pTree->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** there is no key object
    */

    if (NULL == pKey)
    {
        pTree->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** construct a new node
    */

    if (!ConstructNode(pTree, pKey, pData, &lInsertNode))
    {
        return (FALSE); // pass through result code
    }

    /*
    ** set the new node as the current node
    */

    pTree->cursor = lInsertNode;

    /*
    ** add a root node when the tree is empty
    */

    lNode = pTree->root;

    if (NULL == lNode)
    {
        pTree->root = lInsertNode;
        return (TRUE);
    }

    /*
    ** traverse the tree to find the insertion point
    */

    for (;;)
    {
        lComparisonResult = pTree->compareKeyFunction((const void *) lInsertNode->key, (const void *) lNode->key);;

        if (0 == lComparisonResult)
        {
            lInsertNode->instance = lNode->instance + 1;

            lComparisonResult = MORE_THAN;
        }

        if (0 > lComparisonResult)
        {
            /*
            ** traverse lesser
            */

            if (lRebalanceThreshold <= lNode->lesserNullNodes / lNode->greaterNullNodes)
            {
                PivotLesserToGreater(pTree, &lNode);

                lRebalanceThreshold++; /* prevents rebalance hysteresis */

                continue;
            }

            lNode->lesserNullNodes += 1;

            lChild = lNode->lesser;

            if (NULL == lChild)
            {
                lInsertNode->parent = lNode;
                lNode->lesser = lInsertNode;
                return (TRUE);
            }
        }
        else // (0 < lComparisonResult)
        {
            /*
            ** traverse greater
            */

            if (lRebalanceThreshold <= lNode->greaterNullNodes / lNode->lesserNullNodes)
            {
                PivotGreaterToLesser(pTree, &lNode);

                lRebalanceThreshold++; /* prevents rebalance hysteresis */

                continue;
            }

            lNode->greaterNullNodes += 1;

            lChild = lNode->greater;

            if (NULL == lChild)
            {
                lInsertNode->parent = lNode;
                lNode->greater = lInsertNode;
                return (TRUE);
            }
        }

        lNode = lChild;

        lRebalanceThreshold = REBALANCE_THRESHOLD;
    }
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SelectTreeNode
(
    motelTreeHandle pTree,
    void * pKey,
    unsigned long pInstance
)
{
    motelTreeNodeHandle lRoot;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    lRoot = pTree->root;

    if (NULL == lRoot)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    pTree->result = motelResult_OK;

    pTree->cursor = GetEqualNode(pTree, (const void *) pKey, pInstance);

    if (NULL == pTree->cursor)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION FetchTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
)
{
    motelTreeNodeHandle lFetchNode = (motelTreeNodeHandle) NULL;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** there is no node to fetch
    */

    lFetchNode = pTree->cursor;

    if (NULL == lFetchNode)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** copy the data value
    */

    if (NULL != pData)
    {
        memcpy((void *)pData, (const void *) lFetchNode->data, pTree->dataSize);
    }

    /*
    ** copy the key value
    */

    if (NULL != pKey)
    {
        memcpy((void *)pKey, (const void *) lFetchNode->key, pTree->keySize);
    }

    /*
    ** copy the instance value
    */

    if (NULL != pInstance)
    {
        * pInstance = lFetchNode->instance;
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION UpdateTreeNode
(
    motelTreeHandle pTree,
    void * pData
)
{
    motelTreeNodeHandle lUpdateNode = (motelTreeNodeHandle) NULL;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** there is no data to update the node
    */

    if (NULL == pData)
    {
        pTree->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** there is no node to update
    */

    lUpdateNode = pTree->cursor;

    if (NULL == lUpdateNode)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** set the data value
    */

    memcpy((void *) lUpdateNode->data, (const void *)pData, pTree->dataSize);

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeleteTreeNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lDeleteNode = (motelTreeNodeHandle) NULL;

    motelTreeNodeHandle lRoot;
    motelTreeNodeHandle lNode;
    motelTreeNodeHandle lChild;

    long lComparisonResult;

    boolean lNodeToDeleteFound = FALSE;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    lRoot = pTree->root;

    if (NULL == lRoot)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** there is no node to delete
    */

    lDeleteNode = pTree->cursor;

    if (NULL == lDeleteNode)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** traverse the tree to find a suitable substitute leaf or twig node 
    ** to be promoted into the position of node being deleted and rebalance
    ** the tree along the way
    */
    
    lNode = lRoot;

    for (;;)
    {
        /*
        ** decide which branch to follow
        */

        lComparisonResult = NodeCompare(pTree, lDeleteNode, lNode);

        if (0 == lComparisonResult)
        {
            lNodeToDeleteFound = TRUE;

            if (NULL != lNode->lesser)
            {
                lComparisonResult = LESS_THAN;
            }
            else
            {
                lComparisonResult = MORE_THAN;
            }
        }

        /*
        ** follow branch
        */

        if (0 > lComparisonResult)
        {
            /*
            ** traverse lesser
            */

            lChild = lNode->lesser;

            if (NULL == lChild)
            {
                break;
            }

            if (REBALANCE_THRESHOLD <= lNode->greaterNullNodes / (lNode->lesserNullNodes - 1))
            {
                PivotGreaterToLesser(pTree, &lNode);
                lChild = lNode->lesser;
            }

            lNode->lesserNullNodes -= 1;
        }
        else // (0 < lComparisonResult)
        {
            /*
            ** traverse greater
            */

            lChild = lNode->greater;

            if (NULL == lChild)
            {
                break;
            }

            if (REBALANCE_THRESHOLD <= lNode->lesserNullNodes / (lNode->greaterNullNodes - 1))
            {
                PivotLesserToGreater(pTree, &lNode);
                lChild = lNode->greater;
            }

            lNode->greaterNullNodes -= 1;
        }

        lNode = lChild;
    }

    /*
    ** node to delete was not encountered in the tree during traversal
    */

    if (!lNodeToDeleteFound)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE); /* branch weights are messed up now! */
    }

    /*
    ** delete the node
    */

    if (lDeleteNode == lNode)
    {
        /*
        ** the node to be deleted is a leaf node therefore there's no
        ** need for promotion, just disconnect it from its parent
        */

        if (lRoot == lNode)
        {
            pTree->root = (motelTreeNodeHandle) NULL;
        }
        else if (lDeleteNode->parent->lesser == lNode)
        {
            lDeleteNode->parent->lesser = (motelTreeNodeHandle) NULL;
        }
        else // (lDeleteNode->parent->greater == lNode)
        {
            lDeleteNode->parent->greater = (motelTreeNodeHandle) NULL;
        }
    }
    else // (lDeleteNode != lNode)
    {
        /*
        ** promote a leaf or twig node
        */

        /*
        ** when a lesser or greater child branch is attached to the node to promote
        ** move the child branch up to take the place of the to be promoted node
        */

        if (NULL != lNode->lesser)
        {
            if (lNode->parent->lesser == lNode)
            {
                lNode->parent->lesser = lNode->lesser;
            }
            else
            {
                lNode->parent->greater = lNode->lesser;
            }

            lNode->lesser->parent = lNode->parent;
        }
        else if (NULL != lNode->greater)
        {
            if (lNode->parent->lesser == lNode)
            {
                lNode->parent->lesser = lNode->greater;
            }
            else
            {
                lNode->parent->greater = lNode->greater;
            }

            lNode->greater->parent = lNode->parent;
        }
        else
        {
            /*
            ** disconnect the node being promoted from the old parent
            */

            if (lNode == lNode->parent->lesser)
            {
                lNode->parent->lesser = (motelTreeNodeHandle) NULL;
            }
            else // (lNode == lNode->parent->greater)
            {
                lNode->parent->greater = (motelTreeNodeHandle) NULL;
            }
        }

        /*
        ** make the found node assume the position of the node about to be deleted within the tree
        */

        /*
        ** connect the new parent to the node being promoted
        */

        if (NULL == lDeleteNode->parent)
        {
            pTree->root = lNode;
        }		
        else if (lDeleteNode == lDeleteNode->parent->lesser)
        {
            lDeleteNode->parent->lesser = lNode;
        }
        else // (lDeleteNode == lDeleteNode->parent->greater)
        {
            lDeleteNode->parent->greater = lNode;
        }

        /*
        ** connect the node being promoted to the new parent
        */

        lNode->parent = lDeleteNode->parent;

        /*
        ** connect lesser child to the node being promoted
        */

        if (lNode == lDeleteNode->lesser)
        {
            lNode->lesser = (motelTreeNodeHandle) NULL;
        }
        else
        {
            lNode->lesser = lDeleteNode->lesser;

            if (NULL != lNode->lesser)
            {
                lNode->lesser->parent = lNode;
            }
        }

        lNode->lesserNullNodes = lDeleteNode->lesserNullNodes;

        /*
        ** connect the greater child to the node being promoted
        */

        if (lNode == lDeleteNode->greater)
        {
            lNode->greater = (motelTreeNodeHandle) NULL;
        }
        else
        {
            lNode->greater = lDeleteNode->greater;
            
            if (NULL != lNode->greater)
            {
                lNode->greater->parent = lNode;
            }
        }

        lNode->greaterNullNodes = lDeleteNode->greaterNullNodes;
    }

    /*
    ** destruct the disconnected node
    */
    
    if (!DestructNode(pTree))
    {
        return (FALSE);
    }

    return (TRUE);
}
  
EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekLeastTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** position the cursor
    */

    pTree->cursor = GetLeastNode(pTree);

    if (NULL == pTree->cursor)
    {
        return (FALSE); // pass through result code
    }

    /*
    ** copy the data value
    */

    if (NULL != pData)
    {
        memcpy((void *)pData, (const void *) pTree->cursor->data, pTree->dataSize);
    }

    /*
    ** copy the key value
    */

    if (NULL != pKey)
    {
        memcpy((void *)pKey, (const void *) pTree->cursor->key, pTree->keySize);
    }

    /*
    ** copy the instance value
    */

    if (NULL != pInstance)
    {
        * pInstance = pTree->cursor->instance;
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekGreatestTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** position the cursor
    */

    pTree->cursor = GetGreatestNode(pTree);

    if (NULL == pTree->cursor)
    {
        return (FALSE); // pass through result code
    }

    /*
    ** copy the data value
    */

    if (NULL != pData)
    {
        memcpy((void *)pData, (const void *) pTree->cursor->data, pTree->dataSize);
    }

    /*
    ** copy the key value
    */

    if (NULL != pKey)
    {
        memcpy((void *)pKey, (const void *) pTree->cursor->key, pTree->keySize);
    }

    /*
    ** copy the instance value
    */

    if (NULL != pInstance)
    {
        * pInstance = pTree->cursor->instance;
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekLesserTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** when the cursor is not set, move forward from the greatest node
    */

    if (NULL == pTree->cursor)
    {
        pTree->cursor = GetGreatestNode(pTree);
    }
    else
    {
        pTree->cursor = GetLesserNode(pTree);
    }

    if (NULL == pTree->cursor)
    {
        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** copy the data value
    */

    if (NULL != pData)
    {
        memcpy((void *)pData, (const void *) pTree->cursor->data, pTree->dataSize);
    }

    /*
    ** copy the key value
    */

    if (NULL != pKey)
    {
        memcpy((void *)pKey, (const void *) pTree->cursor->key, pTree->keySize);
    }

    /*
    ** copy the instance value
    */

    if (NULL != pInstance)
    {
        * pInstance = pTree->cursor->instance;
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekGreaterTreeNode
(
    motelTreeHandle pTree,
    void * pData,
    void * pKey,
    unsigned long * pInstance
)
{
    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    /*
    ** the tree is empty
    */

    if (NULL == pTree->root)
    {
        pTree->result = motelResult_NoNode;

        return (FALSE);
    }

    /*
    ** when the cursor is not set, move forward from the least node
    */

    if (NULL == pTree->cursor)
    {
        pTree->cursor = GetLeastNode(pTree);
    }
    else
    {
        pTree->cursor = GetGreaterNode(pTree);
    }

    if (NULL == pTree->cursor)
    {
        return (FALSE);
    }

    pTree->result = motelResult_OK;

    /*
    ** copy the data value
    */

    if (NULL != pData)
    {
        memcpy((void *)pData, (const void *) pTree->cursor->data, pTree->dataSize);
    }

    /*
    ** copy the key value
    */

    if (NULL != pKey)
    {
        memcpy((void *)pKey, (const void *) pTree->cursor->key, pTree->keySize);
    }

    /*
    ** copy the instance value
    */

    if (NULL != pInstance)
    {
        * pInstance = pTree->cursor->instance;
    }

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static boolean ValidateSubtree
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pRoot
)
{
    if (NULL != pRoot->lesser)
    {
        /*
        ** validate that the node values are correct
        */

        if (0 > NodeCompare(pTree, pRoot, pRoot->lesser))
        {
            pTree->result = motelResult_Structure;

            return (FALSE); // set breakpoint here for debugging
        }

        /*
        ** validate that the node weights are correct
        */

        if (NULL != pRoot->lesser && pRoot->lesserNullNodes != pRoot->lesser->lesserNullNodes + pRoot->lesser->greaterNullNodes)
        {
            pTree->result = motelResult_NodeCount;

            return (FALSE); // set breakpoint here for debugging
        }

        /*
        ** validate the lesser subtree
        */

        if (!ValidateSubtree(pTree, pRoot->lesser))
        {
            return (FALSE); // pass through result code
        }
    }
    
    if (NULL != pRoot->greater)
    {
        /*
        ** validate that the node values are correct
        */

        if (0 < NodeCompare(pTree, pRoot, pRoot->greater))
        {
            pTree->result = motelResult_Structure;

            return (FALSE); // set breakpoint here for debugging
        }

        /*
        ** validate that the node weights are correct
        */

        if (pRoot->greaterNullNodes != pRoot->greater->lesserNullNodes + pRoot->greater->greaterNullNodes)
        {
            pTree->result = motelResult_NodeCount;

            return (FALSE); // set breakpoint here for debugging
        }

        /*
        ** validate the greater subtree
        */

        if (!ValidateSubtree(pTree, pRoot->greater))
        {
            return (FALSE); // pass through result code
        }
    }

    return (TRUE);
}

static boolean ConstructNode
(
    motelTreeHandle pTree,
    void * pKey,
    void * pData,
    motelTreeNodeHandle * pNode
)
{
    motelTreeNodeHandle lNode = (motelTreeNodeHandle) NULL;

    void * lNodeKey = (void *) NULL;
    void * lNodeData = (void *) NULL;

    pTree->result = motelResult_OK;

    /*
    ** there isn't room for a new node
    */

    if (pTree->maximumSize > 0 && pTree->maximumSize < pTree->size + sizeof(motelTreeNode) + pTree->keySize + pTree->dataSize)
    {
        pTree->result = motelResult_MaximumSize;

        * pNode = (motelTreeNodeHandle) NULL;

        return (FALSE);
    }

    /*
    ** allocate memory for the objects
    */

    if (!ManagedMallocBlock((void **) &lNode, sizeof(motelTreeNode), &pTree->size))
    {
        pTree->result = motelResult_MemoryAllocation;

        * pNode = (motelTreeNodeHandle) NULL;

        return (FALSE);
    }

    if (!ManagedMallocBlock((void **) &lNodeKey, pTree->keySize, &pTree->size))
    {
        ManagedFreeBlock((void **) &lNode, sizeof(motelTreeNode), &pTree->size);

        pTree->result = motelResult_MemoryAllocation;

        * pNode = (motelTreeNodeHandle) NULL;

        return (FALSE);
    }

    if (!ManagedMallocBlock((void **) &lNodeData, pTree->dataSize, &pTree->size))
    {
        ManagedFreeBlock((void **) &lNodeKey, pTree->keySize, &pTree->size);
        ManagedFreeBlock((void **) &lNode, sizeof(motelTreeNode), &pTree->size);

        pTree->result = motelResult_MemoryAllocation;

        * pNode = (motelTreeNodeHandle) NULL;

        return (FALSE);
    }

    /*
    ** copy the key and data into the new node
    */

    memcpy((void *) lNodeKey, (const void *) pKey, pTree->keySize);
    memcpy((void *) lNodeData, (const void *) pData, pTree->dataSize);

    /*
    ** initialize the node
    */

    lNode->instance = 1;

    lNode->parent = (motelTreeNodeHandle) NULL;
    
    lNode->lesser = (motelTreeNodeHandle) NULL;
    lNode->lesserNullNodes = 1;
    
    lNode->greater = (motelTreeNodeHandle) NULL;
    lNode->greaterNullNodes = 1;

    lNode->key = lNodeKey;
    lNode->data = lNodeData;

    /*
    ** return the new node
    */

    * pNode = lNode;

    return (TRUE);
}

static boolean DestructNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lCurrentNode;

    /*
    ** there is no tree
    */

    if (NULL == pTree)
    {
        return (FALSE);
    }

    pTree->result = motelResult_OK;

    if (NULL == pTree->cursor)
    {
        pTree->result = motelResult_NotFound;

        return (FALSE);
    }

    lCurrentNode = pTree->cursor;

    if (!ManagedFreeBlock((void **) &lCurrentNode->data, pTree->dataSize, &pTree->size))
    {
        pTree->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    if (!ManagedFreeBlock((void **) &lCurrentNode->key, pTree->keySize, &pTree->size))
    {
        pTree->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    if (!ManagedFreeBlock((void **) &lCurrentNode, sizeof(motelTreeNode), &pTree->size))
    {
        pTree->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    pTree->cursor = (motelTreeNodeHandle) NULL;

    return (TRUE);
}

static motelTreeNodeHandle GetEqualNode
(
    motelTreeHandle pTree,
    const void * pKey,
    unsigned long pInstance
)
{
    motelTreeNodeHandle lNode;

    long lComparisonResult;

    pTree->result = motelResult_NotFound;

    /*
    ** there is no key
    */

    if (NULL == pKey)
    {
        return (NULL);
    }

    /*
    ** traverse towards the node that matches the key object value
    */

    lNode = pTree->root;

    while (NULL != lNode)
    {
        lComparisonResult = pTree->compareKeyFunction((const void *) pKey, (const void *) lNode->key);

        if (0 == lComparisonResult)
        {
            /*
            ** find the least instance of a potential duplicate
            */
            
            if (0 == pInstance)
            {
                while (NULL != lNode->lesser && 0 == pTree->compareKeyFunction((const void *) pKey, (const void *) lNode->lesser->key))
                {
                    lNode = lNode->lesser;
                }

                pTree->result = motelResult_OK;

                break;
            }
            else
            {
                lComparisonResult = pInstance - lNode->instance;
            }
        }

        if (0 > lComparisonResult)
        {
            lNode = lNode->lesser; /* traverse lesser */
        }
        else if (0 < lComparisonResult)
        {
            lNode = lNode->greater; /* traverse greater */
        }
        else /* (0 == lComparisonResult) */
        {
            pTree->result = motelResult_OK;
            break;
        }
    }

    return (lNode);
}

static long NodeCompare
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pNode1,
    motelTreeNodeHandle pNode2
)
{
    long lComparisonResult;

    lComparisonResult = pTree->compareKeyFunction((const void *) pNode1->key, (const void *) pNode2->key);

    if (0 == lComparisonResult)
    {
        lComparisonResult = pNode1->instance - pNode2->instance;
    }

    return (lComparisonResult);
}

static motelTreeNodeHandle GetLeastNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lNode = (motelTreeNodeHandle) NULL;
    motelTreeNodeHandle lChild;

    pTree->result = motelResult_NotFound;

    /*
    ** traverse towards the most lesser leaf
    */

    lChild = pTree->root;

    while (NULL != lChild)
    {
        lNode = lChild;
        lChild = lNode->lesser;
    }

    if (NULL != lNode)
    {
        pTree->result = motelResult_OK;
    }

    return (lNode);
}

static motelTreeNodeHandle GetGreatestNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lNode = (motelTreeNodeHandle) NULL;
    motelTreeNodeHandle lChild;

    pTree->result = motelResult_NotFound;

    /*
    ** traverse towards the most greater leaf
    */

    lChild = pTree->root;

    while (NULL != lChild)
    {
        lNode = lChild;
        lChild = lNode->greater;
    }

    if (NULL != lNode)
    {
        pTree->result = motelResult_OK;
    }

    return (lNode);
}

static motelTreeNodeHandle GetLesserNode
(
    motelTreeHandle pTree
)
{ 
    motelTreeNodeHandle lCurrentNode;

    motelTreeNodeHandle lChild;

    pTree->result = motelResult_NotFound;

    lCurrentNode = pTree->cursor;

    /*
    ** there is no node
    */

    if (NULL == lCurrentNode)
    {
        return (NULL);
    }

    /*
    ** traverse to the next lesser node in the tree
    */

    lChild = lCurrentNode->lesser;

    if (NULL != lChild)
    {
        /*
        ** get the greater node of the lesser branch of the node passed
        */

        do
        {
            lCurrentNode = lChild;
            lChild = lCurrentNode->greater; /* traverse towards a leaf */
        } 
        while (NULL != lChild);
    }
    else
    {
        /*
        ** get the first ancestor of the node passed that references the node's
        ** subtree via a greater branch
        */

        do
        {
            lChild = lCurrentNode;
            lCurrentNode = lChild->parent; /* traverse towards the root */
        }
        while (NULL != lCurrentNode && lChild != lCurrentNode->greater);
    }

    /*
    ** node not found
    */

    if (NULL != lCurrentNode)
    {
        pTree->result = motelResult_OK;
    }

    return (lCurrentNode);
}

static motelTreeNodeHandle GetGreaterNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lCurrentNode;

    motelTreeNodeHandle lChild;

    pTree->result = motelResult_NotFound;

    lCurrentNode = pTree->cursor;

    /*
    ** there is no node
    */

    if (NULL == lCurrentNode)
    {
        return (NULL);
    }

    /*
    ** traverse to the next greater node in the tree
    */

    lChild = lCurrentNode->greater;

    if (NULL != lChild)
    {
        /*
        ** get the lesser node of the greater branch of the node passed
        */

        do
        {
            lCurrentNode = lChild;
            lChild = lCurrentNode->lesser; /* traverse towards a leaf */
        } 
        while (NULL != lChild);
    }
    else
    {
        /*
        ** get the first ancestor of the node passed that references the node's
        ** subtree via a lesser branch
        */

        do
        {
            lChild = lCurrentNode;
            lCurrentNode = lChild->parent; /* traverse towards the root */
        }
        while (NULL != lCurrentNode && lChild != lCurrentNode->lesser);
    }

    if (NULL != lCurrentNode)
    {
        pTree->result = motelResult_OK;
    }

    return (lCurrentNode);
}

static motelTreeNodeHandle GetRootNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lNode;

    pTree->result = motelResult_NotFound;

    lNode = pTree->root;

    if (NULL != lNode)
    {
        pTree->result = motelResult_OK;
    }

    return (lNode);
}

static motelTreeNodeHandle GetParentNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lCurrentNode;

    pTree->result = motelResult_OK;

    lCurrentNode = pTree->cursor;

    /*
    ** there is no node
    */

    if (NULL == lCurrentNode)
    {
        pTree->result = motelResult_NullPointer;

        return (NULL);
    }

    return (lCurrentNode->parent);
}

static motelTreeNodeHandle GetLesserChildNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lCurrentNode;

    pTree->result = motelResult_OK;

    lCurrentNode = pTree->cursor;

    /*
    ** there is no node
    */

    if (NULL == lCurrentNode)
    {
        pTree->result = motelResult_NullPointer;

        return (NULL);
    }

    return (lCurrentNode->lesser);
}

static motelTreeNodeHandle GetGreaterChildNode
(
    motelTreeHandle pTree
)
{
    motelTreeNodeHandle lCurrentNode;

    pTree->result = motelResult_OK;

    lCurrentNode = pTree->cursor;

    /*
    ** there is no node
    */

    if (NULL == lCurrentNode)
    {
        pTree->result = motelResult_NullPointer;

        return (NULL);
    }

    return (lCurrentNode->greater);
}

static unsigned long GetTreeLevelCount
(
    motelTreeHandle pTree
)
{  
    motelTreeNodeHandle lRoot;

    if (NULL == pTree)
    {
        return (0);
    }

    lRoot = pTree->root;

    if (NULL == lRoot)
    {
        return (0);
    }  

    return (GetSubtreeLevelCount(lRoot));
}

static unsigned long GetSubtreeLevelCount
(
    motelTreeNodeHandle pRoot
)
{  
    long lLesserDepth;
    long lGreaterDepth;

    if (NULL == pRoot)
    {
        return (0);
    }  

    lLesserDepth = GetSubtreeLevelCount(pRoot->lesser);
    lGreaterDepth = GetSubtreeLevelCount(pRoot->greater);

    return ((lLesserDepth > lGreaterDepth) ? (1 + lLesserDepth) : (1 + lGreaterDepth));
}

static void PivotLesserToGreater
(
    motelTreeHandle pTree,
    motelTreeNodeHandle * pRoot
)
{
    motelTreeNodeHandle lOldRoot = * pRoot;
    motelTreeNodeHandle lNewRoot = lOldRoot->lesser;

    lNewRoot->parent = lOldRoot->parent;

    if (pTree->root == lOldRoot)
    {
        pTree->root = lNewRoot;
    }
    else
    {
        if (lOldRoot->parent->lesser == lOldRoot)
        {
            lOldRoot->parent->lesser = lNewRoot;
        }
        else
        {
            lOldRoot->parent->greater = lNewRoot;
        }
    }

    lOldRoot->parent = lNewRoot;

    lOldRoot->lesser = lNewRoot->greater;

    if (NULL != lNewRoot->greater)
    {
        lNewRoot->greater->parent = lOldRoot;
    }

    lNewRoot->greater = lOldRoot;

    /*
    ** update child node counts for the new and old parent working from lower to higher in the subtree
    */

    if (NULL == lOldRoot->lesser)
    {
        lOldRoot->lesserNullNodes = 1;
    }
    else
    {
        lOldRoot->lesserNullNodes = lOldRoot->lesser->lesserNullNodes + lOldRoot->lesser->greaterNullNodes;
    }

    lNewRoot->greaterNullNodes = lOldRoot->lesserNullNodes + lOldRoot->greaterNullNodes;

    /*
    ** set the new parent in the calling function's variable so that in process tree traversals can continue
    */

    (* pRoot) = lNewRoot;
}

static void PivotGreaterToLesser
(
    motelTreeHandle pTree,
    motelTreeNodeHandle * pRoot
)
{
    motelTreeNodeHandle lOldRoot = (* pRoot);
    motelTreeNodeHandle lNewRoot = lOldRoot->greater;

    lNewRoot->parent = lOldRoot->parent;

    if (pTree->root == lOldRoot)
    {
        pTree->root = lNewRoot;
    }
    else
    {
        if (lOldRoot->parent->lesser == lOldRoot)
        {
            lOldRoot->parent->lesser = lNewRoot;
        }
        else
        {
            lOldRoot->parent->greater = lNewRoot;
        }
    }

    lOldRoot->parent = lNewRoot;

    lOldRoot->greater = lNewRoot->lesser;

    if (NULL != lNewRoot->lesser)
    {
        lNewRoot->lesser->parent = lOldRoot;
    }

    lNewRoot->lesser = lOldRoot;

    /*
    ** update child node counts for the new and old parent working from lower to higher in the subtree
    */

    if (NULL == lOldRoot->greater)
    {
        lOldRoot->greaterNullNodes = 1;
    }
    else
    {
        lOldRoot->greaterNullNodes = lOldRoot->greater->lesserNullNodes + lOldRoot->greater->greaterNullNodes;
    }

    lNewRoot->lesserNullNodes = lOldRoot->lesserNullNodes + lOldRoot->greaterNullNodes;

    /*
    ** set the new parent in the calling function's variable so that in process tree traversals can continue
    */

    (* pRoot) = lNewRoot;
}

static boolean PruneSubtree
(
    motelTreeHandle pTree,
    motelTreeNodeHandle pRoot
)
{
    if (NULL != pRoot)
    {
        if (NULL != pRoot->lesser)
        {
            if (!PruneSubtree(pTree, pRoot->lesser))
            {
                return (FALSE); // pass through result code
            }
        }

        if (NULL != pRoot->greater)
        {
            if (!PruneSubtree(pTree, pRoot->greater))
            {
                return (FALSE); // pass through result code
            }
        }

        pTree->cursor = pRoot;

        if (!DestructNode(pTree))
        {
            return (FALSE); // pass through result code
        }
    }

    return (TRUE);
}
