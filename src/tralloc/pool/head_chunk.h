// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRALLOC_POOL_HEAD_CHUNK_H
#define TRALLOC_POOL_HEAD_CHUNK_H

#include "common.h"
#include "../macro.h"
#include "fragment.h"

#undef _TRALLOC_INLINE
#ifdef _TRALLOC_POOL_HEAD_CHUNK_INCLUDED_FROM_OBJECT
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_OBJECT
#else
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_HEADER
#endif


void _tralloc_pool_new_chunk ( _tralloc_chunk * chunk, size_t length );

_TRALLOC_INLINE
tralloc_bool _tralloc_pool_can_alloc ( _tralloc_pool * pool, size_t length )
{
    return _tralloc_pool_fragment_can_alloc ( pool->max_fragment, length );
}

void _tralloc_pool_alloc ( _tralloc_pool * pool, void ** memory, size_t length, tralloc_bool zero, _tralloc_pool_child ** prev_pool_child, _tralloc_pool_child ** next_pool_child );

_TRALLOC_INLINE
tralloc_bool _tralloc_pool_can_free_chunk ( _tralloc_chunk * chunk )
{
    _tralloc_pool * pool = _tralloc_get_pool_from_chunk ( chunk );
    if ( pool->first_child == NULL ) {
        return TRALLOC_TRUE;
    } else {
        pool->autofree = TRALLOC_TRUE;
        return TRALLOC_FALSE;
    }
}

_TRALLOC_INLINE
tralloc_bool _tralloc_pool_can_free_chunk_children ( _tralloc_chunk * _TRALLOC_UNUSED ( chunk ) )
{
    return TRALLOC_TRUE;
}


#endif
