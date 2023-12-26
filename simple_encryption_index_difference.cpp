#include <iostream>
#include <vector>
#include <regex>
#include <string>

class Kata {
std::vector<char> specialChars = {'.',',',':',';','-','?','!',' ','\'','(',')','$','%','&','"'};

public:
std::string encrypt(std::string text)
    {
        std::regex invalid ("[^.,:;?! '()$%&\"a-zA-Z0-9-]");
        std::regex uppercases ("[A-Z]+");
        std::regex lowercases("[a-z]+");
        std::regex digits("[0-9]+");
        if (text.length() == 0) return text;
        
        if (std::regex_search(text, invalid)) {
            throw std::exception();
        }
     


        for (int i = 1; i < text.length(); i += 2) {
            std::string char_string = "";
            char_string += text[i];

            if (std::regex_match(char_string, uppercases)) {
                
                text[i] = tolower(text[i]);
                
            }
            else if (std::regex_match(char_string, lowercases)) {
                text[i] = toupper(text[i]);
            }
        }
        std::string new_text = text;
        for (int i = 1; i < text.length(); i++) {
            std::string char_string = "";
            char_string += text[i];
            std::string prev_string = "";
            prev_string += text[i - 1];
            int ownindex;
            int previndex;
            
            if (std::regex_match(char_string, uppercases)) {
                ownindex = text[i] - 'A';
            }
            else if (std::regex_match(char_string, lowercases)) {
                ownindex = 26 + text[i] - 'a';
            }
            else if (std::regex_match(char_string, digits)) {
                ownindex = 52 + text[i] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[i]);
                ownindex = 62 + it - specialChars.begin();
            }
            if (std::regex_match(prev_string, uppercases)) {
                previndex = text[i - 1] - 'A';
            }
            else if (std::regex_match(prev_string, lowercases)) {
                previndex = 26 + text[i - 1] - 'a';
            }
            else if (std::regex_match(prev_string, digits)) {
                previndex = 52 + text[i - 1] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[i - 1]);
                previndex = 62 + it - specialChars.begin();
            }
            int difference = previndex - ownindex;
            
            difference = difference >= 0 ? difference : 77 + difference;
            
            if (difference <= 25) {
                new_text[i] = 'A' + difference;
            }
            else if (difference <= 51) {
                new_text[i] = 'a' + (difference - 26);
            }
            else if (difference <= 61) {
                new_text[i] = '0' + (difference - 52);
            }
            else {
                new_text[i] = specialChars[difference - 62];
            }

        }
        text = new_text;
        int firstindex;
        std::string first_char_string = "";
        first_char_string += text[0];
        if (std::regex_match(first_char_string, uppercases)) {
                firstindex = text[0] - 'A';
            }
            else if (std::regex_match(first_char_string, lowercases)) {
                firstindex = 26 + text[0] - 'a';
            }
            else if (std::regex_match(first_char_string, digits)) {
                firstindex = 52 + text[0] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[0]);
                firstindex = 62 + it - specialChars.begin();
            }
        firstindex = 76 - firstindex;

        if (firstindex <= 25) {
                text[0] = 'A' + firstindex;
            }
            else if (firstindex <= 51) {
                text[0] = 'a' + (firstindex - 26);
            }
            else if (firstindex <= 61) {
                text[0] = '0' + (firstindex - 52);
            }
            else {
                text[0] = specialChars[firstindex - 62];
            }



        return text;
    }
  
std::string decrypt(std::string text)
    {
        if (text.length() == 0) return text;
        std::regex invalid ("[^.,:;?! '()$%&\"a-zA-Z0-9-]");
        std::regex uppercases ("[A-Z]+");
        std::regex lowercases("[a-z]+");
        std::regex digits("[0-9]+");
        if (std::regex_search(text, invalid)) {
            throw std::exception();
        }


        int firstindex;
        std::string first_char_string = "";
        first_char_string += text[0];
        if (std::regex_match(first_char_string, uppercases)) {
                firstindex = text[0] - 'A';
            }
            else if (std::regex_match(first_char_string, lowercases)) {
                firstindex = 26 + text[0] - 'a';
            }
            else if (std::regex_match(first_char_string, digits)) {
                firstindex = 52 + text[0] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[0]);
                firstindex = 62 + it - specialChars.begin();
            }
        firstindex = 76 - firstindex;

        if (firstindex <= 25) {
                text[0] = 'A' + firstindex;
            }
            else if (firstindex <= 51) {
                text[0] = 'a' + (firstindex - 26);
            }
            else if (firstindex <= 61) {
                text[0] = '0' + (firstindex - 52);
            }
            else {
                text[0] = specialChars[firstindex - 62];
            }

        for (int i = 1; i < text.length(); i++) {
            int difference;
            std::string char_string = "";
            char_string += text[i];
            std::string prev_string = "";
            prev_string += text[i - 1];
            int ownindex;
            int previndex;
            
            if (std::regex_match(char_string, uppercases)) {
                difference = text[i] - 'A';
            }
            else if (std::regex_match(char_string, lowercases)) {
                difference = 26 + text[i] - 'a';
            }
            else if (std::regex_match(char_string, digits)) {
                difference = 52 + text[i] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[i]);
                difference = 62 + it - specialChars.begin();
            }

            if (std::regex_match(prev_string, uppercases)) {
                previndex = text[i - 1] - 'A';
            }
            else if (std::regex_match(prev_string, lowercases)) {
                previndex = 26 + text[i - 1] - 'a';
            }
            else if (std::regex_match(prev_string, digits)) {
                previndex = 52 + text[i - 1] - '0';
            }
            else {
                auto it = find(specialChars.begin(), specialChars.end(), text[i - 1]);
                previndex = 62 + it - specialChars.begin();
            }

            ownindex = previndex - difference;
            ownindex = ownindex >= 0 ? ownindex : (previndex + 77 - difference);

            if (ownindex <= 25) {
                text[i] = 'A' + ownindex;
            }
            else if (ownindex <= 51) {
                text[i] = 'a' + (ownindex - 26);
            }
            else if (ownindex <= 61) {
                text[i] = '0' + (ownindex - 52);
            }
            else {
                text[i] = specialChars[ownindex - 62];
            }

        }
        for (int i = 1; i < text.length(); i += 2) {
            std::string char_string = "";
            char_string += text[i];

            if (std::regex_match(char_string, uppercases)) {
                text[i] = tolower(text[i]);
            }
            else if (std::regex_match(char_string, lowercases)) {
                text[i] = toupper(text[i]);
            }
        }

        return text;
    }

};


int main () {

    Kata kata;
   
    // std::cout << "Encryption tests:\n";

    std::string expected = "5MyQa9p0riYplZc";
    std::string actual = kata.encrypt("This is a test!");
    // std::cout << "Input of 'This is a test!'\n";
    // std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";
    
    // expected = "$-Wy,dM79H'i'o$n0C&I.ZTcMJw5vPlZc Hn!krhlaa:khV mkL;gvtP-S7Rt1Vp2RV:wV9VuhO Iz3dqb.U0w";
    // actual = kata.encrypt("Do the kata \"Kobayashi-Maru-Test!\" Endless fun and excitement when finding a solution!");
    // std::cout << "Input of '\"Do the kata \"Kobayashi-Maru-Test!\" Endless fun and excitement when finding a solution!\"'\n";
    // std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";
    // expected = "5MyQa79H'ijQaw!Ns6jVtpmnlZ.V6p";
    // actual = kata.encrypt("This kata is very interesting!");
    // std::cout << "Input of '\"This kata is very interesting!\"'\n";
    // std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";


    std::cout << "Decryption tests:\n";
    
    expected = "This is a test!";
    std::cout << "Input of '5MyQa9p0riYplZc'\n";
    actual = kata.decrypt("5MyQa9p0riYplZc");
    std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";
    
    expected = "Do the kata \"Kobayashi-Maru-Test!\" Endless fun and excitement when finding a solution!";
    std::cout << "Input of '$-Wy,dM79H'i'o$n0C&I.ZTcMJw5vPlZc Hn!krhlaa:khV mkL;gvtP-S7Rt1Vp2RV:wV9VuhO Iz3dqb.U0w'\n";
    actual = kata.decrypt("$-Wy,dM79H'i'o$n0C&I.ZTcMJw5vPlZc Hn!krhlaa:khV mkL;gvtP-S7Rt1Vp2RV:wV9VuhO Iz3dqb.U0w");
    std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";
    
    expected = "This kata is very interesting!";
    std::cout << "Input of '5MyQa79H'ijQaw!Ns6jVtpmnlZ.V6p'\n";
    actual = kata.decrypt("5MyQa79H'ijQaw!Ns6jVtpmnlZ.V6p");
    std::cout << "Should have: '" << expected << "' did have '" << actual << "\n";
    
    // std::cout << "Empty tests\n";

    // std::cout << "You Have: '" << kata.encrypt("") << "'. Should have: ''\n";
    // std::cout << "You Have: '" << kata.decrypt("") << "'. Should have: ''\n";

    // std::cout << "Invalid character tests\n";
    // std::cout << "Input of 'This is a test including an invalid charact[r]'\n";
    // std::cout << "Should throw a standard exception\n";
    // actual = kata.encrypt("This is a test including an invalid charact[r]");

}