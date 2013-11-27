// This file is part of talloc2. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// talloc2 is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// talloc2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with talloc2. If not, see <http://www.gnu.org/licenses/>.

#ifndef TALLOC_REFERENCE_CHUNK_H
#define TALLOC_REFERENCE_CHUNK_H

#include "../ext/chunk.h"
#include <stdlib.h>

inline
talloc_chunk * talloc_chunk_from_reference ( void * memory )
{
    return ( talloc_chunk * ) ( ( uintptr_t ) memory + sizeof ( talloc_reference ) );
}

inline
talloc_reference * talloc_reference_from_chunk ( talloc_chunk * chunk )
{
    return ( talloc_reference * ) ( ( uintptr_t ) chunk - sizeof ( talloc_reference ) );
}

inline
talloc_chunk * talloc_reference_chunk_new ()
{
    void * memory = malloc ( sizeof ( talloc_reference ) + sizeof ( talloc_chunk ) );
    if ( memory == NULL ) {
        return NULL;
    } else {
        talloc_chunk * chunk = talloc_chunk_from_reference ( memory );
        chunk->mode          = TALLOC_MODE_REFERENCE;
        return chunk;
    }
}

inline
void talloc_reference_chunk_free ( talloc_chunk * chunk )
{
    talloc_reference * reference = talloc_reference_from_chunk ( chunk );
    talloc_ext * chunk_ext       = reference->chunk;

    talloc_reference * prev = reference->prev;
    talloc_reference * next = reference->next;
    if ( prev == NULL ) {
        chunk_ext->first_reference = next;
    } else {
        prev->next = next;
    }
    if ( next != NULL ) {
        next->prev = prev;
    }
    free ( reference );
}

#endif
