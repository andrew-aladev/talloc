// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#if !defined ( TRALLOC_POOL_POOL_CHILD_DATA_H )
#define TRALLOC_POOL_POOL_CHILD_DATA_H

#include "../extensions.h"

#undef _TRALLOC_INLINE
#if defined ( _TRALLOC_INCLUDED_FROM_POOL_POOL_CHILD_DATA_C )
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_OBJECT
#else
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_HEADER
#endif


// "pool_child" should be the first in the stack of extensions.
// This slight limitation makes fragment's calculation much easier and descreases the total amount of pool's memory overhead.

typedef struct _tralloc_pool_type       _tralloc_pool;
typedef struct _tralloc_pool_child_type _tralloc_pool_child;

struct _tralloc_pool_child_type {
    _tralloc_pool * pool;
    _tralloc_pool_child * prev;
    _tralloc_pool_child * next;
    size_t length;
};

void                  _tralloc_pool_child_new    ( _tralloc_pool_child * pool_child, _tralloc_pool * pool, size_t length, _tralloc_pool_child * prev, _tralloc_pool_child * next );
_tralloc_pool_child * _tralloc_pool_child_resize ( _tralloc_pool_child * pool_child, size_t target_length );
tralloc_error         _tralloc_pool_child_free   ( _tralloc_pool_child * pool_child );

_TRALLOC_INLINE
_tralloc_pool_child * _tralloc_chunk_get_pool_child ( _tralloc_chunk * chunk )
{
    return ( _tralloc_pool_child * ) ( ( uintptr_t ) chunk - _tralloc_extensions_get_offset_for_extension ( chunk->extensions, TRALLOC_EXTENSION_POOL_CHILD ) );
}


#endif