#include <sstream>
#include <unordered_map>
#include <vector>

#include "Algorithms.hpp"

struct Node
{
    std::string left;
    std::string right;
};

std::string d8p1(const std::vector<std::string>& p_lines)
{
    int steps = 0;

    int lineNum = 0;
    std::vector<int> directions;
    std::unordered_map<std::string, Node> nodeMap;

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
        }
    }

    std::string location = "AAA";
    const std::string end = "ZZZ";
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

            if (location == "ZZZ")
            {
                repeat = false;
                break;
            }
        }
    }

    steps = counter;

    return std::to_string(steps);
}