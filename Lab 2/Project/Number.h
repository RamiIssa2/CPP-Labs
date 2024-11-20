#pragma once
#include <string>
#include <utility>

class Number
{
    private:
        int value = 0;
        std::string text;

    public:
        // Default Constructor
        Number() = default;
        // Normal Constructor
        explicit Number(int value);
        // Copy Constructor
        Number(const Number& num) = default;
        // Move Constructor
        Number(Number&& num) noexcept = default;

        // Copy Assignment Operator
        Number& operator=(const Number& num) = default;
        // Move Assignment Operator
        Number& operator=(Number&& num) noexcept = default;

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
};