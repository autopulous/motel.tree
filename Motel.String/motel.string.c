/*----------------------------------------------------------------------------
  Motel String
  
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

#include "motel.string.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.string.c - Copyright 2010-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION CopyString
(
    const char * pSource,
    char * pDestination,
    size_t pDestinationSize
)
{
    if (NULL != pDestination && 0 < pDestinationSize)
    {
        /*
        ** append characters from the pSource string
        */

        if (NULL != pSource)
        {
            while (1 < pDestinationSize)
            {
                * pDestination = * pSource;

                if (* CC_STRING_TERMINATOR == * pSource)
                {
                    break;
                }

                pDestination++;
                pSource++;
                pDestinationSize--;
            }
        }

        * pDestination = * CC_STRING_TERMINATOR;
    }

    return (pDestination);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION AppendString
(
    const char * pSource,
    char * pDestination,
    size_t pDestinationSize
)
{
    if (NULL != pDestination && 0 < pDestinationSize)
    {
        /*
        ** find the current end of the pDestination string
        */

        while (1 < pDestinationSize)
        {
            if (* CC_STRING_TERMINATOR == * pDestination)
            {
                break;
            }

            pDestination++;
            pDestinationSize--;
        }

        /*
        ** append characters from the pSource string
        */

        if (NULL != pSource)
        {
            while (1 < pDestinationSize)
            {
                * pDestination = * pSource;

                if (* CC_STRING_TERMINATOR == * pSource)
                {
                    break;
                }

                pDestination++;
                pSource++;
                pDestinationSize--;
            }
        }

        * pDestination = * CC_STRING_TERMINATOR;
    }

    return (pDestination);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION ReverseString
(
    char * pString
)
{
    char lCharacter;

    char * lLeftCharacter;
    char * lRightCharacter;

    /*
    ** find the string's CC_STRING_TERMINATOR
    */
    
    for (lRightCharacter = pString; * CC_STRING_TERMINATOR != * lRightCharacter; lRightCharacter++);

    /*
    ** reverse the string, swapping left for right, working towards the middle
    */

    for (lLeftCharacter = pString, lRightCharacter--; lLeftCharacter < lRightCharacter; lLeftCharacter++, lRightCharacter--)
    {
        lCharacter = * lLeftCharacter, * lLeftCharacter = * lRightCharacter, * lRightCharacter = lCharacter;
    }

    return (pString);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION LeftTrimString
(
    char * pString,
    const char * pCharacterClass
)
{
    if (NULL != pString && NULL != pCharacterClass && * CC_STRING_TERMINATOR != * pCharacterClass)
    {
        char * lSourceCursor = pString;
        char * lDestinationCursor = pString;

        /*
        ** skip over leading character class members
        */

        while (ClassMatchCharacter(*lSourceCursor, pCharacterClass))
        {
            lSourceCursor++;
        }
      
        /*
        ** move remaining characters to the front of the string
        */

        while (* CC_STRING_TERMINATOR != (*lDestinationCursor = *lSourceCursor))
        {
            lSourceCursor++;
            lDestinationCursor++;
        }
    }

    return (pString);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION RightTrimString
(
    char * pString,
    const char * pCharacterClass
)
{
    if (NULL != pString && NULL != pCharacterClass && * CC_STRING_TERMINATOR != * pCharacterClass)
    {
        char * lInspectionCursor = pString;
        char * lTerminationCursor = pString;

        while (* CC_STRING_TERMINATOR != *lInspectionCursor)
        {
            if (!ClassMatchCharacter(*lInspectionCursor++, pCharacterClass))
            {     
                lTerminationCursor = lInspectionCursor;
            }
        }
 
        *lTerminationCursor = 0;      
    }

    return (pString);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION TrimString
(
    char * pString,
    const char * pCharacterClass
)
{
    if (NULL != pString && NULL != pCharacterClass && * CC_STRING_TERMINATOR != * pCharacterClass)
    {
        char * lSourceCursor = pString;
        char * lDestinationCursor = pString;
        char * lTerminationCursor = pString;

        while (ClassMatchCharacter(*lSourceCursor, pCharacterClass))
        {
            lSourceCursor++;
        }
      
        while (* CC_STRING_TERMINATOR != (*lDestinationCursor = *lSourceCursor))
        {
            lSourceCursor++;

            if (!ClassMatchCharacter(*lDestinationCursor++, pCharacterClass))
            {     
                lTerminationCursor = lDestinationCursor;
            }
        }

        *lTerminationCursor = 0;      
    }
   
    return (pString);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION CleanseString
(
    char * pString
)
{
    if (NULL != pString)
    {
        char *lSource = pString;
        char *lDestination = pString;
        char *lTerminationCursor = pString;

        /*
        ** skip over leading whitespace and control characters
        */

        while (* CC_STRING_TERMINATOR != *lSource && ClassMatchCharacter(*lSource, CC_WHITESPACE CC_CONTROL))
        {
            lSource++;
        }

        /*
        ** set the string terminator at the beginning of the trailing space and control characters
        */
      
        while (* CC_STRING_TERMINATOR != (*lDestination = *lSource))
        {
            lSource++;

            if (IsGraph(*lDestination))
            {
                lDestination++;

                lTerminationCursor = lDestination;
            }
            else
            {
                lDestination++;
            }
        }

        /*
        ** truncate trailing space and control characters
        */

        *lTerminationCursor = 0;
    }

    return (pString);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION FindClassMemberCharacter
(
    const char * pString,
    const char * pCharacterClass,
    size_t pInstance
)
{    
    char * lCharacter;
    char * lFoundCharacter;

    /*
    ** no string
    */

    if (NULL == pString)
    {
        return (NULL);
    }

    /*
    ** no character class
    */

    if (NULL == pCharacterClass)
    {
        return (NULL);
    }

    /*
    ** no instances specified
    */

    if (0 == pInstance)
    {
        return (NULL);
    }

    /*
    ** search the string for a character in the character class
    */

    lFoundCharacter = (char *) NULL;

    lCharacter = (char *) pString;

    while (TRUE)
    {
        if (* CC_STRING_TERMINATOR != *lCharacter)
        {
            return (lFoundCharacter);
        }

        if (ClassMatchCharacter(*lCharacter, pCharacterClass))
        {
            if (1 == pInstance)
            {
                return (lCharacter);
            }

            pInstance--;

            lFoundCharacter = lCharacter;
        }

        lCharacter++;
    }

    return ('\0');
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ClassMatchCharacter
(
    const char pCharacter,
    const char * pCharacterClass
)
{
    char * lClassCharacter;

    if (NULL == pCharacterClass)
    {
        return (FALSE);
    }

    lClassCharacter = (char *) pCharacterClass;

    loop
    {
        escape(* CC_STRING_TERMINATOR == * lClassCharacter);
        
        if (pCharacter == * lClassCharacter)
        {
            return (TRUE);
        }

        lClassCharacter++;
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS char CALLING_CONVENTION TranslateCharacter
(
    const char pCharacter, 
    const char * pFromCharacterClass,
    const char * pToCharacterClass
)
{
    if (NULL != pFromCharacterClass && NULL != pToCharacterClass)
    {
        while (* CC_STRING_TERMINATOR != * pFromCharacterClass && * CC_STRING_TERMINATOR != * pToCharacterClass)
        {
            if (* pFromCharacterClass == pCharacter)
            {
                return (* pToCharacterClass);
            }

            pFromCharacterClass++;
            pToCharacterClass++;
        }

        /*
        ** when the "From" character class is longer than the "To" character
        ** class and a match is found in the "From" character class, map the
        ** to character to "no character", represented by STRING_TERMINATOR
        */

        while (* CC_STRING_TERMINATOR != * pFromCharacterClass)
        {
            if (* pFromCharacterClass == pCharacter)
            {
                return (* CC_STRING_TERMINATOR);
            }

            pFromCharacterClass++;
        }
    }

    /*
    ** did not translate
    */

    return (pCharacter);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION SearchString
(
    const char * pSource,
    ...
)
{
    va_list lArgument;

    unsigned int lCount;

    char * pLeftDelimiter[256];
    unsigned int pLeftDelimiterCount = 0;

    char * pRightDelimiter[256];
    unsigned int pRightDelimiterCount = 0;

    unsigned long pFindLeftDelimiterInstance;

    char * lProbeAhead;

    char * lCharacter;
    char * lLookAhead;

    unsigned long lFoundInstance = 0;

    char * lFound = (char *) NULL;

    /*
    ** load variable arguments
    */

    va_start(lArgument, pSource);

    /*
    ** count of source string tokens
    */

    lCount = va_arg(lArgument, unsigned int);

    if (256 < lCount)
    {
        return (NULL);
    }

    /*
    ** list of source string tokens
    */

    while (0 < lCount)
    {
        pLeftDelimiter[pLeftDelimiterCount] = va_arg(lArgument, char *);

        if (* CC_STRING_TERMINATOR != * pLeftDelimiter[pLeftDelimiterCount])
        {
            pLeftDelimiterCount++;
        }

        lCount--;
    }

    /*
    ** which instance of any token should be returned in the source string
    */

    pFindLeftDelimiterInstance = va_arg(lArgument, unsigned long);

    /*
    ** count of source string terminators
    */

    lCount = va_arg(lArgument, unsigned int);

    if (256 < lCount)
    {
        return (NULL);
    }

    /*
    ** list of source string terminators
    */

    while (0 < lCount)
    {
        pRightDelimiter[pRightDelimiterCount] = va_arg(lArgument, char *);

        if (* CC_STRING_TERMINATOR != * pRightDelimiter[pRightDelimiterCount])
        {
            pRightDelimiterCount++;
        }

        lCount--;
    }

    va_end(lArgument);

    /*
    ** search for tokens in source string
    */

    lProbeAhead = (char *) pSource;

    while (* CC_STRING_TERMINATOR != * lProbeAhead)
    {
        /*
        ** terminator?
        */

        lCount = pRightDelimiterCount;

        while (0 < lCount)
        {
            lCount--;

            lCharacter = pRightDelimiter[lCount];

            lLookAhead = lProbeAhead;

            while (* lCharacter == * lLookAhead)
            {
                lCharacter++;

                if (* CC_STRING_TERMINATOR == * lCharacter)
                {
                    if (0 == pFindLeftDelimiterInstance)
                    {
                        return (lFound);
                    }

                    return (NULL);
                }

                lLookAhead++;
            }
        }

        /*
        ** token?
        */

        lCount = pLeftDelimiterCount;

        while (0 < lCount)
        {
            lCount--;

            lCharacter = pLeftDelimiter[lCount];

            lLookAhead = lProbeAhead;

            while (* lCharacter == * lLookAhead)
            {
                lCharacter++;

                if (* CC_STRING_TERMINATOR == * lCharacter)
                {
                    lFoundInstance++;

                    lLookAhead++;

                    if (pFindLeftDelimiterInstance == lFoundInstance)
                    {
                        return (lProbeAhead);
                    }

                    lFound = lProbeAhead;

                    lCount = 0;

                    break;
                }
            }
        }

        pSource++;
    }

    return (lFound);
}

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION ParseString
(
    char * pDestination,
    const char * pSource,
    size_t pDestinationSize,
    ...
)
{
    unsigned int pLeftDelimiterCount = 0;
    char * pLeftDelimiter[MOTEL_PARSE_DELIMITERS];
    unsigned long pLeftDelimiterInstance = 0;

    unsigned int pRightDelimiterCount = 0;
    char * pRightDelimiter[MOTEL_PARSE_DELIMITERS];
    unsigned long pRightDelimiterInstance = 0;

    va_list lArgument;

    unsigned int lCount;

    char * lToken;
    char * lDelimiter;

    /*
    ** no memory to store parsed token
    */

    if (0 == pDestinationSize)
    {
        return ((char *) pSource);
    }

    /*
    ** load variable arguments
    */

    va_start(lArgument, pDestinationSize);

    /*
    ** count of left delimiters
    */

    lCount = va_arg(lArgument, unsigned int);

    /*
    ** too many left delimiters
    */

    if (MOTEL_PARSE_DELIMITERS < lCount)
    {
        return (NULL);
    }

    /*
    ** list of left delimiters
    */

    while (0 < lCount)
    {
        pLeftDelimiter[pLeftDelimiterCount] = va_arg(lArgument, char *);

        if (* CC_STRING_TERMINATOR != * pLeftDelimiter[pLeftDelimiterCount])
        {
            pLeftDelimiterCount++;
        }

        lCount--;
    }

    /*
    ** which instance of any left delimiter should be used to delimit the token found within the source string
    */

    if (0 < pLeftDelimiterCount)
    {
        pLeftDelimiterInstance = va_arg(lArgument, unsigned long);
    }

    /*
    ** count of right delimiters
    */

    lCount = va_arg(lArgument, unsigned int);

    /*
    ** too many right delimiters
    */

    if (MOTEL_PARSE_DELIMITERS < lCount)
    {
        return (NULL);
    }

    /*
    ** list of right delimiters
    */

    while (0 < lCount)
    {
        pRightDelimiter[pRightDelimiterCount] = va_arg(lArgument, char *);

        if (* CC_STRING_TERMINATOR != * pRightDelimiter[pRightDelimiterCount])
        {
            pRightDelimiterCount++;
        }

        lCount--;
    }

    /*
    ** which instance of any right delimiter should be used to delimit the token found within the source string
    */

    if (0 < pRightDelimiterCount)
    {
        pRightDelimiterInstance = va_arg(lArgument, unsigned long);
    }

    va_end(lArgument);

    /*
    ** find the beginning of the token
    */

    lToken = FindToken(pSource, pLeftDelimiter, pLeftDelimiterCount, pLeftDelimiterInstance);

    if (* CC_STRING_TERMINATOR == * lToken)
    {
        lDelimiter = (char *) pSource;
    }
    else
    {
        /*
        ** find the end of the token
        */

        lDelimiter = FindDelimiter(lToken, pRightDelimiter, pRightDelimiterCount, pRightDelimiterInstance);

        /*
        ** copy token into destination buffer
        */

        while (lToken != lDelimiter && 1 < pDestinationSize)
        {
            * pDestination = *lToken;

            pDestination++;
            lToken++;

            pDestinationSize--;
        }
    }

    * pDestination = * CC_STRING_TERMINATOR;

    return (lDelimiter);
}

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareStrings
(
   const char * pString1, 
   const char * pString2
)
{
    lem lResult = EQUAL_TO;

    char * lString1;
    char * lString2;

    char lEmpty = * CC_STRING_TERMINATOR;

    if (NULL != pString1 || NULL != pString2)
    {
        if (NULL != pString1)
        {
            lString1 = (char *) pString1;
        }
        else
        {
            lString1 = & lEmpty;
        }

        if (NULL != pString2)
        {
            lString2 = (char *) pString2;
        }
        else
        {
            lString2 = & lEmpty;
        }

        while (TRUE)
        {
            lResult = (lem) (*lString1 - *lString2);

            if (EQUAL_TO != lResult || * CC_STRING_TERMINATOR == * lString1 || * CC_STRING_TERMINATOR == * lString2)
            {
                break;
            }

            lString1++;
            lString2++;
        }
    }

    return (LESS_THAN >= lResult ? LESS_THAN : EQUAL_TO == lResult ? EQUAL_TO : MORE_THAN);
}

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareiStrings
(
   const char * pString1, 
   const char * pString2
)
{
    lem lResult = EQUAL_TO;

    char * lString1;
    char * lString2;

    char lEmpty = * CC_STRING_TERMINATOR;

    if (NULL != pString1 || NULL != pString2)
    {
        if (NULL != pString1)
        {
            lString1 = (char *) pString1;
        }
        else
        {
            lString1 = & lEmpty;
        }

        if (NULL != pString2)
        {
            lString2 = (char *) pString2;
        }
        else
        {
            lString2 = & lEmpty;
        }

        loop
        {
            lResult = (lem) (ToLower(*lString1) - ToLower(*lString2));

            escape (EQUAL_TO != lResult || * CC_STRING_TERMINATOR == * lString1 || * CC_STRING_TERMINATOR == * lString2);

            lString1++;
            lString2++;
        }
    }

    return (LESS_THAN >= lResult ? LESS_THAN : EQUAL_TO == lResult ? EQUAL_TO : MORE_THAN);
}

EXPORT_STORAGE_CLASS void (CALLING_CONVENTION Allocate)
(
   string ** pString,
   size_t pSize,
   size_t pQuantity
)
{
}

EXPORT_STORAGE_CLASS void (CALLING_CONVENTION Deallocate)
(
   string ** pString
)
{
}

EXPORT_STORAGE_CLASS void (CALLING_CONVENTION Fill)
(
   string * pString,
   element * pValue
)
{
}

/*
string String = {{Allocate, Deallocate, Fill}};

EXPORT_STORAGE_CLASS void CALLING_CONVENTION Test
(
   void
)
{
    string * lString;
    size_t lSize;

    String.Allocate(&lString, 999, 3);
    lSize = lString->Size;
}
*/

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static char * FindToken
(
    const char * pSource,
    char * pDelimiter[256],
    unsigned int pDelimiterCount,
    unsigned long pFindInstance
)
{
    char * lToken = (char *) NULL;
    
    unsigned int lCount;

    char * lProbe = (char *) pSource;

    char * lProbeAhead;
    char * lDelimiter;

    unsigned long lFoundInstance = 0;

    if (0 == pDelimiterCount)
    {
        /*
        ** no delimiters
        */

        return ((char *) pSource);
    }

    while (* CC_STRING_TERMINATOR != * lProbe)
    {
        lCount = pDelimiterCount;

        while (0 < lCount)
        {
            /*
            ** test all charcters in this delimiter against the source
            */

            lProbeAhead = lProbe;

            lCount--;

            lDelimiter = pDelimiter[lCount];

            while (* lDelimiter == * lProbeAhead && * CC_STRING_TERMINATOR != * lDelimiter)
            {
                lProbeAhead++;
                lDelimiter++;
            }

            if (* CC_STRING_TERMINATOR == * lDelimiter)
            {
                /*
                ** found a delimiter
                */

                if (MOTEL_LAST_INSTANCE == pFindInstance)
                {
                    /*
                    ** store the source string position immediately after the delimiter
                    */

                    lToken = lProbeAhead;
                }
                else
                {
                    lFoundInstance++;

                    if (MOTEL_OPTIONAL == pFindInstance || pFindInstance == lFoundInstance)
                    {
                        /*
                        ** the required instance was found
                        */

                        return (lProbeAhead);
                    }
                }

                /*
                ** continue scanning for delimiters after the just found delimiter
                */

                lProbe = lProbeAhead;

                lCount = pDelimiterCount; 
            }
        }

        lProbe++;
    }

    if (NULL == lToken)
    {
        /*
        ** a delimiter was not found
        */

        if (MOTEL_OPTIONAL == pFindInstance)
        {
            return ((char *) pSource);
        }
        else
        {
            return (lProbe);
        }
    }
    else
    {
        /*
        ** a delimiter was found
        */

        return (lToken);
    }
}

static char * FindDelimiter
(
    const char * pSource,
    char * pDelimiter[256],
    unsigned int pDelimiterCount,
    unsigned long pFindInstance
)
{
    char * lToken = (char *) NULL;
    
    unsigned int lCount;

    char * lProbe = (char *) pSource;

    char * lProbeAhead;
    char * lDelimiter;

    unsigned long lFoundInstance = 0;

    while (* CC_STRING_TERMINATOR != * lProbe)
    {
        lCount = pDelimiterCount;

        while (0 < lCount)
        {
            /*
            ** test all charcters in this delimiter against the source
            */

            lProbeAhead = lProbe;

            lCount--;

            lDelimiter = pDelimiter[lCount];

            while (* lDelimiter == * lProbeAhead && * CC_STRING_TERMINATOR != * lDelimiter)
            {
                lProbeAhead++;
                lDelimiter++;
            }

            if (* CC_STRING_TERMINATOR == * lDelimiter)
            {
                /*
                ** found a delimiter
                */

                if (MOTEL_LAST_INSTANCE == pFindInstance)
                {
                    /*
                    ** store the source string position of the delimiter
                    */

                    lToken = lProbe;
                }
                else
                {
                    lFoundInstance++;

                    if (MOTEL_OPTIONAL == pFindInstance || pFindInstance == lFoundInstance)
                    {
                        /*
                        ** the required instance was found
                        */

                        return (lProbe);
                    }
                }

                /*
                ** continue scanning for delimiters after the just found delimiter
                */

                lProbe = lProbeAhead;

                lCount = pDelimiterCount; 
            }
        }

        lProbe++;
    }

    if (NULL == lToken)
    {
        /*
        ** a delimiter was not found
        */

        if (MOTEL_OPTIONAL == pFindInstance)
        {
            return (lProbe);
        }
        else
        {
            return ((char *) pSource);
        }
    }
    else
    {
        /*
        ** a delimiter was found
        */

        return (lToken);
    }
}
