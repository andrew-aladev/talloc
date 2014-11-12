function (check_runnable)
    if (DEFINED CMAKE_CAN_RUN_EXE)
        return ()
    endif ()
    
    include (CheckVerbose)
    check_verbose ()
    
    set (BINARY_DIR "${PROJECT_BINARY_DIR}/CMakeTmp/basic")
    set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/cmake/checks/basic")
    set (NAME "check_basic")
    
    try_compile (CHECK_RUNNABLE_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
        CMAKE_FLAGS
            "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS} ${VERBOSE_CFLAGS} ${WERROR_CFLAGS}"
            "-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_CONFIG_VERBOSE_MAKEFILE}"
            "-DCMAKE_TRY_RUN=1"
        OUTPUT_VARIABLE CHECK_RUNNABLE_COMPILE_RESULT
    )
    if (${CMAKE_CONFIG_VERBOSE_MAKEFILE})
        message (STATUS ${CHECK_RUNNABLE_COMPILE_RESULT})
    endif ()
    FILE (REMOVE_RECURSE ${BINARY_DIR})
    
    if (${CHECK_RUNNABLE_RESULT})
        set (CMAKE_CAN_RUN_EXE true CACHE STRING "Cmake can run exe")
        message (STATUS "Cmake can run exe - yes")
        return ()
    endif ()
    
    set (CMAKE_CAN_RUN_EXE false CACHE STRING "Cmake can run exe")
    message (STATUS "Cmake can run exe - no")
endfunction ()