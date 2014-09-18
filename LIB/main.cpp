#include <iostream>
#include <string.h>
#include "arifm.h"
using std::cout;

using namespace std;
void printmenu()
{
	cout << "Long_ariph <A filelame> <operation> <B filelame> <result filename> [-b] [<mod filename>]" << endl << endl;
	cout << "Ariph operations: + , -, * , / ,^, %"<<endl;
	cout << "mod and binary key isn't required "<<endl;
}

bool procoperation(chislo A, chislo B, chislo mod, char operation, chislo& res)
{
	if (mod < (int)0)
	{
		cout << "Negative mod!" << endl;
		return false;
	}

	if (operation == '^')
	{
		res = Pow(A, B, mod);
		return true;
	}

	if (mod > (int)0)
	{
		A = A % mod;
		B = B % mod;
	}

	switch (operation)
	{
	case '+':
		res = A + B;
		break;

	case '-':
		res = A - B;
		break;

	case '*':
		res = A * B;
		break;

	case '/':
		try
		{
			res = A / B;
		}
		catch (int err)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		break;

	case '%':
		try
		{
			res = A % B;
		}
		catch (int err)
		{
			cout << "Division by zero" << endl;
			return false;
		}
		break;

	default:
		cout << "Wrong operation." << endl;
		printmenu();
		return false;
	}

	if (mod > (int)0)
	{
		res = res % mod;
		while (res < (int)0)
			res = res + mod;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cout << "Don't enough arguments" << endl;
		printmenu();
		return -1;
	}

	if (argc > 7)
	{
		cout << "So many arguments" << endl;
		printmenu();
		return -2;
	}

	if (strlen(argv[2]) > 1)
	{
		cout << "unknown operation" << endl;
		printmenu();
		return -3;
	}

	char* fileA = argv[1];
	char operation = argv[2][0];
	char* fileB = argv[3];
	char* fileRes = argv[4];
	bool binary = false;
	char* fileMod = NULL;

	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))
			binary = true;
		else
			fileMod = argv[5];
	}

	if (argc == 7)
	{
		binary = true;
		fileMod = argv[6];
	}

	chislo A, B, mod = (int)0;

	if (binary)
	{
		A.ReadBin(fileA);
		B.ReadBin(fileB);
		if (fileMod)
			mod.ReadBin(fileMod);
	}
	else
	{
		A.readText(fileA);
		B.readText(fileB);
		if (fileMod)
			mod.readText(fileMod);
	}

	chislo res;
	if (!procoperation(A, B, mod, operation, res))
		return -1;

	if (binary)
		res.WriteBin(fileRes);
	else
		res.writeText(fileRes);

	return 0;
}