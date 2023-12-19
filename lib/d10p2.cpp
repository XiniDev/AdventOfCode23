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

struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &p) const {
        auto hash1 = std::hash<T>{}(p.first);
        auto hash2 = std::hash<U>{}(p.second);
        return hash1 ^ hash2;
    }
};

struct PairEqual {
    template <typename T, typename U>
    bool operator()(const std::pair<T, U> &lhs, const std::pair<T, U> &rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

std::string d10p2(const std::vector<std::string>& p_lines)
{
    int total = 0;

    const std::unordered_map<char, std::bitset<4>> pipeToBitsetMap =
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
                pipeVec2D[lineNum].push_back(pipeToBitsetMap.at(line[i]));
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

    std::unordered_map<std::pair<int, int>, std::bitset<4>, PairHash, PairEqual> loopMap;

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

                loopMap.insert({currPos, pipeVec2D[currPos.first][currPos.second]});
                break;
            }
        }

        count++;

        if (count != 0 && currPos == startPos)
            repeat = false;
    }

    int numberOfInsides = 0;

    // pipes on the edge of the input can never be inside the loop
    for (int i = 1; i < static_cast<int>(pipeVec2D.size() - 1); i++)
    {
        for (int j = 1; j < static_cast<int>(pipeVec2D[i].size() - 1); j++)
        {
            if (loopMap.contains(std::make_pair(i, j)))
                continue;

            int repCount = 0;
            char lastConnective;
            for (int k = j - 1; k >= 0; k--)
            {
                if (auto search = loopMap.find(std::make_pair(i, k)); search != loopMap.end())
                {
                    // increase repCount for '|' pipe connections or 'L / F' ... '-' ... 'J / 7' pipe connections (L7 or FJ counts as odd, LJ or F7 counts as even)
                    if (search->second == pipeToBitsetMap.at('|'))
                        repCount++;
                    else if (search->second == pipeToBitsetMap.at('J'))
                        lastConnective = 'J';
                    else if (search->second == pipeToBitsetMap.at('7'))
                        lastConnective = '7';
                    else if (search->second == pipeToBitsetMap.at('L') && lastConnective == '7')
                        repCount++;
                    else if (search->second == pipeToBitsetMap.at('F') && lastConnective == 'J')
                        repCount++;
                }
            }

            if (repCount % 2 == 1) numberOfInsides++;
        }
    }

    total = numberOfInsides;

    return std::to_string(total);
}