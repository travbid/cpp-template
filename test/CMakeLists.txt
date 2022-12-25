
add_executable(cppsample_test test.cpp)

target_compile_options(cppsample_test PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined>
)
target_link_options(cppsample_test PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined>
)
target_link_libraries(cppsample_test
  PRIVATE GTest::gtest
  PRIVATE trav::cppsample
)
