// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#include "file.h"

extern inline tralloc_error _tralloc_close ( tralloc_context * chunk_context, void * UNUSED ( user_data ) );

extern inline tralloc_error _tralloc_process_descriptor ( tralloc_context * parent_context, int ** descriptor_ptr, int descriptor, tralloc_extensions extensions );

extern inline tralloc_error tralloc_open_with_extensions      ( tralloc_context * parent_context, int ** descriptor_ptr, tralloc_extensions extensions, const char * path_name, int flags );
extern inline tralloc_error tralloc_open_mode_with_extensions ( tralloc_context * parent_context, int ** descriptor_ptr, tralloc_extensions extensions, const char * path_name, int flags, mode_t mode );

extern inline tralloc_error tralloc_open      ( tralloc_context * parent_context, int ** descriptor_ptr, const char * path_name, int flags );
extern inline tralloc_error tralloc_open_mode ( tralloc_context * parent_context, int ** descriptor_ptr, const char * path_name, int flags, mode_t mode );
