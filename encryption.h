#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

namespace Encrypt{
    void init(string& str, string& key);
    void stringMakeUpper(string& str);
    string decryptCaesarCipher(const string& str, const int key);
    char caesarCipher(const char character, const int key);
    void bruteforceCaesarCipher(const string& str);
    void vigenereCipher(const string& str, string& key);
    string decryptVigenereCipher(const string& cipherText, string key);
    char vigenereSquareLookUp(const int row, const int col);
    void bruteforceVigenereCipher(const string & str, const string& key);
    void VigenereBFNoKnownChar(const string& str, string& key);
    void keyRepeater(string& originalKey, const int lengthOfString);

};






#endif