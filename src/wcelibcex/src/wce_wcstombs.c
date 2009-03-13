/*
 * $Id: wce_wcstombs.c 62 2007-01-17 00:04:39Z mloskot $
 *
 * Defines wceex_wcstombs() helper function.
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

char* wceex_wcstombs(const wchar_t* wcstr)
{
    size_t wcs_size = 0;
    size_t mbs_size = 0;
	char*  mbsbuf = NULL;

    /* Calculate required size in wide characters, including null character. */
	wcs_size = WideCharToMultiByte(CP_ACP, 0, wcstr, -1, NULL, 0, NULL, NULL);
    assert(0 != wcs_size);

    mbsbuf = (char*)malloc(sizeof(char) * wcs_size);
    if (NULL != mbsbuf)
    {
        assert((void*)wcstr != (void*)mbsbuf); /* A bit paranoid pre-condition check. */

        memset(mbsbuf, 0, sizeof(char) * wcs_size);
        mbs_size = WideCharToMultiByte(CP_ACP, 0, wcstr, -1, mbsbuf, wcs_size, NULL, NULL);

        assert(mbs_size == wcs_size);
    }

	return mbsbuf;
}
