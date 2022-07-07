add_library(solution INTERFACE)

target_link_libraries(solution INTERFACE random)

target_include_directories(solution INTERFACE include/)
