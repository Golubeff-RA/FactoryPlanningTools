#include <iostream>
#include "src/tool.h"
#include "src/work.h"

int main() {
    Tool test_tool {{35, 40}, {50, 70}, {10, 30}, {75, 80}};
    test_tool.PrintShedule();

    Work::Operation oper {23, true, {}, {1}};
    std::cout<< test_tool.CanStartWork(oper, 50) << std::endl;;
    test_tool.Appoint(oper, 77, 15);
    test_tool.PrintGant();
    std::cout << "\n" << oper.end_time;
    return 0;
}