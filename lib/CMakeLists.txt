include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sk_library_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/sk.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/analytics/http.h

        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/posix/sk.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/analytics/posix/http.c
        )

add_library(sk ${sk_library_src})

target_link_libraries(sk curl asan)