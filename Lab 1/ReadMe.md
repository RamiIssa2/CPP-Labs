# Lab Assignment #1 for the C++ Programming Course

## Topics Covered:

- Input/output
- File input/output
- Basic data types and expressions
- Function concept
- Basics of compilation

You can learn more about basic data types, for example, here: <https://cplusplus.com/doc/tutorial/variables/>

## Task:

Develop a program that takes as input two or three data types from the keyboard. The program should then generate a function in a file. In this function:

- Variables of the specified types will be created and initialized.
- Arithmetic operations on these variables will be performed, and the results will be output.

### Example of a Program Generator:

The following code shows a sample generator program:

cpp

    #include "iostream"
    #include "string"
    #include <fstream>
    using namespace std;

    int main(void){
        string type1, type2;
        cin >> type1;
        cin >> type2;
        cout << type1 << ' ' << type2 << endl;

        ofstream fout("func_1.cpp");
        fout << "#include <iostream>" << endl;
        fout << "int f(void) {" << endl;
        fout << type1 << " var1 = 1;" << endl;
        fout << type1 << " var2 {3};" << endl;
        fout << "std::cout << var1 + var2 << std::endl;" << endl;
        fout << "return 0;" << endl;
        fout << "}" << endl;
        fout.close();

    return 0;

    }

This program creates a file containing a single function `f()`, which:

1.  Defines two variables of the specified type.
2.  Adds them together.
3.  Outputs the result.

## Additional Requirement:

Suggest a way to easily modify the generator program so it can synthesize more complex expressions. For example, use a file where each line contains symbols of operations. Any solutions are welcome.

Create a program that calls this generated function.

## Final Steps:

1.  Compile and run the resulting program.
2.  Prepare a report with:
    - Source code (or a link to GitHub with the source code).
    - Examples of the output.

In your conclusions, list the main drawbacks, in your opinion, of the generated function created in this lab work.
