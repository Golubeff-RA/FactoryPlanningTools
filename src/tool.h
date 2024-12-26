#pragma once
#include <optional>
#include <vector>
#include <cstdint>

class Tool {
public:
    struct TimeInterval {
        uint64_t GetTimeSpan() const {
            return end - start;
        }
        const uint64_t start;
        const uint64_t end;
    };

    struct NamedTimeInterval : TimeInterval {
        const uint32_t operation;
    };

    Tool(const std::vector<TimeInterval>& shedule) : shedule_(std::move(shedule)) {
    }

    std::optional<size_t> CanStartWork(uint64_t timestamp) {
        for (size_t idx = 0; idx < shedule_.size(); ++idx) {
            if (timestamp > shedule_[idx].start && timestamp < shedule_[idx].end) {
                return idx;
            }
        }

        return std::nullopt;
    }

    bool Available(uint64_t timestamp) {
        if (CanStartWork(timestamp))
    }


private:
    const std::vector<TimeInterval> shedule_;
    std::vector<NamedTimeInterval> work_process_;
};