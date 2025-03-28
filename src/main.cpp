#include <iostream>
#include "tool.h"
#include "work.h"

int main() {
    Tool test_tool {{35, 40}, {50, 70}, {10, 30}, {75, 80}};
    test_tool.PrintShedule();

    Work::Operation oper {true, {}, {1}};
    std::initializer_list<uint64_t> prev{1, 3, 2, 4, 5, 6};
    Work::Operation oper2{true, prev, prev};
    std::cout<< test_tool.CanStartWork(oper, 55, 25) << std::endl;;
    test_tool.Appoint(oper, 77, 55, 25);
    test_tool.PrintGant();
    std::cout << "\n" << oper.end_time;
    return 0;
}