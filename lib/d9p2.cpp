#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>

#include "Algorithms.hpp"

std::string d9p2(const std::vector<std::string>& p_lines)
{
    int sum = 0;

    for (const std::string& line : p_lines)
    {
        std::vector<int> readings;

        std::istringstream iss(line);
        int number;

        while (iss >> number)
        {
            readings.push_back(number);
        }

        std::vector<std::vector<int>> diffs;
        diffs.push_back(readings);
        int diffIndex = 0;

        bool repeat = true;
        while (repeat)
        {
            std::vector<int> newDiffs;
            int prev = diffs[diffIndex][0];
            for (int i = 1; i < static_cast<int>(diffs[diffIndex].size()); i++)
            {
                int diff = diffs[diffIndex][i] - prev;
                newDiffs.push_back(diff);
                prev = diffs[diffIndex][i];
            }

            diffs.push_back(newDiffs);
            diffIndex++;

            if (std::adjacent_find(std::begin(newDiffs), std::end(newDiffs), std::not_equal_to<int>()) == std::end(newDiffs))
                repeat = false;
        }

        int prevDiff = 0;
        for (int i = (static_cast<int>(diffs.size()) - 1); i >= 0; i--)
        {
            prevDiff = diffs[i].front() - prevDiff;
        }

        sum += prevDiff;
    }

    return std::to_string(sum);
}