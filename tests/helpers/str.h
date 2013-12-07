// This file is part of talloc2. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// talloc2 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// talloc2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with talloc2. If not, see <http://www.gnu.org/licenses/>.

#include <talloc2/helpers.h>
#include <stdbool.h>

bool test_str ( void * ctx )
{
    char * str  = "Viktor Tsoi Star Called Sun";
    char * full = talloc_strdup ( ctx, str );
    if ( full == NULL ) {
        return false;
    }

    char * walk = str;
    char * part_1 = talloc_strndup ( full, walk, 6 );
    walk += 7;
    char * part_2 = talloc_strndup ( full, walk, 4 );
    walk += 5;
    char * part_3 = talloc_strndup ( full, walk, 4 );
    walk += 5;
    char * part_4 = talloc_strndup ( full, walk, 6 );
    walk += 7;
    char * part_5 = talloc_strndup ( full, walk, 3 );
    if (
        ! (
            part_1 != NULL &&
            part_2 != NULL &&
            part_3 != NULL &&
            part_4 != NULL &&
            part_5 != NULL &&
            !strcmp ( full, str )        &&
            !strcmp ( part_1, "Viktor" ) &&
            !strcmp ( part_2, "Tsoi" )   &&
            !strcmp ( part_3, "Star" )   &&
            !strcmp ( part_4, "Called" ) &&
            !strcmp ( part_5, "Sun" )
        )
    ) {
        talloc_free ( full );
        return false;
    }

    if ( talloc_free ( full ) != 0 ) {
        return false;
    }
    return true;
}