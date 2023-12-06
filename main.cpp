#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>

#include "Algorithms.hpp"
#include "Utils.hpp"

// they will always return a submit answer
using FunctionPtr = std::function<std::string(const std::vector<std::string>&)>;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Please enter the advent date and the advent part as the argv:\n./main [advent date] [advent part]" << std::endl;
        return 0;
    }
    std::string adventDate = argv[1];
    std::string adventPart = argv[2];

    std::string fileName = "inputs/" + adventDate + "/" + adventPart + "/input.txt";
    std::vector<std::string> lines = utils::fileLinesToArray(fileName);

    // d1p1 = 0, d1p2 = 1, d2p2 = 2, ...
    int functionNumber = (std::stoi(adventDate) - 1) * 2 + std::stoi(adventPart) - 1;

    // 50 stars
    FunctionPtr functions[50] = 
    {
        &d1p1,
        &d1p2,
        &d2p1,
        &d2p2,
        &d3p1,
        &d3p2,
        &d4p1,
        &d4p2,
    };

    if (functionNumber >= 0 && functionNumber < 50)
    {
        std::string result = functions[functionNumber](lines);
        std::string outputFile = "solutions/d" + adventDate + "p" + adventPart + ".txt";
        utils::writeSolution(outputFile, result);
    }

    return 0;
}