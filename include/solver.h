#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(ProblemData&& data) : data_(std::move(data)) {cntOperation_ = data.getCntOperations();};

    void setData(ProblemData&& data) {
        data_ = std::move(data);
        cntOperation_ = data.getCntOperations();
    }

    uint64_t Solve(std::vector<Tool::NamedTimeInterval>& gant_plot);

    bool Solve();

    bool CheckSolution(const std::vector<Tool::NamedTimeInterval>& gant_plot);
private:
    ProblemData data_;
    size_t cntOperation_;
    uint64_t time_ = 0; //время глобальное
    std::vector<uint64_t> x_; //вектор с началом выполнения операции
    std::vector<uint64_t> F_ ;// фронт
    std::set<u_int64_t> R_ ;// свободные tools

    void SortFront(); //стратегия сортировки

};

bool Solver::Solve() {
    x_.resize(cntOperation_, 0);
    for (size_t i = 0; i < data_.tools_.size(); ++i) {
        R_.insert(i);
    }
    
    while(true) {
        F_.clear();
        for (size_t i = 0; i< cntOperation_; ++i) {
            if (x_[i] == 0 && data_.works_[0].CanStarted(time_) 
                && data_.works_[0].CanBeAppointed(i, time_) && R_.size() > 0) {
                    F_.push_back(i);
                }
        }

        SortFront();

    }

}