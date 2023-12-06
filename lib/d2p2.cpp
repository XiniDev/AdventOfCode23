#include <cctype>
#include <cmath>

#include "Algorithms.hpp"

std::string d2p2(const std::vector<std::string>& p_lines)
{
    int sum = 0;

    for (const std::string& line : p_lines)
    {
        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        std::string str = line;
        std::size_t split = str.find(":");
        str.erase(0, split + 1);
        do
        {
            split = str.find(";");
            std::string token = str.substr(0, split);
            str.erase(0, split + 1);

            std::size_t red = token.find("red");
            if (red != std::string::npos)
            {
                int i = 2;
                int num = 0;
                while (!std::isspace(token[red - i]))
                {
                    num += (token[red - i] - 48) * (std::pow(10, i - 2));
                    i++;
                }
                if (num > maxRed)
                    maxRed = num;
            }

            std::size_t green = token.find("green");
            if (green != std::string::npos)
            {
                int i = 2;
                int num = 0;
                while (!std::isspace(token[green - i]))
                {
                    num += (token[green - i] - 48) * (std::pow(10, i - 2));
                    i++;
                }
                if (num > maxGreen)
                    maxGreen = num;
            }

            std::size_t blue = token.find("blue");
            if (blue != std::string::npos)
            {
                int i = 2;
                int num = 0;
                while (!std::isspace(token[blue - i]))
                {
                    num += (token[blue - i] - 48) * (std::pow(10, i - 2));
                    i++;
                }
                if (num > maxBlue)
                    maxBlue = num;
            }
        }
        while (split != std::string::npos);

        sum += (maxRed * maxGreen * maxBlue);
    }

    return std::to_string(sum);
}