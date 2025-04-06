#pragma once

#include <set>
#include <vector>

#include "tool.h"
#include "work.h"
class ProblemData {
public:
    // все работы (графы операций)
    std::vector<Work> works_;
    // все операции необходимые для выполнения всех работ
    std::vector<Work::Operation> operations_;
    // все исполнители (ресурсы)
    std::vector<Tool> tools_;
    // матрица времён выполнения i-ой Operation на j-м ресурсе
    const std::vector<std::vector<uint64_t>> time_matrix_;
};

struct Operation_update {
    const bool stoppable;
    const std::set<size_t> previous_op_id;
    const std::set<size_t> possible_tools;
    uint64_t start_time = 0;
    uint64_t end_time = 0;
    Operation_update(bool stoppable, const std::set<size_t>& previous_op_id,
                     const std::set<size_t>& possible_tools)
        : stoppable(stoppable),
          previous_op_id(previous_op_id),
          possible_tools(possible_tools){};
};

// такая структура Work должна быть круче
class Work_update {
public:
    const uint64_t start_time;
    const uint64_t directive;
    const double fine_coef;
    const std::set<size_t> operation_ids;

    Work_update(uint64_t start_time, uint64_t directive, double fine_coef,
                const std::set<size_t>& operation_ids,
                const std::vector<Operation_update>& ref_to_all_opers)
        : start_time(start_time),
          directive(directive),
          fine_coef(fine_coef),
          operation_ids(operation_ids),
          ref_to_all_opers_(ref_to_all_opers) {}

    bool CanBeAppointed(size_t oper_id, uint64_t timestamp) {
        if (!operation_ids.contains(oper_id) || timestamp < start_time) {
            return false;
        }

        const auto& oper = ref_to_all_opers_[oper_id];
        for (auto prev : oper.previous_op_id) {
            if (ref_to_all_opers_[prev].end_time == 0 ||
                ref_to_all_opers_[prev].end_time > timestamp) {
                return false;
            }
        }

        return oper.start_time != 0;
    }

private:
    const std::vector<Operation_update>& ref_to_all_opers_;
};
