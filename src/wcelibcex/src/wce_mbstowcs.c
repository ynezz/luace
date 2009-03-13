/*
 * $Id: wce_mbstowcs.c 62 2007-01-17 00:04:39Z mloskot $
 *
 * Defines wceex_mbstowcs() helper function.
 *
 * Created by Mateusz Loskot (mateusz@loskot.net)
 *
 * Copyright (c) 2006 Mateusz Loskot
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
#include <stdlib.h> /* malloc() */
#include <string.h> /* memset() */
#include <assert.h>

wchar_t* wceex_mbstowcs(const char* mbstr)
{
	size_t   mbs_size = 0;
    size_t   wcs_size = 0;
	wchar_t* wcsbuf = NULL;

    /* Calculate required size in one-byte characters, including null character. */
	mbs_size = MultiByteToWideChar(CP_ACP, 0, mbstr, -1, NULL, 0);
    assert(0 != mbs_size);

	wcsbuf = (wchar_t*)malloc(sizeof(wchar_t) * mbs_size);
    if (NULL != wcsbuf)
    {
        assert((void*)mbstr != (void*)wcsbuf); /* A bit paranoid pre-condition check. */

        memset(wcsbuf, 0, sizeof(wchar_t) * mbs_size);
        wcs_size = MultiByteToWideChar(CP_ACP, 0, mbstr, -1, wcsbuf, mbs_size);

        assert(wcs_size <= mbs_size);
    }

	return wcsbuf;
}
