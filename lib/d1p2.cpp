#include <unordered_map>
#include <cctype>

#include "Algorithms.hpp"

std::string d1p2(const std::vector<std::string>& p_lines)
{
    const std::unordered_map<std::string, int> numbers =
    {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };

    int sum = 0;

    for (const std::string& line : p_lines)
    {
        std::string temp = line;

        for (const auto& pair : numbers)
        {
            std::size_t found = temp.find(pair.first);
            while (found != std::string::npos)
            {
                temp.insert(found + 1, std::to_string(pair.second));
                found = temp.find(pair.first, found + 1);
            }
        }

        int num_1, num_2;

        for (int i = 0; i < static_cast<int>(temp.size()); i++)
        {
            if (std::isdigit(temp[i]))
            {
                num_1 = (int)temp[i] - 48;
                break;
            }
        }

        for (int i = static_cast<int>(temp.size()) - 1; i >= 0; i--)
        {
            if (std::isdigit(temp[i]))
            {
                num_2 = (int)temp[i] - 48;
                break;
            }
        }

        int calibration = num_1 * 10 + num_2;
        sum += calibration;
    }

    return std::to_string(sum);
}