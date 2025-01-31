#include "tool.h"
#include "work.h"


class ProblemData {
public:
    ProblemData(std::istream&& input);
private:
    std::vector<Tool> tools_;
    std::vector<Work> works_;
}