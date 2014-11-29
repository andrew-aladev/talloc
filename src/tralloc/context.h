// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#if !defined ( TRALLOC_CONTEXT_H )
#define TRALLOC_CONTEXT_H

#include "macro.h"
#include "types.h"

#undef _TRALLOC_INLINE
#if defined ( _TRALLOC_INCLUDED_FROM_CONTEXT_C )
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_OBJECT
#else
#    define _TRALLOC_INLINE _TRALLOC_INLINE_IN_HEADER
#endif


_TRALLOC_INLINE
tralloc_context * _tralloc_chunk_get_context ( _tralloc_chunk * chunk )
{
    return ( tralloc_context * ) ( ( uintptr_t ) chunk + sizeof ( _tralloc_chunk ) );
}

_TRALLOC_INLINE
_tralloc_chunk * _tralloc_context_get_chunk ( tralloc_context * context )
{
    return ( _tralloc_chunk * ) ( ( uintptr_t ) context - sizeof ( _tralloc_chunk ) );
}


#endif