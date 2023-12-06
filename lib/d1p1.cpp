#include <cctype>

#include "Algorithms.hpp"

std::string d1p1(const std::vector<std::string>& p_lines)
{
    int sum = 0;

    for (const std::string& line : p_lines)
    {
        int num_1, num_2;

        for (int i = 0; i < static_cast<int>(line.size()); i++)
        {
            if (std::isdigit(line[i]))
            {
                num_1 = (int)line[i] - 48;
                break;
            }
        }

        for (int i = static_cast<int>(line.size()) - 1; i >= 0; i--)
        {
            if (std::isdigit(line[i]))
            {
                num_2 = (int)line[i] - 48;
                break;
            }
        }

        int calibration = num_1 * 10 + num_2;
        sum += calibration;
    }

    return std::to_string(sum);
}