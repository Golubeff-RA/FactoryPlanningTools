#include <iostream>
#include "src/tool.h"

int main() {
    std::vector<Tool::TimeInterval> intervals = {{20, 40}, {50, 80}, {90, 120}};
    Tool test_tool(intervals);
    std::cout << test_tool.IsAvailable(20, 81, true);
    return 0;
}