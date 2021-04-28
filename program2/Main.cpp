#include "Shannon-Fano.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	string str, encoding_result, decoding_result;
	string test = "0100 11 101 100 0101 11 0001 011 011 11 0100 11 101 100 0101 11 0011 0010 0000";
	cout << "Введите текст: " << str << endl;
	getline(cin, str);
	Result(str, encoding_result, decoding_result);
	cout << "\nРезультат кодирования: " << encoding_result << endl;
	cout << "\nРезультат декодирования: " << decoding_result << endl;
	return 0;
}