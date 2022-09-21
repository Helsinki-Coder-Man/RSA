#include <iostream>
#include <cmath>
#include <stdint.h>

#include <unistd.h>

const char* alph =  "-abcdefghijklmnopqrstuvwxyz";
const char* cAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* nums = "0123456789";

std::string encrypt(int64_t e, int64_t n, std::string plaintext){
	std::string cipher;
	for(int i = 0; i < plaintext.length(); i++)
	{
		int loc = 0;
		std::cout << (int)plaintext[i] << '\n';
		if((int)plaintext[i] >= 65 && (int)plaintext[i] <= 90){
			for(int k = 0; k < 26; k++){
				if(plaintext[i] == cAlph[k]){
					loc = k;
				}
			}
			cipher += cAlph[ (((int64_t)pow(loc,e) % n) % 26) ];
			
		}

		if((int)plaintext[i] >= 97 && (int)plaintext[i] <= 122){
			for(int k = 1; k < 26; k++){
				if(plaintext[i] == alph[k]){
					loc = k;
				}
			}
			int64_t nLoc = (((int64_t)pow(loc,e) % n) % 26) ;
			if(nLoc == 0)
				nLoc++;
					
			cipher += alph[nLoc];

			
		}

	}	

	return cipher;
}


std::string decrypt(int64_t d, int64_t n, std::string cipher){
	std::string plaintext;
	int loc = 0;
	for(int i = 0; i < cipher.length(); i++)
	{
		if((int)cipher[i] >= 65 && (int)cipher[i] <= 90){
			for(int k = 0; k < 26; k++){
				if(cipher[i] == cAlph[k]){
					loc = k;
				}
			}
			plaintext += cAlph[ ((int64_t)pow(loc,d) % n) % 26 ];	
		}

		if((int)cipher[i] >= 97 && (int)cipher[i] <= 122){
			for(int k = 0; k < 26; k++){
				if(cipher[i] == alph[k]){
					loc = k;
					
				}
			}
			int64_t nLoc = ((int64_t)pow(loc,d) % n) % 26 ;
			if (nLoc == 0) 
			nLoc++; std::cout << 'X' <<  nLoc;
			plaintext += alph[nLoc];
		}
		

	}	


	std::cout << "RETURN";
	return plaintext;
}


int main()
{
	std::string plaintext = "b"; std::cout << 's' << (int64_t)pow(2,65537) % 2314654961 % 26 << '\n';

	std::string cipher = encrypt( 13, 119 ,plaintext);
	std::string undone = decrypt( 37, 119,cipher);

	std::cout << "\nOriginal String: " << plaintext;
	std::cout << "\nEncrypted text: " << cipher;
	std::cout << "\nDecrypted text: " << undone;
	
}
