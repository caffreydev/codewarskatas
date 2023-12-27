#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <bitset>

// 1. Change the fifth bit of the char and the first bit of the next char. (C1.5 <==> C2.1, only if there is a next char!)
// 2. Inverse the second and the forth bit of the char.           (2,4 => 0->1 or 1->0)
// 3. Change the first 3 bit against the last 3 bit of the char.  (1,2,3 <==> 4,5,6)
// 4. Change every odd bit against the following bit of the char. (1 <==> 2, 3 <==> 4, 5 <==> 6)
// 5. Reverse the whole line of bits of the char.
// 6. Change the first against the third bit of the char.         (1 <==> 3)


std::string encrypt(std::string text)
{
    std::vector<char> region;
    for (int i = 0; i < 26; i++) {
        region.push_back('A' + i);
    }
    for (int i = 0; i < 26; i++) {
        region.push_back('a' + i);
    }
    for (int i = 0; i < 10; i++) {
        region.push_back('0' + i);
    }
    region.push_back(' ');
    region.push_back('.');

    if (text.length() == 0) return text;
    for (int i = 0; i < text.length(); i++) {
        if (find(region.begin(), region.end(), text[i]) == region.end()) {
        throw std::exception();
    }
    }

    for (int i = 0; i < text.length(); i++) {
        auto own_it = find(region.begin(), region.end(), text[i]);
        int own_index = own_it - region.begin();
        std::string own_bits = std::bitset <6>(own_index).to_string();
        char holder;

        //rule 1
        if (i != text.length() -1) {
        auto next_it = find(region.begin(), region.end(), text[i + 1]);
        int next_index = next_it - region.begin();
        std::string next_bits = std::bitset <6>(next_index).to_string();
        holder = own_bits[4];
        own_bits[4] = next_bits[0];
        next_bits[0] = holder;
        next_index = stoi(next_bits, 0, 2);
        text[i + 1] = region[next_index];
        }

        //rule 2
        own_bits[1] = own_bits[1] == '1' ? '0' : '1';
        own_bits[3] = own_bits[3] == '1' ? '0' : '1';

        //rule 3
        holder = own_bits[0];
        own_bits[0] = own_bits[3];
        own_bits[3] = holder;

        holder = own_bits[1];
        own_bits[1] = own_bits[4];
        own_bits[4] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[5];
        own_bits[5] = holder;

        //rule 4
        holder = own_bits[0];
        own_bits[0] = own_bits[1];
        own_bits[1] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[3];
        own_bits[3] = holder;

        holder = own_bits[4];
        own_bits[4] = own_bits[5];
        own_bits[5] = holder;

        //rule 5
        holder = own_bits[0];
        own_bits[0] = own_bits[5];
        own_bits[5] = holder;

        holder = own_bits[1];
        own_bits[1] = own_bits[4];
        own_bits[4] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[3];
        own_bits[3] = holder;

        //rule 6
        holder = own_bits[0];
        own_bits[0] = own_bits[2];
        own_bits[2] = holder;
        
        own_index = stoi(own_bits, 0, 2);
        text[i] = region[own_index];
    }
    

    return text;
}
  
std::string decrypt(std::string text)
{
    std::vector<char> region;
    for (int i = 0; i < 26; i++) {
        region.push_back('A' + i);
    }
    for (int i = 0; i < 26; i++) {
        region.push_back('a' + i);
    }
    for (int i = 0; i < 10; i++) {
        region.push_back('0' + i);
    }
    region.push_back(' ');
    region.push_back('.');
    if (text.length() == 0) return text;
    for (int i = 0; i < text.length(); i++) {
        if (find(region.begin(), region.end(), text[i]) == region.end()) {
        throw std::exception();
    }
    }

    for (int i = text.length() - 1; i >= 0; i--) {
        auto own_it = find(region.begin(), region.end(), text[i]);
        int own_index = own_it - region.begin();
        std::string own_bits = std::bitset <6>(own_index).to_string();
        char holder;

        //rule 6
        holder = own_bits[0];
        own_bits[0] = own_bits[2];
        own_bits[2] = holder;

        //rule 5
        holder = own_bits[0];
        own_bits[0] = own_bits[5];
        own_bits[5] = holder;

        holder = own_bits[1];
        own_bits[1] = own_bits[4];
        own_bits[4] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[3];
        own_bits[3] = holder;

        //rule 4
        holder = own_bits[0];
        own_bits[0] = own_bits[1];
        own_bits[1] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[3];
        own_bits[3] = holder;

        holder = own_bits[4];
        own_bits[4] = own_bits[5];
        own_bits[5] = holder;

        //rule 3
        holder = own_bits[0];
        own_bits[0] = own_bits[3];
        own_bits[3] = holder;

        holder = own_bits[1];
        own_bits[1] = own_bits[4];
        own_bits[4] = holder;

        holder = own_bits[2];
        own_bits[2] = own_bits[5];
        own_bits[5] = holder;

        //rule 2
        own_bits[1] = own_bits[1] == '1' ? '0' : '1';
        own_bits[3] = own_bits[3] == '1' ? '0' : '1';

        //rule 1
        if (i != text.length() -1) {
        auto next_it = find(region.begin(), region.end(), text[i + 1]);
        int next_index = next_it - region.begin();
        std::string next_bits = std::bitset <6>(next_index).to_string();
        holder = own_bits[4];
        own_bits[4] = next_bits[0];
        next_bits[0] = holder;
        next_index = stoi(next_bits, 0, 2);
        text[i + 1] = region[next_index];
        }

        own_index = stoi(own_bits, 0, 2);
        text[i] = region[own_index];
    }

    return text;
}

int main() {


        // std::cout << "Encryption tests:\n";
        // std:: cout << "Input of 'A'. You have '" << encrypt("A") << "' Should have:" << "'K'\n";
        // std:: cout << "Input of 'Abc'. You have '" << encrypt("Abc") << "' Should have:" << "'KyU'\n";
        // std:: cout << "Input of 'B9'. You have '" << encrypt("B9") << "' Should have:" << "'rw'\n";
    
    
    std::cout << "Decryption tests:\n";
        std:: cout << "Input of 'K'. You have '" << decrypt("K") << "' Should have:" << "'A'\n";
        std:: cout << "Input of 'KyU'. You have '" << decrypt("KyU") << "' Should have:" << "'Abc'\n";
        std:: cout << "Input of 'rw'. You have '" << decrypt("rw") << "' Should have:" << "'B9'\n";
        std:: cout << "Input of 'jvLdRPdQXV8Rd5x'. You have '" << decrypt("jvLdRPdQXV8Rd5x") << "' Should have:" << "'This is a test.'\n";
        std:: cout << "Input of 'rfR9qRVMT8TUfeyXGXdrLUcT.dUmVd5xUNo1oRdZQ1dtUXs1QVmRL8RMVt9RHqRtU1Ps1LtPQXVdbpZ9Lfp1'. You have '" << decrypt("rfR9qRVMT8TUfeyXGXdrLUcT.dUmVd5xUNo1oRdZQ1dtUXs1QVmRL8RMVt9RHqRtU1Ps1LtPQXVdbpZ9Lfp1") << "' Should have:" << "'Do the kata Kobayashi Maru Test. Endless fun and excitement when finding a solution.'\n";
    

//    std::cout << "Empty tests:\n";
//    std::cout << "For encrypt of empty string, should have empty string. You have: '" << encrypt("") << "'\n";
//    std::cout << "For decrypt of empty string, should have empty string. You have: '" << decrypt("") << "'\n";
  
//   std::cout << "Invalid character tests:\n";
//   try {
//     std::cout << "1. You should have an exception for encrypt 'A5#'\n";
//     encrypt("A5#");
//   }
//   catch (std::exception e) {
//     std::cout << "Exception 1 thrown\n";
//   }
//   try {
//     std::cout << "2. You should have an exception for decrypt 'A5#'\n";
//     decrypt("A5#");
//   }
//   catch (std::exception e) {
//     std::cout << "Exception 2 thrown\n";
//   }
//   try {
//     std::cout << "3. You should have an exception for encrypt 'A5!'\n";
//     encrypt("A5!");
//   }
//   catch (std::exception e) {
//     std::cout << "Exception 3 thrown\n";
//   }
//   try {
//     std::cout << "4. You should have an exception for decrypt 'A5!'\n";
//     decrypt("A5!");
//   }
//   catch (std::exception e) {
//     std::cout << "Exception 4 thrown\n";
//   }
     
    
}