#include <iostream>

int solution(std::string roman) {
    int value = 0;
    int length = roman.length();
    int cursor = 0;

    while (cursor < length) 
    {
        if (cursor != length - 1) {
            if (roman[cursor] == 'C' & roman[cursor + 1] == 'M') {
                value += 900;
                cursor += 2;
                continue;
            } else if (roman[cursor] == 'C' & roman[cursor + 1] == 'D') {
                value += 400;
                cursor += 2;
                continue;
            } else if (roman[cursor] == 'X' & roman[cursor + 1] == 'C') {
                value += 90;
                cursor += 2;
                continue;
            } else if (roman[cursor] == 'X' & roman[cursor + 1] == 'L') {
                value += 40;
                cursor += 2;
                continue;
            } else if (roman[cursor] == 'I' && roman[cursor + 1] == 'X') {
                value += 9;
                cursor += 2;
                continue;
            } else if (roman[cursor] == 'I' && roman[cursor + 1] == 'V') {
                value += 4;
                cursor += 2;
                continue;
            }
        }
        
        switch (roman[cursor]) {
            case 'M':
            value += 1000;
            break;
            case 'D':
            value += 500;
            break;
            case 'C':
            value += 100;
            break;
            case 'L':
            value += 50;
            break;
            case 'X':
            value += 10;
            break;
            case 'V':
            value += 5;
            break;
            case 'I':
            value++;
            break;
        }
        cursor++;
    }

    return value;
}

int main ()
{
    std::cout << solution("I") << " should equal: 1\n";
    std::cout << solution("IV") << " should equal: 4\n";
    std::cout << solution("MMVIII") << " should equal: 2008\n";
    std::cout << solution("MDCLXVI") << " should equal: 1666\n";
    std::cout << solution("XCV") << " should equal: 95\n";
}