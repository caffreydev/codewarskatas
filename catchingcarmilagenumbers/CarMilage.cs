// "7777...8?!??!", exclaimed Bob, "I missed it again! Argh!" Every time there's an interesting number coming up, he notices and then promptly forgets. Who doesn't like catching those one-off interesting mileage numbers?

// Let's make it so Bob never misses another interesting number. We've hacked into his car's computer, and we have a box hooked up that reads mileage numbers. We've got a box glued to his dash that lights up yellow or green depending on whether it receives a 1 or a 2 (respectively).

// It's up to you, intrepid warrior, to glue the parts together. Write the function that parses the mileage number input, and returns a 2 if the number is "interesting" (see below), a 1 if an interesting number occurs within the next two miles, or a 0 if the number is not interesting.

// Note: In Haskell, we use No, Almost and Yes instead of 0, 1 and 2.

// "Interesting" Numbers
// Interesting numbers are 3-or-more digit numbers that meet one or more of the following criteria:

// Any digit followed by all zeros: 100, 90000
// Every digit is the same number: 1111
// The digits are sequential, incementing†: 1234
// The digits are sequential, decrementing‡: 4321
// The digits are a palindrome: 1221 or 73837
// The digits match one of the values in the awesomePhrases array
// † For incrementing sequences, 0 should come after 9, and not before 1, as in 7890.
// ‡ For decrementing sequences, 0 should come after 1, and not before 9, as in 3210.

// So, you should expect these inputs and outputs:

// // "boring" numbers
// Kata.IsInteresting(3, new List<int>() { 1337, 256 });    // 0
// Kata.IsInteresting(3236, new List<int>() { 1337, 256 }); // 0

// // progress as we near an "interesting" number
// Kata.IsInteresting(11207, new List<int>() { });   // 0
// Kata.IsInteresting(11208, new List<int>() { });   // 0
// Kata.IsInteresting(11209, new List<int>() { });   // 1
// Kata.IsInteresting(11210, new List<int>() { });   // 1
// Kata.IsInteresting(11211, new List<int>() { });   // 2

// // nearing a provided "awesome phrase"
// Kata.IsInteresting(1335, new List<int>() { 1337, 256 });   // 1
// Kata.IsInteresting(1336, new List<int>() { 1337, 256 });   // 1
// Kata.IsInteresting(1337, new List<int>() { 1337, 256 });   // 2
// Error Checking
// A number is only interesting if it is greater than 99!
// Input will always be an integer greater than 0, and less than 1,000,000,000.
// The awesomePhrases array will always be provided, and will always be an array, but may be empty. (Not everyone thinks numbers spell funny words...)
// You should only ever output 0, 1, or 2.


namespace CarMilage;

using System;
using System.Collections.Generic;
using System.Linq;
using NUnit.Framework;



public static class Kata
    {
        public static int IsInteresting(int number, List<int> awesomePhrases)
        {
             return InterestingCheck(number, awesomePhrases) ? 2 : InterestingCheck(number + 1, awesomePhrases) || InterestingCheck(number + 2, awesomePhrases) ? 1 : 0;
        }

        private static bool InterestingCheck(int number, List<int> awesomePhrases)
        {
            if (number < 100) return false;
            var numString = "" + number;
            return DigitFollowedZeros(numString) || AllSameDigit(numString)
            || Incrementing(numString) || Decrementing(numString)
            || Palindrome(numString) || AwesomPhrase(number, awesomePhrases);
        }

        private static bool DigitFollowedZeros(string numString)
        {
            if (numString.StartsWith('0')) return false;
            for (int i = 1; i < numString.Length; i++)
            {
                if (numString[i] != '0') return false;
            }
            return true;
        }

        private static bool AllSameDigit(string numString)
        {
            var digit = numString[0];
            for (int i = 1; i < numString.Length; i++)
            {
                if (numString[i] != digit) return false;
            }
            return true;
        }

        private static bool Incrementing(string numString)
        {
            for (int i = 0; i < numString.Length -1; i++)
            {
                if (numString[i] == '0') return false;
                if (numString[i] == '9' && numString[i + 1] != '0') return false;
                if(numString[i] != '9' && numString[i] + 1 != numString[i + 1]) return false;
            }
            return true;
        }

        private static bool Decrementing(string numString)
        {
            for (int i = numString.Length -1; i > 0; i--)
            {
                if (numString[i - 1] == '0') return false;
                if (numString[i] == '0' && numString[i - 1] != '1') return false;
                else if(numString[i] + 1 != numString[i - 1]) return false;
            }
            return true;
        }

        private static bool Palindrome(string numString)
        {
            for (int i = 0; i < numString.Length; i++)
            {
                if (numString[i] != numString[numString.Length - i - 1]) return false;
            }
            return true;
        }

        private static bool AwesomPhrase(int num, List<int> awesomePhrases)
        {
            return awesomePhrases.Contains(num);
        }
    }