#include <array>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Algorithms.hpp"

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

std::string d3p1(const std::vector<std::string>& p_lines)
{
    int sum = 0;
    int lineNum = 0;

    std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual> numMap;
    std::unordered_set<std::pair<int, int>, PairHash, PairEqual> symSet;

    for (const std::string& line : p_lines)
    {
        int posNum = -1;

        for (int i = 0; i < static_cast<int>(line.size()); i++)
        {
            std::pair<int, int> pos = std::make_pair(lineNum, i);

            if (line[i] == 46 || std::isalpha(line[i]))
                posNum = -1;
            else if (std::isdigit(line[i]))
            {
                std::pair<int, int> prevPos = std::make_pair(lineNum, posNum);
                auto it = numMap.find(prevPos);
                if (it != numMap.end())
                    it->second = it->second * 10 + (line[i] - 48);
                else
                {
                    posNum = i;
                    numMap[pos] = line[i] - 48;
                }
            }
            else
            {
                posNum = -1;
                symSet.insert(pos);
            }
        }

        lineNum++;
    }

    for (const auto& pair: numMap)
    {
        bool found = false;
        int numSize = static_cast<int>(log10(pair.second) + 1);

        for (int i = 0; i < numSize; i++)
        {
            std::array<std::pair<int, int>, 8> directionPairs =
            {
                std::make_pair(pair.first.first - 1, pair.first.second + i - 1),        // top left
                std::make_pair(pair.first.first - 1, pair.first.second + i),            // top
                std::make_pair(pair.first.first - 1, pair.first.second + i + 1),        // top right
                std::make_pair(pair.first.first, pair.first.second + i + 1),            // right
                std::make_pair(pair.first.first + 1, pair.first.second + i + 1),        // bottom right
                std::make_pair(pair.first.first + 1, pair.first.second + i),            // bottom
                std::make_pair(pair.first.first + 1, pair.first.second + i - 1),        // bottom left
                std::make_pair(pair.first.first, pair.first.second + i - 1)             // left
            };

            for (int j = 0; j < 8; j++)
            {
                if (symSet.find(directionPairs[j]) != symSet.end())
                {
                    found = true;
                    break;
                }
            }

            if (found) break;
        }

        if (found) sum += pair.second;
    }

    return std::to_string(sum);
}