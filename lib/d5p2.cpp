#include <algorithm>
#include <cmath>
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

std::string d5p2(const std::vector<std::string>& p_lines)
{
    std::int64_t min = 0;

    std::vector<std::pair<std::int64_t, std::int64_t>> seedRanges;
    std::vector<std::unordered_map<std::pair<std::int64_t, std::int64_t>, std::pair<std::int64_t, std::int64_t>, PairHash, PairEqual>> mappings;
    int category = -1;

    for (const std::string& line : p_lines)
    {
        if (line.find("seeds:") != std::string::npos)
        {
            std::string str = line;
            std::size_t split = str.find(":");
            str.erase(0, split + 1);

            std::vector<std::int64_t> temp;
            std::istringstream issSeeds(str);
            std::int64_t seedNum;

            while (issSeeds >> seedNum)
            {
                temp.push_back(seedNum);
            }

            std::int64_t firstNum;
            for (int i = 0; i < static_cast<int>(temp.size()); i++)
            {
                if (i % 2 == 0) firstNum = temp[i];
                else seedRanges.push_back(std::make_pair(firstNum, firstNum + temp[i] - 1));
            }
        }
        else if (line.find("map:") != std::string::npos)
        {
            category++;
            std::unordered_map<std::pair<std::int64_t, std::int64_t>, std::pair<std::int64_t, std::int64_t>, PairHash, PairEqual> mapping;
            mappings.push_back(mapping);
        }
        else if (line.find_first_of("0123456789") != std::string::npos)
        {
            std::vector<std::int64_t> temp;
            std::string str = line;
            std::istringstream issMapping(str);
            std::int64_t mappingNum;

            while (issMapping >> mappingNum) {
                temp.push_back(mappingNum);
            }

            mappings[category].insert({std::make_pair(temp[1], (temp[1] + temp[2] - 1)), std::make_pair(temp[0], (temp[0] + temp[2] - 1))});
        }
    }

    std::vector<std::pair<std::int64_t, std::int64_t>> locationRanges = seedRanges;

    for (int i = 0; i <= category; i++)
    {
        std::vector<std::pair<std::int64_t, std::int64_t>> mappedRanges;

        for (const auto& mapping: mappings[i])
        {
            std::vector<std::pair<std::int64_t, std::int64_t>> tempRanges;

            for (int j = 0; j < static_cast<int>(locationRanges.size()); j++)
            {
                if (locationRanges[j].first > mapping.first.second || locationRanges[j].second < mapping.first.first)
                {
                    tempRanges.push_back(locationRanges[j]);
                    continue;
                }

                // add the head and tail pairs that isn't mapped
                if (locationRanges[j].first < mapping.first.first)
                {
                    tempRanges.push_back(std::make_pair(locationRanges[j].first, mapping.first.first - 1));
                    locationRanges[j].first = mapping.first.first;
                }
                if (locationRanges[j].second > mapping.first.second)
                {
                    tempRanges.push_back(std::make_pair(mapping.first.second + 1, locationRanges[j].second));
                    locationRanges[j].second = mapping.first.second;
                }

                // create a new mapped pair that already performed the linear transformations
                std::pair<std::int64_t, std::int64_t> mapPair = std::make_pair
                (
                    (locationRanges[j].first + mapping.second.first - mapping.first.first),
                    (locationRanges[j].second + mapping.second.second - mapping.first.second)
                );

                mappedRanges.push_back(mapPair);
            }

            locationRanges = tempRanges;
        }

        for (const auto& mappedRange: mappedRanges)
        {
            locationRanges.push_back(mappedRange);
        }
    }

    auto result = std::min_element(std::begin(locationRanges), std::end(locationRanges), [](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    min = (*result).first;

    return std::to_string(min);
}