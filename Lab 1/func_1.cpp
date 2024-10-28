#include <iostream>

int f(void) {
bool var1 = false;
bool var2 = true;

std::cout << "var1 = " << false;
std::cout << "var2 = " << true;

std::cout << "var1 + var2 = ";
std::cout << var1 + var2 << std::endl;
std::cout << "var1 - var2 = ";
std::cout << var1 - var2 << std::endl;
std::cout << "var1 * var2 = ";
std::cout << var1 * var2 << std::endl;
std::cout << "var1 / var2 = ";
std::cout << var1 / var2 << std::endl;
std::cout << "var1 % var2 = ";
std::cout << var1 % var2 << std::endl;
std::cout << "var1 && var2 = ";
std::cout << (var1 && var2) << std::endl;
std::cout << "var1 || var2 = ";
std::cout << (var1 || var2) << std::endl;
std::cout << "var1 ^ var2 = ";
std::cout << (var1 ^ var2) << std::endl;

return 0;
}

int main(void){
f();
return 0;
}
