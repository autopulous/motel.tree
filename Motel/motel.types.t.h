/*----------------------------------------------------------------------------
  Motel Types
  
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

#ifndef MOTEL_TYPES_T_H
#define MOTEL_TYPES_T_H

#include <stddef.h>

#include "motel.signal.t.h"

#ifdef NULL
#undef NULL
#endif
#define NULL ((void *) 0)

/*
** The byte type
*/

typedef unsigned char byte;

/*
** bit bucket types
*/

#if defined _WIN32 || defined _WIN64

typedef unsigned char      bits8;
typedef unsigned short     bits16;
typedef unsigned long      bits32;
typedef unsigned long long bits64;

#else

#error need to define bit bucket types for this compiler/architecture

#endif

/*
** Used to reference an item count
*/

typedef size_t count;

/*
** Used to reference an item index
*/

typedef size_t index;

/*
** The boolean (Boolean) type
*/

typedef bits8 boolean;

#ifdef FALSE
#undef FALSE
#endif
#define FALSE ((boolean)(1 != 1))

#ifdef TRUE
#undef TRUE
#endif
#define TRUE ((boolean)(1 == 1))

/*
** Function return values
*/

typedef boolean success;

/*
** The looping constructs
*/

#define loop for(;;)
#define escape(expression) if (expression) break

/*
** The try/catch constructs
*/

#define attempt for(;;)
#define exception(expression) if (expression) break

/*
** The lem (Less than, Equal, More than) type
*/

typedef signed char lem;

#ifdef LESS_THAN
#undef LESS_THAN
#endif
#define LESS_THAN ((lem) -1)

#ifdef EQUAL_TO
#undef EQUAL_TO
#endif
#define EQUAL_TO ((lem) 0)

#ifdef MORE_THAN
#undef MORE_THAN
#endif
#define MORE_THAN ((lem) 1)

/*
** The autopulation mode specifiers
*/

typedef unsigned int autopulation;

#ifdef CATENATE
#undef CATENATE
#endif
#define CATENATE ((autopulation) (0<<0)) /* spread existing nodes and insert */

#ifdef EXCISE
#undef EXCISE
#endif
#define EXCISE ((autopulation) (1<<0)) /* remove existing nodes and insert */

#ifdef COPY
#undef COPY
#endif
#define COPY ((autopulation) (0<<1)) /* copy and preserve nodes */

#ifdef MOVE
#undef MOVE
#endif
#define MOVE ((autopulation) (1<<1)) /* copy and destroy nodes */

/*
** Interfaces
*/

typedef void (* _MotelFunctionPointer)(void);

/*------------------------------------------------------------------------------------------------------*/
/*                                           Resource References                                        */
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/*                                  Hierarchical Resource Reference (HRR)                               */
/*                                                                                                      */
/*    154.211.100.76:8080$https/delta\ws\listserver1@johnhart:mysecret?weekly=on;when=friday#public     */
/*                                                 or                                                   */
/*    org.speakhuman:8080$https/beta\ws/script.motel@johnhart:mysecret?debug=on;action=parse#strict     */
/*    \_________________/\____/\___________________/\________________/\____________________/\_____/     */
/*           device      scheme       resource         credentials            query         fragment    */
/*    \____________/\___/                           \_______/\_______/                                  */
/*         host     port                             identity password                                  */
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/*                               Uniform Resource Locator (URL) structure                               */
/*                                                                                                      */
/* https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel?debug=on;action=parse#strict  */
/* \___/   \_______________________________________/\___________________/ \___________________/ \____/  */
/* scheme                 authority                     resource path             query        fragment */
/*         \_______________/ \________________/ \__/       \____________/                               */
/*            credentials           host        port       resource name                                */
/*         \______/ \______/                                         \__/                               */
/*         username password                                  resource extension                        */
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/*                                      Local File Reference (LFR)                                      */
/*                                                                                                      */
/*                                                script                                                */
/*                                                 or                                                   */
/*                                                script.motel                                          */
/*                                                 or                                                   */
/*                                             ../script.motel                                          */
/*                                                 or                                                   */
/*                                             ..\script.motel                                          */
/*                                                 or                                                   */
/*                                       /beta\ws/script.motel                                          */
/*                                                 or                                                   */
/*                                     c:/beta\ws\script.motel                                          */
/*                                     \/\___________________/                                          */
/*                                   drive    resource path                                             */
/*                                                \__________/                                          */
/*                                                resource name                                         */
/*                                                       \___/                                          */
/*                                                 resource extension                                   */
/*------------------------------------------------------------------------------------------------------*/

#define MOTEL_RESOURCE_EXTENSION_SIZE 128
#define MOTEL_EXTENSION_DELIMITER_SIZE 8
#define MOTEL_RESOURCE_NAME_SIZE (512 + MOTEL_RESOURCE_EXTENSION_SIZE)
#define MOTEL_RESOURCE_NAME_DELIMITER_SIZE 8
#define MOTEL_RESOURCE_PATH_SIZE (1024 + MOTEL_RESOURCE_NAME_SIZE)

#define MOTEL_HOST_DELIMITER_SIZE 8
#define MOTEL_HOST_SIZE 1024

#define MOTEL_PORT_DELIMITER_SIZE 8
#define MOTEL_PORT_SIZE 16

#define MOTEL_DEVICE_SIZE (MOTEL_HOST_SIZE +                            \
                           MOTEL_PORT_DELIMITER_SIZE + MOTEL_PORT_SIZE)

#define MOTEL_SCHEME_DELIMITER_SIZE 8
#define MOTEL_SCHEME_SIZE 32

#define MOTEL_RESOURCE_REFERENCE_DELIMITER_SIZE 8

#define MOTEL_RESOURCE_REFERENCE_SIZE MOTEL_RESOURCE_PATH_SIZE

#define MOTEL_CREDENTIALS_DELIMITER_SIZE 8

#define MOTEL_USERNAME_DELIMITER_SIZE 8
#define MOTEL_IDENTITY_SIZE 1024
#define MOTEL_USERNAME_SIZE MOTEL_IDENTITY_SIZE

#define MOTEL_PASSWORD_DELIMITER_SIZE 8
#define MOTEL_PASSWORD_SIZE 1024

#define MOTEL_CREDENTIALS_SIZE (MOTEL_CREDENTIALS_DELIMITER_SIZE + MOTEL_IDENTITY_SIZE + \
                                MOTEL_PASSWORD_DELIMITER_SIZE + MOTEL_PASSWORD_SIZE)

#define MOTEL_AUTHORITY_SIZE (MOTEL_CREDENTIALS_SIZE +                      \
                              MOTEL_HOST_DELIMITER_SIZE + MOTEL_HOST_SIZE + \
                              MOTEL_PORT_DELIMITER_SIZE + MOTEL_PORT_SIZE)

#define MOTEL_QUERY_DELIMITER_SIZE 8
#define MOTEL_QUERY_SIZE 4096

#define MOTEL_FRAGMENT_DELIMITER_SIZE 8
#define MOTEL_FRAGMENT_SIZE 4096

#define MOTEL_HRR_SIZE (MOTEL_HOST_SIZE +                                                         \
                        MOTEL_PORT_DELIMITER_SIZE + MOTEL_PORT_SIZE +                             \
                        MOTEL_SCHEME_DELIMITER_SIZE + MOTEL_SCHEME_SIZE +                         \
                        MOTEL_RESOURCE_REFERENCE_DELIMITER_SIZE + MOTEL_RESOURCE_REFERENCE_SIZE + \
                        MOTEL_CREDENTIALS_DELIMITER_SIZE + MOTEL_IDENTITY_SIZE +                  \
                        MOTEL_PASSWORD_DELIMITER_SIZE + MOTEL_PASSWORD_SIZE +                     \
                        MOTEL_QUERY_DELIMITER_SIZE + MOTEL_QUERY_SIZE +                           \
                        MOTEL_FRAGMENT_DELIMITER_SIZE + MOTEL_FRAGMENT_SIZE)

#define MOTEL_URL_SIZE (MOTEL_SCHEME_SIZE + MOTEL_SCHEME_DELIMITER_SIZE +                    \
                        MOTEL_CREDENTIALS_DELIMITER_SIZE + MOTEL_USERNAME_SIZE +             \
                        MOTEL_PASSWORD_DELIMITER_SIZE + MOTEL_PASSWORD_SIZE +                \
                        MOTEL_HOST_DELIMITER_SIZE + MOTEL_HOST_SIZE +                        \
                        MOTEL_PORT_DELIMITER_SIZE + MOTEL_PORT_SIZE +                        \
                        MOTEL_RESOURCE_REFERENCE_DELIMITER_SIZE + MOTEL_RESOURCE_PATH_SIZE + \
                        MOTEL_QUERY_DELIMITER_SIZE + MOTEL_QUERY_SIZE +                      \
                        MOTEL_FRAGMENT_DELIMITER_SIZE + MOTEL_FRAGMENT_SIZE)

#define MOTEL_DRIVE_REFERENCE_SIZE 8
#define MOTEL_DRIVE_REFERENCE_DELIMITER_SIZE 8

#define MOTEL_FILE_REFERENCE_SIZE (MOTEL_DRIVE_REFERENCE_SIZE + MOTEL_DRIVE_REFERENCE_DELIMITER_SIZE +      \
                                   MOTEL_RESOURCE_REFERENCE_DELIMITER_SIZE + MOTEL_RESOURCE_REFERENCE_SIZE)

#define X__X "----------------------------------------------------------------------------"

#endif
