#include "Number.cpp"
#include <iostream>
#include <vector>
#include <list>

using namespace std;


vector<Number> makeNumberVector(int length) {
    vector<Number> numbers;

    for (int i = 0; i < length; i++){
        Number num(i + 1);

        numbers.push_back(num);
    }

    return numbers;
}

list<Number> makeNumberList(int length) {
    list<Number> numbers;

    for (int i = 0; i < length; i++){
        Number num = Number(i + 1);

        numbers.push_back(num);
    }

    return numbers;
}

int main() {
    cout << endl;
    
    cout << "Testing Constructors" << endl;
    Number n1;
    cout << n1 << endl;

    Number n2(4);
    cout << n2 << endl;

    Number n3 = n2;
    cout << n3 << endl;

    Number n4 = move(n1);
    cout << n4 << endl;

    cout << endl;

    cout << "Testing Assignment Operators" << endl;
    Number n5(13);
    n5 = n3;
    cout << n5 << endl << n3 << endl;

    Number n6(17);
    n6 = move(n5);
    cout <<  n6 << endl << n5 << endl;
    
    cout << endl;

    cout << "Testing Addition Operators" << endl;
    n5 = n3 + n2;
    cout << n5 << endl << n3 << endl << n2 << endl;

    cout << endl;

    n6 = move(n5) + move(n2);
    cout <<  n6 << endl << n5 << endl << n2 << endl;

    cout << endl;

    cout << "Resetting all numbers to the value corresponding to their order of creation:" << endl;
    n1 = Number(1);
    n2 = Number(2);
    n3 = Number(3);
    n4 = Number(4);
    n5 = Number(5);
    n6 = Number(6);
    cout << endl;

    cout << "Processing Number Vector:" << endl;
    vector<Number> numberVector = makeNumberVector(9);
    for (Number num:numberVector){
        cout << num << endl;
    }
    cout << endl;

    cout << "Processing Number List:" << endl;
    list<Number> numberList = makeNumberList(6);
    for (Number num:numberList){
        cout << num << endl;
    }
    cout << endl;

    cout << "The end of the program where the destructors are called:" << endl;

    return 0;
}