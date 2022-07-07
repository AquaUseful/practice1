add_library(random INTERFACE)

target_link_libraries(random INTERFACE utils)
target_link_libraries(random INTERFACE solution)

target_include_directories(random INTERFACE include/)
