file(GLOB libstack_SRC "stackcollection/*")

add_library(libstackcollection STATIC ${libstack_SRC})

target_include_directories(libstackcollection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
