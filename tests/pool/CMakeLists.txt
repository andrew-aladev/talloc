set (SOURCES errors.c add.c move.c free.c test.c)
add_subdirectory ("resize")

if (${TRALLOC_SHARED})
    add_library (${TRALLOC_TARGET}-libtest-pool SHARED ${SOURCES})
    target_link_libraries (${TRALLOC_TARGET}-libtest-pool ${TRALLOC_TARGET})
endif ()
if (${TRALLOC_STATIC})
    add_library (${TRALLOC_TARGET}-libtest-pool-static STATIC ${SOURCES})
    target_link_libraries (${TRALLOC_TARGET}-libtest-pool-static ${TRALLOC_TARGET}-static)
    set_target_properties (${TRALLOC_TARGET}-libtest-pool-static PROPERTIES OUTPUT_NAME ${TRALLOC_TARGET}-libtest-pool-static)
endif ()

if (${TRALLOC_SHARED})
    set (NAME ${TRALLOC_TARGET}-test-pool)
    add_executable (${NAME} main.c)
    target_link_libraries (${NAME} ${TRALLOC_TARGET}-libtest-pool)
    add_test (${NAME} ${NAME})
endif ()
if (${TRALLOC_STATIC})
    set (NAME ${TRALLOC_TARGET}-test-pool-static)
    add_executable (${NAME} main.c)
    target_link_libraries (${NAME} ${TRALLOC_TARGET}-libtest-pool-static)
    add_test (${NAME} ${NAME})
endif ()
