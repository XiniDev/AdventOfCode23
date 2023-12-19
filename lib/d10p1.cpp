#include <bitset>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Algorithms.hpp"

enum Directions {
    NORTH = 3,
    EAST = 2,
    SOUTH = 1,
    WEST = 0,
};

std::string d10p1(const std::vector<std::string>& p_lines)
{
    int steps = 0;

    const std::unordered_map<char, std::bitset<4>> pipeNeighboursMap =
    {
        {'|', std::bitset<4>("1010")},
        {'-', std::bitset<4>("0101")},
        {'L', std::bitset<4>("1100")},
        {'J', std::bitset<4>("1001")},
        {'7', std::bitset<4>("0011")},
        {'F', std::bitset<4>("0110")},
        {'.', std::bitset<4>("0000")},
    };

    std::vector<std::vector<std::bitset<4>>> pipeVec2D;
    std::pair<int, int> startPos;
    int lineNum = 0;

    int totalLines = static_cast<int>(p_lines.size());
    int lineSize = static_cast<int>(p_lines[0].size());

    for (const std::string& line : p_lines)
    {
        pipeVec2D.push_back(std::vector<std::bitset<4>>());

        for (int i = 0; i < lineSize; i++)
        {
            if (line[i] != 'S')
                pipeVec2D[lineNum].push_back(pipeNeighboursMap.at(line[i]));
            else
            {
                pipeVec2D[lineNum].push_back(std::bitset<4>("0000"));
                startPos = std::make_pair(lineNum, i);
            }
        }

        lineNum++;
    }

    if (startPos.first > 0 && pipeVec2D[startPos.first - 1][startPos.second][Directions::SOUTH])
        pipeVec2D[startPos.first][startPos.second].set(Directions::NORTH);
    if (startPos.first < (totalLines - 1) && pipeVec2D[startPos.first + 1][startPos.second][Directions::NORTH])
        pipeVec2D[startPos.first][startPos.second].set(Directions::SOUTH);
    if (startPos.second > 0 && pipeVec2D[startPos.first][startPos.second - 1][Directions::EAST])
        pipeVec2D[startPos.first][startPos.second].set(Directions::WEST);
    if (startPos.second < (lineSize - 1) && pipeVec2D[startPos.first][startPos.second + 1][Directions::WEST])
        pipeVec2D[startPos.first][startPos.second].set(Directions::EAST);

    std::pair<int, int> currPos = startPos;
    Directions fromDir;
    for (int i = 0; i < 4; i++)
    {
        if (pipeVec2D[startPos.first][startPos.second][i])
        {
            fromDir = static_cast<Directions>(i);
            break;
        }
    }

    int count = 0;
    bool repeat = true;

    while (repeat)
    {
        for (int i = 0; i < 4; i++)
        {
            if (fromDir != static_cast<Directions>(i) && pipeVec2D[currPos.first][currPos.second][i])
            {
                switch (i)
                {
                    case Directions::NORTH:
                        currPos.first--;
                        fromDir = Directions::SOUTH;
                        break;
                    case Directions::SOUTH:
                        currPos.first++;
                        fromDir = Directions::NORTH;
                        break;
                    case Directions::WEST:
                        currPos.second--;
                        fromDir = Directions::EAST;
                        break;
                    case Directions::EAST:
                        currPos.second++;
                        fromDir = Directions::WEST;
                        break;
                    default:
                        break;
                }
                break;
            }
        }

        count++;

        if (count != 0 && currPos == startPos)
            repeat = false;
    }

    steps = count / 2;

    return std::to_string(steps);
}