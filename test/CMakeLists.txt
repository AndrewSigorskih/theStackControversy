include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB test_SRC "src/*.cpp")

add_executable(test_libstackcollection ${test_SRC})

target_link_libraries(
  test_libstackcollection
  libstackcollection
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_libstackcollection)

# Alternatively, advanced example on how to write and configure a custom test main()
# can be found here https://github.com/dacorvo/gtest-cmake-example
