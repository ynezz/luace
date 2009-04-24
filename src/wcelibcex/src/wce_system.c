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
#include "wce_errno.h"

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
	SHELLEXECUTEINFO sei;
	unsigned long exit_code = 0;
	BOOL ret;
	wchar_t *wpath;
	wchar_t *wfile;
	wchar_t *wdir;
	wchar_t *wparams;
	wchar_t stopch;

	if(command == 0) {
		return -1;
	}

	// trim front
	while(*command == ' ' || *command == '\t') {
		command++;
	}

	// if starting char is a quote then look for end quote
	if(*command == '\"') {
		command++;
		stopch = L'\"';
	} else {
		stopch = L' ';
	}

	// create wide version of command
	wpath = wceex_mbstowcs(command);

	// find the end of the path and start of parameters
	wparams = wcschr(wpath, stopch);
	if(wparams != NULL) {
		*wparams = L'\0';
		wparams++;
	}

	// find the filename
	wfile = wcsrchr(wpath, L'\\');
	if(wfile != NULL) {
		wfile++;
	} else {
		wfile = wpath;
	}

	// copy the directory
	wdir = (wchar_t*) malloc((wfile-wpath + 1) * sizeof(wchar_t));
	wcsncpy(wdir, wpath, wfile-wpath);
	wdir[wfile-wpath] = L'\0';

	// set up call
	memset(&sei, 0, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.lpFile = wpath;
	sei.lpParameters = wparams;
	sei.lpDirectory = wdir;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.nShow = SW_SHOWNORMAL;

	// call now
	ret = ShellExecuteEx(&sei);

	if(ret) {
		// wait for process to exit
		WaitForSingleObject(sei.hProcess, INFINITE);
		GetExitCodeProcess(sei.hProcess, &exit_code);
		CloseHandle(sei.hProcess);
	} else {
		exit_code = -1;
	}

	free(wdir);
	free(wpath);

	return exit_code;
}
