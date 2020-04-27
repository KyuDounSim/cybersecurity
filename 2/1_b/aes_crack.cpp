#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main()
{
    ifstream input("aestext");
    ofstream output("de_aestext");

    string cipher_text, result = "";
    input >> cipher_text;
    input.close();

    cout << cipher_text << endl;

    output << result;
    output.close();
    
    return 0;
}
