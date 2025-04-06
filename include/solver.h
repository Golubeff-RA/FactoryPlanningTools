#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(const ProblemData& data) : data_(data) {cntOperation_ = data_.getCntOperations();};

    void SetData(const ProblemData& data) {
        data_ = data;
        cntOperation_ = data_.getCntOperations();
    }

    uint64_t Solve(std::vector<Tool::NamedTimeInterval>& gant_plot);
    bool Solve();

    bool CheckSolution(const std::vector<Tool::NamedTimeInterval>& gant_plot);
private:
    ProblemData data_;
    size_t cntOperation_;
    uint64_t time_ = 0; //время глобальное
    std::vector<std::vector<uint64_t>> x_; //вектор с началом выполнения операции
    std::vector<std::pair<uint64_t, u_int64_t>> F_ ;// фронт
    std::set<u_int64_t> R_ ;// свободные tools
 
    void SortFront(){} //стратегия сортировки
};

bool Solver::Solve() {
    std::vector<std::vector<uint64_t>> stanok_; //вектор станков выполнеемых
    stanok_.resize(data_.works_.size(), std::vector<uint64_t> (cntOperation_, -1));
    //step1
    x_.resize(data_.works_.size(), std::vector<uint64_t> (cntOperation_, 0));
    for (size_t i = 0; i < data_.tools_.size(); ++i) {
        R_.insert(i);
    }
    
    while(true) {
        //step2
        //создает фронт и записывает пустые станки
        F_.clear();
        for(size_t j = 0; j< data_.works_.size(); ++j) {
            auto work = data_.works_[j];
            for (size_t i = 0; i< work.getCntOperations(); ++i) {
                if (x_[j][i] == 0 && work.CanStarted(time_) 
                    && data_.works_[0].CanBeAppointed(i, time_) && R_.size() > 0) {
                        F_.push_back({j, i});
                    }
                auto toolNumber = work.getToolNumber(i, time_);
                if (toolNumber != -1) {
                    R_.insert(toolNumber);
                }
            }
        }

        SortFront();

        //step3
        if(R_.size() > 0) {
            //нет проверки что операция может выполняться на станке
            // нет ни какой проверки
            for (auto e : F_) {
                if(R_.empty()) break;
                x_[e.first][e.second] = time_;
                data_.works_[e.first].setTimeOperation(e.second, time_);
                data_.works_[e.first].setToolNumber(*R_.begin(), e.second);
                R_.erase(R_.begin());
            }
        }

        //stap4
        //проверяет что все работы закончены
        bool idContinue = false;
        for (size_t i = 0; i < data_.works_.size(); ++i) {
            for (size_t j = 0; j < cntOperation_; ++j) {
                if(x_[i][j] == 0) {
                    idContinue = true;
                    break;
                }
            }
        }
        if(!idContinue) {
            break;
        }
        ++time_;
    }
    return true;
}