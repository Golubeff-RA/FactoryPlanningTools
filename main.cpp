#include <iostream>
#include "src/tool.h"

int main() {
    Tool::TimeInterval test{100, 1000};
    std::cout << test.start << " || " << test.end;
    return 0;
}