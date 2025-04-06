#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <map>
#include <vector>
#include <iostream>

// Хранит инфу о том какие операции надо назначить, чтобы выполнить работу
class Work {
public:
    struct Operation {
        const bool stoppable;     // прерываемая или нет
        uint64_t start_time = 0;  // начало выполнения
        uint64_t end_time = 0;    // конец выполнения
        const std::set<uint64_t> previous_ops_id;  // предшественники
        const std::vector<uint64_t> possible_tools;  // на каких исполнителях можно выполнить
        const size_t number_;
        Operation(bool stoppable,
                  const std::initializer_list<uint64_t>& previous,
                  const std::initializer_list<uint64_t>& tools, size_t number)
            : stoppable(stoppable),
              previous_ops_id(previous),
              possible_tools(tools), 
              number_(number){};
        Operation(bool stoppable,
                const std::set<uint64_t>& previous, size_t number)
          : stoppable(stoppable),
            previous_ops_id(previous), 
            number_(number){};
    };

    bool CanBeAppointed(const size_t idOperation, uint64_t timestamp) {
        for (uint64_t prev : operations_[idOperation]->previous_ops_id) {
            if (operations_[prev]->end_time == 0 || operations_[prev]->end_time > timestamp) {
                return false;
            }
        }

        return true;
    }

    bool CanStarted(uint64_t time) { return time > start_time_;}
    Work() {}
    Work(uint64_t st_time, uint64_t directive, uint64_t fine_coef, std::vector<Operation*>& operations) :
        start_time_(st_time),  directive_(directive), fine_coef_(fine_coef), operations_(operations) {}

    void setStartTime(uint64_t start_time) { start_time_ = start_time;}
    void setDirective(uint64_t directive) { directive_= directive;}
    void setFineCoef(uint64_t fine_coef) { fine_coef_= fine_coef;}
    void setOperations(std::vector<Operation*>& operations ) {operations_ = operations;}

    void print() {
        std::cout << start_time_ <<' ' << directive_ <<' ' << fine_coef_ <<' ';
        for(auto e : operations_){
            std::cout << e->stoppable <<' ' << "/*prev ";
            for(auto o : e->previous_ops_id) std::cout << o <<' ';
            std::cout << "prev*/";
        }
        std::cout << "\n\n";
    }

private:
    uint64_t start_time_;
    uint64_t directive_;
    uint64_t fine_coef_;
    std::vector<Operation*> operations_;  // Множество всех операций в данной работе
};