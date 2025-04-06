#pragma once
#include "problem_data.h"

//здесь будем решать задачу
class Solver {
public:
    Solver(const ProblemData& data) : data_(data) {};

    uint64_t Solve();

    bool CheckSolution();
    
private:
    // проверка ранних времён начала
    /*bool CheckStartTimes() {
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
    // и назначены в соответствии с графом создания
    bool CheckAllAppointedRight() {
        for (auto& work : data_.works_) {
            auto& oper_vec = work.getOperations();
            for (auto& op : oper_vec) {
                //проверим что операция назначена
                if (op->end_time == 0 || op->start_time == 0) {
                    return false;
                }
                //проверим что все её предшественники выполнены
                for (auto& pre : op->previous_ops_id) {
                    if (oper_vec[pre]->end_time > op->start_time) {
                        return false;
                    }
                }
            }
        }

        return true;
    }*/

    ProblemData data_;
};