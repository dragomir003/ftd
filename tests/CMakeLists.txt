project(tests)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

function(add_test name)
    add_executable("${name}" "src/${name}.cpp")
    target_link_libraries("${name}" PRIVATE Catch2::Catch2WithMain)
    catch_discover_tests("${name}")
endfunction()

add_test(result)
