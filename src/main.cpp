#include <iostream>
#include <fstream>
#include <string>
#include "problem_data.h"
#include "tool.h"
#include "work.h"
#include "solver.h"
#include <memory>


int main() {
    std::ifstream input_file("../test_data/data.DAT");
    ProblemData test_data(input_file);
    input_file.close();
    Solver solv(&test_data);
    solv.Solve();

    std::cout << "Shedules:\n";
    for (auto& tool : test_data.tools) {
        tool.PrintShedule();
        std::cout << "\n";
    }
    std::cout << "\nGant plots:\n";
    for (auto& tool : test_data.tools) {
        tool.PrintGant();
        std::cout << "\n";
    }
    return 0;
}