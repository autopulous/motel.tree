/*----------------------------------------------------------------------------
  Motel Signal
  
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

#ifndef MOTEL_SIGNAL_T_H
#define MOTEL_SIGNAL_T_H

// todo: implement this functionality

#include "motel.types.t.h"

/*----------------------------------------------------------------------------
  Signal bit mask layout

   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
  +-+-+---------------------------+-------------------------------+
  |E|T|       Signal Source       |          Signal Value         |
  +-+-+---------------------------+-------------------------------+

  E - Error signal
      0 - No error
      1 - Error
    
  T - Terminate signal
      0 - Do not terminate
      1 - Terminate
  ----------------------------------------------------------------------------*/

#define MOTEL_SIGNAL_ERROR_MASK     ((bits32) 0x80000000)
#define MOTEL_SIGNAL_TERMINATE_MASK ((bits32) 0x40000000)

#define MOTEL_SIGNAL_SOURCE_MASK    ((bits32) 0x3FFF0000)
#define MOTEL_SIGNAL_VALUE_MASK     ((bits32) 0x0000FFFF)

#define MOTEL_SIGNAL_CLEAR          ((bits32) 0x00000000)

#define IsErrorSignal(pSignal)      ((MOTEL_SIGNAL_ERROR_MASK & (bits32) pSignal) ? TRUE : FALSE)
#define IsTerminateSignal(pSignal)  ((MOTEL_SIGNAL_TERMINATE_MASK & (bits32) pSignal) ? TRUE : FALSE)

#define SourceMaskSignal(pSignal)   ((bits32) (MOTEL_SIGNAL_SOURCE_MASK & (bits32) pSignal))
#define ValueMaskSignal(pSignal)    ((bits32) (MOTEL_SIGNAL_VALUE_MASK & (bits32) pSignal))

#define ClearSignal(pSignal)        ((bits32) pSignal = MOTEL_SIGNAL_CLEAR)

/* To assure signal uniqueness, source components must register at speakhuman.org */
/* Source component signal values and descriptions may also be registered at speakhuman.org */
/* It is recommended that all components use the standard signal values provided in this header file as the base set of signal values */

#endif
