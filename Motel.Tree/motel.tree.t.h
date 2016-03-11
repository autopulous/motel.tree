/*----------------------------------------------------------------------------
  Motel Tree
 
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

#ifndef MOTEL_TREE_T_H
#define MOTEL_TREE_T_H

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public members
*/

typedef enum motelTreeMember motelTreeMember;

enum motelTreeMember
{
    motelTreeMember_Result,          /*!< Data type:   (motelResult *)
                                          Description: The method result code */

    motelTreeMember_Size,            /*!< Data type:   (size_t *)
                                          Description: Memory currently allocated by the tree object */

    motelTreeMember_LevelCount,      /*!< Data type:   (unsigned long *)
                                          Description: The highest number of nodes from the root to a leaf */

    motelTreeMember_Nodes,           /*!< Data type:   (unsigned long *)
                                          Description: The number of nodes in the tree */

    motelTreeMember_Least,           /*!< Data type:   NULL
                                          Description: Move the node cursor to lowest key value */

    motelTreeMember_Greatest,        /*!< Data type:   NULL
                                          Description: Move the node cursor to greatest key value */

    motelTreeMember_Lesser,          /*!< Data type:   NULL
                                          Description: Move the node cursor to next lower value */

    motelTreeMember_Greater,         /*!< Data type:   NULL
                                          Description: Move the node cursor to next greater value */

    motelTreeMember_Root,            /*!< Data type:   NULL
                                          Description: Move the node cursor to the tree root */

    motelTreeMember_Parent,          /*!< Data type:   NULL
                                          Description: Move the node cursor to the current node's parent */

    motelTreeMember_LesserChild,     /*!< Data type:   NULL
                                          Description: Move the node cursor to the current node's lesser child */

    motelTreeMember_GreaterChild,    /*!< Data type:   NULL
                                          Description: Move the node cursor to the current node's greater child */

    motelTreeMember_
};

typedef struct motelTreeNode motelTreeNode;
typedef MUTABILITY motelTreeNode * motelTreeNodeHandle;

struct motelTreeNode
{
    MUTABILITY unsigned long instance;

    MUTABILITY motelTreeNodeHandle parent;
  
    MUTABILITY motelTreeNodeHandle lesser;
    MUTABILITY unsigned long lesserNullNodes;

    MUTABILITY motelTreeNodeHandle greater;
    MUTABILITY unsigned long greaterNullNodes;

    MUTABILITY void * MUTABILITY key;
    MUTABILITY void * MUTABILITY data;
};

typedef struct motelTree motelTree;
typedef MUTABILITY motelTree * motelTreeHandle;

struct motelTree
{
    MUTABILITY motelResult result;

    MUTABILITY size_t maximumSize;
    MUTABILITY size_t size;

    MUTABILITY long (* compareKeyFunction)(const void * pKey1, const void * pKey2);
    
    MUTABILITY size_t keySize;
    MUTABILITY size_t dataSize;

    MUTABILITY motelTreeNodeHandle root;

    MUTABILITY motelTreeNodeHandle cursor;
};

#endif
