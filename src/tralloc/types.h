// This file is part of tralloc. Copyright (C) 2013 Andrew Aladjev aladjev.andrew@gmail.com
// tralloc is free software: you can redistribute it and/or modify it under the terms of the GNU General Lesser Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// tralloc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Lesser Public License for more details.
// You should have received a copy of the GNU General Lesser Public License along with tralloc. If not, see <http://www.gnu.org/licenses/>.

#ifndef TRALLOC_TYPES_H
#define TRALLOC_TYPES_H

#include <stdint.h>
#include <stddef.h>

#include "config.h"

#if defined(TRALLOC_THREADS)
#   include <pthread.h>
#endif


#ifdef TRALLOC_HAVE_BOOL
#    include <stdbool.h>
typedef bool tralloc_bool;
#    define TRALLOC_TRUE true
#    define TRALLOC_FALSE false
#else
typedef char tralloc_bool;
#    define TRALLOC_TRUE 1
#    define TRALLOC_FALSE 0
#endif

typedef void tralloc_context;

enum {

    TRALLOC_ERROR_REQUIRED_ARGUMENT_IS_NULL = 1,
    TRALLOC_ERROR_MALLOC_FAILED,
    TRALLOC_ERROR_CALLOC_FAILED,
    TRALLOC_ERROR_REALLOC_FAILED,
    TRALLOC_ERROR_OPEN_DESCRIPTOR_FAILED,
    TRALLOC_ERROR_CLOSE_DESCRIPTOR_FAILED,
    TRALLOC_ERROR_PRINTF_FAILED,

    TRALLOC_ERROR_CHILD_EQUALS_PARENT,
    TRALLOC_ERROR_CHILD_HAS_SAME_PARENT,

#   if defined(TRALLOC_EXTENSIONS)
    TRALLOC_ERROR_NO_SUCH_EXTENSION,
#   endif

#   if defined(TRALLOC_POOL)
    TRALLOC_ERROR_POOL_CANT_BE_REALLOCATED,
#   endif

#   if defined(TRALLOC_UTILS_BUFFER)
    TRALLOC_ERROR_UTILS_BUFFER_OVERFLOW,
#   endif

#   if defined(TRALLOC_THREADS)
    TRALLOC_ERROR_MUTEX_FAILED,
    TRALLOC_ERROR_SPINLOCK_FAILED,

    TRALLOC_ERROR_NO_CHILDREN_LOCK,
#   endif

};
typedef uint8_t tralloc_error;

#if defined(TRALLOC_EXTENSIONS)
enum {

#   if defined(TRALLOC_LENGTH)
    TRALLOC_EXTENSION_LENGTH = 1,
#   endif

#   if defined(TRALLOC_DESTRUCTOR)
    TRALLOC_EXTENSION_DESTRUCTORS = 1 << 1,
#   endif

#   if defined(TRALLOC_REFERENCE)
    TRALLOC_EXTENSION_REFERENCE  = 1 << 2,
    TRALLOC_EXTENSION_REFERENCES = 1 << 3,
#   endif

#   if defined(TRALLOC_POOL)
    TRALLOC_EXTENSION_POOL       = 1 << 4,
    TRALLOC_EXTENSION_POOL_CHILD = 1 << 5,
#   endif

#   if defined(TRALLOC_THREADS)
    TRALLOC_EXTENSION_LOCK_PARENT      = 1 << 6,
    TRALLOC_EXTENSION_LOCK_PREV        = 1 << 7,
    TRALLOC_EXTENSION_LOCK_NEXT        = 1 << 8,
    TRALLOC_EXTENSION_LOCK_FIRST_CHILD = 1 << 9,

    TRALLOC_EXTENSION_LOCK_CHILDREN    = 1 << 10,
#   endif

};
#endif

typedef uint16_t tralloc_extensions;

#if defined(TRALLOC_LENGTH)
typedef struct _tralloc_length_type {
    size_t length;
} _tralloc_length;
#endif

#if defined(TRALLOC_DESTRUCTOR)
typedef tralloc_error ( * tralloc_destructor_function ) ( tralloc_context * chunk_context, void * user_data );

typedef struct _tralloc_destructor_type {
    struct _tralloc_destructor_type * next;
    tralloc_destructor_function function;
    void * user_data;
} _tralloc_destructor;

// Destructors represent single linked.
// "first_destructor" is the start of this list, "last_destructor" - end.
// Order of destructors is given by user (append and prepend functions).
typedef struct _tralloc_destructors_type {
    _tralloc_destructor * first_destructor;
    _tralloc_destructor * last_destructor;
} _tralloc_destructors;
#endif

#if defined(TRALLOC_REFERENCE)
typedef struct _tralloc_reference_type {
    struct _tralloc_references_type * references;
    struct _tralloc_reference_type * prev;
    struct _tralloc_reference_type * next;
} _tralloc_reference;

// References represent double linked list.
// "first_reference" is the start of this list.
// Order of references is given by user (move_reference function).
typedef struct _tralloc_references_type {
    _tralloc_reference * first_reference;
    tralloc_extensions extensions;
    tralloc_bool autofree;
} _tralloc_references;
#endif

#if defined(TRALLOC_POOL)
// "pool_child" should be the first in the stack of extensions.
// This slight limitation makes fragment's calculation much easier and descreases the total amount of pool's memory overhead.
typedef struct _tralloc_pool_child_type {
    struct _tralloc_pool_type * pool;
    struct _tralloc_pool_child_type * prev;
    struct _tralloc_pool_child_type * next;
    size_t length;
} _tralloc_pool_child;

typedef struct _tralloc_pool_fragment_type {
    struct _tralloc_pool_fragment_type * prev;
    struct _tralloc_pool_fragment_type * next;
    _tralloc_pool_child * prev_child;
    _tralloc_pool_child * next_child;
    size_t length;
} _tralloc_pool_fragment;

// Fragments represent double linked ordered list.
// "max_fragment" is the start of this list.
// It is the longest fragment available.

// Pool child represent double linked list.
// "first_child" is the start of this list.
// Order of pool childs is given by user (the order of chunks allocation and movement).
typedef struct _tralloc_pool_type {
    _tralloc_pool_child    * first_child;
    _tralloc_pool_fragment * max_fragment;
    tralloc_extensions extensions;
    void * memory;
    size_t length;
    tralloc_bool autofree;
} _tralloc_pool;
#endif

#if defined(TRALLOC_DEBUG) && defined(TRALLOC_THREADS)
enum {
    _TRALLOC_CHILDREN_NOT_USED,
    _TRALLOC_CHILDREN_USED_BY_SINGLE_THREAD,
    _TRALLOC_CHILDREN_USED_BY_MULTIPLE_THREADS
};

typedef uint8_t _tralloc_children_status;
#endif

typedef struct _tralloc_chunk_type {
    // "parent", "prev", "next", "first_child" should be locked for thread safety.
    struct _tralloc_chunk_type * parent;
    struct _tralloc_chunk_type * prev;
    struct _tralloc_chunk_type * next;
    struct _tralloc_chunk_type * first_child;

#   if defined(TRALLOC_EXTENSIONS)
    // "extensions" should not be locked for thread safety.
    // It will be written only in alloc function. Other functions will read it.
    tralloc_extensions extensions;
#   endif

#   if defined(TRALLOC_DEBUG)
    // "chunk_length" should not be locked for thread safety.
    // It will be written only in alloc function. Other functions will read it.
    size_t chunk_length;

    // "length" will be locked for thread safety by "length_lock".
    size_t length;

#   if defined(TRALLOC_THREADS)

    // "length_lock" should not be locked for thread safety.
    // It will be written only in alloc function. Other functions will read it.
#   if TRALLOC_DEBUG_THREADS_LENGTH == TRALLOC_SPINLOCK
    pthread_spinlock_t length_lock;
#   elif TRALLOC_DEBUG_THREADS_LENGTH == TRALLOC_MUTEX
    pthread_mutex_t length_lock;
#   endif

#   endif

    // "initialized_in_file" and "initialized_at_line" should not be locked for thread safety.
    // It will be written only in alloc function. Other functions will read it.
    char * initialized_in_file;
    size_t initialized_at_line;

#   if defined(TRALLOC_THREADS)

    // "children_touched_by_thread" and "children_touched_by_multiple_threads" will be locked for thread safety by "children_lock".
    pthread_t children_status_thread;
    _tralloc_children_status children_status;

    // "children_status_lock" should not be locked for thread safety.
    // It will be written only in alloc function. Other functions will read it.
#   if TRALLOC_DEBUG_THREADS_CHILDREN == TRALLOC_SPINLOCK
    pthread_spinlock_t children_status_lock;
#   elif TRALLOC_DEBUG_THREADS_CHILDREN == TRALLOC_MUTEX
    pthread_mutex_t children_status_lock;
#   endif

#   endif

#   endif

} _tralloc_chunk;


#endif
