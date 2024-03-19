#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../utils/FileReader.h"

using testing::Eq;

TEST(FileReader, ReadsClassesFile) {
    EXPECT_EQ(3020, 3020);
}