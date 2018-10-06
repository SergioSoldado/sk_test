include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/include)
set(main_src ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
add_executable(samknows ${main_src})
target_link_libraries(samknows sk)