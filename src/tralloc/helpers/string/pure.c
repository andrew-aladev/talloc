// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#define _TRALLOC_HELPERS_STRING_PURE_INCLUDED_FROM_OBJECT
#include "pure.h"
#include "../../tree.h"
#include <stdio.h>


tralloc_error _tralloc_strndup ( tralloc_context * parent_context, char ** child_context, const char * str, size_t length )
{
    tralloc_error result = tralloc ( parent_context, ( tralloc_context ** ) child_context, sizeof ( char ) * ( length + 1 ) );
    if ( result != 0 ) {
        return result;
    }
    memmove ( * child_context, str, length );
    ( * child_context ) [length] = '\0';
    return 0;
}

tralloc_error tralloc_vasprintf ( tralloc_context * parent_context, char ** child_context, const char * format, va_list arguments )
{
    if ( child_context == NULL ) {
        return TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL;
    }

    va_list arguments_copy;

    va_copy ( arguments_copy, arguments );
    int predicted_length = vsnprintf ( NULL, 0, format, arguments_copy );
    va_end ( arguments_copy );
    if ( predicted_length <= 0 ) {
        return TRALLOC_ERROR_PRINTF_FAILED;
    }
    predicted_length++;

    tralloc_error result = tralloc ( parent_context, ( tralloc_context ** ) child_context, sizeof ( char ) * predicted_length );
    if ( result != 0 ) {
        return result;
    }
    va_copy ( arguments_copy, arguments );
    int length = vsnprintf ( * child_context, predicted_length, format, arguments_copy );
    va_end ( arguments_copy );
    if ( length + 1 != predicted_length ) {
        tralloc_free ( * child_context );
        return TRALLOC_ERROR_PRINTF_FAILED;
    }
    return 0;
}

tralloc_error tralloc_asprintf ( tralloc_context * parent_context, char ** child_context, const char * format, ... )
{
    va_list arguments;
    va_start ( arguments, format );
    tralloc_error result = tralloc_vasprintf ( parent_context, child_context, format, arguments );
    va_end ( arguments );
    return result;
}
