#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

namespace Encrypt{
    string caesarCipher(const string& str, const int key);
    void bruteforceCaesarCipher(const string& str);
    void makeUpper(string& str);
    void vigenereCipher(const string& str, string& key);
    char vigenereSquareLookUp(const int row, const int col);
    string keyRepeater(string originalKey, const int lengthOfString);
    string removesSpacesInString(const string str);




};






#endif