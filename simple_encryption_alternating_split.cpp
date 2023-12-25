#include <vector>
#include <cmath>
#include <iostream>

std::string encrypt(std::string text, int n)
{
  int length = text.length();
  if (length == 0 || n <= 0) return text;
  int count = 0;
  
  while (count++ < n) {
    std::string new_text = "";
    for (int i = 1; i < length; i += 2) {
      new_text += text[i];
    }
    for (int i = 0; i < length; i += 2) {
      new_text += text[i];
    }
    text = new_text;
  }
  
    return text;
}

std::string decrypt(std::string encryptedText, int n)
{
    int length = encryptedText.length();
    if (length == 0 || n <= 0) return encryptedText;
    int count = 0;
  
    while (count++ < n) {
    std::vector <char> oddOnes;
    std::vector <char> evenOnes;
    for (int i = 0; i < length / 2; i++) {
      oddOnes.push_back(encryptedText[i]);
    }
    for (int i = ceil(length / 2); i < length; i++) {
      evenOnes.push_back(encryptedText[i]);
    }

    std::string new_text = "";
    int oddCount = 0;
    int evenCount = 0;
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            new_text += evenOnes[evenCount++];
        } else {
            new_text += oddOnes[oddCount++];
        }
    }
    encryptedText = new_text;
    }
    
    return encryptedText;
}


int main() {
    

std::cout << "Encryption tests:\n";
        std::cout << "You got: " << encrypt("This is a test!",0) << " With a string of: " << "This is a test!" << " With number of: " << "0" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << encrypt("This is a test!",1) << " With a string of: " << "This is a test!" << " With number of: " << "1" << " Should Equal: " << "hsi  etTi sats!\n";
        std::cout << "You got: " << encrypt("This is a test!",2) << " With a string of: " << "This is a test!" << " With number of: " << "2" << " Should Equal: " << "s eT ashi tist!\n";
        std::cout << "You got: " << encrypt("This is a test!",3) << " With a string of: " << "This is a test!" << " With number of: " << "3" << " Should Equal: " << " Tah itse sits!\n";
        std::cout << "You got: " << encrypt("This is a test!",4) << " With a string of: " << "This is a test!" << " With number of: " << "4" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << encrypt("This is a test!",-1) << " With a string of: " << "This is a test!" << " With number of: " << "-1" <<  "Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << encrypt("This kata is very interesting!",1) << " With a string of: " << "This kata is very interesting!" << " With number of: " << "1" << " Should Equal: " << "hskt svr neetn!Ti aai eyitrsig\n";
    
    
    std::cout << "\nDecryption tests\n";
        std::cout << "You got: " << decrypt("This is a test!",0) << " With a string of: " << "This is a test!" << " With number of: " << "0" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt("hsi  etTi sats!",1) << " With a string of: " << "hsi  etTi sats!" << " With number of: " << "1" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt("s eT ashi tist!",2) << " With a string of: " << "s eT ashi tist!" << " With number of: " << "2" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt(" Tah itse sits!",3) << " With a string of: " << " Tah itse sits!" << " With number of: " << "3" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt("This is a test!",4) << " With a string of: " << "This is a test!" << " With number of: " << "4" << " Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt("This is a test!",-1) << " With a string of: " << "This is a test!" << " With number of: " << "-1" <<  "Should Equal: " << "This is a test!\n";
        std::cout << "You got: " << decrypt("hskt svr neetn!Ti aai eyitrsig",1) << " With a string of: " << "hskt svr neetn!Ti aai eyitrsig" << " With number of: " << "1" << " Should Equal: " << "This kata is very interesting!\n";
    
    
    std::cout << "\nEmpty tests\n";
        std::cout << "You got: " << encrypt("",0) << " With a string of: " << "" << " With number of: " << "0" << " Should Equal: " << "\n";
        std::cout << "You got: " << encrypt("",3) << " With a string of: " << "" << " With number of: " << "3" << " Should Equal: " << "\n";
        std::cout << "You got: " << decrypt("",0) << " With a string of: " << "" << " With number of: " << "0" << " Should Equal: " << "\n";
        std::cout << "You got: " << decrypt("",3) << " With a string of: " << "" << " With number of: " << "3" << " Should Equal: " << "\n";
  
}