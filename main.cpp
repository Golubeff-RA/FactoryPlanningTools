#include <iostream>
#include "src/tool.h"
#include "src/work.h"

int main() {
    Tool test_tool {{35, 40}, {50, 70}, {10, 30}, {75, 80}};
    test_tool.Appoint(35, 40, 99);

    Work::Operation oper {10, false, {}, {1}};
    test_tool.PrintShedule();

    std::cout<< test_tool.CanStartWork(oper, 61) << std::endl;;
    return 0;
}