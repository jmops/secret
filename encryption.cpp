#include "encryption.h"
#include <iostream>
#include <fstream>
//using namespace std;

/**
 * Initializes the key and ciphered string, by making both uppercase
 * 
 **/ 
void Encrypt::init(string& str, string& key){
    if(str.length() > 0){
        Encrypt::stringMakeUpper(str);    
    }
    if(key.length() > 0){
        Encrypt::stringMakeUpper(key);
    }
    
}

/**
 * Makes the given string uppercase only.
 * @param   -   the string
 **/
void Encrypt::stringMakeUpper(string& str){
    for_each(str.begin(), str.end(), 
                                [](char& ch){ch= toupper(ch); }); //Lambda

}

/**
 * Decipher an uppercase string encrypted with a Caesar cipher. 
 * 
 * @param   -   uppercase string to decipher
 * @param   -   right-shift key
 * @return  -   the solved string
 **/
string Encrypt::decryptCaesarCipher(const string& str, const int key){
    string solution = "";
    char temp;

    for(auto j : str){
        if(isalpha(j)){
            temp = Encrypt::caesarCipher(j, key);
        }
        else{
            temp = j;//if it's not a letter in the a-z alphabet, the character stays.
        }
        solution.push_back(temp);
    }
    return solution;
}

/**
 * Decrypts an uppercased Caesar encrypted character with a given key, and returns it.
 * 
 **/
char Encrypt::caesarCipher(const char character, const int key){
/* (value of the current char) - (the value of 'A') is the number of characters 
    into the alphabet (to the right of 'A') + the key(right shift that amount) % 26 in case
    the current value surpasses the length of the alphabet.
*/
    return ((character - 'A' + key) % 26) + 'A';

}



/**
 * Bruteforces a Caesar cipher, and prints them out with their given keys.
 * 
 * @param   -   the string
 * 
 **/
void Encrypt::bruteforceCaesarCipher(const string& str){
    string possibleSolution = "";
    //Loops through all possibilities
    for(int key = 1; key < 26; key++){
        possibleSolution = decryptCaesarCipher(str, key);
        cout << key << ":> " << possibleSolution << endl << endl;
        possibleSolution.clear();
    }

}


/**
 * The Vigenere cipher is basically Caesar cipher on steroids. 
 * 
 * A textbased key is used, this key has to be shorter or equally long as the original string.
 * The original character is paired with the given key. E.g the 1 character from the string is 
 * paired with the first character in the key. The character from the key decides the row,
 * while the character from the original string decides the collum.
 * E.g row B, collum C gives the character 'D'.
 * 
 * The key is repeated until it is the same length as the original text:
 *         Original text: "THISISATEST"
 *                   key: "ABC"
 * Key while deciphering: "ABCABCABCAB"
 *        Encrypted text: "TIKSJUAUGSU"
 *  
 * 
 **/
void Encrypt::vigenereCipher(const string& str, string& key){
    string result = "";
    int row, col;
    char temp;
    
    Encrypt::keyRepeater(key, str.length()); // makes the key the same length as the original string

    
    for(int i = 0, keyIndex = 0; i < str.length(); i++, keyIndex++){
        if(isalpha(str.at(i)) ){    //checks to see if the current character a letter
        
            row = key.at(keyIndex) - 'A';
            col = str.at(i) - 'A';
            temp = Encrypt::vigenereSquareLookUp(row, col);
        }
        else if(str.at(i) == ' '){
            temp = ' '; //add a space if the current character in the original string is a space
            keyIndex--;
        }
        else{
            temp = '?';
            keyIndex--; //if the current char of str is not a letter, use the same character of the key next time
        }

        result.push_back(temp);


    }
    cout << result << endl;
    

}

/**
 * Repeats the key until it is the correct length, and decrypts the text with the key.
 * 
 * When decrypting a Vigenere cipher, you uses the current character of the key for the row,
 * and the current character of the text as a collum. The decrypted character is the character of the alphabet
 * with the same index (collum nr.) as the encrypted character. 
 *  
 * E.g key      = 'C'
 *    char      = 'F'
 * soution      = 'D'
 * (see the Vigenere Square below)
 * 
 * @param   -   The encrypted text
 * @param   -   the key
 * 
 * @return  -   the decrypted text
 * 
 **/
string Encrypt::decryptVigenereCipher(const string& cipherText, string key){
    string solution = "";
    char temp;
    int row, col, difference;
    Encrypt::keyRepeater(key, cipherText.length());

    for(int i = 0, keyIndex = 0; i < cipherText.length(); i++, keyIndex++){
        if(isalpha(cipherText.at(i)) ){
            difference = key.at(keyIndex) - 'A';
            temp = Encrypt::caesarCipher(cipherText.at(i), (26 - difference) );
            

            
        }
        else if(cipherText.at(i) == ' '){
            temp = ' '; //add a space if the current character in the original string is a space
            keyIndex--;
        }

        else{
            temp = '?';
            keyIndex--; //if the current char of str is not a letter, use the same character of the key next time
        }
        solution.push_back(temp);


    }
    return solution;

}
/**
 * finds the character based on the row and collum index, and returns it.
 * 
 * @param   -   row number
 * @param   -   collum number
 * 
 **/
char Encrypt::vigenereSquareLookUp(const int row, const int col){
    /*
        vector<string>vigSquare = {         // This is how the Vigenere square looks like, 
            {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}, // the alphabet encrypted with all the possible Caesar keys: 0 <= n <= 25
            {"BCDEFGHIJKLMNOPQRSTUVWXYZA"}, // the top row is the original alphabet, and the first collum is the alphabet
            {"CDEFGHIJKLMNOPQRSTUVWXYZAB"},
            {"DEFGHIJKLMNOPQRSTUVWXYZABC"},
            {"EFGHIJKLMNOPQRSTUVWXYZABCD"},
            {"FGHIJKLMNOPQRSTUVWXYZABCDE"},
            {"GHIJKLMNOPQRSTUVWXYZABCDEF"},
            {"HIJKLMNOPQRSTUVWXYZABCDEFG"},
            {"IJKLMNOPQRSTUVWXYZABCDEFGH"},
            {"JKLMNOPQRSTUVWXYZABCDEFGHI"},
            {"KLMNOPQRSTUVWXYZABCDEFGHIJ"},
            {"LMNOPQRSTUVWXYZABCDEFGHIJK"},
            {"MNOPQRSTUVWXYZABCDEFGHIJKL"},
            {"NOPQRSTUVWXYZABCDEFGHIJKLM"},
            {"OPQRSTUVWXYZABCDEFGHIJKLMN"},
            {"PQRSTUVWXYZABCDEFGHIJKLMNO"},
            {"QRSTUVWXYZABCDEFGHIJKLMNOP"},
            {"RSTUVWXYZABCDEFGHIJKLMNOPQ"},
            {"STUVWXYZABCDEFGHIJKLMNOPQR"},
            {"TUVWXYZABCDEFGHIJKLMNOPQRS"},
            {"UVWXYZABCDEFGHIJKLMNOPQRST"},
            {"VWXYZABCDEFGHIJKLMNOPQRSTU"},
            {"WXYZABCDEFGHIJKLMNOPQRSTUV"},
            {"XYZABCDEFGHIJKLMNOPQRSTUVW"},
            {"YZABCDEFGHIJKLMNOPQRSTUVWX"},
            {"ZABCDEFGHIJKLMNOPQRSTUVWXY"}
    };
*/
    
//instead of using the vector to find the character, using this is a lot faster:
    char character = (row % 26) + 'A';           //how far down/ row
    character = 'A' + ((character - 'A' + col) % 26);   //how far inn, literally just a Caesar cipher

    return character;
    //return vigSquare[row].at(col);

}
/**
 * This bruteforce method requires that you have atleast the length of the key,
 * a character in the key that you do not know what is, is symbolised as a '?'. 
 * 
 * E.g if you know that the key is 5 characters long, the given key should be "?????"
 * 
 * 
 **/
void Encrypt::bruteforceVigenereCipher(const string & str, const string& key){
    string firstKey = "";
    vector<int>knownIndex;
    bool characterIsKnown = false;
    /*Creates the first key that should be tried*/
    for(int i = 0; i < key.length(); i++){
        if(key.at(i) == '?'){
            firstKey.push_back('A');
        }
        else{
            firstKey.push_back(key.at(i) );
            knownIndex.push_back(i);
            characterIsKnown = true;
        }        
    }
    
    if(characterIsKnown){

    }
    else{
        cout << "Bruteforcing the encrypted string as a Vigenere cipher, without knowing any of the characters:\n...\n";
        Encrypt::VigenereBFNoKnownChar(str, firstKey);
    }
}
/**
 * Bruteforces a Vigenere Cipher without knowing any of the characters of the key, but knowing the length.
 * 
 * 
 * 
 **/
void Encrypt::VigenereBFNoKnownChar(const string& str, string& key){
    int keyLength = key.length(),
        lastUpdatedIndex = 1;
    ofstream toFile;
    toFile.open("VigenereBruteforce.dat", ios::out);

    while(key.at(keyLength -1) != ('Z' +1)){ // loops until the last character is 'Z' +1, which means that all combinations have been tried 

        for(int z = 0; z < 26; z++){                    //Updated the first index, and tries the key
            key.at(0) = ('A' + z); 
            //cout << key << endl;
            toFile << "Key: " << key << "\nText: " << Encrypt::decryptVigenereCipher(str, key) << "\n";                      //
            
        }
        key.at(1) += 1;                 //after one complete loop of the first index, updates the 2 index
        for(int i = 1; i <= lastUpdatedIndex; i++){ //loops until the most recent change
            if(key.at(i) == ('Z' + 1) && i != keyLength-1){ //checks to see if the current index has completed a cycle (passed 'Z'), and if the current index is not the last index
                key.at(i) = 'A';        //if the index has completed a cycle, reset it to 'A' 

                     
                    key.at(i+1) += 1;  // Updates the next index (since the current index has completed a cycle)
                
                lastUpdatedIndex = i+1;// Takes note of what the last index that got changed was (so it doesn't have to loop through the entire key to check for completed cycles) 
            }
        }        
    }

    toFile.close();




}


/**
 * Repeats the key until it is of the correct length, used by the Vigenere- and Beaufort ciphers.
 * 
 * @param   -   the key
 * @param   -   length of the original string
 * 
 * The length of the original text does not take into account spaces and other non-alphabetic characters.
 * However, making the key a bit longer won't do anything, since it is just a repetition of itself.
 * 
 **/
void Encrypt::keyRepeater(string& originalKey, const int lengthOfString){
    int stringIndex = 0,
        lastIndexOfOriginalKey = originalKey.length() -1;
    
    
    for(int i = originalKey.length(); i < lengthOfString; i++, stringIndex++){

        originalKey.push_back(originalKey[stringIndex]);
        if(stringIndex == lastIndexOfOriginalKey){ // if the current index is the same as the last index of the string
            stringIndex = -1;                      // -1 since it is going to be incremented (and we want stringIndex to be 0)
        }


    }
    
}



/**
 * The Beafort cipher is just like the Vigenere cipher, but reversed. 
 * 
 **/
/*void beaufortCipher(){

}*/