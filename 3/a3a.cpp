// File name: a3a.cpp
#include <string>
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned char byte;

int *char2bin(byte ch);
byte bin2char(const int bin[8]);

int string2hamming(const string &str, vector<byte> &hamming);
void calculateHamming(vector<byte> &hamming, int k);
void hamming2string(vector<byte> &hamming, string &str, vector<byte> &parity);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <str>" << endl;
        return 1;
    }
    
    vector<byte> hamming;
    int k = string2hamming(string(argv[1]), hamming);

/*    
    for (int i=0; i<hamming.size(); i++)
        cout << static_cast<char>(hamming[i] + '0');
    cout << endl;
    cout << "Need " << k << " parity bits" << endl << endl;
*/    
    calculateHamming(hamming, k);
/*    cout << "Calculated Hamming:" << endl;
    for (int i=0; i<hamming.size(); i++)
        cout << static_cast<char>(hamming[i] + '0');
    cout << endl << endl;
    
    cout << "Reverse:" << endl;
*/    
    vector<byte> parity;
    string str;
    hamming2string(hamming, str, parity);
    for (int i=0; i<k; i++)
        cout << static_cast<char>(parity[i] + '0');
    cout << endl;
/*    
    cout << str << endl;
*/       
    return 0;        
}

/*
 Convert a character to its bits representation
 */
int *char2bin(byte ch)
{
    static int bin[8];
    for (int i=0; i<8; i++) {
        bin[7-i] = ch % 2;
        ch >>= 1;
    }
    return bin;
}

/*
 Convert bit representation back to character
 */
byte bin2char(const int bin[8])
{
    byte ch=0;
    for (int i=0; i<8; i++) {
        ch = (ch << 1) + bin[i];
    }
    return ch;
}

/*
 Represent a string as a sequence of bits inserting parity bits
 (with zero value) to form Hamming code
 Return number of parity bits inserted
 */
int string2hamming(const string &str, vector<byte> &hamming)
{
    int n = 8*str.size();   // length of a string
    int k = 4;              // number of parity bits
    int q = 16;
    
    while (q < n + k + 1) {
        k++;
        q *= 2;
    }
    hamming.resize(n+k);
    
    int ind = 0;
    q = 1;
    
    for (int i=0; i<str.size(); i++) {
        int *bin = char2bin(str[i]);
        int j = 0;
        while (j <8) {
            if (ind + 1 == q) {
                hamming[ind++] = 0;
                q *= 2;
                continue;
            }
            hamming[ind++] = bin[j++];
        }
    }
    return k;
}

/*
  Calculate parity bits to form Hamming code
 */ 
void calculateHamming(vector<byte> &hamming, int k)
{
    int step = 1;
    for (int p=0; p<k; p++) {
        // Set parity bit p
        int sum = 0;
        int i = step - 1;
        while (i < hamming.size()) {
            for (int j=i; j<i+step; j++) {
                sum += hamming[j];
                if ( j == hamming.size()) {
                    break;
                }
            }
            i += 2*step;
        }
        sum -= hamming[step-1];
        hamming[step-1] = sum % 2;
        step *= 2;
    }
}

/* 
 Separate Hamming code into data and parity, data converted to string formatt
 */
void hamming2string(vector<byte> &hamming, string &str, vector<byte> &parity)
{
    str = "";
    parity.clear();
    int nextParity=1;
    int bits[8];
    int nextBit = 0;
    
    for (int i=0; i<hamming.size(); i++) {
        if (i+1 == nextParity) {
            nextParity *= 2;
            parity.push_back(hamming[i]);
        }
        else {
            bits[nextBit++] = hamming[i];
            if (nextBit == 8) {
                str += bin2char(bits);
                nextBit = 0;
            }
        }
    }
}