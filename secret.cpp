/*********************************************************************************************************
 * This is a basic Caesar cipher. 
 * The program tries every solution and prints out the finished string,  
 * and the given key.
 * 
 * You have to read through the output to look for a string 
 * that could be the correct one / the one you want.
 * 
 * Caesar cipher is a simple encryption technique, where the original character is 
 * replaced by another letter some fixed number of positions down/up the alphabet.
 * 
 * @author  -   Jørgen Mo Opsahl
 * @date    -   15.01.2020
 ********************************************************************************************************/


#include "encryption.h"
#include <iostream>
using namespace std;

int main(){

    string orStr = "AAAA";

    cout << Encrypt::keyRepeater(orStr, 8) << endl;

}