/*
 * $Id$
 *
 * Defines freopen() function.
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

#include <stdio.h>

/*******************************************************************************
* wceex_freopen - Reopen stream with different file or mode
*
* Description:
*
*   This function is like a combination of fclose and fopen. It first closes the
*   stream referred to by stream, ignoring any errors that are detected in the
*   process. (Because errors are ignored, you should not use freopen on an output
*   stream if you have actually done any output using the stream.) Then the file
*   named by filename is opened with mode opentype as for fopen, and associated
*   with the same stream object stream.
*
*   If the operation fails, a null pointer is returned; otherwise, freopen returns
*   stream.
*
*   freopen has traditionally been used to connect a standard stream such as stdin
*   with a file of your own choice. This is useful in programs in which use of a
*   standard stream for certain purposes is hard-coded. In the GNU C library, you
*   can simply close the standard streams and open new ones with fopen. But other
*   systems lack this ability, so using freopen is more portable. 
*
* Reference:
*
*   The GNU C Library Manual
* 
*******************************************************************************/
FILE * wceex_freopen(const char *filename, const char *opentype, FILE *stream)
{
	if (stream == NULL || filename == NULL || opentype == NULL)
		return NULL;

	fflush(stream);
	fclose(stream);

	return fopen(filename, opentype);
}
