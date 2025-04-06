#pragma once
#include <fstream>
#include <string>
#include "tool.h"
#include "work.h"


class ProblemData {
public:
    //здесь будем парсить данные из файла
    ProblemData(std::ifstream &input);
    std::vector<Tool> tools_;
    std::vector<Work> works_;
    std::vector<std::vector<uint64_t>> times_matrix_;
    size_t getCntOperations() { return times_matrix_.size();}
    void print() {
        std::cout << "hkhkhk  ";
        for(auto t : works_) {
            t.print();
        }
    }
private:
    std::vector<bool> operationsContinius_;
    size_t indWork_ = 0;
    void fillTools(std::ifstream &input);
    void parseTools(std::string& str, int idTool);
    void fillContinius(std::ifstream &input);
    void fillOperations(std::ifstream &input);
    void fillTimes(std::ifstream &input);
    void fillGraph(std::ifstream &input);
    void fillStart(std::ifstream &input);
    void fillDirective(std::ifstream &input);
    void fillFines(std::ifstream &input);
    void fillWork(std::ifstream &input);
};
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
ProblemData::ProblemData(std::ifstream &input){ 
    std::string str;
    while(!input.eof()){
        std::getline(input, str);
        //std::cout << str << "\n";

        if(str == "TOOLS") {
            fillTools(input);
        } else if (str == "OPERATIONS") {
            fillOperations(input);
        } else if (str == "CONTINIOUS") {
            fillContinius(input);
        } else if (str == "TIMES") {
            fillTimes(input);
        } else if (str == "GRAPHS") {
            fillGraph(input);
        } else if (str == "START") {
            fillStart(input);
        } else if (str == "DIRECTIVE") {
            fillDirective(input);
        } else if (str == "FINES") {
            fillFines(input);
        } else if (str == "g") {
            fillWork(input);
        }
    }
}

void ProblemData::parseTools(std::string& str, int idTool){
    std::set<Tool::TimeInterval> schedule;
    std::string time1 = "", time2 = "";
    for(size_t i = 0; i< str.size();) {
        if(str[i] == '(') {
            ++i;
            while('0' <= str[i] && str[i] <= '9') {
                time1.push_back(str[i]);
                ++i;
            }
            continue;
        } else if (str[i] == ',') {
            i+=2;//числа разделяются запятой с пробелом
            while('0' <= str[i] && str[i] <= '9') {
                time2.push_back(str[i]);
                ++i;
            }
            continue;
        } else if (str[i] == ')') {
            schedule.insert(Tool::TimeInterval(std::stoi(time1), std::stoi(time2)));
            time1.clear();
            time2.clear();
        } 
        ++i;
    }
    tools_.push_back(Tool(schedule));
}

void ProblemData::fillTools(std::ifstream &input) {
    std::string str;
    std::getline(input, str);

    int cntTools = std::stoi(str);
    //tools_.resize(cntTools);
    for(int i = 0; i < cntTools && !input.eof(); ++i){
        std::getline(input, str);
        parseTools(str, i);
    }
}

void ProblemData::fillContinius(std::ifstream &input) {
    std::string str;

    size_t cntOperations = operationsContinius_.size();
    for(size_t i = 0; i < cntOperations && !input.eof(); ++i){
        input >> str;
        operationsContinius_[i] = (str == "1" ? true : false);
    }
}

void ProblemData::fillOperations(std::ifstream &input) {
    std::string str;
    std::getline(input, str);

    int cntOperations = std::stoi(str);
    operationsContinius_.resize(cntOperations);
}

void ProblemData::fillTimes(std::ifstream &input) {
    std::string str;
    
    size_t cntOperations = operationsContinius_.size();
    times_matrix_.resize(cntOperations);
    for(size_t i = 0; i < cntOperations && !input.eof(); ++i) {
        std::getline(input, str);
        str += " ";
        //times_matrix_.resize(cntTool);
        std::string number = "";
        for (auto e : str) {
            if ('0' <= e && e <= '9') {
                number.push_back(e);
            } else if (!number.empty()) {
                times_matrix_[i].push_back(std::stoi(number));
                number.clear();
            }
        }
    }
}

void ProblemData::fillGraph(std::ifstream &input) {
    std::string str;
    
    std::getline(input, str);
    int cntGraph = std::stoi(str);
    works_.resize(cntGraph, Work());
}

void ProblemData::fillStart(std::ifstream &input) {
    std::string str;
    
    for (size_t i = 0; i < works_.size(); ++i) {
        input >> str;
        works_[i].setStartTime(std::stoi(str));
    }
}

void ProblemData::fillDirective(std::ifstream &input) {
    std::string str;
    
    for (size_t i = 0; i < works_.size(); ++i) {
        input >> str;
        works_[i].setDirective(std::stoi(str));
    }
}

void ProblemData::fillFines(std::ifstream &input) {
    std::string str;
    
    for (size_t i = 0; i < works_.size(); ++i) {
        input >> str;
        works_[i].setFineCoef(std::stoi(str));
    }
}

void ProblemData::fillWork(std::ifstream &input) {
    std::vector<std::set<uint64_t>> g(operationsContinius_.size());
    std::string str1, str2;

    std::getline(input, str1);
    int cntRebr = std::stoi(str1);
    for (int i = 0; i < cntRebr; ++i) {
        input >> str1 >> str2;
        g[std::stoi(str1)].insert(std::stoi(str2));
    }

    std::vector<Work::Operation*> vOper;
    for (size_t i = 0; i < operationsContinius_.size(); ++i) {
        vOper.push_back(new Work::Operation(operationsContinius_[i], g[i], i));
    }
    
    works_[indWork_++].setOperations(vOper);
}