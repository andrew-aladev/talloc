function (tralloc_check_lto)
    if (DEFINED TRALLOC_HAVE_LTO)
        return ()
    endif ()
    
    include (TrallocCheckVerbose)
    tralloc_check_verbose ()
    
    set (BINARY_DIR "${PROJECT_BINARY_DIR}/CMakeTmp/basic")
    set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/cmake/checks/basic")
    set (NAME "tralloc_check_basic")
    
    try_compile (CHECK_LTO_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
        CMAKE_FLAGS
            "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS} ${TRALLOC_VERBOSE_CFLAGS} ${TRALLOC_WERROR_CFLAGS} -flto -fuse-linker-plugin"
            "-DCMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS} -flto -fuse-linker-plugin"
        OUTPUT_VARIABLE CHECK_LTO_COMPILE_RESULT
    )
    if (${CMAKE_CONFIG_VERBOSE_MAKEFILE})
        message (STATUS ${CHECK_LTO_COMPILE_RESULT})
    endif ()
    FILE (REMOVE_RECURSE ${BINARY_DIR})
    
    if (${CHECK_LTO_RESULT})
        set (TRALLOC_HAVE_LTO true CACHE STRING "Status of LTO support")
        set (TRALLOC_LTO_CFLAGS "-flto -fuse-linker-plugin" CACHE STRING "LTO cflags")
        set (TRALLOC_LTO_LDLAGS "-flto -fuse-linker-plugin" CACHE STRING "LTO ldflags")
        message (STATUS "Check for C compiler LTO support - yes")
        return ()
    endif ()
    
    set (TRALLOC_HAVE_LTO false CACHE STRING "Status of LTO support")
    set (TRALLOC_LTO_CFLAGS "" CACHE STRING "LTO cflags")
    set (TRALLOC_LTO_LDLAGS "" CACHE STRING "LTO ldflags")
    message (STATUS "Check for C compiler LTO support - no")
endfunction ()
