#include <iostream>
#include "src/tool.h"

int main() {
    std::vector<Tool::TimeInterval> intervals = {{20, 40}, {50, 80}, {90, 120}};
    Tool test_tool(intervals);
    return 0;
}