project(test)

add_subdirectory(../../../lib/code_practise/gtest gtest.out)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${SOURCE_DIR}/src)
file(GLOB testSRCs *.cc)
add_executable(gtest_run ${testSRCs} ${SRCs})
target_link_libraries(gtest_run gtest gtest_main)
