// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#include <tralloc/tests/tree/common.h>
#include <tralloc/tree.h>


int test_tree ( tralloc_context * ctx )
{
    test_tree_data * tr;
    if ( tralloc_new ( ctx, ( tralloc_context ** ) &tr, sizeof ( test_tree_data ) ) != 0 ) {
        return 1;
    }
    if ( !test_tree_alloc ( tr ) ) {
        return 2;
    }
    if ( !test_tree_move ( tr ) ) {
        return 3;
    }
    if ( !test_tree_errors ( tr ) ) {
        tralloc_free ( tr );
        return 4;
    }
    if ( !test_tree_move_and_resize ( tr ) ) {
        tralloc_free ( tr );
        return 5;
    }
    if ( !test_tree_free_subtree ( tr ) ) {
        tralloc_free ( tr );
        return 6;
    }
    if ( tralloc_free ( tr ) != 0 ) {
        return 7;
    }
    return 0;
}
