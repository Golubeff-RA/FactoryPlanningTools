#pragma once
#include <expected>
#include <memory>
#include <queue>

#include "problem_data.h"

using CheckType = std::expected<bool, std::string>;
// здесь будем решать задачу
class Solver {
public:
    Solver(ProblemData* data) : data_(data){};
    // новые данные задачи
    //void SetProblemData(std::shared_ptr<ProblemData> data) { data_ = data; }

    void Solve() {
        std::set<uint64_t> timestamps;
        FillStartTimes(timestamps);
        std::set<size_t> R;  // множество доступных станков
        // основной цикл по событиям
        while (!timestamps.empty()) {
            current_time = *timestamps.begin();
            timestamps.erase(timestamps.begin());
            std::vector<size_t> F;
            // фронт операций
            for (auto& work : data_->works) {
                for (auto& op_idx : work.operation_ids) {
                    if (work.CanBeAppointed(op_idx, current_time)) {
                        F.push_back(op_idx);
                    }
                }
            }
    
            SortFront(F);
            // собираем множесво возможных исполнителей для фронта
            for (size_t oper : F) {
                for (size_t i : data_->operations[oper].possible_tools) {
                    if (data_->tools[i].CanStartWork(
                            data_->operations[oper], current_time,
                            data_->times_matrix[oper][i])) {
                        R.insert(i);
                    }
                }
            }

            // возьмём первую операцию из фронта как самую важную
            for (size_t oper_in_f : F) {
                Operation& cool_operation = data_->operations[oper_in_f];
                for (size_t r : R) {
                    if (cool_operation.possible_tools.contains(r)) {
                        data_->tools[r].Appoint(
                            cool_operation, oper_in_f, current_time,
                            data_->times_matrix[oper_in_f][r]);
                        timestamps.insert(cool_operation.end_time);
                        R.erase(r);
                        break;
                    }
                }
            }
        }
    }

    void SortFront(std::vector<size_t> front) {}

    //CheckType CheckSolution() {}

private:
    void FillStartTimes(std::set<uint64_t>& times) {
        for (const auto& work : data_->works) {
            times.insert(work.start_time);
        }

        for (const auto& tool : data_->tools) {
            tool.GetSheduleStarts(times);
        }
    }
    uint64_t current_time = 0;
    ProblemData* data_;
};