#include <algorithm>
#include <cstdint>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

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

std::string d5p1(const std::vector<std::string>& p_lines)
{
    std::uint64_t min = 0;

    std::vector<std::uint64_t> seeds;
    std::vector<std::unordered_map<std::pair<std::uint64_t, std::uint64_t>, std::pair<std::uint64_t, std::uint64_t>, PairHash, PairEqual>> mappings;
    int category = -1;

    for (const std::string& line : p_lines)
    {
        if (line.find("seeds:") != std::string::npos)
        {
            std::string str = line;
            std::size_t split = str.find(":");
            str.erase(0, split + 1);

            std::istringstream issSeeds(str);
            std::uint64_t seedNum;

            while (issSeeds >> seedNum)
            {
                seeds.push_back(seedNum);
            }
        }
        else if (line.find("map:") != std::string::npos)
        {
            category++;
            std::unordered_map<std::pair<std::uint64_t, std::uint64_t>, std::pair<std::uint64_t, std::uint64_t>, PairHash, PairEqual> mapping;
            mappings.push_back(mapping);
        }
        else if (line.find_first_of("0123456789") != std::string::npos)
        {
            std::vector<std::uint64_t> temp;
            std::string str = line;
            std::istringstream issMapping(str);
            std::uint64_t mappingNum;

            while (issMapping >> mappingNum) {
                temp.push_back(mappingNum);
            }

            mappings[category].insert({std::make_pair(temp[1], (temp[1] + temp[2] - 1)), std::make_pair(temp[0], (temp[0] + temp[2] - 1))});
        }
    }

    std::vector<std::uint64_t> locations;

    for (const auto& seed: seeds)
    {
        std::uint64_t location = seed;

        for (int i = 0; i <= category; i++)
        {
            for (const auto& mapping: mappings[i])
            {
                if (location >= mapping.first.first && location <= mapping.first.second)
                {
                    location += mapping.second.first - mapping.first.first;
                    break;
                }
            }
        }

        locations.push_back(location);
    }

    auto result = std::min_element(std::begin(locations), std::end(locations));
    min = *result;

    return std::to_string(min);
}