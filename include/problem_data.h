#pragma once
#include "tool.h"
#include "work.h"


class ProblemData {
public:
    //здесь будем парсить данные из файла
    ProblemData(std::istream&& input);
    std::vector<Tool> tools_;
    std::vector<Work> works_;
    std::vector<std::vector<uint64_t>> times_matrix_;
};