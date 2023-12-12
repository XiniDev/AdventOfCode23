#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

#include "Algorithms.hpp"

std::string d6p2(const std::vector<std::string>& p_lines)
{
    std::uint64_t prod = 0;

    std::pair<std::uint64_t, std::uint64_t> race;

    for (const std::string& line : p_lines)
    {
        bool time = (line.find("Time:") != std::string::npos) ? true : false;

        std::string str = line;
        std::size_t split = str.find(":");
        str.erase(0, split + 1);

        str.erase(std::remove_if(std::begin(str), std::end(str), [](const unsigned char c) 
        {
            return std::isspace(c);
        }), std::end(str));

        std::istringstream iss(str);
        std::uint64_t number;

        while (iss >> number)
        {
            if (time) race = std::make_pair(number, 0);
            else race.second = number;
        }
    }

    std::uint64_t counter = 0;

    for (std::uint64_t i = 0; i <= race.first; i++)
    {
        std::uint64_t distance = i * (race.first - i);
        if (distance > race.second) counter++;
    }
    
    prod = counter;

    return std::to_string(prod);
}