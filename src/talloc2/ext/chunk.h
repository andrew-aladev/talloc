// This file is part of talloc2. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// talloc2 is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// talloc2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with talloc2. If not, see <http://www.gnu.org/licenses/>.

#ifndef TALLOC_EXT_CHUNK_H
#define TALLOC_EXT_CHUNK_H

#include <stdlib.h>

#include "../common.h"

#if defined(TALLOC_EXT_DESTRUCTOR)
#include "destructor.h"
#endif

#if defined(TALLOC_REFERENCE)
#include "../reference/chunk.h"
#endif

inline
talloc_chunk * talloc_ext_chunk_malloc ( size_t length )
{
    talloc_ext * ext = malloc ( sizeof ( talloc_ext ) + sizeof ( talloc_chunk ) + length );
    if ( ext == NULL ) {
        return NULL;
    }

#if defined(TALLOC_EXT_DESTRUCTOR)
    ext->first_destructor = NULL;
#endif

    talloc_chunk * chunk = talloc_chunk_from_ext ( ext );

#if defined(TALLOC_REFERENCE)
    chunk->mode = TALLOC_MODE_EXT;
#endif

    return chunk;
}

inline
talloc_chunk * talloc_ext_chunk_calloc ( size_t length )
{
    talloc_ext * ext = calloc ( 1, sizeof ( talloc_ext ) + sizeof ( talloc_chunk ) + length );
    if ( ext == NULL ) {
        return NULL;
    }

#if defined(TALLOC_EXT_DESTRUCTOR)
    ext->first_destructor = NULL;
#endif

    talloc_chunk * chunk = talloc_chunk_from_ext ( ext );

#if defined(TALLOC_REFERENCE)
    chunk->mode = TALLOC_MODE_EXT;
#endif

    return chunk;
}

inline
talloc_chunk * talloc_ext_chunk_realloc ( talloc_chunk * chunk, size_t length )
{
    talloc_ext * old_ext = talloc_ext_from_chunk ( chunk );
    talloc_ext * new_ext = realloc ( old_ext, sizeof ( talloc_ext ) + sizeof ( talloc_chunk ) + length );
    if ( new_ext == NULL ) {
        return NULL;
    }

    chunk = talloc_chunk_from_ext ( new_ext );

#if defined(TALLOC_REFERENCE)
    if ( old_ext != new_ext ) {
        // now pointers to old_ext is invalid
        // each pointer to old_ext should be replaced with new_ext
        talloc_update_references ( new_ext, chunk );
    }
#endif

    return chunk;
}

inline
uint8_t talloc_ext_chunk_free ( talloc_chunk * chunk )
{
    talloc_ext * ext = talloc_ext_from_chunk ( chunk );
    uint8_t result, error = 0;

#if defined(TALLOC_REFERENCE)
    ;
#endif

#if defined(TALLOC_EXT_DESTRUCTOR)
    result = talloc_destructor_free ( chunk, ext );
    if ( result != 0 ) {
        error = result;
    }
#endif

    free ( ext );
    return error;
}

#endif
