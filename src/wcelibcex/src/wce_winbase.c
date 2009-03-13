/*
 * $Id: wce_winbase.c 74 2009-02-04 13:45:23Z mloskot $
 *
 * Defines GetStdHandle() function with dummy implementation.
 *
 * Created by Stéphane Dunand (sdunand@sirap.fr)
 *
 * Copyright (c) 2006 Stéphane Dunand
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

#include <wce_winbase.h>
#include <wce_stdlib.h>

HANDLE GetStdHandle(DWORD nStdHandle)
{
    (void)nStdHandle;

	return NULL;
}

LPWSTR wceex_lstrcpyn( LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength )
{
    lpString1[0] = '\0';
    wcsncat( lpString1, lpString2, iMaxLength - 1 );
    return lpString1;
}

HMODULE wceex_LoadLibraryA(const char *filename)
{
	wchar_t *wfilename = wceex_mbstowcs(filename);
	return LoadLibrary(wfilename);
}

DWORD wceex_FormatMessageA(unsigned long dwFlags, LPCVOID lpSource, DWORD dwMessageId,
		     DWORD dwLanguageId, LPSTR lpBuffer, DWORD nSize, va_list *Arguments)
{
	DWORD ret = 0;
	wchar_t *wbuf = wceex_mbstowcs(lpBuffer);

	ret = FormatMessage(dwFlags, lpSource, dwMessageId, dwLanguageId, wbuf, nSize, Arguments);
	return ret;
}

DWORD wceex_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	DWORD ret = 0;
	wchar_t *wbuf = wceex_mbstowcs(lpFilename);

	ret = GetModuleFileName(hModule, wbuf, nSize);
	return ret;
}