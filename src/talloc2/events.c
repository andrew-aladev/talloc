// This file is part of talloc2. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// talloc2 is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// talloc2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with talloc2. If not, see <http://www.gnu.org/licenses/>.

#include "events.h"

#ifdef TALLOC_EVENTS

#ifdef TALLOC_DEBUG
extern inline
void talloc_set_callback ( talloc_callback on_add, talloc_callback on_update, talloc_callback on_move, talloc_callback on_del );
#endif

extern inline
uint8_t talloc_on_add ( talloc_chunk * chunk, size_t length, uint8_t mode );

extern inline
uint8_t talloc_on_update ( talloc_chunk * chunk, size_t length );

extern inline
uint8_t talloc_on_move ( talloc_chunk * child );

extern inline
uint8_t talloc_on_del ( talloc_chunk * chunk );

#endif