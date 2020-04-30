#include <iostream>
#include <fstream>

using namespace std;

int main() {
    cout << "Hello, asdfasdf!" << endl;

    ifstream input("aestext");
    ofstream output("de_aestext");

    char[1000] cipher_text, result;
    input >> cipher_text;
    input.close();

    for(int i = 0; i < 1000; ++i) {
        cout << cipher_text[i];
    }
    cout << endl;

    output << result;
    output.close();

    return 0;
}
