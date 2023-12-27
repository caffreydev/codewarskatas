import codewars_test as test
import math

# The crypting-regions are these 3 lines from your keyboard:
# 1. "qwertyuiop"
# 2. "asdfghjkl"
# 3. "zxcvbnm,."

# If a char of the string is not in any of these regions, take the char direct in the output.
# If a char of the string is in one of these regions: Move it by the part of the key in the 
## region and take this char at the position from the region. 
# If the movement is over the length of the region, continue at the beginning.
# The encrypted char must have the same case like the decrypted char! 
# So for upperCase-chars the regions are the same, but with pressed "SHIFT"!

# The Encryption-Key is an integer number from 000 to 999. E.g.: 127

# The first digit of the key (e.g. 1) is the movement for the first line.
# The second digit of the key (e.g. 2) is the movement for the second line.
# The third digit of the key (e.g. 7) is the movement for the third line.

# (Consider that the key is an integer! When you got a 0 this would mean 000. A 1 would mean 001. 
# And so on.)

regions =  [
 "qwertyuiop",
 "asdfghjkl",
 "zxcvbnm,.",
 "QWERTYUIOP",
 "ASDFGHJKL",
 "ZXCVBNM<>"
]

def encrypt(text, encryptKey):
    movements_dict = {}
    first = math.floor(encryptKey / 100)
    second = math.floor((encryptKey - first * 100) / 10)
    third = encryptKey - first * 100 - second * 10
    movements = [first, second, third]
    for i in range(3):
        movements_dict[regions[i]] = movements[i]
        movements_dict[regions[i + 3]] = movements[i]
    
    encrypted_text = ""
    for character in text:
        source_region = ""
        for region in regions:
            if character in region:
                source_region = region
                break
        if not len(source_region):
            encrypted_text += character
            continue
        index = (source_region.index(character) + movements_dict[source_region]) % len(source_region)
        encrypted_text += source_region[index]
    return encrypted_text
    
def decrypt(text, encryptKey):
    movements_dict = {}
    first = math.floor(encryptKey / 100)
    second = math.floor((encryptKey - first * 100) / 10)
    third = encryptKey - first * 100 - second * 10
    movements = [first, second, third]
    for i in range(3):
        movements_dict[regions[i]] = movements[i]
        movements_dict[regions[i + 3]] = movements[i]
    
    decrypted_text = ""
    for character in text:
        source_region = ""
        for region in regions:
            if character in region:
                source_region = region
                break
        if not len(source_region):
            decrypted_text += character
            continue
        index = (source_region.index(character) - movements_dict[source_region]) % len(source_region)
        decrypted_text += source_region[index]
    return decrypted_text



test.describe("Example tests")
test.it("Encryption tests")

test.assert_equals(encrypt("A", 111), "S")
test.assert_equals(encrypt("Abc", 212), "Smb")
test.assert_equals(encrypt("Wave", 0), "Wave") # -> 000
test.assert_equals(encrypt("Wave", 345), "Tg.y")
test.assert_equals(encrypt("Ball", 134), ">fdd")
test.assert_equals(encrypt("Ball", 444), ">gff")

test.assert_equals(encrypt("This is a test.", 348), "Iaqh qh g iyhi,")
test.assert_equals(encrypt("Do the kata Kobayashi Maru Test. Endless fun and excitement when finding a solution.", 583),
                  "Sr pgi jlpl Jr,lqlage Zlow Piapc I.skiaa dw. l.s ibnepizi.p ugi. de.se.f l arkwper.c")


test.it("Decryption tests")

test.assert_equals(decrypt("S", 111), "A")
test.assert_equals(decrypt("Smb", 212), "Abc")
test.assert_equals(decrypt("Wave", 0), "Wave") # -> 000
test.assert_equals(decrypt("Tg.y", 345), "Wave")
test.assert_equals(decrypt(">fdd", 134), "Ball")
test.assert_equals(decrypt(">gff", 444), "Ball")

test.assert_equals(decrypt("Iaqh qh g iyhi,", 348), "This is a test.")
test.assert_equals(decrypt("Sr pgi jlpl Jr,lqlage Zlow Piapc I.skiaa dw. l.s ibnepizi.p ugi. de.se.f l arkwper.c", 583),
                  "Do the kata Kobayashi Maru Test. Endless fun and excitement when finding a solution.")