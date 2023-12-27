import codewars_test as test

def same_structure_as(original,other):
    if type(original) == list and type(other) != list: return False
    if type(other) == list and type(original) != list: return False
    if type(original) != list: return True
    
    
    if len(original) != len(other): return False
    
    for i in range(len(original)):
        if type(original[i]) == list and type(other[i]) != list: return False
        if type(other[i]) == list and type(original[i]) != list: return False
        if type(original[i]) == list:
            if not same_structure_as(original[i], other[i]): return False
    
    return True

test.assert_equals(same_structure_as([1,[1,1]],[2,[2,2]]), True, "[1,[1,1]] same as [2,[2,2]]")
test.assert_equals(same_structure_as([1,[1,1]],[[2,2],2]), False, "[1,[1,1]] not same as [[2,2],2]")
test.assert_equals(same_structure_as([1,'[',']'], ['[',']',1]), True, "[1,'[',']'] same as ['[',']',1]")