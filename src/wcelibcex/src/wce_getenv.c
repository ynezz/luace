/*
 * $Id: wce_getenv.c 56 2007-01-16 13:03:42Z mloskot $
 *
 * Defines getenv() function with dummy implementation.
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


/*******************************************************************************
* wceex_getenv - get value of an environment variable
*
* Description:
*
*   Implements the concept of environment variable for Windows CE platform.
*   The environment list is based n Windows CE Registry and dedicated subkey,
*   global for all users of WCELIBCEX library.
*
* Return:
*
*   Upon successful completion, getenv() shall return a pointer to a string
*   containing the value for the specified name.
*   If the specified name cannot be found in the environment,
*   a null pointer shall be returned.
*
*   The return value from getenv() points to global data are released and reallocated
*   by subsequent calls to getenv().
*   IMPORTANT: Unline in POSIX, user is allowed and even encouraged to free
*   returned value manually, by calling free() function.
*       
*******************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "wce_stdlib.h"

/*
 * Global environment buffer.
 *
 * TODO: mloskot - Who is supposed to free this value?
 *       Unlike in POSIX, should we allow/require users to free it?
 */
char* _environ = NULL;


char* wceex_getenv(const char* name)
{
    size_t var_size = 0;
    wchar_t* wcs_value = NULL;
    wchar_t* wcs_name = NULL;
    
    /*
     * TODO: mloskot - Do we need to check if environment is initialized?
     * For example, if Registry Key for WCELIBCEX exits, etc.
     */

    /* Free previously allocated environment value. */
    free(_environ);
    _environ = NULL;

    if (NULL != name);
    {
        wcs_value = (wchar_t*)malloc(REG_VALUE_SIZE_MAX * sizeof(wchar_t));
        if (NULL == wcs_value)
            return NULL;

        wcs_name = wceex_mbstowcs(name);

        /* Get environment from the Windows CE registry. */
        var_size = wceex_GetEnvironmentVariable(wcs_name, wcs_value, REG_VALUE_SIZE_MAX);
        if (0 != var_size)
        {
            /* Assign new value fetched from the registry. */
            _environ = wceex_wcstombs(wcs_value);
        }

        free(wcs_value);
        free(wcs_name);
    }

    return _environ;
}
