#include <cstdint>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Algorithms.hpp"

struct Node
{
    std::string left;
    std::string right;
};

std::string d8p2(const std::vector<std::string>& p_lines)
{
    std::uint64_t steps = 0;

    int lineNum = 0;
    std::vector<int> directions;
    std::unordered_map<std::string, Node> nodeMap;

    std::vector<std::string> locations;

    for (const std::string& line : p_lines)
    {
        lineNum++;
        if (lineNum == 1)
        {
            for (const auto& c : line)
            {
                if (c == 'L') directions.push_back(0);
                else directions.push_back(1);
            }
        }
        else if (lineNum == 2) continue;
        else
        {
            Node node;
            std::string data = line.substr(0, 3);
            std::string left = line.substr(7, 3);
            std::string right = line.substr(12, 3);

            nodeMap.insert({data, Node
            {
                .left = left,
                .right = right
            }});

            if (data[2] == 'A') locations.push_back(data);
        }
    }

    std::vector<int> counters;

    for (auto location : locations)
    {
        bool repeat = true;
        int counter = 0;

        while (repeat)
        {
            for (const int lr : directions)
            {
                if (auto search = nodeMap.find(location); search != std::end(nodeMap))
                {
                    if (lr == 0) location = (search->second).left;
                    else location = (search->second).right;
                }

                counter++;

                if (location[2] == 'Z')
                {
                    repeat = false;
                    break;
                }
            }
        }

        counters.push_back(counter);
    }

    std::uint64_t mult = 1;
    for (const auto& counter: counters)
    {
        mult = std::lcm(mult, counter);
    }

    steps = mult;

    return std::to_string(steps);
}