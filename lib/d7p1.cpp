#include <algorithm>
#include <sstream>
#include <vector>

#include "Algorithms.hpp"

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

struct Hand {
    int key;
    std::string cards;
    HandType type;
    int totalValue;
    int bidding;
};

std::string d7p1(const std::vector<std::string>& p_lines)
{
    int winnings = 0;

    std::vector<Hand> hands;

    for (const std::string& line : p_lines)
    {
        std::size_t pos = line.find(' ');
        if (pos != std::string::npos)
        {
            std::string handCards = line.substr(0, pos);

            // type calculation
            std::string sortedCards = handCards;
            std::sort(std::begin(sortedCards), std::end(sortedCards));

            char prev;
            int rep = 0;
            std::vector<int> repVec;
            for (const auto& c: sortedCards)
            {
                if (c == prev || rep == 0) rep++;
                else
                {
                    repVec.push_back(rep);
                    rep = 1;
                }
                prev = c;
            }
            repVec.push_back(rep);

            HandType handType;
            switch (repVec.size())
            {
                case 1:
                    handType = HandType::FIVE_OF_A_KIND;
                    break;
                case 2:
                    if (std::find(std::begin(repVec), std::end(repVec), 4) != std::end(repVec))
                        handType = HandType::FOUR_OF_A_KIND;
                    else
                        handType = HandType::FULL_HOUSE;
                    break;
                case 3:
                    if (std::find(std::begin(repVec), std::end(repVec), 3) != std::end(repVec))
                        handType = HandType::THREE_OF_A_KIND;
                    else
                        handType = HandType::TWO_PAIR;
                    break;
                case 4:
                    handType = HandType::ONE_PAIR;
                    break;
                case 5:
                    handType = HandType::HIGH_CARD;
                    break;
                default:
                    handType = HandType::HIGH_CARD;
                    break;
            }

            // value calculation
            int totalValue = 0;
            for (const auto& c: handCards)
            {
                int value;
                switch (c)
                {
                    case 'A':
                        value = 13;
                        break;
                    case 'K':
                        value = 12;
                        break;
                    case 'Q':
                        value = 11;
                        break;
                    case 'J':
                        value = 10;
                        break;
                    case 'T':
                        value = 9;
                        break;
                    default:
                        value = (c - 48) - 1;
                        break;
                }
                totalValue = totalValue * 13 + value;
            }

            // strongest value = (((13 * 13 + 13) * 13 + 13) * 13 + 13) * 13 + 13 = 402233

            hands.push_back(
                Hand
                {
                    .key = handType * 1000000 + totalValue,
                    .cards = handCards,
                    .type = handType,
                    .totalValue = totalValue,
                    .bidding = std::stoi(line.substr(pos + 1, std::string::npos))
                }
            );
        }
    }

    std::sort(std::begin(hands), std::end(hands), [] (const auto& lhs, const auto& rhs)
    {
        return lhs.key < rhs.key;
    });

    for (int i = 0; i < static_cast<int>(hands.size()); i++)
    {
        winnings += hands[i].bidding * (i + 1);
    }

    return std::to_string(winnings);
}