#include "encryption.h"



/**
 * Makes the given string uppercase only.
 * @param   -   the string
 **/
void Encrypt::makeUpper(string& str){
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
string Encrypt::caesarCipher(const string& str, const int key){
    string solution = "";
    char temp;

    for(auto j : str){
        if(j == ' '){
            temp = j;
        }
        else if(!isalpha(j) ){
            temp = '?'; //Any character that is not a letter or space, gets the '?' symbol in its place
        }
        else{
            temp = 'A' + ((j - 'A' + key) % 26); // (value of the current char) - (the value of 'A') is
                                                 // the number of characters into the alphabet (to the right of 'A')
                                                 // + the key(right shift that amount) % 26 in case 
        }                                        // the current value surpasses the length of the alphabet
        solution.push_back(temp);
    }
    return solution;
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
        possibleSolution = caesarCipher(str, key);
        cout << key << ":> "<< possibleSolution << endl << endl;
        possibleSolution.clear();
    }

}


/**
 * The Vigenere cipher is basically Caesar cipher on steroids. 
 * 
 * A textbased key is used, this key has to be shorter than the original string.
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
void Encrypt::vigenereCipher(const string& str, const string& key){

}
/**
 * finds the character based on the row and collum index, and returns it.
 * 
 * @param   -   row number
 * @param   -   collum number
 * 
 **/
char Encrypt::vigenereSquareLookUp(const int row, const int col){
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

    return vigSquare[row].at(col);

}


/**
 * Repeats the key until it is of the correct length, used by the Vigenere- and Beaufort ciphers.
 * 
 **/
string Encrypt::keyRepeater(string originalKey, const int lengthOfString){
    int stringIndex = 0;
    
    for(int i = originalKey.length(); i < lengthOfString; i++, stringIndex++){

        originalKey.push_back(originalKey[stringIndex]);
        if(stringIndex == originalKey.end()){ // if the current index is the same as the last index of the string
            stringIndex = 0;
        }
        

    }

    return originalKey;
}

/**
 * The Beafort cipher is just like the Vigenere cipher, but reversed. 
 * 
 **/
/*void beaufortCipher(){

}*/