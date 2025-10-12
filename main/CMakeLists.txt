set(main_SRC main.cpp)

add_executable(stackPerfComp ${main_SRC})

target_link_libraries(stackPerfComp libstackcollection)
