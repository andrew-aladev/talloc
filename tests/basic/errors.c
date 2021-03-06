// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#include "common.h"
#include <tralloc/tree.h>


tralloc_bool test_basic_errors ( tralloc_context * ctx )
{
    if (
        tralloc      ( NULL, NULL, 0 ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_zero ( NULL, NULL, 0 ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_new  ( NULL, NULL )    != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL
    ) {
        return TRALLOC_FALSE;
    }

#   if defined(TRALLOC_EXTENSIONS)
    if (
        tralloc_with_extensions      ( NULL, NULL, 0, 0 ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_zero_with_extensions ( NULL, NULL, 0, 0 ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_with_extensions_new  ( NULL, NULL, 0 )    != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL
    ) {
        return TRALLOC_FALSE;
    }
#   endif

    if (
        tralloc_move ( NULL, NULL ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_move ( ctx, ctx )   != TRALLOC_ERROR_CHILD_EQUALS_PARENT
    ) {
        return TRALLOC_FALSE;
    }

    tralloc_context * test;
    if (
        tralloc_new  ( ctx, &test ) != 0 ||
        tralloc_move ( test, ctx )  != TRALLOC_ERROR_CHILD_HAS_SAME_PARENT ||
        tralloc_move ( test, NULL ) != 0 ||
        tralloc_move ( test, NULL ) != TRALLOC_ERROR_CHILD_HAS_SAME_PARENT ||
        tralloc_move ( test, ctx )  != 0
    ) {
        return TRALLOC_FALSE;
    }

    tralloc_context * empty = NULL;
    if (
        tralloc_realloc ( NULL, 0 )   != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ||
        tralloc_realloc ( &empty, 0 ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL
    ) {
        return TRALLOC_FALSE;
    }

    if ( tralloc_free ( NULL ) != TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL ) {
        return TRALLOC_FALSE;
    }

    if ( tralloc_free ( test ) != 0 ) {
        return TRALLOC_FALSE;
    }
    return TRALLOC_TRUE;
}
