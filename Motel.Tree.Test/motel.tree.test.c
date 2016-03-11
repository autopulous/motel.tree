/*----------------------------------------------------------------------------
  Motel Tree Test

  executable implementation file
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
  Standard libraries
  ----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*----------------------------------------------------------------------------
  Public data types
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"
#include "../Motel/motel.math.t.h"

#include "../Motel.String/motel.string.t.h"
#include "../Motel.Pool/motel.pool.t.h"

#include "../Motel.Tree/motel.tree.t.h"

  /*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.String/motel.string.i.h"
#include "../Motel.Memory/motel.memory.i.h"
#include "../Motel.Pool/motel.pool.i.h"

#include "../Motel.Tree/motel.tree.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.tree.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.tree.test.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

motelTreeHandle gTree;

long gKey;
char gData[DATA_ELEMENT_SIZE];

unsigned long gInstance;

long gKeys[THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES];

unsigned long gInstances[THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES];

unsigned long gNodeCount;

FILE *gFile;

/*----------------------------------------------------------------------------
  Main
  ----------------------------------------------------------------------------*/

void main
(
    void
)
{
    int lOption;

    gFile = stdout;

    srand(TEST_SEED);

    Construct();

    do
    {
        printf("Option: ");

        do
        {
            lOption = fgetc(stdin);
        }
        while (!IsPrintable(lOption)); /* eat carriage returns (etc) */

        switch ((char) lOption)
        {
            case '?':

                DisplayOptions();
                break;

            case 'Q':
            case 'q':

                Destruct();
                break;

            case 'X':
            case 'x':

                Destruct();
                Construct();
                break;

            case 'I': // insert
            case 'i':

                InsertNode();
                break;

            case 'S': // select
            case 's':

                SelectNode();
                break;

            case 'F': // fetch singly

                FetchNode();
                break;

            case 'f': // fetch duplicates

                FetchDuplicatedNodes();
                break;

            case 'U': // update
            case 'u':

                UpdateNode();
                break;

            case 'D': // delete
            case 'd':

                DeleteNode();
                break;

            case '[': // move to head

                LeastNode();
                break;

            case ']': // move to tail

                GreatestNode();
                break;

            case '>': // move to next

                GreaterNode();
                break;

            case '<': // move to previous

                LesserNode();
                break;

            case '{': // peek head

                PeekLeastNode();
                break;

            case '}': // peek tail

                PeekGreatestNode();
                break;

            case ')': // peek next

                PeekGreaterNode();
                break;

            case '(': // peek previous

                PeekLesserNode();
                break;

            case '^': // display tree diagram

                TreeDiagram();
                break;

            case '#': // display node structure

                TreeStructure();
                break;

            case 'A': // fetch all nodes head to tail

                FetchLeastToGreatest();
                break;

            case 'Z': // fetch all nodes tail to head

                FetchGreatestToLeast();
                break;

            case 'a': // peek all nodes head to tail

                PeekLeastToGreatest();
                break;

            case 'z': // peek all nodes tail to head

                PeekGreatestToLeast();
                break;

            case '1':

                IteratedTest1();
                break;

            case '2':

                IteratedTest2();
                break;

            case '!':

                OutputTreeState();
                break;

            default:

                printf("Valid options are I,S,F,U,D,[,],>,<,{,},),(,A,Z,a,z,1,2,!,X,Q,?\n");
                continue;
        }
    }
    while ('Q' != lOption && 'q' != lOption);
}

void DisplayOptions
(
    void
)
{
    printf("\n"
           "Options:\n"
           "\n"
           "I - Insert a node\n"
           "S - Select a node altering the cursor location\n"
           "F - Fetch the node at the cursor location\n"
           "f - Fetch the nodes of equal value at the cursor location\n"
           "U - Update the node at the cursor location\n"
           "D - Delete the node at the cursor location\n"
           "\n"
           "[ - Move the cursor to the least node\n"
           "] - Move the cursor to the greatest node\n"
           "> - Move the cursor to the greater node\n"
           "< - Move the cursor to the lesser node\n"
           "\n"
           "{ - Peek at the least node\n"
           "} - Peek at the greatest node\n"
           ") - Peek at the greater node\n"
           "( - Peek at the lesser node\n"
           "\n"
           "^ - Display tree diagram\n"
           "# - Display node structure\n"
           "\n"
           "A - Fetch all nodes in least to greatest order\n"
           "Z - Fetch all nodes in greatest to least order\n"
           "a - Peek all nodes in least to greatest order\n"
           "z - Peek all nodes in greatest to least order\n"
           "\n"
           "1 - Iterated performance test\n"
           "2 - Iterated thorough test\n"
           "\n"
           "! - Display tree state\n"
           "\n"
           "X - Reset tree\n"
           "\n"
           "Q - Quit\n"
           "? - Display this option list\n"
           "\n");
}

void Validate
(
    void
)
{
    unsigned long lNodes = 0;

    if (!ValidateTree(gTree))
    {
        fprintf(gFile, "Tree self validation failed.\n\n");
        return;
    }
    
    GetTreeMember(gTree, motelTreeMember_Nodes, (void **) &lNodes);

    if (gNodeCount != lNodes)
    {
        fprintf(gFile, "Tree length disagreement: Application = %d, API = %d\n\n", gNodeCount, lNodes);
    }
}

void Construct
(
    void
)
{
    if (!ConstructTree(&gTree, (size_t) 0, (size_t) DATA_ELEMENT_SIZE, sizeof(gKey), _compare))
    {
        return;
    }

    memset(&gKeys, 0, sizeof(gKeys));
    memset(&gInstances, 0, sizeof(gInstances));

    gNodeCount = 0;

    Validate();
}

void Destruct
(
    void
)
{
    Validate();

    if (!DestructTree(&gTree))
    {
        return;
    }

    memset(&gKeys, 0, sizeof(gKeys));
    memset(&gInstances, 0, sizeof(gInstances));

    gNodeCount = 0;
}

void InsertNode
(
    void
)
{
    printf("\n");
    printf("Enter integer key for new node: ");
    scanf("%ld", &gKey);
    printf("\n");

    GenerateInsertData();

    if (InsertTreeNode(gTree, gData, &gKey))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            gKeys[gNodeCount] = gKey;
            gInstances[gNodeCount] = gInstance;

            gNodeCount++;

            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void SelectNode
(
    void
)
{
    printf("\n");
    printf("Enter integer key for node to find: ");
    scanf("%ld", &gKey);
    printf("\n");

    if (SelectTreeNode(gTree, &gKey, 0))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void FetchNode
(
    void
)
{
    if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();
    }

    OutputResult();

    Validate();
}

void FetchDuplicatedNodes
(
    void
)
{
    long lKey;

    if (SelectTreeNode(gTree, &gKey, 1))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
            OutputResult();

            lKey = gKey;

            while (PeekGreaterTreeNode(gTree, gData, &gKey, &gInstance))
            {
                if (lKey != gKey)
                {
                    break;
                }

                OutputNodeData();
                OutputResult();
            }

            /*
            ** reposition the cursor to the first (lowest) duplicate
            */

            if (SelectTreeNode(gTree, &lKey, 1))
            {
                FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance);
            }
        }
        else
        {
            OutputResult();
        }
    }
    else
    {
        OutputResult();
    }

    Validate();
}

void UpdateNode
(
    void
)
{
    if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();

        GenerateUpdateData();

        if (UpdateTreeNode(gTree, gData))
        {
            if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
            {
                OutputNodeData();
            }
        }
    }

    OutputResult();

    Validate();
}

void DeleteNode
(
    void
)
{
    unsigned long lNodeIndex;

    if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();

        if (DeleteTreeNode(gTree))
        {
            gNodeCount--;

            for (lNodeIndex = 0; lNodeIndex < gNodeCount; lNodeIndex++)
            {
                if (gKey == gKeys[lNodeIndex] && gInstance == gInstances[lNodeIndex])
                {
                    break;
                }
            }
            
            for (lNodeIndex = lNodeIndex; lNodeIndex < gNodeCount; lNodeIndex++)
            {
                gKeys[lNodeIndex] = gKeys[lNodeIndex + 1];
                gInstances[lNodeIndex] = gInstances[lNodeIndex + 1];
            }

            gKeys[lNodeIndex] = 0;
            gInstances[lNodeIndex] = 0;
        }
    }

    OutputResult();

    Validate();
}

void LeastNode
(
    void
)
{
    if (SetTreeMember(gTree, motelTreeMember_Least, NULL))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void GreatestNode
(
    void
)
{
    if (SetTreeMember(gTree, motelTreeMember_Greatest, NULL))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void GreaterNode
(
    void
)
{
    if (SetTreeMember(gTree, motelTreeMember_Greater, NULL))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void LesserNode
(
    void
)
{
    if (SetTreeMember(gTree, motelTreeMember_Lesser, NULL))
    {
        if (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();
        }
    }

    OutputResult();

    Validate();
}

void PeekLeastNode
(
    void
)
{
    if (PeekLeastTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();
    }

    OutputResult();

    Validate();
}

void PeekGreatestNode
(
    void
)
{
    if (PeekGreatestTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();
    }

    OutputResult();

    Validate();
}

void PeekGreaterNode
(
    void
)
{
    if (PeekGreaterTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();
    }

    OutputResult();

    Validate();
}

void PeekLesserNode
(
    void
)
{
    if (PeekLesserTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        OutputNodeData();
    }

    OutputResult();

    Validate();
}

void TreeStructure
(
    void
)
{
    unsigned long lIndex;

    fprintf(gFile, "Index Current      Lesser       Parent       Greater\n"
                   "----- ------------ ------------ ------------ ------------\n");

    for (lIndex = 0; gNodeCount > lIndex; lIndex++)
    {
         fprintf(gFile, "% 4ld: ", lIndex + 1);

        if (SelectTreeNode(gTree, &gKeys[lIndex], gInstances[lIndex]))
        {
            FetchTreeNode(gTree, gData, &gKey, &gInstance);

            fprintf(gFile, "(% 06ld:%03ld) ", gKey, gInstance);
        }
        else
        {
            fprintf(gFile, "(          ) ");
        }

        SelectTreeNode(gTree, &gKeys[lIndex], gInstances[lIndex]);

        if (SetTreeMember(gTree, motelTreeMember_LesserChild, (const void *) NULL))
        {
            FetchTreeNode(gTree, gData, &gKey, &gInstance);

            fprintf(gFile, "(% 06ld:%03ld) ", gKey, gInstance);
        }
        else
        {
            fprintf(gFile, "(          ) ");
        }

        SelectTreeNode(gTree, &gKeys[lIndex], gInstances[lIndex]);

        if (SetTreeMember(gTree, motelTreeMember_Parent, (const void *) NULL))
        {
            FetchTreeNode(gTree, gData, &gKey, &gInstance);

            fprintf(gFile, "(% 06ld:%03ld) ", gKey, gInstance);
        }
        else
        {
            fprintf(gFile, "(   root   ) ");
        }

        SelectTreeNode(gTree, &gKeys[lIndex], gInstances[lIndex]);

        if (SetTreeMember(gTree, motelTreeMember_GreaterChild, (const void *) NULL))
        {
            FetchTreeNode(gTree, gData, &gKey, &gInstance);

            fprintf(gFile, "(% 06ld:%03ld)\n", gKey, gInstance);
        }
        else
        {
            fprintf(gFile, "(          )\n");
        }
    }

    fprintf(gFile, "\n");
}

void TreeDiagram
(
    void
)
{  
    unsigned long lLevels;
    unsigned long lPrintLevel;
    unsigned long lTraversalLevel;

    unsigned long lNodesOnLevel;
    unsigned long lNodeOnLevel;

    long lPrintPosition = 1;

    boolean lPopulated;

    GetTreeMember(gTree, motelTreeMember_LevelCount, &lLevels);

    /*
    ** print the tree a level at a time
    */

    for (lPrintLevel = 1; lLevels >= lPrintLevel; lPrintLevel++)
    {
        int lLeading = (TwoRaisedToThePowerOf(lLevels - lPrintLevel) - 1) * 10;
        int lBetween = (TwoRaisedToThePowerOf(lLevels - (lPrintLevel - 1)) - 1) * 10;

        /*
        ** center the the nodes on the current level
        */

        if (0 != lLeading)
        {
            fprintf(gFile, "%*s", lLeading, " ");
        }

        lNodesOnLevel = TwoRaisedToThePowerOf(lPrintLevel - 1);

        for (lNodeOnLevel = 1; lNodesOnLevel >= lNodeOnLevel; lNodeOnLevel++)
        {
            lPopulated = TRUE;

            SetTreeMember(gTree, motelTreeMember_Root, (const void *) NULL);

            for (lTraversalLevel = 1; lPrintLevel > lTraversalLevel; lTraversalLevel++)
            {
                if (lPrintPosition & TwoRaisedToThePowerOf((lPrintLevel - lTraversalLevel) - 1))
                {
                    if (!SetTreeMember(gTree, motelTreeMember_GreaterChild, (const void *) NULL))
                    {
                        lPopulated = FALSE;
                        break;
                    }
                }
                else
                {
                    if (!SetTreeMember(gTree, motelTreeMember_LesserChild, (const void *) NULL))
                    {
                        lPopulated = FALSE;
                        break;
                    }
                }
            }

            if (1 < lNodeOnLevel)
            {
                fprintf(gFile, "%*s", lBetween, " ");
            }

            /*
            ** at the level currently being printed:
            **
            ** print a blank for an empty node or the key from the node
            */	

            if (!lPopulated)
            {
                fprintf(gFile, "%*s", 10, " ");
            }
            else
            {
                FetchTreeNode(gTree, gData, &gKey, &gInstance);

                fprintf(gFile, "%06ld:%03ld", gKey, gInstance);
            }

            lPrintPosition++;
        }

        fprintf(gFile, "\n\n");
    }

    fprintf(gFile, "\n");
}

void FetchLeastToGreatest
(
    void
)
{
    long lLastKey;

    long lIndex = 1;

    if (SetTreeMember(gTree, motelTreeMember_Least, NULL))
    {
        while (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();

            if (1 != lIndex && 0 < _compare(&lLastKey, &gKey))
            {
                fprintf(gFile, "<error> - out of sequence\n\n");
            }

            lIndex++;

            lLastKey = gKey;

            if (!SetTreeMember(gTree, motelTreeMember_Greater, NULL))
            {
                break;
            }
        }
    }

    OutputResult();

    Validate();
}

void FetchGreatestToLeast
(
    void
)
{
    long lLastKey;

    long lIndex = 1;

    if (SetTreeMember(gTree, motelTreeMember_Greatest, NULL))
    {
        while (FetchTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
        {
            OutputNodeData();

            if (1 != lIndex && 0 > _compare(&lLastKey, &gKey))
            {
                fprintf(gFile, "<error> - out of sequence\n\n");
            }

            lIndex++;

            lLastKey = gKey;

            if (!SetTreeMember(gTree, motelTreeMember_Lesser, NULL))
            {
                break;
            }
        }
    }

    OutputResult();

    Validate();
}

void PeekLeastToGreatest
(
    void
)
{
    long lLastKey;

    long lIndex = 1;

    if (PeekLeastTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        do
        {
            OutputNodeData();

            if (1 != lIndex && 0 < _compare(&lLastKey, &gKey))
            {
                fprintf(gFile, "<error> - out of sequence\n\n");
            }

            lIndex++;

            lLastKey = gKey;
        }
        while (PeekGreaterTreeNode(gTree, gData, &gKey, &gInstance));
    }

    OutputResult();

    Validate();
}

void PeekGreatestToLeast
(
    void
)
{
    long lLastKey;

    long lIndex = 1;

    if (PeekGreatestTreeNode(gTree, (void *) gData, (void *) &gKey, &gInstance))
    {
        do
        {
            OutputNodeData();

            if (1 != lIndex && 0 > _compare(&lLastKey, &gKey))
            {
                fprintf(gFile, "<error> - out of sequence\n\n");
            }

            lIndex++;

            lLastKey = gKey;
        }
        while (PeekLesserTreeNode(gTree, gData, &gKey, &gInstance));
    }

    OutputResult();

    Validate();
}

void IteratedTest1
(
    void
)
{
    unsigned long lCounter;
    unsigned long lSearchCounter;

    time_t lStartTime;

    double lSeconds;

    double lInsertSeconds = 0;
    double lFetchSeconds = 0;
    double lDeleteSeconds = 0;
    double lTotalSeconds;

    double lNormalizedInsertSeconds;
    double lNormalizedFetchSeconds;
    double lNormalizedDeleteSeconds;
    double lNormalizedTotalSeconds;

    double lInsertTransactions = 0;
    double lFetchTransactions = 0;
    double lDeleteTransactions = 0;
    double lTotalTransactions;

    Destruct();
    Construct();

    lStartTime = time((time_t *) NULL);

    do
    {
        for (lCounter = 0; lCounter < PERFORMANCE_TEST_NODES; lCounter++)
        {
            gKey = (rand() + rand() - RAND_MAX) % 99999;
            sprintf(gData, "Entry #%06d", lCounter + 1);

            InsertTreeNode(gTree, &gData, &gKey);

            gNodeCount++;

            lInsertTransactions++;

            if (0L == (long) lInsertTransactions % 500)
            {
                switch (((long) lInsertTransactions / 500) % 4)
                {
                case 0:
                    printf("-\b");
                    break;
                case 1:
                    printf("\\\b");
                    break;
                case 2:
                    printf("|\b");
                    break;
                case 3:
                    printf("/\b");
                    break;
                }
            }
        }

        lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

    lInsertSeconds += lSeconds;

    printf(">");

    lStartTime = time((time_t *) NULL);

    do
    {
        for (lSearchCounter = 0; lSearchCounter < 25; lSearchCounter++)
        {
            for (lCounter = 0; lCounter < gNodeCount; lCounter++)
            {
                gKey = (rand() + rand() - RAND_MAX) % 99999;

                SelectTreeNode(gTree, &gKey, 1);
                FetchTreeNode(gTree, gData, &gKey, &gInstance);

                lFetchTransactions++;

                if (0L == (long) lFetchTransactions % 500)
                {
                    switch (((long) lFetchTransactions / 500) % 4)
                    {
                    case 0:
                        printf(".  \b\b\b");
                        break;
                    case 1:
                        printf(" . \b\b\b");
                        break;
                    case 2:
                        printf("  .\b\b\b");
                        break;
                    case 3:
                        printf(" . \b\b\b");
                        break;
                    }
                }
            }
        }

        lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

    lFetchSeconds += lSeconds;

    printf(":");

    lStartTime = time((time_t *) NULL);

    while (gNodeCount)
    {
        SetTreeMember(gTree, motelTreeMember_Root, NULL);

        switch (rand() % 3)
        {
        case 0:

            SetTreeMember(gTree, motelTreeMember_Least, NULL);
            break;

        case 1:

            SetTreeMember(gTree, motelTreeMember_Root, NULL);
            break;

        case 2:

            SetTreeMember(gTree, motelTreeMember_Greatest, NULL);
            break;
        }

        DeleteTreeNode(gTree);

        lDeleteTransactions++;

        if (0L == (long) lDeleteTransactions % 500)
        {
            switch (((long) lDeleteTransactions / 500) % 4)
            {
            case 0:
                printf("-\b");
                break;
            case 1:
                printf("/\b");
                break;
            case 2:
                printf("|\b");
                break;
            case 3:
                printf("\\\b");
                break;
            }
        }

        gNodeCount--;
    }

    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    lDeleteSeconds += lSeconds;

    printf("<");

    printf("\r");

    lTotalSeconds = lInsertSeconds + lFetchSeconds + lDeleteSeconds;
    lTotalTransactions = lInsertTransactions + lFetchTransactions + lDeleteTransactions;

    lNormalizedInsertSeconds = (lTotalTransactions / lInsertTransactions) * lInsertSeconds;
    lNormalizedFetchSeconds = (lTotalTransactions / lFetchTransactions) * lFetchSeconds;
    lNormalizedDeleteSeconds = (lTotalTransactions / lDeleteTransactions) * lDeleteSeconds;

    lNormalizedTotalSeconds = lNormalizedInsertSeconds + lNormalizedFetchSeconds + lNormalizedDeleteSeconds;

    printf("\n\n");

    printf("Insert: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lInsertTransactions, lInsertSeconds, lInsertTransactions/lInsertSeconds, 100.0 * lNormalizedInsertSeconds / lNormalizedTotalSeconds);
    printf("Fetch:  %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lFetchTransactions, lFetchSeconds, lFetchTransactions/lFetchSeconds, 100.0 * lNormalizedFetchSeconds / lNormalizedTotalSeconds);
    printf("Delete: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lDeleteTransactions, lDeleteSeconds, lDeleteTransactions/lDeleteSeconds, 100.0 * lNormalizedDeleteSeconds / lNormalizedTotalSeconds);
    printf("        -----------------------------------------------\n");
    printf("Totals: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n\n", lTotalTransactions, lTotalSeconds, lTotalTransactions/lTotalSeconds, 100.0);
}

void IteratedTest2
(
    void
)
{
    unsigned long lIterations;
    unsigned long lIteration;

    unsigned long lIndex;
    unsigned long lNodeIndex;

    Destruct();
    Construct();

    printf("\n");
    printf("Iterations: ");
    scanf("%ld", &lIterations);

    for (lIteration = 1; ; lIteration++)
    {
        if (lIteration > lIterations)
        {
            break;
        }

        printf("Iteration : %ld ", lIteration);

        for (lNodeIndex = 0; lNodeIndex < THOROUGH_TEST_NODES; lNodeIndex++)
        {
            gKey = (rand() + rand() - RAND_MAX) % 99999;
            sprintf(gData, "Entry #%06d", lNodeIndex + 1);

            gKeys[lNodeIndex] = gKey;

            InsertTreeNode(gTree, gData, &gKey);

            FetchTreeNode(gTree, gData, &gKey, &gInstance);

            gInstances[lNodeIndex] = gInstance;

            gNodeCount++;

            ValidateTree(gTree);

            if (stdout != gFile)
            {
                fprintf(gFile, "-------------------------------------Insert---------------------------------------\n");
                fprintf(gFile, "%s: (%ld:%03ld)\n\n", gData, gKey, gInstance);
                fflush(gFile);

                TreeStructure();
                fprintf(gFile, "\n");
                fflush(gFile);

                PeekLeastToGreatest();
                fprintf(gFile, "\n");
                fflush(gFile);
            }

            if (0 == lNodeIndex % (THOROUGH_TEST_NODES / 100))
            {
                switch ((lNodeIndex / (THOROUGH_TEST_NODES / 100)) % 4L)
                {
                case 0:
                    printf("-\b");
                    break;
                case 1:
                    printf("\\\b");
                    break;
                case 2:
                    printf("|\b");
                    break;
                case 3:
                    printf("/\b");
                    break;
                }
            }
        }

        printf(">");

        if (stdout != gFile)
        {
            PeekGreatestToLeast();
            fprintf(gFile, "\n");
            fflush(gFile);
        }

        for (gNodeCount = lNodeIndex; gNodeCount > 0;)
        {
            lIndex = rand() % gNodeCount;

            SelectTreeNode(gTree, &gKeys[lIndex], gInstances[lIndex]);

            if (stdout != gFile)
            {
                FetchTreeNode(gTree, gData, &gKey, &gInstance);

                fprintf(gFile, "--------------------------------------Delete--------------------------------------\n");
                fprintf(gFile, "%s: (%ld:%03ld)\n\n", gData, gKey, gInstance);
                fflush(gFile);
            }

            DeleteTreeNode(gTree);

            gNodeCount--;

            ValidateTree(gTree);

            /*
            ** squish the deleted node from the node array
            */
            
            for (; lIndex < gNodeCount; lIndex++)
            {
                gKeys[lIndex] = gKeys[lIndex + 1];
                gInstances[lIndex] = gInstances[lIndex + 1];
            }

            if (stdout != gFile)
            {
                TreeStructure();
                fprintf(gFile, "\n");
                fflush(gFile);

                FetchLeastToGreatest();
                fprintf(gFile, "\n");
                fflush(gFile);
            }

            if (0 == gNodeCount % (THOROUGH_TEST_NODES / 100))
            {
                switch ((gNodeCount / (THOROUGH_TEST_NODES / 100)) % 4L)
                {
                case 0:
                    printf("-\b");
                    break;
                case 1:
                    printf("\\\b");
                    break;
                case 2:
                    printf("|\b");
                    break;
                case 3:
                    printf("/\b");
                    break;
                }
            }
        }

        printf("<");

        if (stdout != gFile)
        {
            FetchGreatestToLeast();
            fprintf(gFile, "\n");
            fflush(gFile);
        }

        printf("\r");
    }

    ValidateTree(gTree);

    printf("\n\n");
}

void OutputTreeState
(
    void
)
{
    unsigned long lNodes;
    unsigned long lLevels;

    size_t lSize;

    GetTreeMember(gTree, motelTreeMember_Nodes, (void **) &lNodes);
    GetTreeMember(gTree, motelTreeMember_LevelCount, &lLevels);
    GetTreeMember(gTree, motelTreeMember_Size, (void **) &lSize);

    fprintf(gFile, "Node Count = %ld\n", lNodes);
    fprintf(gFile, "Tree Depth = %ld\n", lLevels);
    fprintf(gFile, "\n");
    fprintf(gFile, "Memory Allocated = %zd\n\n", lSize);
}

void GenerateInsertData
(
    void
)
{
    static unsigned long lCreationOrdinal = 1;

    sprintf(gData, "Insert Ordinal:%08ld", lCreationOrdinal++);
}

void GenerateUpdateData
(
    void
)
{
    static unsigned long lUpdateOrdinal = 1;

    sprintf(gData, "Update Ordinal:%08ld", lUpdateOrdinal++);
}

void OutputNodeData
(
    void
)
{
    fprintf(gFile, "Key: \"%06ld:%03ld\"\n", gKey, gInstance);
    fprintf(gFile, "Data: \"%s\"\n\n", gData);
}

void OutputResult
(
    void
)
{
    long lResultCode;

    if (GetTreeMember(gTree, motelTreeMember_Result, (void **) &lResultCode))
    {
        fprintf(gFile, "Result Code: %ld\n\n", lResultCode);
    }
    else
    {
        fprintf(gFile, "Result Code: (could not be retrieved)\n\n");
    }
}

long _compare
(
    const void * pKey1,
    const void * pKey2
)
{
  return (* (long *) pKey1 - * (long *) pKey2);
}
