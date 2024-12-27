#pragma once
#include <cstdint>
#include <optional>
#include <vector>

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
    };

    struct NamedTimeInterval : TimeInterval {
        NamedTimeInterval(uint64_t start, uint64_t end, uint32_t operation)
            : TimeInterval(start, end), operation(operation) {}
        const uint32_t operation;
    };

    Tool(const std::vector<TimeInterval>& shedule)
        : shedule_(std::move(shedule)) {}

    // вернёт индекс интервала из общего расписания, если исполнитель может
    // начать работу
    std::optional<size_t> CanStartWork(uint64_t timestamp) {
        // проверим есть ли эта временная метка в общем расписании исполнителя
        size_t answer = shedule_.size();
        for (size_t idx = 0; idx < shedule_.size(); ++idx) {
            if (timestamp >= shedule_[idx].start &&
                timestamp < shedule_[idx].end) {
                answer = idx;
            }
        }
        // проверим нет ли этой временной метки в именованном расписании
        // исполнителя
        if (answer != shedule_.size()) {
            for (const auto& named : work_process_) {
                if (named.start <= timestamp && named.end > timestamp) {
                    return std::nullopt;
                }
            }
        } else {
            return std::nullopt;
        }

        return answer;
    }

    bool IsAvailable(uint64_t timestamp, uint64_t timespan, bool stoppable) {
        auto idx = CanStartWork(timestamp);
        if (idx.has_value()) {
            // если операция прерываемая, то сумма длин всех интервалов начиная
            // с shedule_[idx] должна быть >= timespan
            if (stoppable) {
                uint64_t sum_span = shedule_[(*idx)++].GetTimeSpan(timestamp);
                while (sum_span < timespan && (*idx) < shedule_.size()) {
                    sum_span += shedule_[(*idx)++].GetTimeSpan();
                }
                return sum_span >= timespan;
            }
            // если непрерываемая то в интервале от idx должно быть
            // достаточно времени
            return shedule_[(*idx)].GetTimeSpan(timestamp) >= timespan;
        }

        return false;
    }

private:
    const std::vector<TimeInterval>
        shedule_;  // изначальное расписание исполнителя
    std::vector<NamedTimeInterval>
        work_process_;  // расписание в которое будем класть назначенную
                        // операцию
};