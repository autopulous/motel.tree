/*----------------------------------------------------------------------------
  Motel String

  application programmer's interface (API) header file
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

#ifndef MOTEL_STRING_I_H
#define MOTEL_STRING_I_H

#if defined MOTEL_NAMESPACE

#define CopyString               Motel_CopyString
#define AppendString             Motel_AppendString
#define ReverseString            Motel_ReverseString

#define LeftTrimString           Motel_LeftTrimString
#define RightTrimString          Motel_RightTrimString
#define TrimString               Motel_TrimString
#define CleanseString            Motel_CleanseString

#define FindClassMemberCharacter Motel_FindClassMemberCharacter
#define ClassMatchCharacter      Motel_ClassMatchCharacter
#define TranslateCharacter       Motel_TranslateCharacter
#define SearchString             Motel_SearchString

#define ParseString              Motel_ParseString

#define CompareStrings           Motel_CompareStrings
#define CompareiStrings          Motel_CompareiStrings

/*
** convenience macros
*/

#define FindFirstCharacterInClass(pString, pCharacterClass) Motel_FindClassMemberCharacter(pString, pCharacterClass, 1)
#define FindLastCharacterInClass(pString, pCharacterClass)  Motel_FindClassMemberCharacter(pString, pCharacterClass, MOTEL_LAST_INSTANCE)

#define IsAlphanumeric(pCharacter)        Motel_ClassMatchCharacter(pCharacter, CC_ALPHANUMERIC)
#define IsAlphabetic(pCharacter)          Motel_ClassMatchCharacter(pCharacter, CC_ALPHA)
#define IsAlphabeticLower(pCharacter)     Motel_ClassMatchCharacter(pCharacter, CC_ALPHA_LOWER)
#define IsAlphabeticUpper(pCharacter)     Motel_ClassMatchCharacter(pCharacter, CC_ALPHA_UPPER)
#define IsBracket(pCharacter)             Motel_ClassMatchCharacter(pCharacter, CC_BRACKET)
#define IsControl(pCharacter)             Motel_ClassMatchCharacter(pCharacter, CC_CONTROL)
#define IsDecimal(pCharacter)             Motel_ClassMatchCharacter(pCharacter, CC_DECIMAL_DIGIT)
#define IsGraph(pCharacter)               Motel_ClassMatchCharacter(pCharacter, CC_GRAPH)
#define IsHexidecimal(pCharacter)         Motel_ClassMatchCharacter(pCharacter, CC_HEXIDECIMAL_DIGIT)
#define IsOctal(pCharacter)               Motel_ClassMatchCharacter(pCharacter, CC_OCTAL_DIGIT)
#define IsPrintable(pCharacter)           Motel_ClassMatchCharacter(pCharacter, CC_PRINT)
#define IsPunctuation(pCharacter)         Motel_ClassMatchCharacter(pCharacter, CC_PUNCTUATION)
#define IsWhitespace(pCharacter)          Motel_ClassMatchCharacter(pCharacter, CC_WHITESPACE)

#define ToLower(pCharacter)               Motel_TranslateCharacter(pCharacter, CC_ALPHA_UPPER, CC_ALPHA_LOWER)
#define ToUpper(pCharacter)               Motel_TranslateCharacter(pCharacter, CC_ALPHA_LOWER, CC_ALPHA_UPPER)

#define EqualStrings(pString1, pString2)  (EQUAL_TO == Motel_CompareStrings(pString1, pString2))
#define EqualStringsi(pString1, pString2) (EQUAL_TO == Motel_CompareiStrings(pString1, pString2))

#else

#define FindFirstCharacterInClass(pString, pCharacterClass) FindClassMemberCharacter(pString, pCharacterClass, 1)
#define FindLastCharacterInClass(pString, pCharacterClass)  FindClassMemberCharacter(pString, pCharacterClass, MOTEL_LAST_INSTANCE)

#define IsAlphanumeric(pCharacter)        ClassMatchCharacter(pCharacter, CC_ALPHANUMERIC)
#define IsAlphabetic(pCharacter)          ClassMatchCharacter(pCharacter, CC_ALPHA)
#define IsAlphabeticLower(pCharacter)     ClassMatchCharacter(pCharacter, CC_ALPHA_LOWER)
#define IsAlphabeticUpper(pCharacter)     ClassMatchCharacter(pCharacter, CC_ALPHA_UPPER)
#define IsBracket(pCharacter)             ClassMatchCharacter(pCharacter, CC_BRACKET)
#define IsControl(pCharacter)             ClassMatchCharacter(pCharacter, CC_CONTROL)
#define IsDecimal(pCharacter)             ClassMatchCharacter(pCharacter, CC_DECIMAL_DIGIT)
#define IsGraph(pCharacter)               ClassMatchCharacter(pCharacter, CC_GRAPH)
#define IsHexidecimal(pCharacter)         ClassMatchCharacter(pCharacter, CC_HEXIDECIMAL_DIGIT)
#define IsOctal(pCharacter)               ClassMatchCharacter(pCharacter, CC_OCTAL_DIGIT)
#define IsPrintable(pCharacter)           ClassMatchCharacter(pCharacter, CC_PRINT)
#define IsPunctuation(pCharacter)         ClassMatchCharacter(pCharacter, CC_PUNCTUATION)
#define IsWhitespace(pCharacter)          ClassMatchCharacter(pCharacter, CC_WHITESPACE)

#define ToLower(pCharacter)               TranslateCharacter(pCharacter, CC_ALPHA_UPPER, CC_ALPHA_LOWER)
#define ToUpper(pCharacter)               TranslateCharacter(pCharacter, CC_ALPHA_LOWER, CC_ALPHA_UPPER)

#define EqualStrings(pString1, pString2)  (EQUAL_TO == CompareStrings(pString1, pString2))
#define EqualStringsi(pString1, pString2) (EQUAL_TO == CompareiStrings(pString1, pString2))

#endif

/*----------------------------------------------------------------------------
  CopyString()
  ----------------------------------------------------------------------------
  This function insures that the pDestination strings is always terminated
  with a STRING_TERMINATOR when copying characters from pSource and that the
  size of the destination string is not overrun.
  ----------------------------------------------------------------------------
  Parameters:
  
  pSource          - (I) Pointer to source string buffer
  pDestination     - (O) Pointer to destination string buffer
  pDestinationSize - (I) The size in bytes of the destination buffer
  ----------------------------------------------------------------------------
  Notes:

  Replaces standard C library functions:

  strcpy()
  strncpy()

  ----------------------------------------------------------------------------
  Returns:

  pDestination
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION CopyString
(
    const char * pSource,
    char * pDestination,
    size_t pDestinationSize
);

/*----------------------------------------------------------------------------
  AppendString()
  ----------------------------------------------------------------------------
  This function concatenates two strings and insures that the size of the
  destination string is not overrun and that the destination string is always
  STRING_TERMINATOR terminated.
  ----------------------------------------------------------------------------
  Parameters:

  pSource          - (I) Pointer to source string buffer
  pDestination     - (O) Pointer to destination string buffer
  pDestinationSize - (I) The size in bytes of the destination buffer
  ----------------------------------------------------------------------------
  Notes:

  Replaces standard C library functions:

  strcat()
  strncat()

  ----------------------------------------------------------------------------
  Returns:

  pDestination
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION AppendString
(
    const char * pSource,
    char * pDestination,
    size_t pDestinationSize
);

/*----------------------------------------------------------------------------
  ReverseString()
  ----------------------------------------------------------------------------
  This function reverses a string
  ----------------------------------------------------------------------------
  Parameters:

  pString - (IO) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  pString
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION ReverseString
(
    char * pString
);

/*----------------------------------------------------------------------------
  LeftTrimString()
  ----------------------------------------------------------------------------
  Remove leading (leftmost) characters within a character class from a string
  ----------------------------------------------------------------------------
  Parameters:

  pString - (IO) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  pString
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION LeftTrimString
(
    char * pString,
    const char * pCharacterClass
);

/*----------------------------------------------------------------------------
  RightTrimString()
  ----------------------------------------------------------------------------
  Remove trailing (rightmost) characters within a character class from a
  string
  ----------------------------------------------------------------------------
  Parameters:

  pString - (IO) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  pString
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION RightTrimString
(
    char * pString,
    const char * pCharacterClass
);

/*----------------------------------------------------------------------------
  TrimString()
  ----------------------------------------------------------------------------
  Remove leading (leftmost) and trailing (rightmost) characters within a
  character class  from a string
  ----------------------------------------------------------------------------
  Parameters:

  pString - (IO) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  pString
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION TrimString
(
    char * pString,
    const char * pCharacterClass
);

/*----------------------------------------------------------------------------
  CleanseString()
  ----------------------------------------------------------------------------
  Remove control characters, trim and compress whitespace within a string
  ----------------------------------------------------------------------------
  Parameters:

  pString - (IO) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  pString
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION CleanseString
(
    char * pString
);

/*----------------------------------------------------------------------------
  FindClassMemberCharacter()
  ----------------------------------------------------------------------------
  Find an instance of a member of a character class within a string
  ----------------------------------------------------------------------------
  Parameters:

  pString         - (I) The source string
  pCharacterClass - (I) The set of characters that make up the character class
  pInstance       - (I) The instance of a character class member to find
  ----------------------------------------------------------------------------
  Notes:

  The last instance of a character within pCharacterClass that is found within
  pString that is less than or equal to the instance count.

  Replaces standard C library functions:

  strchr()
  strrchr()
  strpbrk()

  ----------------------------------------------------------------------------
  Returns:

  The address of the delimiter character found within pString or NULL when
  not found.
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION FindClassMemberCharacter
(
    const char * pString,
    const char * pCharacterClass,
    size_t pInstance
);

/*----------------------------------------------------------------------------
  ClassMatchCharacter()
  ----------------------------------------------------------------------------
  Determine if a character is a member of a character class
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter      - (I) The character being tested
  pCharacterClass - (I) The set of characters that make up the character class
  ----------------------------------------------------------------------------
  Notes:

  Replaces standard C library functions:

  isalnum()  - CC_ALPHANUMERIC
  isalpha()  - CC_ALPHA
  iscntrl()  - CC_CONTROL
  isdigit()  - CC_DECIMAL_DIGIT
  isgraph()  - CC_GRAPH
  islower()  - CC_ALPHA_LOWER
  isprint()  - CC_PRINT
  ispunct()  - CC_PUNCTUATION
  isspace()  - CC_WHITESPACE
  isupper()  - CC_ALPHA_UPPER
  isxdigit() - CC_HEXIDECIMAL_DIGIT

  ----------------------------------------------------------------------------
  Returns:

  TRUE  - the character is in the character class
  FALSE - the character is not in the character class
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ClassMatchCharacter
(
    const char pCharacter,
    const char * pCharacterClass
);

/*----------------------------------------------------------------------------
  TranslateCharacter()
  ----------------------------------------------------------------------------
  Translate a character that is a member a one character class into the
  corresponding character in a second character class
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter          - (I) The character being translated
  pFromCharacterClass - (I) The set of characters that make up the character
                            class to matched
  pToCharacterClass   - (I) The set of characters that make up the character
                            class to which to translate
  ----------------------------------------------------------------------------
  Notes:

  Replaces standard C library functions:

  tolower() - CC_ALPHA_UPPER, CC_ALPHA_LOWER
  toupper() - CC_ALPHA_LOWER, CC_ALPHA_UPPER

  ----------------------------------------------------------------------------
  Returns:

  The translated character
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char CALLING_CONVENTION TranslateCharacter
(
    const char pCharacter, 
    const char * pFromCharacterClass,
    const char * pToCharacterClass
);

/*----------------------------------------------------------------------------
  SearchString()
  ----------------------------------------------------------------------------
  Find any of a list of tokens within a source string
  ----------------------------------------------------------------------------
  Parameters:

  pSource       - (I) The source string
  pTokens       - (I) The count of search substrings
  pToken_1      - (I) A search substring to find (may be a regexp)
  pToken_2
  ...
  pToken_n
  pInstance     - (I) The instance of a search substring to return
  pTerminators  - (I) The count of terminator substrings
  pTerminator_1 - (I) A terminator substring to end a search
  pTerminator_2 - (I)
  ...
  pTerminator_n - (I)
  ----------------------------------------------------------------------------
  Notes:

  A zero instance indicator causes the last instance of a token to be returned

  A zero terminator substring count indicates that no terminator substring is
  provided

  ----------------------------------------------------------------------------
  Returns:

  The address of the token instance found within the source string.
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION SearchString
(
    const char * pSource,
    ...
);

/*----------------------------------------------------------------------------
  ParseString()
  ----------------------------------------------------------------------------
  Retrieve a substring token between a right and left delimter string
  ----------------------------------------------------------------------------
  Parameters:

  pDestination            - (O) Receives the parsed substring token
  pSource                 - (I) Scanned for a substring token
  pDestinationSize        - (I) The size in bytes of the destination buffer
  
  pLeftDelimiters         - (I) The count of left delimiter strings
  pLeftDelimiter_1        - (I) A left delimiter string (regexp)
  pLeftDelimiter_2
  ...
  pLeftDelimiter_n
  
  pLeftDelimiterInstance  - (I) The left delimiter instance to parse

  pRightDelimiters        - (I) The count of right delimiter strings
  pRightDelimiter_1       - (I) A right delimiter string (regexp)
  pRightDelimiter_2
  ...
  pRightDelimiter_n
  pRightDelimiterInstance - (I) The right delimiter instance to parse

  ----------------------------------------------------------------------------
  Notes:

  A zero left delimiter instance causes the last instance of a left delimiter
  to be used to delimit the token to retrieve

  A zero right delimiters count indicates that no right delimiter substring
  is provided - the end of the source string is the right delimiter
  ----------------------------------------------------------------------------
  Returns:

  The address of the right delimiter within the source string or NULL if the
  delimited substring is not found
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION ParseString
(
    char * pDestination,
    const char * pSource,
    size_t pDestinationSize,
    ...
);

/*----------------------------------------------------------------------------
  CompareStrings()
  ----------------------------------------------------------------------------
  String comparison
  ----------------------------------------------------------------------------
  Parameters:

  pString1 - (I) Pointer to string buffer
  pString2 - (I) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  lem (LESS_THAN, EQUAL_TO, MORE_THAN) value
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION	CompareStrings
(
    const char * pString1, 
    const char * pString2
);

/*----------------------------------------------------------------------------
  CompareiStrings()
  ----------------------------------------------------------------------------
  Case insensitive string comparison
  ----------------------------------------------------------------------------
  Parameters:

  pString1 - (I) Pointer to string buffer
  pString2 - (I) Pointer to string buffer
  ----------------------------------------------------------------------------
  Returns:

  lem (LESS_THAN, EQUAL_TO, MORE_THAN) value
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareiStrings
(
    const char * pString1, 
    const char * pString2
);

#endif
