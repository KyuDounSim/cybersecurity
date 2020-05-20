// File name: a3b.cpp
#include <string>
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned char byte;

int *char2bin(byte ch);
byte bin2char(const int bin[8]);
int bin2int(const vector<byte> &bin);

vector<byte> string2bin(const string &str);
string bin2string(const vector<byte> &bin);

int string2hamming(const string &str, vector<byte> &hamming);
int string2hamming(const string &str, const vector<byte> &parity, vector<byte> &hamming);
void calculateHamming(vector<byte> &hamming, int k);
bool correctHamming(vector<byte> &hamming, int k);
void hamming2string(vector<byte> &hamming, string &str, vector<byte> &parity);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <parity> <str>" << endl;
        return 1;
    }
    
    vector<byte> parity = string2bin(string(argv[1]));
    vector<byte> hamming;
    int k = string2hamming(string(argv[2]), parity, hamming);
/*    
    cout << "Hamming code:" << endl;
    cout << bin2string(hamming) << endl;
*/   
    bool res = correctHamming(hamming, k);
    string str;
/*    if (res) 
        cout << "error was corrected" << endl;   
    cout << "Hamming code:" << endl;
    cout << bin2string(hamming) << endl;
*/    
    hamming2string(hamming, str, parity);
    cout << bin2string(parity) << endl;
    cout << str << endl;
    
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
 Convert bit representation  to int
 */
int bin2int(const vector<byte> &bin)
{
    int x=0;
    int n = bin.size();
    for (int i=n-1; i>=0; i--) {
        x = (x << 1) + bin[i];
    }
    return x;
}

/* 
 Convert string representation of a binary number 
 to vector of bits
 */
vector<byte> string2bin(const string &str)
{
    vector<byte> aBits(str.size());
    for (int i=0; i<aBits.size(); i++) {
        aBits[i] =  str[i] - '0';
    }
    return aBits;
}

/*
 Convert a vector representation of a binary number 
 to a string
 */
string bin2string(const vector<byte> &bin)
{
    string str;
    for (int i=0; i<bin.size(); i++) {
        str += static_cast<char>(bin[i] + '0');
    }
    return str;
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
 Represent a string as a sequence of bits inserting parity bits
 to form Hamming code
 Return number of parity bits inserted
 */
int string2hamming(const string &str, const vector<byte> &parity, vector<byte> &hamming)
{
    int n = 8*str.size();   // length of a string
    int k = 4;              // number of parity bits
    int q = 16;
    
    while (q < n + k + 1) {
        k++;
        q *= 2;
    }
    if ( k != parity.size()) {
        cerr << "string2hamming: incorrect number of parity bits" << endl;
        return 0;
    }
    
    hamming.resize(n+k);
    
    int ind = 0;
    int iParity = 0;
    q = 1;
    
    for (int i=0; i<str.size(); i++) {
        int *bin = char2bin(str[i]);
        int j = 0;
        while (j <8) {
            if (ind + 1 == q) {
                hamming[ind++] = parity[iParity++];
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
  Check Hamming code and correct it if needed
  Return true if error has found
 */ 
bool correctHamming(vector<byte> &hamming, int k)
{
    vector<byte> bin_err(k);    // Binary representation of error bit
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
        bin_err[p] =  sum % 2;
        step *= 2;
    }
    int err_bit = bin2int(bin_err);
    if (err_bit == 0)
        return false;
    hamming[err_bit-1] ^= 1;
    return true;    
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