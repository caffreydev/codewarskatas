namespace Poker;

using NUnit.Framework;
using System;
using System.Linq;
using System.Collections.Generic;


public enum Result 
{ 
    Win, 
    Loss, 
    Tie 
}

public enum Suit
{
    Hearts,
    Spades,
    Clubs,
    Diamonds
}

public class Card
{
    public char Value { get; set; }
    public Suit Suit { get; set; }
    public int Rank { get; set; }
}

public class PokerHand
{
    private List<Card> _hand { get; set; }

    public PokerHand(string hand)
    {
        this._hand = ToCardList(hand);
    }

    public Result CompareWith(PokerHand hand)
    {
        return hand.CompareHands(this._hand);
    }

    public Result CompareHands(List<Card> hand)
    {
        var hand1StraightFlush = IsStraightFlush(hand);
        var hand2StraightFlush = IsStraightFlush(this._hand);   
        if (hand1StraightFlush.Item1 && hand2StraightFlush.Item1)
        {
            var diff = hand1StraightFlush.Item2 - hand2StraightFlush.Item2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            return Result.Tie;
        }
        if (hand1StraightFlush.Item1)
            return Result.Win;
        if (hand2StraightFlush.Item1)
            return Result.Loss;
        
        var hand1FourOfAKind = IsFourOfAKind(hand);
        var hand2FourOfAKind = IsFourOfAKind(this._hand);
        
        if (hand1FourOfAKind.Item1 && hand2FourOfAKind.Item1)
        {
            var val1 = hand1FourOfAKind.Item2;
            var val2 = hand2FourOfAKind.Item2;
            var diff = val1 - val2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            int highCard1 = 0;
            int highCard2 = 0;

            foreach (Card card in hand)
            {
                if (card.Rank != val1)
                {
                    highCard1 = card.Rank;
                    break;
                }
            }

            foreach (Card card in this._hand)
            {
                if (card.Rank != val2)
                {
                    highCard2 = card.Rank;
                    break;
                }
            }

            diff = highCard1 - highCard2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            return Result.Tie;
        }

        if (hand1FourOfAKind.Item1)
            return Result.Win;
        if (hand2FourOfAKind.Item1)
            return Result.Loss;

        var hand1FullHouse = IsFullHouse(hand);
        var hand2FullHouse = IsFullHouse(this._hand);
        if (hand1FullHouse.Item1 && hand2FullHouse.Item1)
        {
            var vals1 = hand1FullHouse.Item2;
            var vals2 = hand2FullHouse.Item2;
            var diff = vals1.Item1 - vals2.Item1;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            diff = vals1.Item2 - vals2.Item2;

            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            return Result.Tie;
        }

        if (hand1FullHouse.Item1)
            return Result.Win;
        if (hand2FullHouse.Item1)
            return Result.Loss;


        var hand1Flush = IsFlush(hand);
        var hand2Flush = IsFlush(this._hand);
        if (hand1Flush && hand2Flush)
        {
            for (int i = 4; i >= 0; i--)
            {
                var diff = hand[i].Rank - this._hand[i].Rank;
                if (diff > 0)
                {
                    return Result.Win;
                }
                if (diff < 0)
                {
                    return Result.Loss;
                }
            }
            return Result.Tie;
        }

        if (hand1Flush)
            return Result.Win;
        if (hand2Flush)
            return Result.Loss;

        var hand1Straight = IsStraight(hand);
        var hand2Straight = IsStraight(this._hand);
        if (hand1Straight.Item1 && hand2Straight.Item1)
        {
            var diff = hand1Straight.Item2 - hand2Straight.Item2;
            if (diff > 0)
                {
                    return Result.Win;
                }
                if (diff < 0)
                {
                    return Result.Loss;
                }
                return Result.Tie;
        }

        if (hand1Straight.Item1)
            return Result.Win;
        if (hand2Straight.Item1)
            return Result.Loss;

        var hand1ThreeOfAKind = IsThreeOfAKind(hand);
        var hand2ThreeOfAKind = IsThreeOfAKind(this._hand);

        if (hand1ThreeOfAKind.Item1 && hand2ThreeOfAKind.Item1)
        {
            var val1 = hand1ThreeOfAKind.Item2;
            var val2 = hand2ThreeOfAKind.Item2;
            var diff = val1 - val2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }

            var highCards1 = new List<int>();
            var highCards2 = new List<int>();
            foreach (var card in hand)
            {
                if (card.Rank != val1)
                {
                    highCards1.Add(card.Rank);
                }
            }

            foreach (var card in this._hand)
            {
                if (card.Rank != val2)
                {
                    highCards2.Add(card.Rank);
                }
            }

            diff = highCards1.Max() - highCards2.Max();
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            
            diff = highCards1.Min() - highCards2.Min();
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            return Result.Tie;
        }

        if (hand1ThreeOfAKind.Item1)
            return Result.Win;
        if (hand2ThreeOfAKind.Item1)
            return Result.Loss;

        var hand1TwoPair = IsTwoPair(hand);
        var hand2TwoPair = IsTwoPair(this._hand);

        if (hand1TwoPair.Item1 && hand2TwoPair.Item1)
        {
            var vals1 = hand1TwoPair.Item2;
            var vals2 = hand2TwoPair.Item2;
            var diff = vals1.Item1 - vals2.Item1;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }

            diff = vals1.Item2 - vals2.Item2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }


            int highCard1 = 0;
            int highCard2 = 0;

            foreach (Card card in hand)
            {
                if (card.Rank != vals1.Item1 && card.Rank != vals1.Item2)
                    highCard1 = card.Rank;
                    break;
            }

            foreach (Card card in this._hand)
            {
                if (card.Rank != vals2.Item1 && card.Rank != vals2.Item2)
                    highCard2 = card.Rank;
                    break;
            }

            diff = highCard1 - highCard2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }
            return Result.Tie;
        }

        if (hand1TwoPair.Item1)
            return Result.Win;
        if (hand2TwoPair.Item1)
            return Result.Loss;

        var hand1Pair = IsPair(hand);
        var hand2Pair = IsPair(this._hand);

        if (hand1Pair.Item1 && hand2Pair.Item1)
        {
            var diff = hand1Pair.Item2 - hand2Pair.Item2;
            if (diff > 0)
            {
                return Result.Win;
            }
            if (diff < 0)
            {
                return Result.Loss;
            }

            var highCards1 = new List<int>();
            var highCards2 = new List<int>();

            foreach(var card in hand)
            {
                if (card.Rank != hand1Pair.Item2)
                {
                    highCards1.Add(card.Rank);
                }
            }

            foreach(var card in this._hand)
            {
                if (card.Rank != hand2Pair.Item2)
                {
                    highCards2.Add(card.Rank);
                }
            }

            for (int i = 2; i >= 0; i--)
            {
                diff = highCards1[i] - highCards2[i];
                if (diff > 0)
                {
                    return Result.Win;
                }
                if (diff < 0)
                {
                    return Result.Loss;
                }
            }
            return Result.Tie;
        }

        if (hand1Pair.Item1)
            return Result.Win;
        if (hand2Pair.Item1)
            return Result.Loss;

        for (int i = 4; i >= 0; i--)
            {
                var diff = hand[i].Rank - this._hand[i].Rank;
                if (diff > 0)
                {
                    return Result.Win;
                }
                if (diff < 0)
                {
                    return Result.Loss;
                }
            }
            return Result.Tie;
        }

    private (bool, int?) IsStraightFlush(List<Card> hand)
    {
        if (IsFlush(hand))
        {
            return IsStraight(hand);
        }
        return (false, null);
    }

    private (bool, int?) IsFourOfAKind(List<Card> hand)
    {
        var dict = CountRanks(hand);

        foreach (KeyValuePair<int, int> kvp in dict)
        {
            if (kvp.Value == 4)
            {
                return (true, kvp.Key);
            }
        }
        
        return (false, null);
    }

    private (bool, (int?, int?)) IsFullHouse(List<Card> hand)
    {
        var dict = CountRanks(hand);

        bool threes = false, twos = false;
        int? threeRank = null;
        int? twoRank = null;

        foreach (KeyValuePair<int, int> kvp in dict)
        {
            if (kvp.Value == 3)
            {
                threes = true;
                threeRank = kvp.Key;
            }
            if (kvp.Value == 2)
            {
                twos = true;
                twoRank = kvp.Key;
            }
        }
        if (threes && twos)
        {
            return (true, (threeRank, twoRank));
        }

        return (false, (null, null));
    }

    private bool IsFlush(List<Card> hand)
    {
        int H = 0, D = 0, C = 0, S = 0;
        foreach (Card card in hand)
        {
            switch(card.Suit)
            {
            case Suit.Hearts:
                H++;
                break;
            case Suit.Spades:
                S++;
                break;
            case Suit.Clubs:
                C++;
                break;
            case Suit.Diamonds:
                D++;
                break;
            default:
                throw new ArgumentException($"Invalid suit character: {card.Suit}");
            }
        }
        if (H == 5) return (true);
        if (D == 5) return (true);
        if (C == 5) return (true);
        if (S == 5) return (true);
        return (false);
    }

    private (bool, int?) IsStraight(List<Card> hand)
    {
        // First do the check for a straight to 5.
        if (hand[0].Rank == 2 && hand[1].Rank == 3
            && hand[2].Rank == 4 && hand[3].Rank == 4 && hand[4].Rank == 14)
        {
            return (true, 5);
        }

        for (int i = 0; i < 4; i++) 
        {
            if (hand[i].Rank + 1 != hand[i + 1].Rank) return (false, null);
        }

        return (true, hand[4].Rank);
    }

    private (bool, int?) IsThreeOfAKind(List<Card> hand)
    {
        var dict = CountRanks(hand);

        foreach (KeyValuePair<int, int> kvp in dict)
        {
            if (kvp.Value == 3)
            {
                return (true, kvp.Key);
            }
        }
        
        return (false, null);
    }

    private (bool, (int?, int?)) IsTwoPair(List<Card> hand)
    {
        var dict = CountRanks(hand);
        var pairs = new List<int>();

        foreach (KeyValuePair<int, int> kvp in dict)
        {
            if (kvp.Value == 2)
            {
                pairs.Add(kvp.Key);
            }
        }
        if (pairs.Count == 2)
        {
            return pairs[0] > pairs[1] ? (true, (pairs[0], pairs[1])) : (true, (pairs[1], pairs[0]));
        }
        return (false, (null, null));
    }

    private (bool, int?) IsPair(List<Card> hand)
    {
        var dict = CountRanks(hand);
        var pairs = new List<int>();

        foreach (KeyValuePair<int, int> kvp in dict)
        {
            if (kvp.Value == 2)
            {
                return (true, kvp.Key);
            }
        }
        
        return (false, null);
    }

    private Dictionary<int, int> CountRanks(List<Card> hand)
    {
        var dict = new Dictionary<int, int>();
        for (var i = 0; i < 5; i++)
        {
            var rank = hand[i].Rank;
            if (dict.ContainsKey(rank))
            {
                dict[rank]++;
            }
            else
            {
                dict.Add(rank, 1);
            }
        }
        return dict;
    }

    private List<Card> ToCardList(string hand)
    {
        var handList = new List<Card>();
        foreach(string card in hand.Split(' '))
        {
            if (card[0] == 'A')
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = 14,
                });
            }
            else if (card[0] == 'K')
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = 13,
                });
            }
            else if (card[0] == 'Q')
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = 12,
                });
            }
            else if (card[0] == 'J')
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = 11,
                });
            }
            else if (card[0] == 'T')
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = 10,
                });
            }
            else 
            {
                handList.Add(new Card() {
                    Value = card[0],
                    Suit = CharToSuit(card[1]),
                    Rank = card[0] - '0',
                });
            }
        };
        return handList.OrderBy(c => c.Rank).ToList();
    }

    private Suit CharToSuit(char suitChar)
    {
        switch (suitChar)
        {
            case 'H':
                return Suit.Hearts;
            case 'S':
                return Suit.Spades;
            case 'C':
                return Suit.Clubs;
            case 'D':
                return Suit.Diamonds;
            default:
                throw new ArgumentException($"Invalid suit character: {suitChar}");
        }
    }
}