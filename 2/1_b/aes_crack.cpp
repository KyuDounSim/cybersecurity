#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <openssl/aes.h>

std::vector<unsigned char> ReadFileToVector(const std::string& fileName)
{
    std::ifstream ifs(fileName, std::ios::binary);

        if(!ifs)
        {
            std::cout << "Open file '" << fileName<< "' failed\n";
            return std::vector<unsigned char>();
        }
    
    std::vector<char> data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        if(data.empty())
        {
            std::cout << "No data read from file '" << fileName<< "'\n";
            return std::vector<unsigned char>();
        }

        if(data.size() % 16 != 0)
        {
            std::cout << "Size of read data is not multiple of 16 bytes\n";
            return std::vector<unsigned char>();
        }
    
    return std::vector<unsigned char>(data.begin(), data.end());;
}

bool WriteStringToFile(const std::string& fileName, const std::string& data)
{
    std::ofstream ofs(fileName, std::ios::binary);

        if(!ofs)
        {
            std::cout << "Create file '" << fileName<< "' failed\n";
            return false;
        }
    
    std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(ofs));

        if(!ofs)
        {
            std::cout << "Write data to file '" << fileName<< "' failed\n";
            return false;            
        }
    
    return true;
}

std::string DecryptData(const std::vector<unsigned char>& key
                       ,const std::vector<unsigned char>& cipherText)
{
    //Set key
    AES_KEY AESkey;
    AES_set_decrypt_key(&key[0], 128, &AESkey);

    std::string decryptedText;

    //Handle all blocks encrypted in ECB-mode 
    for(size_t i=0; i<cipherText.size(); i+=16)
    {
        //Decrypt current block
        unsigned char buffer[16];
        AES_decrypt(&cipherText[i], buffer, &AESkey); 

        //Add decrypted bytes to result string
        for(int j=0; j<16; ++j)
        {
            decryptedText.push_back(buffer[j]);
        }
    }

    return decryptedText;
}

bool withinRange(unsigned char a)
{
    if( (32 <= a && a <= 34) || (39 <= a && a <= 41) || (44 <= a && a <= 59) || a == 63 || (65 <= a && a <= 90) || (97 <= a && a <= 122)) {

        return true;

    } else {
    
	return false;
    }
}
bool CheckDecryptedData(const std::string& data)
{
    //Decrypted text is considered correct if all of its characters are withinrange
    for(size_t i=0; i<data.size(); ++i)
    {
        if(!withinRange(static_cast<unsigned char>(data[i])))
        {
            return false;
        }
    }

    return true;    
}

int main()
{
    //Read data for decryption
    std::vector<unsigned char> cipherText = ReadFileToVector("aestext");

        if(cipherText.empty())
        {
            //Error of reading
            return 2;
        }
    
    //By the task's condition the 128-bit AES key has the value 1...2^20 (1...0x100000)
    const int max_key_value = 0x100000;

    //Check all keys in a given range
    for(int i=1; i<max_key_value; ++i)
    {
        //Create 16 bytes (128 bits) AES key: 13 bytes are 0, three low bytes get from counter
        std::vector<unsigned char> key(13);
        key.push_back(static_cast<unsigned char>((i & 0x00FF0000) >> 16));
        key.push_back(static_cast<unsigned char>((i & 0x0000FF00) >>  8));
        key.push_back(static_cast<unsigned char>((i & 0x000000FF)));

        //Decrypt cipherText using current key
        std::string decryptedText = DecryptData(key, cipherText);

        if(CheckDecryptedData(decryptedText))
        {
            //Decrypted data is valid
            std::cout << "Data decrypted successfully!\n";
            std::cout << "Decrypted data: " << decryptedText << "\n";
            std::cout << "AES key:        0x" << std::hex << std::uppercase << i << "\n";

            //Write decrypted text to file
            if(WriteStringToFile("de_aestext", decryptedText))
            {
                std::cout << "The decrypted data has written to 'de_aestext' file.\n";
            }

            return 0;
        }
    }

    std::cout << "Error: Valid text is not detected\n";
    
    return 1;
}

