import codewars_test as test

class VigenereCipher(object):

    def __init__(self, key, alphabet):
        self.key = key
        self.alphabet = alphabet
        return
    
    def encode(self, text):
        cursor = -1
        encoded = ""
        for character in text:
            cursor = (cursor + 1) % len(self.key)
            if self.alphabet.find(character) > -1:
                index = (self.alphabet.index(character) + self.alphabet.index(self.key[cursor])) % len(self.alphabet)
                encoded += self.alphabet[index]
            else: 
                encoded += character
        return encoded
    
    def decode(self, text):
        cursor = -1
        encoded = ""
        for character in text:
            cursor = (cursor + 1) % len(self.key)
            if self.alphabet.find(character) > -1:
                index = (self.alphabet.index(character) - self.alphabet.index(self.key[cursor])) % len(self.alphabet)
                encoded += self.alphabet[index]
            else: 
                encoded += character
        return encoded

@test.describe('Vignere Cipher Helper')
def desc():
    abc = "abcdefghijklmnopqrstuvwxyz"
    key = "password"
    c = VigenereCipher(key, abc)
    @test.it('Sample tests')
    def it():
        test.assert_equals(c.encode('codewars'), 'rovwsoiv')
        test.assert_equals(c.decode('rovwsoiv'), 'codewars')

        test.assert_equals(c.encode('waffles'), 'laxxhsj')
        test.assert_equals(c.decode('laxxhsj'), 'waffles')

        test.assert_equals(c.encode('CODEWARS'), 'CODEWARS')
        test.assert_equals(c.decode('CODEWARS'), 'CODEWARS')
