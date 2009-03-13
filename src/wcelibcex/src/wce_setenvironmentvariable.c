/*
 * $Id: wce_setenvironmentvariable.c 62 2007-01-17 00:04:39Z mloskot $
 *
 * Defines SetEnvironmentVariable() function.
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
#include <assert.h>
#include "wce_stdlib.h"

/* NOTE: The same private variable is redefined in
 *       file wce_getenvironmentvariable.c
 */
static const wchar_t lpGlobalEnvSubKey[] = _T("Software\\WCELIBCEX\\Environment");

BOOL wceex_SetEnvironmentVariable(LPCWSTR lpName, LPCWSTR lpValue)
{   
    LONG   nRet;
    HKEY   hKey;
    LPWSTR lpClass = _T("");
    LPBYTE lpData = NULL;
    DWORD  cbData = 0;
    DWORD  dwType = REG_SZ;
    DWORD  dwDisposition = 0;

    cbData = ((wcslen(lpValue) + 1) * sizeof(*lpValue));
    
    assert(wcslen(lpName) <= REG_VALUE_NAME_SIZE_MAX);
    assert(cbData <= REG_VALUE_SIZE_MAX);

    nRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpGlobalEnvSubKey, 0, lpClass,
                          REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, &dwDisposition);
	if (ERROR_SUCCESS != nRet)
	{
		return FALSE;
	}
 
    lpData = (LPBYTE)lpValue;
    nRet = RegSetValueEx(hKey, lpName, 0, dwType, lpData, cbData); 
    RegCloseKey(hKey);
	
	return (ERROR_SUCCESS == nRet);
}
