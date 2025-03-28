#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <map>
#include <vector>

// Хранит инфу о том какие операции надо назначить, чтобы выполнить работу
class Work {
public:
    struct Operation {
        const bool stoppable;     // прерываемая или нет
        uint64_t start_time = 0;  // начало выполнения
        uint64_t end_time = 0;    // конец выполнения
        const std::set<uint64_t> previous_ops_id;  // предшественники
        const std::vector<uint64_t>
            possible_tools;  // на каких исполнителях можно выполнить
        Operation(bool stoppable,
                  const std::initializer_list<uint64_t>& previous,
                  const std::initializer_list<uint64_t>& tools)
            : stoppable(stoppable),
              previous_ops_id(previous),
              possible_tools(tools){};
    };

    bool CanBeAppointed(const Operation& operation, uint64_t timestamp) {
        for (uint64_t prev : operation.previous_ops_id) {
            if (operations_[prev]->end_time == 0 || operations_[prev]->end_time > timestamp) {
                return false;
            }
        }

        return true;
    }

private:
    std::vector<std::shared_ptr<Operation>> operations_;  // Множество всех операций в данной работе
    /*uint64_t start_time_;
    uint64_t directive_;
    uint64_t fine_coef_;*/
};