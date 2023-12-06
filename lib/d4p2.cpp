#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>

#include "Algorithms.hpp"

int cardWinnings(std::string p_line)
{
    std::vector<int> winNums;
    std::vector<int> yourNums;

    std::string str = p_line;
    std::size_t split = str.find(":");
    str.erase(0, split + 1);

    std::size_t mid = str.find('|');
    std::string winStr = str.substr(0, mid);
    std::string yourStr = str.substr(mid + 1, std::string::npos);
    
    std::istringstream issWin(winStr);
    int winNum;

    while (issWin >> winNum) {
        winNums.push_back(winNum);
    }
    
    std::istringstream issYour(yourStr);
    int yourNum;

    while (issYour >> yourNum) {
        yourNums.push_back(yourNum);
    }

    std::sort(winNums.begin(), winNums.end());
    std::sort(yourNums.begin(), yourNums.end());

    std::vector<int> intersection;
    std::set_intersection(winNums.begin(), winNums.end(), yourNums.begin(), yourNums.end(), std::back_inserter(intersection));

    return(intersection.size());
}

std::string d4p2(const std::vector<std::string>& p_lines)
{
    int sum = 0;

    int index = 0;
    std::vector<int> multiplier(p_lines.size(), 1);

    for (const std::string& line : p_lines)
    {
        int copiedCards = cardWinnings(line);
        for (int i = 0; i < multiplier[index]; i++)
        {
            for (int j = 1; j <= copiedCards; j++)
            {
                multiplier[index + j] += 1;
            }

            sum += 1;
        }

        index++;
    }

    return std::to_string(sum);
}