#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(const ProblemData& data) : data_(data) {};

    void SetData(const ProblemData& data) {
        data_ = data;
    }

    uint64_t Solve();

    
private:
    // проверка ранних времён начала
    bool CheckStartTimes() {
        for (auto& work : data_.works_) {
            auto start = work.getStartTime();
            for (auto& op : work.getOperations()) {
                if (op->start_time < start) {
                    return false;
                }
            }
        }
        return true;
    }

    // проверка на коллизии в интервалах исполнения
    bool CheckCollisions() {
        for (auto& tool : data_.tools_) {
            if (tool.CheckCollisions()) {
                return false;
            }
        }

        return true;
    }

    // проверка что все операции назначены
    ProblemData data_;
};