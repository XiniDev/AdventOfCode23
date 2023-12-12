#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>

#include "Algorithms.hpp"

std::string d4p1(const std::vector<std::string>& p_lines)
{
    int sum = 0;

    for (const std::string& line : p_lines)
    {
        std::vector<int> winNums;
        std::vector<int> yourNums;

        std::string str = line;
        std::size_t split = str.find(":");
        str.erase(0, split + 1);

        std::size_t mid = str.find('|');
        std::string winStr = str.substr(0, mid);
        std::string yourStr = str.substr(mid + 1, std::string::npos);
        
        std::istringstream issWin(winStr);
        int winNum;

        while (issWin >> winNum)
        {
            winNums.push_back(winNum);
        }
        
        std::istringstream issYour(yourStr);
        int yourNum;

        while (issYour >> yourNum)
        {
            yourNums.push_back(yourNum);
        }

        std::sort(winNums.begin(), winNums.end());
        std::sort(yourNums.begin(), yourNums.end());

        std::vector<int> intersection;
        std::set_intersection(winNums.begin(), winNums.end(), yourNums.begin(), yourNums.end(), std::back_inserter(intersection));

        if (intersection.size() > 0) sum += pow(2, (intersection.size() - 1));
    }

    return std::to_string(sum);
}