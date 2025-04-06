#include <gtest/gtest.h>

#include "tool.h"
#include "work.h"

const std::vector<std::vector<uint64_t>> kTimesMatrix{
    {1, 0, 4, 5},
    {0, 2, 3, 1},
    {0, 0, 0, 4},
    {5, 1, 3, 5},
    {10, 5, 1, 0},
    {0, 3, 4, 0},
    {3, 5, 3, 0},
    {0, 0, 10, 5}
};

const std::vector<Tool> kTools{
    Tool({{5, 10}, {15, 35}, {40, 47}, {50, 62}}),
    Tool({{35, 40}, {50, 70}, {10, 30}, {75, 80}, {88, 105}}),
    Tool({{1, 5}, {15, 25}, {27, 37}, {44, 55}, {90, 100}}),
    Tool({{3, 10}, {25, 50}, {60, 90}})
};


TEST(Tools__Test, can_start_work) {
    Tool test_tool ({{35, 40}, {50, 70}, {10, 30}, {75, 80}});
    Work::Operation op1 {true, {}, {0}};
    Work::Operation op2 {true, {0}, {0}};
    Work::Operation op3 {false, {0, 1}, {0}};

    ASSERT_EQ(test_tool.CanStartWork(op1, 11, 10), true);
    ASSERT_EQ(test_tool.CanStartWork(op1, 9, 10), false);
    ASSERT_EQ(test_tool.CanStartWork(op3, 50, 10), true);
    ASSERT_EQ(test_tool.CanStartWork(op3, 35, 10), false);
    ASSERT_EQ(test_tool.CanStartWork(op1, 35, 100), false);
    ASSERT_EQ(test_tool.CanStartWork(op2, 51, 12), true);
}

TEST(Tools__Test, check_collisions) {
    Tool test_tool ({{35, 40}, {50, 70}, {10, 30}, {75, 80}});
    Work::Operation op1 {true, {}, {0}};
    Work::Operation op2 {true, {}, {0}};

    ASSERT_EQ(test_tool.CanStartWork(op1, 10, 15), true);
    ASSERT_EQ(test_tool.CanStartWork(op2, 10, 15), true);

    test_tool.Appoint(op1, 0, 10, 10);
    test_tool.Appoint(op2, 1, 50, 12);
    
    ASSERT_EQ(test_tool.CheckCollisions(), true);
    test_tool.Appoint(op1, 3, 11, 5);
    ASSERT_EQ(test_tool.CheckCollisions(), false);
    ASSERT_THROW(test_tool.Appoint(op1, 5, 10, 3), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}