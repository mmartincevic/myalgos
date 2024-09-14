#include <gtest/gtest.h>

// Include a header from your project
// Replace "example.h" with an actual header from your project
#include "playground/example.h"

// Test if Google Test is set up correctly
TEST(SetupTest, GoogleTestWorking)
{
    EXPECT_TRUE(true);
}

// Test if includes are working
TEST(SetupTest, IncludesWorking)
{
    // Replace this with an actual function or class from your project
    Example example;
    EXPECT_EQ(example.getValue(), 42);
}

// Test a simple addition function (you can replace this with an actual function from your project)
int add(int a, int b)
{
    return a + b;
}

TEST(MathTest, Addition)
{
    EXPECT_EQ(add(2, 3), 5);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}