/*----------------------------------------------------------------------------
  Motel Tree Test

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

#ifndef MOTEL_TREE_TEST_H
#define MOTEL_TREE_TEST_H

#define TEST_DURATION 3
#define THOROUGH_TEST_NODES 10000
#define PERFORMANCE_TEST_NODES THOROUGH_TEST_NODES * 250

#define DATA_ELEMENT_SIZE 64

#ifdef UNPREDICTABLE_RANDOMNESS
#define TEST_SEED ((unsigned int)time((time_t *) NULL))
#else
#define TEST_SEED 1
#endif

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

void DisplayOptions
(
    void
);

void Validate
(
    void
);

void Construct
(
    void
);

void Destruct
(
    void
);

void InsertNode
(
    void
);

void SelectNode
(
    void
);

void FetchNode
(
    void
);

void FetchDuplicatedNodes
(
    void
);

void UpdateNode
(
    void
);

void DeleteNode
(
    void
);

void LeastNode
(
    void
);

void GreatestNode
(
    void
);

void GreaterNode
(
    void
);

void LesserNode
(
    void
);

void PeekLeastNode
(
    void
);

void PeekGreatestNode
(
    void
);

void PeekGreaterNode
(
    void
);

void PeekLesserNode
(
    void
);

void TreeStructure
(
    void
);

void TreeDiagram
(
    void
);

void FetchLeastToGreatest
(
    void
);

void FetchGreatestToLeast
(
    void
);

void PeekLeastToGreatest
(
    void
);

void PeekGreatestToLeast
(
    void
);

void IteratedTest1
(
    void
);

void IteratedTest2
(
    void
);

void OutputTreeState
(
    void
);

void GenerateInsertData
(
    void
);

void GenerateUpdateData
(
    void
);

void OutputNodeData
(
    void
);

void OutputResult
(
    void
);

long _compare
(
    const void * pKey1,
    const void * pKey2
);

#endif
