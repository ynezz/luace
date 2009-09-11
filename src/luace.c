/*
 *  $Id$
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

#include <wce_winbase.h>
#include <wce_stdlib.h>
#include <windows.h>

int main (int argc, char **argv);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR wcmdline, int show)
{
	unsigned long ret = 0;
	int argc = 0;
	char *args[MAX_PATH] = {0};
	char **argv = args;
	int len = 0;
	char *p = NULL;
	char *cmd = NULL;
	char quote = '\0';
	char path[MAX_PATH+1] = {0};

	ret = wceex_GetModuleFileNameA(NULL, path, MAX_PATH);
	if (ret > 0) {
		argv[0] = (char *) malloc(ret + 1);
		memset(argv[0], 0, ret);
		strncpy(argv[0], path, ret);
		len = 1;
	}

	p = cmd = wceex_wcstombs(wcmdline);

	/* parse commandline */
	while (*p) {

		/* remove whitespaces */
		while (*p) {
			if ((*p != ' ') && (*p != '\t'))
				break;
			p++;
		}

		/* quote character? */
		if ((*p == '"') || (*p== '\'')) {
			quote = *p;
			p++;
		}

		if (!*p)
			break;

		/* find begining of argument */
		argv[len++] = p;

		/* find end of argument */
		while (*p) {
			if (quote) {
				if (*p == quote) {
					quote = '\0';
					*p++ = 0;
					break;
				}
			} else {
				if ((*p == ' ') || (*p == '\t')) {
					*p++ = 0;
					break;
				}
			}
			p++;
		}
	}

	argc = len;
	ret = main(argc, argv);
	free(cmd);
	return ret;
}
