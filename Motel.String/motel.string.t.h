/*----------------------------------------------------------------------------
  Motel String
 
  application programmer's types (APT) header file
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

#ifndef MOTEL_STRING_T_H
#define MOTEL_STRING_T_H

#include <limits.h>

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Character class definitions
*/

#define CC_STRING_TERMINATOR     "\0"

#define CC_CONTROL_C             "\3"
#define CC_CONTROL_X             "\30"

#define CC_CONTROL               "\0\1\2\3\4\5\6\7"         \
                                 "\10\11\12\13\14\15\16\17" \
                                 "\20\21\22\23\24\25\26\27" \
                                 "\30\31\32\33\34\35\36\37" \
                                 "\177"

#define CC_SPACE                 " "
#define CC_TAB				     "\t"
#define CC_NEW_LINE              "\n"
#define CC_RETURN                "\r"
#define CC_FORM_FEED             "\f"
#define CC_VERTICAL_TAB          "\v"

#define CC_WHITESPACE            CC_SPACE CC_TAB CC_NEW_LINE CC_RETURN CC_FORM_FEED CC_VERTICAL_TAB

#define CC_BACKSPACE             "\b"
#define CC_BELL                  "\a"

#define CC_OCTAL_DIGIT           "01234567"

#define CC_HEXIDECIMAL_DIGIT     "0123456789ABCDEF"

#define CC_LEADING_DECIMAL_DIGIT "123456789"
#define CC_DECIMAL_DIGIT         "0" CC_LEADING_DECIMAL_DIGIT

#define CC_NUMERIC               CC_DECIMAL_DIGIT

#define CC_ALPHA_LOWER           "abcdefghijklmnopqrstuvwxyz"
#define CC_ALPHA_UPPER           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define CC_ALPHA                 CC_ALPHA_LOWER CC_ALPHA_UPPER
#define CC_ALPHANUMERIC          CC_ALPHA CC_NUMERIC

#define CC_BRACKET               "()<>[]{}"

#define CC_PUNCTUATION           "!\"#$%'*+,-./:;=?@\\^_`|~" CC_BRACKET

#define CC_GRAPH                 CC_ALPHANUMERIC CC_PUNCTUATION

#define CC_PRINT                 CC_GRAPH CC_SPACE

/*
** Parsing constants
*/

#define MOTEL_OPTIONAL      0
#define MOTEL_LAST_INSTANCE ULONG_MAX

#define MOTEL_PARSE_DELIMITERS 256

typedef union string string;

typedef byte element;

typedef void (CALLING_CONVENTION allocate)
(
   string **,
   size_t,
   size_t
);

typedef void (CALLING_CONVENTION deallocate)
(
   string **
);

typedef void (CALLING_CONVENTION fill)
(
   string *,
   element *
);

union string
{
    struct
    {
         allocate * MUTABILITY Allocate;
         deallocate * MUTABILITY Deallocate;
         fill * MUTABILITY Fill;
    };

    struct
    {
        MUTABILITY size_t Size;
        MUTABILITY size_t Quantity;
        MUTABILITY size_t Count;

        MUTABILITY element * MUTABILITY First;
        MUTABILITY element * MUTABILITY Current;
    };
};

#endif
