/*
 * $Id$
 *
 * Defines system() function.
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
#include "wce_stdlib.h"

BOOL wceex_CreateProcessA(LPCSTR lpApplicationName, LPCSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			  LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
			  LPVOID lpEnvironment, LPSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo,
			  LPPROCESS_INFORMATION lpProcessInformation)
{
	wchar_t *wapp = wceex_mbstowcs(lpApplicationName);
	wchar_t *wcmd = wceex_mbstowcs(lpCommandLine);
	wchar_t *wcwd = wceex_mbstowcs(lpCurrentDirectory);

	return CreateProcess(wapp, wcmd, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags,
			    lpEnvironment, wcwd, lpStartupInfo, lpProcessInformation);
}

/*******************************************************************************
* wceex_system - Executes command as a shell command
*
* Description:
*
*   This function executes command as a shell command. In the GNU C library, it
*   always uses the default shell sh to run the command. In particular, it searches
*   the directories in PATH to find programs to execute. The return value is -1 if
*   it wasn't possible to create the shell process, and otherwise is the status of
*   the shell process. See Process Completion, for details on how this status code
*   can be interpreted.
*
*   If the command argument is a null pointer, a return value of zero indicates that
*   no command processor is available.
*
*
* Reference:
*
*   The GNU C Library Manual
* 
*******************************************************************************/
int wceex_system(const char *command)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	unsigned long exit_code = 0;
	BOOL ret;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	ret = wceex_CreateProcessA(command, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (ret == FALSE)
		return -1;

	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(pi.hProcess, &exit_code);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return exit_code;
}
