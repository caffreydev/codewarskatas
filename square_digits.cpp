#include <cmath>
#include <iostream>

int square_digits(int num)
{
    std::string digits = std::to_string(num);
    std::string converted = "";

    for (int i = 0; i < digits.length(); i++)
    {
        int square = pow(digits[i] - '0', 2);
        converted += std::to_string(square);
    }


    return stoi(converted);
}


int main ()
{   
    std::cout << square_digits(3212) << " Equals: 9414\n";   
    std::cout << square_digits(2112) << " Equals: 4114\n"; 
    std::cout << square_digits(0) << " Equals: 0\n";
    std::cout << square_digits(13579) << " Equals: 19254981\n";   
    std::cout << square_digits(24680) << " Equals: 41636640\n"; 

}