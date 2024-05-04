import codewars_test as test
import math

class RomanNumerals:
    @staticmethod
    def to_roman(val : int) -> str:
        romanised = ""
        dictionary = {
            "M": 1000,
            "CM": 900,
            "D": 500,
            "CD": 400,
            "C": 100,
            "XC": 90,
            "L": 50,
            "XL": 40,
            "X": 10,
            "IX": 9,
            "V": 5,
            "IV": 4,
            "I": 1
        }
        for character in dictionary.keys():
            count = math.floor(val / dictionary[character])
            val -= count * dictionary[character]
            for i in range(count):
                romanised += character
        return romanised
        
            


    @staticmethod
    def from_roman(roman_num : str) -> int:
        arabicised = 0
        dictionary = {
            "M": 1000,
            "CM": 900,
            "D": 500,
            "CD": 400,
            "C": 100,
            "XC": 90,
            "L": 50,
            "XL": 40,
            "X": 10,
            "IX": 9,
            "V": 5,
            "IV": 4,
            "I": 1
        }
        for character in roman_num:
            arabicised += dictionary[character]
            
        #Adjusts for the max of 1 CM, CD etc.
        if "CM" in roman_num or "CD" in roman_num:
            arabicised -= 200
        if "XC" in roman_num or "XL" in roman_num:
            arabicised -= 20
        if "IX" in roman_num or "IV" in roman_num:
            arabicised -= 2
        return arabicised
    
@test.describe('fixed tests')
def fixed_tests():

    def do_test(input, expected):
        func = RomanNumerals.to_roman if type(input) is int else RomanNumerals.from_roman
        actual = func(input)
        test.assert_equals(actual, expected, f'testing {func.__name__}, for input {input}\n')

    @test.it('to roman')
    def fixed_tests_to():
        do_test(1000, 'M')
        do_test(4, 'IV')
        do_test(1, 'I')
        do_test(1990, 'MCMXC')
        do_test(2008, 'MMVIII')

    @test.it('from roman')
    def fixed_tests_from():
        do_test('XXI', 21)
        do_test('I', 1)
        do_test('IV', 4)
        do_test('MMVIII', 2008)
        do_test('MDCLXVI', 1666)