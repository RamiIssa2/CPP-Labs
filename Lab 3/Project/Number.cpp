#include "Number.h"
#include <iostream>
#include <vector>
#include <string>

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
Number::Number() :value(0), text("zero") {}

// Normal Constructor
Number::Number(int value) :value(value) {
    text = numberToText(value);
}

// Copy Constructor
Number::Number(const Number& num) :value(num.value), text(num.text) {
}

// Move Constructor
Number::Number(Number&& num) noexcept {
    value = std::move(num.value);
    text = std::move(num.text);
}

// Assignment Operators
// Copy Assignment Operator
Number& Number::operator=(const Number& num) {
    if (this == &num) return *this;

    // Copy resources
    value = num.value;
    text = num.text;
    
    return *this;
}

// Move Assignment Operator
Number& Number::operator=(Number&& num) noexcept {
    if (this == &num) return *this;
    
    // Move resources
    value = num.value;
    text = std::move(num.text);

    // Reset the moved-from object
    num.value = 0;
    num.text = "zero";

    return *this;
}

// Addition Operators
// Copy Addition Operator
Number Number::operator+(const Number& num) const {
    return Number(value + num.value);
}

// Move Addition Operator
Number Number::operator+(Number&& num) const noexcept {
    int sum = value + num.value;

    // Reset both operands
    // Reset the first operand (requires const_cast)
    const_cast<Number*>(this)->value = 0;
    const_cast<Number*>(this)->text = "zero";

    // Reset the second operand
    num.value = 0;
    num.text = "zero";

    return Number(sum);
}

// Destructor
Number::~Number() {}