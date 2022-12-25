#include "gtest/gtest.h"

#include "add.hpp"

TEST(Test, Add) {
    const auto result = add(5.0f, 2.5f);
    const float expected = 7.5f;
    EXPECT_FLOAT_EQ(expected, result);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
