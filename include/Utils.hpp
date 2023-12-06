#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace utils
{
    std::vector<std::string> fileLinesToArray(const std::string& p_fileName)
    {
        std::ifstream inputFile(p_fileName);
        std::vector<std::string> lines;

        if (inputFile.is_open())
        {
            std::string line;
            while (std::getline(inputFile, line))
            {
                lines.push_back(line);
            }
            inputFile.close();
        }
        else
        {
            std::cout << "Unable to open file: " << p_fileName << std::endl;
        }

        return lines;
    }

    void writeSolution(const std::string& p_fileName, const std::string& p_result)
    {
        std::ofstream outputFile(p_fileName);
        if (outputFile.is_open()) {
            outputFile << p_result;
            outputFile.close();
        }
        else
        {
            std::cout << "Unable to open file: " << p_fileName << std::endl;
        }
    }
}