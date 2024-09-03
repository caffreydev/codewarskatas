namespace CarMilage;

using System;
using System.Collections.Generic;
using System.Linq;
using NUnit.Framework;
    
[TestFixture]
public class CarMileageTests
{
    [TestCase("Number 3", 0, 3, new int[] { 1337, 256 })]
    [TestCase("Number 1336", 1, 1336, new int[] { 1337, 256 })]
    [TestCase("Number 1337", 2, 1337, new int[] { 1337, 256 })]
    [TestCase("Number 11208", 0, 11208, new int[] { 1337, 256 })]
    [TestCase("Number 11209", 1, 11209, new int[] { 1337, 256 })]
    [TestCase("Number 11211", 2, 11211, new int[] { 1337, 256 })]
    [TestCase("Number 10000", 2, 10000, new int[] { 1337, 256 })]
    [TestCase("Number 777777", 2, 777777, new int[] { 1337, 256 })]
    [TestCase("Number 12345", 2, 12345, new int[] { 1337, 256 })]
    [TestCase("Number 54321", 2, 54321, new int[] { 1337, 256 })]
    [TestCase("Number 73837", 2, 73837, new int[] { 1337, 256 })]
    [TestCase("Number 1221", 2, 1221, new int[] { 1337, 256 })]
    [TestCase("Number 67890", 2, 67890, new int[] { 1337, 256 })]
    [TestCase("Number 543210", 2, 543210, new int[] { 1337, 256 })]
    public void IsInterestingTest(string description, int expected, int number, int[] awesomePhrases)
    {
        Assert.That(Kata.IsInteresting(number, new List<int>(awesomePhrases)), Is.EqualTo(expected), description);
    }
}