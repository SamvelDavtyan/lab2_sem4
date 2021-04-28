#pragma once

#include <iostream>
#include "List.h"
#include "RB-Tree.h"
#include <string>

// Sorting arrays
template<class A_type1, class A_type2>
void BubbleSort(A_type1* Arr_1, A_type2* Arr_2, int size)
{
	if (size <= 0)
		throw "Error! Incorrect size.";
	bool control = true;

	A_type1 temp_1;
	A_type2 temp_2;

	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (Arr_1[i] < Arr_1[j])
			{
				temp_1 = Arr_1[i];
				Arr_1[i] = Arr_1[j];
				Arr_1[j] = temp_1;
				temp_2 = Arr_2[i];
				Arr_2[i] = Arr_2[j];
				Arr_2[j] = temp_2;
			}
		}
	}
}

// Finding the middle of an array
template<class A_type>
int SearchMiddle(A_type* Arr, int start, int end)
{
	float average = 0;
	for (int i = start; i < end; i++)
		average = average + Arr[i];
	average = average / 2;
	int sum = 0, i = start, middle = i;
	while ((sum + Arr[i] < average) && (i < end))
	{
		sum = sum + Arr[i];
		i++;
		middle++;
	}
	return middle;
}

// The Shannon-Fano algorithm
void Shannon_Fano_Algorithm(unsigned* num_of_sym, char* sym, string& Branch, string& Full_Branch, int start, int end, Tree_Node<char, string>* Symbols_Code, unsigned& memory_after)
{
	size_t middle;
	string Temp_Branch;
	Temp_Branch = Full_Branch + Branch;
	if (start == end)
	{
		memory_after += Temp_Branch.length() * num_of_sym[start];
		Symbols_Code->Insert(sym[start], Temp_Branch);
		cout << "Символ: "<< sym[start] << "\tЧастота: " << num_of_sym[start] << "\t\tКод: " << Temp_Branch << endl;
		return;
	}
	middle = SearchMiddle(num_of_sym, start, end);
	string zero = "0", one = "1";
	Shannon_Fano_Algorithm(num_of_sym, sym, one, Temp_Branch, start, middle, Symbols_Code, memory_after);
	Shannon_Fano_Algorithm(num_of_sym, sym, zero, Temp_Branch, middle + 1, end, Symbols_Code, memory_after);
}

// Encodes and decodes the entered string
void Result(string& str, string& Eresult, string& Dresult)
{
	cout << "Введенный пользователем текст: " << str << endl;
	unsigned memory_before = str.length() * 8, memory_after = 0;
	Tree_Node<char, size_t> Number_of_characters;
	Number_of_characters.Nil_Creating();
	for (int i = 0; i < str.length(); ++i)
	{
		try
		{
			Number_of_characters.Insert(str[i], 1);
		}
		catch (int ex)
		{
			if (ex == 0)
				Number_of_characters[str[i]]++;
		}
	}
	size_t Array_Size = Number_of_characters.Get_Size();
	unsigned* number_of_symbols = new unsigned[Array_Size];
	char* symbols = new char[Array_Size];
	Number_of_characters.A_input(Number_of_characters.Get_Root(), number_of_symbols, 0);
	Number_of_characters.A_input(Number_of_characters.Get_Root(), symbols, 1);
	BubbleSort(number_of_symbols, symbols, Array_Size);

	// Encoding
	string temp = "";
	Tree_Node<char, string> Symbols_Code;
	Symbols_Code.Nil_Creating();
	Shannon_Fano_Algorithm(number_of_symbols, symbols, temp, temp, 0, Array_Size - 1, &Symbols_Code, memory_after);
	string Encoding_Result = "";
	for (int i = 0; i < str.length(); i++)
	{
		Encoding_Result += Symbols_Code[str[i]] + ' ';
	}
	Eresult = Encoding_Result;
	cout << "\nКоэффициент сжатия " << (1 - ((float)memory_after / (float)memory_before)) * 100 << "%\n";
	cout << "Память, занимаемая до кодироваиня (в битах): " << memory_before << endl;
	cout << "Память, занимаемая после кодирования (в битах): " << memory_after << endl;
	// Decoding
	Tree_Node<string, char> Codes_Symbol;
	Codes_Symbol.Nil_Creating();
	for (int i = 0; i < Array_Size; ++i)
	{
		Codes_Symbol.Insert(Symbols_Code[symbols[i]], symbols[i]);
	}
	string Decoding_Result = "", Code;
	for (int i = 0; i < Encoding_Result.length(); i++)
	{
		Code = "";
		while (Encoding_Result[i] != ' ')
		{
			Code += Encoding_Result[i++];
		}
		Decoding_Result += Codes_Symbol[Code];
	}
	Dresult = Decoding_Result;
	delete[] number_of_symbols;
	delete[] symbols;
}
