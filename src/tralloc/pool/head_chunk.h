// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRALLOC_POOL_HEAD_CHUNK_H
#define TRALLOC_POOL_HEAD_CHUNK_H

#include "../tree/common.h"
#include <stdbool.h>
#include <string.h>


inline
tralloc_error _tralloc_pool_new_chunk ( _tralloc_chunk * chunk, void * memory, size_t length )
{
    _tralloc_pool * pool = _tralloc_get_pool_from_chunk ( chunk );
    pool->first_child    = NULL;
    pool->autofree       = false;

    if ( length < sizeof ( _tralloc_pool_fragment ) ) {
        pool->max_fragment = NULL;
        return 0;
    }

    _tralloc_pool_fragment * fragment = memory;
    fragment->prev       = NULL;
    fragment->next       = NULL;
    fragment->prev_child = NULL;
    fragment->next_child = NULL;
    fragment->length     = length;

    pool->max_fragment = fragment;

    return 0;
}

inline
bool _tralloc_pool_can_alloc ( _tralloc_pool * pool, size_t length )
{
    _tralloc_pool_fragment * fragment = pool->max_fragment;
    if ( fragment == NULL || length > fragment->length ) {
        return false;
    }
    return true;
}

inline
void _tralloc_pool_attach_fragment ( _tralloc_pool * pool, _tralloc_pool_fragment * fragment, _tralloc_pool_fragment * prev, _tralloc_pool_fragment * next )
{
    fragment->prev = prev;
    fragment->next = next;

    if ( prev != NULL ) {
        prev->next = fragment;
    } else {
        pool->max_fragment = fragment;
    }
    if ( next != NULL ) {
        next->prev = fragment;
    }
}

inline
void _tralloc_pool_detach_fragment ( _tralloc_pool * pool, _tralloc_pool_fragment * fragment )
{
    _tralloc_pool_fragment * prev = fragment->prev;
    _tralloc_pool_fragment * next = fragment->next;

    if ( prev != NULL ) {
        prev->next = next;
    } else {
        pool->max_fragment = next;
    }
    if ( next != NULL ) {
        next->prev = prev;
    }
}

inline
void _tralloc_pool_new_fragment_insert_after ( _tralloc_pool * pool, _tralloc_pool_fragment * new_fragment, _tralloc_pool_fragment * prev_fragment, _tralloc_pool_fragment * next_fragment )
{
    size_t length = new_fragment->length;
    while ( next_fragment != NULL && length < next_fragment->length ) {
        prev_fragment = next_fragment;
        next_fragment = next_fragment->next;
    }

    _tralloc_pool_attach_fragment ( pool, new_fragment, prev_fragment, next_fragment );
}

inline
void _tralloc_pool_alloc ( _tralloc_pool * pool, void ** memory, size_t length, bool zero, _tralloc_pool_child ** prev_pool_child, _tralloc_pool_child ** next_pool_child )
{
    _tralloc_pool_fragment * fragment = pool->max_fragment;
    _tralloc_pool_detach_fragment ( pool, fragment );

    _tralloc_pool_fragment * prev_fragment = fragment->prev;
    _tralloc_pool_fragment * next_fragment = fragment->next;
    size_t new_fragment_length = fragment->length - length;

    * prev_pool_child = fragment->prev_child;
    * next_pool_child = fragment->next_child;
    if ( zero ) {
        memset ( fragment, 0, length );
    }
    * memory = fragment;

    if ( new_fragment_length < sizeof ( _tralloc_pool_fragment ) ) {
        return;
    }

    _tralloc_pool_fragment * new_fragment = fragment + length;
    new_fragment->prev_child = ( _tralloc_pool_child * ) fragment;
    new_fragment->length     = new_fragment_length;
    _tralloc_pool_new_fragment_insert_after ( pool, new_fragment, prev_fragment, next_fragment );
}

inline
bool _tralloc_pool_try_free_chunk ( _tralloc_chunk * chunk )
{
    _tralloc_pool * pool = _tralloc_get_pool_from_chunk ( chunk );
    if ( pool->first_child == NULL ) {
        return true;
    }
    _tralloc_detach_chunk ( chunk );
    pool->autofree = true;
    return false;
}


#endif