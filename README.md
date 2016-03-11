# MOTEL Tree

## Description
A variation of the [red/black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) that has [O(log n)](https://en.wikipedia.org/wiki/Big-O_notation) time performance characteristics for insertion, search, and deletion of nodes within the tree.

The implementation replaces the node reb/black 'painting' with node branch weights that represent the number of descendant nodes on each branch.

The `motel.tree.i.h` file contains the list of function (operations) that can be performed and is provided as (API) module documentation.
The `motel.tree.t.h` file contains the type definitions used by the module.
The `motel.tree.h` file contains prototypes for the internal (private) function of the module.
The `motel.tree.c` file contains the implementation of the module.

## License
The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Included
**ANSI C** source code for the **MOTEL Tree** and test functions, plus supporting **MOTEL suite** library functions (**Memory**, **String**, and **Pool**) that are required to execute the **MOTEL Tree tester**. 

## Requirements
A **C** compiler

## Building the software
1: Clone the Git repository
```
git clone https://github.com/autopulous/motel.tree.git
```
2: Include all source code in a C project (e.g. Visual Studio, GNU C Compiler, etc)
3: Build the source

## Pivoting branches (the tricky part)
#### lesser to greater pivot

```
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
```

#### greater to lesser pivot

```
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
```