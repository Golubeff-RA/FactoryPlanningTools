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

    Tool(std::vector<TimeInterval>&& shedule) : shedule_(std::move(shedule)) {
    }

    bool CanStartWork(uint64_t timestamp) {
        
    }
private:
    const std::vector<TimeInterval> shedule_;
    std::vector<NamedTimeInterval> work_process_;
};