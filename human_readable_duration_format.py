# Your task in order to complete this Kata is to write a function which formats a duration, given as a number of seconds, in a human-friendly way.

# The function must accept a non-negative integer. If it is zero, it just returns "now". Otherwise, the duration is expressed as a combination of years, days, hours, minutes and seconds.

# It is much easier to understand with an example:

# * For seconds = 62, your function should return 
#     "1 minute and 2 seconds"
# * For seconds = 3662, your function should return
#     "1 hour, 1 minute and 2 seconds"
# For the purpose of this Kata, a year is 365 days and a day is 24 hours.

# Note that spaces are important.

# Detailed rules
# The resulting expression is made of components like 4 seconds, 1 year, etc. In general, a positive integer and one of the valid units of time, separated by a space. The unit of time is used in plural if the integer is greater than 1.

# The components are separated by a comma and a space (", "). Except the last component, which is separated by " and ", just like it would be written in English.

# A more significant units of time will occur before than a least significant one. Therefore, 1 second and 1 year is not correct, but 1 year and 1 second is.

# Different components have different unit of times. So there is not repeated units like in 5 seconds and 1 second.

# A component will not appear at all if its value happens to be zero. Hence, 1 minute and 0 seconds is not valid, but it should be just 1 minute.

# A unit of time must be used "as much as possible". It means that the function should not return 61 seconds, but 1 minute and 1 second instead. Formally, the duration specified by of a component must not be greater than any valid more significant unit of time.
import codewars_test as test
from math import floor

def format_duration(seconds):
    if seconds == 0:
        return "now"
    mapping = {31536000: "year", 86400: "day", 3600: "hour", 60: "minute", 1: "second"}
    outString = ""
    for key in mapping:
        multiple = floor(seconds / key)
        if multiple == 0:
            continue
        seconds = seconds - key * multiple
        outString += f', {multiple} {mapping[key]}{"s" if multiple > 1 else ""}'
    
    
    commas = []
    for i in range(len(outString)):
        if outString[i] == ",":
            commas.append(i)
    if len(commas) > 1:
        index = commas[len(commas) - 1]
        outString = outString[2:index] + " and" + outString[index+1:] # Adjusts to turn final comma into an 'and'
    else:
        index = commas[0]
        outString = outString[2:] # Adjust to remove trailing ", "
    return outString



@test.describe("Fixed Tests")
def fixed_tests():
    @test.it('Basic Test Cases')
    def basic_test_cases():
        test.assert_equals(format_duration(0), "now")
        test.assert_equals(format_duration(1), "1 second")
        test.assert_equals(format_duration(62), "1 minute and 2 seconds")
        test.assert_equals(format_duration(120), "2 minutes")
        test.assert_equals(format_duration(3600), "1 hour")
        test.assert_equals(format_duration(3662), "1 hour, 1 minute and 2 seconds")
        test.assert_equals(format_duration(15731080), "182 days, 1 hour, 44 minutes and 40 seconds")
        test.assert_equals(format_duration(132030240), "4 years, 68 days, 3 hours and 4 minutes")
        test.assert_equals(format_duration(205851834), "6 years, 192 days, 13 hours, 3 minutes and 54 seconds")
        test.assert_equals(format_duration(253374061), "8 years, 12 days, 13 hours, 41 minutes and 1 second")
        test.assert_equals(format_duration(242062374), "7 years, 246 days, 15 hours, 32 minutes and 54 seconds")
        test.assert_equals(format_duration(101956166), "3 years, 85 days, 1 hour, 9 minutes and 26 seconds")
        test.assert_equals(format_duration(33243586), "1 year, 19 days, 18 hours, 19 minutes and 46 seconds")