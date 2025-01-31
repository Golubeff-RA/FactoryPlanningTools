#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(ProblemData&& data) : data_(std::move(data)) {};

    void SetData(ProblemData&& data) {
        data_ = std::move(data);
    }

    uint64_t Solve(std::vector<Tool::NamedTimeInterval>& gant_plot);

    bool CheckSolution(const std::vector<Tool::NamedTimeInterval>& gant_plot);
private:
    ProblemData data_;
};