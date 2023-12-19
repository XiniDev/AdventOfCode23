#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

#include "Algorithms.hpp"

std::string d11p2(const std::vector<std::string>& p_lines)
{
    uint64_t sum = 0;

    std::vector<std::pair<int, int>> galaxies;

    std::vector<bool> emptyRows(p_lines[0].size(), true);
    std::vector<bool> emptyCols(p_lines.size(), true);
    int lineNum = 0;

    for (const std::string& line : p_lines)
    {
        for (int i = 0; i < static_cast<int>(line.size()); i++)
        {
            if (line[i] == '#')
            {
                galaxies.push_back(std::make_pair(i, lineNum));
                emptyRows[lineNum] = false;
                emptyCols[i] = false;
            }
        }

        lineNum++;
    }

    uint64_t pairDists = 0;

    for (int i = 0; i < static_cast<int>(galaxies.size()); i++)
    {
        for (int j = i + 1; j < static_cast<int>(galaxies.size()); j++)
        {
            int dist = 0;

            int xExpansion = 0;
            int xDiff = std::abs(galaxies[i].first - galaxies[j].first);
            for (int k = 0; k < xDiff; k++)
            {
                int base = (galaxies[i].first < galaxies[j].first) ? galaxies[i].first : galaxies[j].first;
                if (emptyCols[k + base]) xExpansion += (1000000 - 1);
            }

            int yExpansion = 0;
            int yDiff = std::abs(galaxies[i].second - galaxies[j].second);
            for (int k = 0; k < yDiff; k++)
            {
                int base = (galaxies[i].second < galaxies[j].second) ? galaxies[i].second : galaxies[j].second;
                if (emptyRows[k + base]) yExpansion += (1000000 - 1);
            }
            // L1 distance = |x_1 − x_2| + |y_1 − y_2|
            dist = xDiff + xExpansion + yDiff + yExpansion;
            pairDists += dist;
        }
        
    }

    sum = pairDists;

    return std::to_string(sum);
}