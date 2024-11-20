#include "Number.h"
#include <iostream>
#include <vector>
#include<string>

std::string numberToText(int num) {
    if (num > 999999999) {
        throw std::out_of_range("Error: Number exceeds the maximum limit for this function which is 999,999,999");
    }
    
    if (num == 0) return "zero";

    // Text of numbers that are below twenty
    std::vector<std::string> numbersBelowTwenty = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" 
    };

    // Text of numbers that are tens
    std::vector<std::string> numbersTens = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" 
    };

    std::string number_text = "";

    if (num >= 1000000) {
        number_text += numberToText(num / 1000000) + " million ";
        num %= 1000000;        
    }
    
    if (num >= 1000) {
        number_text += numberToText(num / 1000) + " thousand ";
        num %= 1000;        
    }

    if (num >= 100) {
        number_text += numbersBelowTwenty[num / 100] + " hundred ";
        num %= 100;
    }

    if (num >= 20) {
        number_text += numbersTens[num / 10] + " ";
        num %= 10;
    }

    if (num > 0){
        number_text += numbersBelowTwenty[num];
    }

    return number_text;
}

// Constructors
// Default Constructor
Number::Number() :value(0), text("zero") { std::cout << "Default Constructor Called" << std::endl; }

// Normal Constructor
Number::Number(int value) :value(value) {
    text = numberToText(value);
    std::cout << "Normal Constructor Called" << std::endl;
}

// Copy Constructor
Number::Number(const Number& num) :value(num.value), text(num.text) {
    std::cout << "Copy Constructor Called" << std::endl;
}

// Move Constructor
Number::Number(Number&& num) noexcept {
    value = std::move(num.value);
    text = std::move(num.text);
    std::cout << "Move Constructor Called" << std::endl;
}

int main(){
    try {
        std::cout << numberToText(1000000000) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
    Number n1;
    Number n2(4);
    Number n3 = n2;
    Number n4 = std::move(n1);
    return 0;
}