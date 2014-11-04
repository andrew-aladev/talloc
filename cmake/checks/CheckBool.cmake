function (check_bool)
    if (DEFINED TRALLOC_HAVE_BOOL)
        return ()
    endif ()
    
    include (CheckVerbose)
    check_verbose ()
    
    set (BINARY_DIR "${PROJECT_BINARY_DIR}/CMakeTmp/bool")
    set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/cmake/checks/bool")
    set (NAME "check_bool")
    
    try_compile (CHECK_BOOL_COMPILE_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
        CMAKE_FLAGS "-DCMAKE_C_FLAGS:STRING = ${CMAKE_C_FLAGS} ${VERBOSE_CFLAGS}"
    )
    FILE (REMOVE_RECURSE ${BINARY_DIR})
    
    if (${CHECK_BOOL_COMPILE_RESULT})
        set (TRALLOC_HAVE_BOOL true CACHE STRING "Status of Bool support")
        message (STATUS "Check for Bool support - yes")
        return ()
    endif ()
    
    set (TRALLOC_HAVE_BOOL false CACHE STRING "Status of Bool support")
    message (STATUS "Check for Bool support - no")
endfunction ()
