#include "Shannon-Fano.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	string str, encoding_result, decoding_result;
	string test = "0100 11 101 100 0101 11 0001 011 011 11 0100 11 101 100 0101 11 0011 0010 0000";
	cout << "������� �����: " << str << endl;
	getline(cin, str);
	Result(str, encoding_result, decoding_result);
	cout << "\n��������� �����������: " << encoding_result << endl;
	cout << "\n��������� �������������: " << decoding_result << endl;
	return 0;
}