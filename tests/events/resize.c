// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#include "resize.h"
#include "../lib/malloc_dynarr.h"
#include <tralloc/tree.h>
#include <tralloc/events.h>

typedef struct resize_info_t {
    tralloc_chunk * chunk;
    size_t old_length;
} resize_info;

static
malloc_dynarr * malloc_history()
{
    malloc_dynarr * tralloc_history = malloc_dynarr_new ( 8 );
    if ( tralloc_history == NULL ) {
        return NULL;
    }
    malloc_dynarr_set_free_item ( tralloc_history, free );
    _tralloc_set_user_data ( tralloc_history );
    return tralloc_history;
}

static
void free_history ( malloc_dynarr * tralloc_history )
{
    malloc_dynarr_free ( tralloc_history );
}

static
uint8_t on_resize ( void * user_data, tralloc_chunk * chunk, size_t old_length )
{
    malloc_dynarr * tralloc_history = ( malloc_dynarr * ) user_data;
    resize_info * info = malloc ( sizeof ( resize_info ) );
    if ( info == NULL ) {
        return 1;
    }
    info->chunk      = chunk;
    info->old_length = old_length;
    if ( malloc_dynarr_append ( tralloc_history, info ) != 0 ) {
        free ( info );
        return 2;
    }
    return 0;
}

bool test_resize ( const tralloc_context * root )
{
    malloc_dynarr * tralloc_history = malloc_history();
    if ( tralloc_history == NULL ) {
        return false;
    }
    _tralloc_set_callback ( NULL, on_resize, NULL, NULL );

    int * a   = tralloc ( root, sizeof ( int ) * 2 );
    char * b  = tralloc ( root, sizeof ( char ) * 3 );
    float * c = tralloc ( a,    sizeof ( float ) * 4 );

    if ( a == NULL || b == NULL || c == NULL ) {
        tralloc_free ( a );
        tralloc_free ( b );
        free_history ( tralloc_history );
        return false;
    }

    b = tralloc_realloc ( b, sizeof ( char ) * 8 );
    a = tralloc_realloc ( a, sizeof ( int ) * 9 );
    c = tralloc_realloc ( c, sizeof ( float ) * 10 );

    if ( a == NULL || b == NULL || c == NULL ) {
        tralloc_free ( a );
        tralloc_free ( b );
        free_history ( tralloc_history );
        return false;
    }

    tralloc_chunk * a_chunk = _tralloc_chunk_from_context ( a );
    tralloc_chunk * b_chunk = _tralloc_chunk_from_context ( b );
    tralloc_chunk * c_chunk = _tralloc_chunk_from_context ( c );
    resize_info * info;

    if (
        malloc_dynarr_get_length ( tralloc_history ) != 3 ||
        ( info = malloc_dynarr_get ( tralloc_history, 0 ) ) == NULL ||
        info->chunk != b_chunk || info->old_length != sizeof ( char ) * 3 || info->chunk->length != sizeof ( char ) * 8 ||
        ( info = malloc_dynarr_get ( tralloc_history, 1 ) ) == NULL ||
        info->chunk != a_chunk || info->old_length != sizeof ( int ) * 2 || info->chunk->length != sizeof ( int ) * 9 ||
        ( info = malloc_dynarr_get ( tralloc_history, 2 ) ) == NULL ||
        info->chunk != c_chunk || info->old_length != sizeof ( float ) * 4 || info->chunk->length != sizeof ( float ) * 10
    ) {
        tralloc_free ( a );
        tralloc_free ( b );
        free_history ( tralloc_history );
        return false;
    }

    if (
        tralloc_free ( a ) != 0 ||
        tralloc_free ( b ) != 0
    ) {
        free_history ( tralloc_history );
        return false;
    }

    free_history ( tralloc_history );
    return true;
}