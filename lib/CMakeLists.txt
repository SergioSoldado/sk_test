include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sk_library_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/sk.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/macros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/analytics/http.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/math/math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sk/data/string_list.h

        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/sk/curl/sk.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/analytics/http.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/math/math.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sk/data/string_list/curl/string_list.c
        )

add_library(sk ${sk_library_src})

target_link_libraries(sk curl asan)
