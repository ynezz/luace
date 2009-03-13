/*
 * $Id$
 *
 * Defines tmpnam() function.
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
 * MIT License:
 * http://opensource.org/licenses/mit-license.php
 *
 */

#include <windows.h>
#include <wce_stdio.h>
#include <wce_stdlib.h>

/*******************************************************************************
* wceex_tmpnam - constructs and returns a valid file name that does not refer to
*                any existing file
*
* Description:
*
*   This function constructs and returns a valid file name that does not refer to
*   any existing file. If the result argument is a null pointer, the return value
*   is a pointer to an internal static string, which might be modified by subsequent
*   calls and therefore makes this function non-reentrant. Otherwise, the result
*   argument should be a pointer to an array of at least L_tmpnam characters, and
*   the result is written into that array.
*
*   It is possible for tmpnam to fail if you call it too many times without removing
*   previously-created files. This is because the limited length of the temporary file
*   names gives room for only a finite number of different names. If tmpnam fails it
*   returns a null pointer.
*
*
* Reference:
*
*   The GNU C Library Manual
* 
*******************************************************************************/

char * wceex_tmpnam(char * result)
{
	char *filename = NULL;
	wchar_t wpath[MAX_PATH+1] = {0};
	wchar_t wfilename[MAX_PATH+1] = {0};
	static char buf[L_tmpnam+1] = {0};

	GetTempPath(MAX_PATH, wpath);
	GetTempFileName(wpath, L"_", 0, wfilename);
	filename = wceex_wcstombs(wfilename);

	if (result == NULL)
		result = buf;

	_snprintf(result, L_tmpnam, "%s", filename);
	return result;
}