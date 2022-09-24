//#include "stdafx.h"

#include <cryptopp/rsa.h>
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;

#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <cryptopp/secblock.h>
using CryptoPP::SecByteBlock;

#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;
using CryptoPP::DecodingResult;

#include <string>
using std::string;

#include <iostream>


#include <assert.h>

AutoSeededRandomPool rng;
InvertibleRSAFunction parameters;
//parameters.GenerateRandomWithKeySize(rng, 1024);	


std::string encrypt(const std::string plaintext, RSA::PublicKey publicKey)
{
	RSAES_OAEP_SHA_Encryptor e (publicKey);
	std::string cipher;
	CryptoPP::StringSource ss1(plaintext, true , 
	new CryptoPP::PK_EncryptorFilter(rng, e , new CryptoPP::StringSink(cipher)));
	return cipher;
}

std::string decrypt(const std::string cipher, RSA::PrivateKey privateKey)
{
	RSAES_OAEP_SHA_Decryptor  d (privateKey);
	std::string plaintext;
	CryptoPP::StringSource ss1( cipher, true , 
	new CryptoPP::PK_DecryptorFilter(rng, d , new CryptoPP::StringSink(plaintext)));
	return plaintext;
}




int main()
{

	parameters.GenerateRandomWithKeySize(rng, 512);	
	RSA::PublicKey publicKey ( parameters );
	RSA::PrivateKey privateKey ( parameters );


	std::string plaintext = "Hello World";
	std::cout << "\nOriginal text: " << plaintext ;

	std::string ciphered  = encrypt(plaintext, publicKey);
	std::cout << "\nEncrypted text: " << ciphered;

	std::string deciphered = decrypt(ciphered, privateKey);
	std::cout << "\n\nDecrypted text: " << deciphered << std::endl;

}
