/*
 * $Id: wce_getenvironmentvariable.c 62 2007-01-17 00:04:39Z mloskot $
 *
 * Defines GetEnvironmentVariable() function.
 *
 * Created by Mateusz Loskot (mloskot@loskot.net)
 *
 * Copyright (c) 2006 Mateusz Loskot (mloskot@loskot.net)
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
#include <string.h> /* memset() */
#include <assert.h>
#include "wce_stdlib.h"

/* NOTE: The same private variable is redefined in
 *       file wce_setenvironmentvariable.c
 */
static const wchar_t lpGlobalEnvSubKey[] = _T("Software\\WCELIBCEX\\Environment");

DWORD wceex_GetEnvironmentVariable(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize)
{   
    LONG   nRet;
    HKEY   hKey;
	LPWSTR lpValueName = NULL;
    LPBYTE lpData = NULL;
    DWORD  dwType = REG_SZ;
    DWORD  cbMaxSubKeyLen = 0;
    DWORD  cbMaxValueNameLen = 0;
    DWORD  cbMaxValueLen = 0;
    TCHAR szBuf[REG_VALUE_SIZE_MAX];

    assert(nSize <= REG_VALUE_SIZE_MAX);
    assert(wcslen(lpName) <= REG_VALUE_NAME_SIZE_MAX);

    /* nSize - length of output buffer in characters. */
    memset(szBuf, 0, REG_VALUE_SIZE_MAX);
    memset(lpBuffer, 0, nSize * sizeof(wchar_t));

	nRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpGlobalEnvSubKey, 0, 0, &hKey);
	if (ERROR_SUCCESS != nRet)
	{
		wcsncpy(lpBuffer, _T(""), 2);
		return 0;
	}

    nRet = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, &cbMaxSubKeyLen,
                          NULL, NULL, &cbMaxValueNameLen, &cbMaxValueLen,
                          NULL, NULL);
	if (ERROR_SUCCESS != nRet)
	{
		wcsncpy(lpBuffer, _T(""), 2);
		return 0;
    }

    lpData = (LPBYTE)szBuf;
	nRet = RegQueryValueEx(hKey, lpName, NULL, &dwType, lpData, &cbMaxValueLen);
	RegCloseKey(hKey);
	if (ERROR_SUCCESS != nRet)
	{
		wcsncpy(lpBuffer, _T(""), 2);
		return 0;
	}

    /* cbMaxValueLen - length, in bytes, of the longest data component,
     * including NULL character
     */
    wcsncpy(lpBuffer, szBuf, cbMaxValueLen - 1);
    cbMaxValueLen = wcslen(szBuf);

	return cbMaxValueLen;
}
