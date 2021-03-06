// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRALLOC_REFERENCE_CHUNK_H
#define TRALLOC_REFERENCE_CHUNK_H

#include "common.h"

#undef _TRALLOC_INLINE
#ifdef _TRALLOC_REFERENCE_CHUNK_INCLUDED_FROM_OBJECT
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_OBJECT
#else
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_HEADER
#endif


_TRALLOC_INLINE
void _tralloc_reference_new_chunk ( _tralloc_chunk * chunk )
{
    _tralloc_reference * reference = _tralloc_get_reference_from_chunk ( chunk );
    reference->references = NULL;
    reference->next       = NULL;
    reference->prev       = NULL;
}

void          _tralloc_reference_update_chunk ( _tralloc_chunk * reference_chunk );
tralloc_error _tralloc_reference_free_chunk   ( _tralloc_chunk * chunk );


#endif
