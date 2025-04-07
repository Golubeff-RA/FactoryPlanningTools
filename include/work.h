#pragma once
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <vector>

// Хранит инфу о том какие операции надо назначить, чтобы выполнить работу
/*class Work {
public:
    struct Operation {
        const bool stoppable;     // прерываемая или нет
        uint64_t start_time = 0;  // начало выполнения
        uint64_t end_time = 0;    // конец выполнения
        // предшественники
        const std::set<uint64_t> previous_ops_id;
        // на каких исполнителях можно выполнить
        const std::vector<uint64_t> possible_tools;
        Operation(bool stoppable,
                  const std::initializer_list<uint64_t>& previous,
                  const std::initializer_list<uint64_t>& tools)
            : stoppable(stoppable),
              previous_ops_id(previous),
              possible_tools(tools){};
        Operation(bool stoppable, const std::set<uint64_t>& previous)
            : stoppable(stoppable), previous_ops_id(previous){};
    };

    bool CanBeAppointed(const Operation& operation, uint64_t timestamp) {
        // ещё не прошло раннее время начала
        if (timestamp < start_time_) {
            return false;
        }
        for (uint64_t prev : operation.previous_ops_id) {
            if (operations_[prev]->end_time == 0 ||
                operations_[prev]->end_time > timestamp) {
                return false;
            }
        }

        return true;
    }
    Work() {}
    Work(uint64_t st_time, uint64_t directive, uint64_t fine_coef,
         std::vector<Operation*>& operations)
        : start_time_(st_time),
          directive_(directive),
          fine_coef_(fine_coef),
          operations_(operations) {}

    void setStartTime(uint64_t start_time) { start_time_ = start_time; }
    void setDirective(uint64_t directive) { directive_ = directive; }
    void setFineCoef(double fine_coef) { fine_coef_ = fine_coef; }
    void setOperations(std::vector<Operation*>& operations) {
        operations_ = operations;
    }

    void print() {
        std::cout << start_time_ << ' ' << directive_ << ' ' << fine_coef_
                  << ' ';
        for (auto e : operations_) {
            std::cout << e->stoppable << ' ' << "prev ";
            for (auto o : e->previous_ops_id) std::cout << o << ' ';
            std::cout << "prev";
        }
        std::cout << "\n\n";
    }

    uint64_t getStartTime() const { return start_time_; }

    uint64_t getDirective() const { return directive_; }

    double getFineCoef() const { return fine_coef_; }

    const std::vector<Operation*>& getOperations() const {
        return operations_;
    }

private:
    uint64_t start_time_;
    uint64_t directive_;
    double fine_coef_;
    std::vector<Operation*>
        operations_;  // Множество всех операций в данной работе
};*/

struct Operation {
    const bool stoppable;
    const std::set<size_t> previous_op_id;
    const std::set<size_t> possible_tools;
    uint64_t start_time = 0;
    uint64_t end_time = 0;
    Operation(bool stoppable, const std::set<size_t>& previous_op_id,
              const std::set<size_t>& possible_tools)
        : stoppable(stoppable),
          previous_op_id(previous_op_id),
          possible_tools(possible_tools){};
};

// такая структура Work должна быть круче
class Work {
public:
    const uint64_t start_time;
    const uint64_t directive;
    const double fine_coef;
    const std::set<size_t> operation_ids;

    Work(uint64_t start_time, uint64_t directive, double fine_coef,
         const std::set<size_t>& operation_ids,
         const std::vector<Operation>& ref_to_all_opers)
        : start_time(start_time),
          directive(directive),
          fine_coef(fine_coef),
          operation_ids(operation_ids),
          ref_to_all_opers_(ref_to_all_opers) {}

    bool CanBeAppointed(size_t oper_id, uint64_t timestamp) const{
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

        return oper.start_time == 0;
    }

private:
    const std::vector<Operation>& ref_to_all_opers_;
};