#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../App/Lib/file_wrapper.h"

using testing::Eq;

TEST(FileWrapper, ReadsClassesFile) {
    EXPECT_EQ(FileWrapper::readFile("airports").size(), 3020);
    EXPECT_EQ(FileWrapper::readFile("airlines").size(), 445);
    EXPECT_EQ(FileWrapper::readFile("flights").size(), 63833);
}