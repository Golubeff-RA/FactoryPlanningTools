#pragma once
#include <cstdint>
#include <optional>
#include <set>
#include <vector>
#include <iostream>

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

    Tool(std::initializer_list<TimeInterval>&& shedule) : shedule_(shedule) {}

    bool CanStartWork(const Work::Operation& operation, uint64_t timestamp, uint64_t timespan) {
        auto it = GetStartIterator(timestamp);
        if (it == shedule_.end()) {
            return false;
        }

        TimeInterval interval{timestamp, timestamp};
        // мы можем попробовать начать выполнение операции, но
        // надо убедиться, что в рабочем расписании есть место.
        // проверим не занят ли исполнитель в это время
        for (auto& gant : work_process_) {
            if (gant.Intersects(interval)) {
                return false;
            }
        }

        if (operation.stoppable) {
            uint64_t time = 0;
            while (it != shedule_.end() && time < timespan) {
                time += it->GetTimeSpan(timestamp);
                it = std::next(it);
                timestamp = it->start;
            }

            return time >= timespan;
        } else {
            return it->GetTimeSpan(timestamp) >= timespan;
        }
    }

    // Положим в именованное расписание исполнителя выполнение операции
    void Appoint(Work::Operation& operation, uint32_t id,
                 uint64_t timestamp, uint64_t timespan) {
        uint64_t time = 0;
        auto it = GetStartIterator(timestamp);
        operation.start_time = timestamp;
        while (it != shedule_.end() && time < timespan) {
            work_process_.insert({timestamp, std::min(it->end, timestamp + timespan - time), id});
            time += it->GetTimeSpan(timestamp);
            it = std::next(it);
            timestamp = it->start;
        }
        operation.end_time = (work_process_.end().operator--())->end;
    }

    void PrintShedule() {
        for (auto inter : shedule_) {
            std::cout << "(" << inter.start << ", " << inter.end << ") ";
        }
    }

    void PrintGant() {
        for (auto inter : work_process_) {
            std::cout << "(" << inter.start << ", " << inter.end << ", " << inter.operation << ") ";
        }
    }

private:
    std::set<Tool::TimeInterval>::const_iterator GetStartIterator(
        uint64_t timestamp) {
        TimeInterval interval{timestamp, timestamp};
        auto it = shedule_.lower_bound(interval);

        if (it == shedule_.begin() && it->start > timestamp) {
            return shedule_.end();
        }

        if (it == shedule_.end() || it->start > timestamp) {
            it = std::prev(it);
        }

        if (timestamp >= it->start && timestamp < it->end) {
            return it;
        }

        return shedule_.end();
    }

    const std::set<TimeInterval>
        shedule_;  // изначальное расписание исполнителя
    std::set<NamedTimeInterval> work_process_;  // расписание в которое будем
                                                // класть назначенную операцию
};