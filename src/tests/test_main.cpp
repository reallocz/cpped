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

TEST_F(StringTest, Assignment)
{
    *s1 = "Yolo";
    EXPECT_EQ(4, s1->length());
}

TEST_F(StringTest, Slice)
{
    *s1 = "Yolo";
    int len = 2;

    String s2 = s1->slice(2, len);

    EXPECT_EQ(len, s2.length());

    String s3 = s2;
    EXPECT_EQ(s3.length(), s2.length());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
