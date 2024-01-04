import codewars_test as test

def strip_comments(strng, markers):
    lines = strng.split("\n")
    for i in range(len(lines)):
        for marker in markers:
            lines[i] = lines[i].split(marker)[0].rstrip()
            
    new_string = ""
    for i in range(len(lines)):
        new_string += lines[i]
        if i != len(lines) - 1:
            new_string += "\n"
    return new_string
        

@test.describe('Test case')
def test_group():
    @test.it('Example')
    def test_case():
        test.assert_equals(strip_comments('apples, pears # and bananas\ngrapes\nbananas !apples', ['#', '!']), 'apples, pears\ngrapes\nbananas')
        test.assert_equals(strip_comments('a #b\nc\nd $e f g', ['#', '$']), 'a\nc\nd')
        test.assert_equals(strip_comments(' a #b\nc\nd $e f g', ['#', '$']), ' a\nc\nd')