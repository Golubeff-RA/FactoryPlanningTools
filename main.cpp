#include <iostream>
#include "src/tool.h"
#include "src/work.h"

int main() {
    std::vector<Tool::TimeInterval> intervals = {{20, 40}, {50, 80}, {90, 120}};
    Tool test_tool(intervals);
    std::cout << test_tool.IsAvailable(20, 81, true);
    Work::Operation test_operation {10, {12, 13, 18, 90}, {1, 2, 3, 4, 5, 8}};
    return 0;
}