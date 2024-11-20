#pragma once
#include <string>
#include <iostream>
#include <utility>

class Number
{
    private:
        int value = 0;
        std::string text;

    public:
        // Constructors
        // Default Constructor
        Number();

        // Normal Constructor
        explicit Number(int value);

        // Copy Constructor
        Number(const Number& num);

        // Move Constructor
        Number(Number&& num) noexcept;

        // Assignment Operators
        // Copy Assignment Operator
        Number& operator=(const Number& num);

        // Move Assignment Operator
        Number& operator=(Number&& num) noexcept;

        // Addition Operators
        // Copy Addition Operator
        Number operator+(const Number& num) const;

        // Move Addition Operator
        Number operator+(Number&& num) const noexcept; 

        // Destructor
	    ~Number() = default;

        // Setters
        void setValue(int value) { this->value = value; }
        void setText(std::string text) { this->text = text; }
        
        // Getters
        [[nodiscard]] int getValue() const { return value; }
        [[nodiscard]] std::string getText() const { return text; }

        // Friend function to overload `<<` operator
        friend std::ostream& operator<<(std::ostream& os, const Number& num);
};

// Implementation of friend operator
std::ostream& operator<<(std::ostream& os, const Number& num) {
    os << num.value << " [" << num.text << "]";
    return os;
}