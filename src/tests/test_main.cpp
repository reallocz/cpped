#include <gtest/gtest.h>
#include "core/string.h"
#include <iostream>

struct StringTest : testing::Test
{
    String* s1;
    StringTest()
    {
        s1 = new String();
    }
    ~StringTest()
    {
    }
};

TEST_F(StringTest, Constructor)
{
    EXPECT_EQ(0, s1->length());
    EXPECT_EQ(0, s1->getLengthBytes());
    EXPECT_EQ(SDEF_SIZE * sizeof(char), s1->getSizeBytes());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
