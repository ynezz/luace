/*
 *  $Id: luace.h 4 2009-03-13 09:47:42Z petr $
 *
 * Copyright (c) 2009 Petr Stetiar <ynezz@true.cz>, Gaben Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom 
 * the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _LUACE_H_
#define _LUACE_H_

#ifdef UNDER_CE
#include <wce_stdio.h>
#include <wce_stdlib.h>
#include <wce_string.h>
#include <wce_time.h>
#include <wce_locale.h>
#include <wce_winbase.h>

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

#ifndef MAX_PATH
#define MAX_PATH 2048
#endif

#ifndef L_tmpnam
#define L_tmpnam MAX_PATH
#endif

#ifndef getenv
#define getenv wceex_getenv
#endif

#ifndef strerror
#define strerror wceex_strerror
#endif

#ifndef freopen
#define freopen wceex_freopen
#endif

#ifndef tmpfile
#define tmpfile wceex_tmpfile
#endif

#ifndef tmpnam
#define tmpnam wceex_tmpnam
#endif

#ifndef rename
#define rename wceex_rename
#endif

#ifndef remove
#define remove wceex_unlink
#endif

#ifndef system
#define system wceex_system
#endif

#ifndef clock
#define clock wceex_clock
#endif

#ifndef stcoll
#define strcoll strcmp
#endif

#ifndef localeconv
#define localeconv wceex_localeconv
#endif

#ifndef mktime
#define mktime wceex_mktime
#endif

#ifndef localtime
#define localtime wceex_localtime
#endif

#ifndef setlocale
#define setlocale wceex_setlocale
#endif

#ifndef gmtime
#define gmtime wceex_gmtime
#endif

#ifndef time
#define time wceex_time
#endif

#ifndef strftime
#define strftime wceex_strftime
#endif

#ifndef _pclose
#define _pclose(x) -1
#endif

#ifndef _popen
#define _popen(x, y) NULL
#endif

#undef GetProcAddress
#define GetProcAddress GetProcAddressA

#undef LoadStringW
#undef LoadString

#ifndef LoadLibraryA
#define LoadLibraryA wceex_LoadLibraryA
#endif

#ifndef FormatMessageA
#define FormatMessageA wceex_FormatMessageA
#endif

#ifndef GetModuleFileNameA
#define GetModuleFileNameA wceex_GetModuleFileNameA
#endif

#define _IOFBF          0x0000
#define _IOLBF          0x0040
#define _IONBF          0x0004

#endif /* UNDER_CE */

#endif /* _LUACE_H_ */
