#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(const ProblemData& data) : data_(data) {};

    void SetData(const ProblemData& data) {
        data_ = data;
    }

    uint64_t Solve(std::vector<Tool::NamedTimeInterval>& gant_plot);

    bool CheckSolution(const std::vector<Tool::NamedTimeInterval>& gant_plot);
private:
    ProblemData data_;
};