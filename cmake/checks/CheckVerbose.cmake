function (check_verbose)
    if (DEFINED TRALLOC_HAVE_VERBOSE)
        return ()
    endif ()
    
    set (VERBOSE_CFLAGS "")
    
    try_compile (
        CHECK_VERBOSE_COMPILE_RESULT
        "${PROJECT_BINARY_DIR}/CMakeTmp/basic"
        "${PROJECT_SOURCE_DIR}/cmake/checks/basic" "check_basic"
        CMAKE_FLAGS "-DCMAKE_C_FLAGS:STRING = ${CMAKE_C_FLAGS} -pedantic"
    )
    if (${CHECK_VERBOSE_COMPILE_RESULT})
        set (VERBOSE_CFLAGS "${VERBOSE_CFLAGS} -pedantic")
        message (STATUS "Check for C compiler -pedantic support \t- yes")
    else ()
        message (STATUS "Check for C compiler -pedantic support \t- no")
    endif ()
    
    try_compile (
        CHECK_VERBOSE_COMPILE_RESULT
        "${PROJECT_BINARY_DIR}/CMakeTmp/basic"
        "${PROJECT_SOURCE_DIR}/cmake/checks/basic" "check_basic"
        CMAKE_FLAGS "-DCMAKE_C_FLAGS:STRING = ${CMAKE_C_FLAGS} -Wall"
    )
    if (${CHECK_VERBOSE_COMPILE_RESULT})
        set (VERBOSE_CFLAGS "${VERBOSE_CFLAGS} -Wall")
        message (STATUS "Check for C compiler -Wall support \t\t- yes")
    else ()
        message (STATUS "Check for C compiler -Wall support \t\t- no")
    endif ()
    
    try_compile (
        CHECK_VERBOSE_COMPILE_RESULT
        "${PROJECT_BINARY_DIR}/CMakeTmp/basic"
        "${PROJECT_SOURCE_DIR}/cmake/checks/basic" "check_basic"
        CMAKE_FLAGS "-DCMAKE_C_FLAGS:STRING = ${CMAKE_C_FLAGS} -Wextra"
    )
    if (${CHECK_VERBOSE_COMPILE_RESULT})
        set (VERBOSE_CFLAGS "${VERBOSE_CFLAGS} -Wextra")
        message (STATUS "Check for C compiler -Wextra support \t- yes")
    else ()
        message (STATUS "Check for C compiler -Wextra support \t- no")
    endif ()
    
    set (VERBOSE_CFLAGS ${VERBOSE_CFLAGS} CACHE STRING "verbose cflags")
    set (TRALLOC_HAVE_VERBOSE true CACHE STRING "Status of verbose support")
endfunction ()
