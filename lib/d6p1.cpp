#include <functional>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

#include "Algorithms.hpp"

std::string d6p1(const std::vector<std::string>& p_lines)
{
    int prod = 0;

    std::vector<std::pair<int, int>> races;

    for (const std::string& line : p_lines)
    {
        bool time = (line.find("Time:") != std::string::npos) ? true : false;

        std::string str = line;
        std::size_t split = str.find(":");
        str.erase(0, split + 1);

        std::istringstream iss(str);
        int number;

        int issInd = 0;
        while (iss >> number)
        {
            if (time) races.push_back(std::make_pair(number, 0));
            else races[issInd].second = number;
            issInd++;
        }
    }

    std::vector<int> counters;

    for (const auto& race : races)
    {
        int counter = 0;

        for (int i = 0; i <= race.first; i++)
        {
            int distance = i * (race.first - i);
            if (distance > race.second) counter++;
        }

        counters.push_back(counter);
    }

    prod = std::accumulate(std::begin(counters), std::end(counters), 1, std::multiplies<int>());

    return std::to_string(prod);
}