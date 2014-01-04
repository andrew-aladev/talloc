// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRALLOC_TREE_COMMON_H
#define TRALLOC_TREE_COMMON_H

#include "../common.h"

#if defined(TRALLOC_DEBUG)
#include "../events.h"
#endif


_tralloc_chunk * _tralloc_realloc ( _tralloc_chunk * chunk, size_t length );

inline
tralloc_context * tralloc_realloc ( tralloc_context * chunk_context, size_t length )
{
    if ( chunk_context == NULL ) {
        return NULL;
    }
    _tralloc_chunk * chunk = _tralloc_realloc ( _tralloc_chunk_from_context ( chunk_context ), length );
    if ( chunk == NULL ) {
        return NULL;
    }
    return _tralloc_context_from_chunk ( chunk );
}


uint8_t tralloc_move ( tralloc_context * child_context, tralloc_context * parent_context );


inline
void _tralloc_set_child_chunk ( _tralloc_chunk * parent, _tralloc_chunk * child )
{
    _tralloc_chunk * parent_first_child = parent->first_child;

    child->parent = parent;
    if ( parent_first_child != NULL ) {
        parent_first_child->prev = child;
        child->next = parent_first_child;
        child->prev = NULL;
    } else {
        child->next = NULL;
        child->prev = NULL;
    }
    parent->first_child = child;
}

inline
uint8_t _tralloc_add_chunk ( tralloc_context * parent_context, _tralloc_chunk * child )
{
    child->first_child = NULL;

    if ( parent_context != NULL ) {
        _tralloc_chunk * parent = _tralloc_chunk_from_context ( parent_context );
        _tralloc_set_child_chunk ( parent, child );
    } else {
        child->parent = NULL;
        child->prev   = NULL;
        child->next   = NULL;
    }

#if defined(TRALLOC_DEBUG)
    return _tralloc_on_add ( child );
#else
    return 0;
#endif

}

inline
void _tralloc_detach_chunk ( _tralloc_chunk * chunk )
{
    _tralloc_chunk * prev   = chunk->prev;
    _tralloc_chunk * next   = chunk->next;
    _tralloc_chunk * parent = chunk->parent;

    if ( prev != NULL ) {
        if ( next != NULL ) {
            prev->next = next;
            next->prev = prev;
        } else {
            prev->next = NULL;
        }
    } else {
        if ( next != NULL ) {
            next->prev = NULL;
        }
        if ( parent != NULL ) {
            parent->first_child = next;
        }
    }

    chunk->parent = NULL;
}


uint8_t _tralloc_free_chunk ( _tralloc_chunk * chunk );

inline
uint8_t _tralloc_free_chunk_children ( _tralloc_chunk * chunk )
{
    uint8_t result, error  = 0;
    _tralloc_chunk * child = chunk->first_child;

    _tralloc_chunk * next_child;
    while ( child != NULL ) {
        next_child = child->next;
        if ( ( result = _tralloc_free_chunk ( child ) ) != 0 ) {
            error = result;
        }
        child = next_child;
    }

    return error;
}

inline
uint8_t tralloc_free ( tralloc_context * chunk_context )
{
    if ( chunk_context == NULL ) {
        return 0;
    }
    _tralloc_chunk * chunk = _tralloc_chunk_from_context ( chunk_context );
    _tralloc_detach_chunk ( chunk );
    return _tralloc_free_chunk ( chunk );
}


#endif