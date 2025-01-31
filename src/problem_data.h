#pragma once
#include "tool.h"
#include "work.h"


class ProblemData {
public:
    //здесь будем парсить данные из файла
    ProblemData(std::istream&& input);
    std::vector<Tool> tools_;
    std::vector<Work> works_;
}