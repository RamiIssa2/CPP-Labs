#include "iostream"
#include "string"
#include <fstream>

using namespace std;

string char_types[4] = {"char", "char16_t", "char32_t", "wchar_t"};
string sint_types[14] = {"signed int", "signed short int", "signed char", "singed long int", "signed long long int",
 "int","short","short int","signed short","long","long int", "signed long", "signed long long", "long long int"};
string uint_types[9] = {"unsigned char", "unsigned short int", "unsigned int", "unsigned long int", "unsigned long long int",
"unsigned short", "unsigned", "unsigned long", "unsigned long long"};
string float_types[3] = {"float", "double", "long double"};
string bool_types[1] = {"bool"};

string allowed_ops1[8] = {"+", "-", "*", "/", "%", "&&", "||", "^"};
string allowed_ops2[5] = {"+", "-", "*", "/", "%"};
string allowed_ops3[4] = {"+", "-", "*", "/"};

string char_vals[2] = {"\'3\'", "\'5\'"};
string sint_vals[2] = {"3", "-5"};
string uint_vals[2] = {"3", "5"};
string float_vals[2] = {"3.2", "5.8"};
string bool_vals[2] = {"false", "true"};

bool element_in_array(string array[], int size, string element){
    for (int i = 0; i < size; i++){
        if (element == array[i]){
            return true;
        }
    }
    return false;
}

bool Check_type(string type, int &type_code){
    if (element_in_array(char_types, 4, type)){
        type_code = 1;
        return true;
    }else if (element_in_array(sint_types, 14, type))
    {
        type_code = 2;
        return true;
    }else if (element_in_array(uint_types, 9, type))
    {
        type_code = 3;
        return true;
    }else if (element_in_array(float_types, 3, type))
    {
        type_code = 4;
        return true;
    }else if (element_in_array(bool_types, 1, type))
    {
        type_code = 5;
        return true;
    }else{
        type_code = 0;
        return false;
    }    
}

string Initialize_Values(int code, int index){
    string val = "Error";

    switch (code)
    {
    case 1:
        val = char_vals[index];
        break;
    case 2:
        val = sint_vals[index];
        break;
    case 3:
        val = uint_vals[index];
        break;
    case 4:
        val = float_vals[index];
        break;
    case 5:
        val = bool_vals[index];
        break;
    default:
        break;
    }

    return val;
}

int Find_Allowed_ops(int code1, int code2){
    if ((code1 == 4) || (code2 == 4)){
        return 3;
    }else if ((code1 == 5) && (code2 == 5))
    {
        return 1;
    }else
    {
        return 2;
    }
}

int main(void){

    string type1, type2;
    string val1, val2;
    int type_code1, type_code2;

    bool correct_types = false;

    while (!correct_types)
    {
        cout << "Enter three types:" << endl;
	    cin >> type1;
	    cin >> type2;

        correct_types = Check_type(type1, type_code1) && Check_type(type2, type_code2);
        if (type_code1 == 0){
            cout << "Type 1 is incorrect" << endl;
        }
        if (type_code2 == 0){
            cout << "Type 2 is incorrect" << endl;
        }
    }
    

    cout << "The types declared are:\n";
	cout << "Type 1:\t" << type1 << endl;
	cout << "Type 2:\t" << type2 << endl;

    val1 = Initialize_Values(type_code1, 0);
    val2 = Initialize_Values(type_code2, 1);

    if ((val1 == "Error") || (val2 == "Error")){
        cout << "Unknown error occurred while initializing values" << endl;
    }

    int ops_code = Find_Allowed_ops(type_code1, type_code2);


	ofstream fout("func_1.cpp");
	fout << "#include <iostream>" << endl;
	fout << endl;
	fout << "int f(void) {"<< endl;
	fout << type1 << " var1 = " << val1 <<";"<< endl;
	fout << type2 << " var2 = " << val2 << ";"<< endl;
	fout << endl;
    fout << "std::cout << \"var1 = \" << " << val1 <<" << std::endl;"<< endl;
	fout << "std::cout << \"var2 = \" << " << val2 << " << std::endl;"<< endl;
	fout << endl;
    if (ops_code == 1){
        for (string op : allowed_ops1){
            fout << "std::cout << \"var1 " << op << " var2 = \";"<< endl;
            if ((op == "&&") || (op == "||") || (op == "^")){
                fout << "std::cout << (var1 " << op << " var2) << std::endl;"<< endl;
            }else{
                fout << "std::cout << var1 " << op << " var2 << std::endl;"<< endl;
            }
        }
    }else if (ops_code == 2){
        for (string op : allowed_ops2){
            fout << "std::cout << \"var1 " << op << " var2 = \";"<< endl;
            fout << "std::cout << var1 " << op << " var2 << std::endl;"<< endl;
        }
    }else if (ops_code == 3){
        for (string op : allowed_ops3){
            fout << "std::cout << \"var1 " << op << " var2 = \";"<< endl;
            fout << "std::cout << var1 " << op << " var2 << std::endl;"<< endl;
        }
    }
	fout << endl;
	fout << "return 0;" << endl;
	fout << "}" << endl;
    fout << endl;
    fout << "int main(void){" << endl;
    fout << "f();" << endl;
    fout << "return 0;" << endl;
    fout << "}" << endl;
	fout.close();
	return 0;
}
