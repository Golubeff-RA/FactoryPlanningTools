#pragma once
#include <cstdint>
#include <optional>
#include <vector>
#include <set>
#include "work.h"

class Tool {
public:
    struct TimeInterval {
        TimeInterval(uint64_t start, uint64_t end) : start(start), end(end) {}
        uint64_t GetTimeSpan() const { return end - start; }

        uint64_t GetTimeSpan(uint64_t timestamp) const {
            if (end >= timestamp) {
                return end - timestamp;
            }

            return 0;
        }

        const uint64_t start;
        const uint64_t end;
        // проверяет интервал на пересечение с другим
        bool Intersects(const TimeInterval& other) const {
            return !(end < other.start || other.end < start);
        }
        
        bool operator<(const TimeInterval& other) const {
            return start < other.start;
        }

        bool operator==(const TimeInterval& other) const {
            return start <= other.start && other.end <= end;
        }

        bool operator!=(const TimeInterval& other) const {
            return !(this->operator==(other));
        }
    };

    struct NamedTimeInterval : TimeInterval {
        NamedTimeInterval(uint64_t start, uint64_t end, uint32_t operation)
            : TimeInterval(start, end), operation(operation) {}
        const uint32_t operation;
    };

    Tool(std::initializer_list<TimeInterval> shedule) : shedule_(shedule) {}

    bool CanStartWork(const Work::Operation& operation, uint64_t timestamp) {
        TimeInterval interval {timestamp, timestamp};
        auto it = shedule_.lower_bound(interval);

        if (it == shedule_.begin() && it->start > timestamp) {
            return false;
        }

        if (it == shedule_.end() || it->start > timestamp) {
            it = std::prev(it);
        } 

        // мы можем попробовать начать выполнение операции, но 
        // надо убедиться, что в рабочем расписании есть место.
        if (timestamp >= it->start && timestamp < it->end) {
            // проверим не занят ли исполнитель в это время
            for (auto& gant: work_process_) {
                if (gant.Intersects(interval)) {
                    return false;
                }
            }
            
            if (operation.stoppable) {
                uint64_t time = 0;
                while (it != shedule_.end() && time < operation.timespan) {
                    time += it->GetTimeSpan(timestamp);
                    it = std::next(it);
                    timestamp = it->start;
                }
                
                return time >= operation.timespan;
            } else {
                return it->GetTimeSpan(timestamp) >= operation.timespan;
            }
        }

        return false;
    }

    // Положим в именованное расписание исполнителя выполнение операции
    void Appoint(const Work::Operation& operation, uint32_t id, uint64_t timestamp) {
        uint64_t time = 0;
        
        while (time < operation.timespan) {

        }
    }

    void PrintShedule() {
        for (auto inter : shedule_) {
            std::cout << inter.start << " || " << inter.end << std::endl;
        }
    }

private:
    // Hint: наверное здесь лучше подойдёт set<TimeInterval>, но я хз как
    // сделать, чтобы можно было искать интервал по временной метке.
    // нужно перегрузить операторы < и == ?
    // или учитывая что shedule_ сортированный, то можно бин_поиском искать
    // нужный
    const std::set<TimeInterval>
        shedule_;  // изначальное расписание исполнителя
    std::set<NamedTimeInterval>
        work_process_;  // расписание в которое будем класть назначенную
                        // операцию
};