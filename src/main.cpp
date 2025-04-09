#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "solver.h"
#include "solution_checker.h"

int main() {
    std::ifstream input_file("../test_data/data.DAT");
    ProblemData test_data(input_file);
    input_file.close();
    Solver::Solve(&test_data);

    std::cout << "Shedules:\n";
    for (auto& tool : test_data.tools) {
        tool.PrintShedule(std::cout);
        std::cout << "\n";
    }

    std::cout << "\nGant plots:\n";
    for (auto& tool : test_data.tools) {
        tool.PrintGant(std::cout);
        std::cout << "\n";
    }

    //test_data.tools[0].DestroyWorkProcess();
    try {
        SolutionChecker::Check(&test_data);
    } catch (std::runtime_error& e) {
        std::cout << "Ваше решение не прошло проверку! " << e.what();
    }

    return 0;
}
