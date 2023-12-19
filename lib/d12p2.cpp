#include <algorithm>
#include <cstdint>
#include <numeric>
#include <sstream>
#include <vector>

#include "Algorithms.hpp"

std::string d12p2(const std::vector<std::string>& p_lines)
{
    std::uint64_t sum = 0;

    for (const std::string& line : p_lines)
    {
        std::string groupings;
        std::vector<int> tempNumVec;

        std::size_t pos = line.find(' ');
        if (pos != std::string::npos)
        {
            groupings = line.substr(0, pos);
            std::string numStr = line.substr(pos + 1, std::string::npos);

            std::istringstream iss(numStr);
            std::string number;

            while (std::getline(iss, number, ','))
            {
                int num = std::stoi(number);
                tempNumVec.push_back(num);
            }
        }

        std::string repeat = groupings;
        for (int i = 0; i < (5 - 1); i++)
        {
            groupings += ("?" + repeat);
        }

        std::vector<int> numVec;
        for (int i = 0; i < 5; i++) {
            numVec.insert(std::end(numVec), std::begin(tempNumVec), std::end(tempNumVec));
        }

        int numVecSize = static_cast<int>(numVec.size());
        int groupingsSize = static_cast<int>(groupings.size());

        std::vector<std::vector<std::uint64_t>> dpTable(numVecSize + 1, std::vector<std::uint64_t>(groupingsSize + 1, 0));

        dpTable[0][0] = 1;

        std::vector<int> numVecSums;

        // both i and j are counted from 1 for the dynamic programming table to have an extra row and column for base case
        for (int i = 0; i < (numVecSize + 1); i++)
        {
            // sum up the numbers in numVec with spaces to get the shortest length possible for current combination
            if (i != 0)
                numVecSums.push_back(std::accumulate(std::begin(numVec), std::begin(numVec) + i, 0) + i - 1);

            for (int j = 1; j < (groupingsSize + 1); j++)
            {
                if (i == 0)
                {
                    if (groupings[j - 1] == '.' || groupings[j - 1] == '?')
                        dpTable[i][j] = dpTable[i][j - 1];
                }
                else
                {
                    if (groupings[j - 1] == '.' || groupings[j - 1] == '?')
                        dpTable[i][j] += dpTable[i][j - 1];

                    if (groupings[j - 1] == '#' || groupings[j - 1] == '?')
                    {
                        // if sum is within the limits of current index j, and
                        // there are no '.' within the space between the current number and j, and
                        // avoiding consecutive '#'s for different numbers
                        if (numVecSums[i - 1] <= j &&
                            groupings.substr(j - numVec[i - 1], numVec[i - 1]).find('.') == std::string::npos &&
                            (groupings[j - numVec[i - 1] - 1] != '#' ||
                            (numVecSums[i - 1] == j &&
                            std::all_of(std::begin(numVecSums), std::end(numVecSums), [groupings, j] (int pos)
                            {
                                if (pos < j)
                                    return groupings[pos] != '#';
                                else
                                    return true;
                            }))))
                            {
                                    if (i == 1)
                                        dpTable[i][j] += dpTable[i - 1][j - numVec[i - 1]];
                                    else
                                        dpTable[i][j] += dpTable[i - 1][j - numVec[i - 1] - 1];
                            }
                    }
                }
            }
        }
        sum += dpTable[numVecSize][groupingsSize];
    }

    return std::to_string(sum);
}