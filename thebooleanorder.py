import codewars_test as test

# https://www.codewars.com/kata/59eb1e4a0863c7ff7e000008/train/python
# In this Kata, you will be given boolean values and boolean operators. Your task will be to return the number of arrangements that evaluate to True.

# t,f will stand for true, false and the operators will be Boolean AND (&), OR (|), and XOR (^).

# For example, solve("tft","^&") = 2, as follows:

# "((t ^ f) & t)" = True
# "(t ^ (f & t))" = True
# Notice that the order of the boolean values and operators does not change. What changes is the position of braces.

# More examples in the test cases.

# Good luck!



def solve(s,ops):
    boolean_list = []
    for character in s:
        if character == 't':
            boolean_list.append(True)
        else:
            boolean_list.append(False)
    placement = []
    
    
    pass

@test.it("Basic tests")
def basic_tests():
    test.assert_equals(solve("tft","^&"),2)
    test.assert_equals(solve("ttftff","|&^&&"),16)
    test.assert_equals(solve("ttftfftf","|&^&&||"),339)
    test.assert_equals(solve("ttftfftft","|&^&&||^"),851)
    test.assert_equals(solve("ttftfftftf","|&^&&||^&"),2434)

