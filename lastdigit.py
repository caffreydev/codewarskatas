import codewars_test as test

def last_digit(n1, n2):
    loops = {2: 4, 3: 4, 4: 2, 7: 4, 8: 4, 9: 2 }
    if n2 == 0:
        return 1
    val1 = n1 % 10
    if val1 == 0 or val1 == 1 or val1 == 5 or val1== 6:
        return val1
    n2 = ((n2 - 1) % loops[val1]) + 1
    val = 1
    for i in range(n2):
        val = (val * val1) % 10
    return val

@test.describe("Example tests")
def test_group():
    @test.it("Should work for example tests")
    def test_case():
        for n1, n2, exp in [(4, 1, 4),
                            (4, 2, 6),
                            (9, 7, 9),
                            (10, 10 ** 10, 0),
                            (2 ** 200, 2 ** 300, 6),
                            (3715290469715693021198967285016729344580685479654510946723, 68819615221552997273737174557165657483427362207517952651, 7),
                           ]:
            test.assert_equals(last_digit(n1, n2), exp, f"Testing last_digit({n1}, {n2})")
            
            
    @test.it("Testing x ** 0, must return 1")
    def test_case():
        for nmbr in range(1, 9):
            a = nmbr ** nmbr
            test.assert_equals(last_digit(a, 0), 1, f"Testing last_digit({a}, 0)" )
