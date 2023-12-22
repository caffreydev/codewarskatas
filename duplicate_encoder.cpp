#include <iostream>
#include <map>
// The goal of this exercise is to convert a string to a new string where each character in the new string is "(" if that character appears only once in the original 
// string, or ")" if that character appears more than once in the original string. Ignore capitalization when determining if a character is a duplicate.

std::string duplicate_encoder(const std::string& word)
{
    std::map <char, int> characterCount = {};
    std::string lowercase = "";
    for (int i = 0; i < word.length(); i++) {
        lowercase += tolower(word[i]);
    }

    for (int i = 0; i < lowercase.length(); i++)
    {
        if (characterCount.count(lowercase[i])) {
            characterCount[lowercase[i]]++;
        } else {
            characterCount[lowercase[i]] = 1;
        }
    }
    std::string encoded = "";
    for (int i = 0; i < lowercase.length(); i++)
    {
        if (characterCount[lowercase[i]] > 1) {
            encoded += ")";
        } else {
            encoded += "(";
        }
    }
    
    return encoded;
}


int main()
{
        std::cout << duplicate_encoder("din") << " equals: ((( \n";
        std::cout << duplicate_encoder("recede") << " equals: ()()() \n";
        std::cout << duplicate_encoder("Success") << " equals: )())()) \n";
        std::cout << duplicate_encoder("CodeWarrior") << " equals: ()(((())()) \n";
        std::cout << duplicate_encoder("Supralapsarian") << " equals: )()))()))))()( \n";
        std::cout << duplicate_encoder("(( @") << " equals: ))(( \n";
        std::cout << duplicate_encoder(" ( ( )") << " equals: )))))( \n";
}