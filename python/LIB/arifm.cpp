#include "arifm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>

using std::ifstream;
using std::ofstream;

#define divnull 1


chislo::chislo()
{//Конструктор по умолчанию
	this->razmer = 1;
	this->znak = 0;
	this->razr = new unsigned char[1];
	this->razr[0] = 0;
}

chislo::chislo(const char* inputstr)
{
	//Конструктор от входной строки
	
	int sLen = strlen(inputstr);
	int sznak = 0;
	if (inputstr[0] == '-')
	{
		sznak = 1;
		sLen--;
	}

	chislo res;
	chislo pow_of_ten = 1;  // Для того,чтобы преобразовать char в число по основанию 256 необходимо каждый 
								//Каждый символ превести к int значению и далее умножить на 10 в степени i, где i номер разряда.

	for (int i = sLen + sznak - 1; i >= sznak; i--)
	{
		int razryad = inputstr[i] - '0';
		res = res + pow_of_ten * razryad;
		pow_of_ten = pow_of_ten * 10;
	}
	res.znak = sznak;

	this->razmer = 0;
	*this = res;
}

chislo::chislo(const chislo &right)
{	//конструктор от chislo
	this->razmer = right.razmer;
	this->razr = new unsigned char[this->razmer];
	this->znak = right.znak;
	memcpy(razr, right.razr, this->razmer * sizeof(unsigned char));
	return;
}

chislo::chislo(int value)
{   
	//Конструктор от int-ового значения

	this->razr = new unsigned char[11]();
	this->razmer = 0;
	this->znak = 0;
	if (value < 0)
	{
		this->znak = 1;
		value = -value;
	}
	do
	{
		this->razmer++;
		this->razr[this->razmer - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->dellnull();
}

chislo::~chislo()
{// Деструктор
	delete[] razr;
}

char* chislo::GetString()
{
	//Фукция получения строки в 10-й записи
	
	chislo temp = *this; 
	temp.znak = 0;
	
	std::vector<char> tempStr; // Вектор для хранения строки


	while (temp != (int)0)
	{
		chislo rem;
		temp = delen(temp, 10, rem); 
		char ost = rem[0] + '0'; 
		tempStr.push_back(ost);
	}

	
	if (this->znak)
		tempStr.push_back('-');


	int srazmer = tempStr.size();
	char* string = new char[srazmer + 1]();

	for (int i = 0; i < tempStr.size(); i++)
	{
		string[srazmer - i - 1] = tempStr[i];
	}

	return string;
}

	
	char* chislo::__str__()
		{
			return GetString();
		}

	char* chislo::__repr__()
		{
			return GetString();
		}

bool chislo::readText(const char* filename)
{
	ifstream fp(filename);
	if (fp.fail())
		return false;

	fp.seekg(0, std::ios::end);
	int File_razmer = fp.tellg();
	fp.seekg(0, std::ios::beg);

	char* string = new char[File_razmer + 1]();
	fp >> string;
	fp.close();

	*this = chislo(string);
	delete[] string;
	return true;
}

bool chislo::writeText(const char* filename)
{
	ofstream fp_r(filename);
	if (fp_r.fail())
		return false;

	char* string = this->GetString();
	fp_r << string;
	delete[] string;
	fp_r.close();

	return true;
}

bool chislo::WriteBin(const char* filename)
{

	ofstream fp_ob(filename, std::ios::binary);
	if (fp_ob.fail())
		return false;

	fp_ob.write((char*) this->razr, this->razmer); 

	fp_ob.close();
	return true;
}

bool chislo::ReadBin(const char* filename)
{
	ifstream fp_ib(filename, std::ios::binary);
	if (fp_ib.fail())
		return false;

	fp_ib.seekg(0, std::ios::end);
	int File_razmer = fp_ib.tellg();
	fp_ib.seekg(0, std::ios::beg);

	delete[] this->razr;
	this->razr = new unsigned char[File_razmer];
	this->razmer = File_razmer;
	this->znak = 0;

	fp_ib.read((char*)this->razr, File_razmer);
	fp_ib.close();

	return true;
}


void chislo::zad_razmer(int newrazmer)
{	
	if (this->razmer)
		delete[] this->razr;
	this->razmer = newrazmer;
	this->znak = 0;
	this->razr = new unsigned char[this->razmer]();
}

void chislo::dellnull()
{
	while ((razmer - 1)&& razr[razmer - 1] == 0)
		this->razmer--;

	if (this->razmer == 1 && razr[0] == 0)
		this->znak = 0;
}

int chislo::sravn(const chislo& b)
{

	int znakFlag = 1;
	if (this->znak == 1)
		znakFlag = -1;

	if (this->znak != b.znak)
		return znakFlag;

	if (this->razmer > b.razmer)
		return znakFlag;

	if (this->razmer < b.razmer)
		return -znakFlag;

	int i = this->razmer - 1;

	while (this->razr[i] == b[i] && i > 0)
	{
		i--;
	}
	return ( (int) this->razr[i] - (int) b[i]) * znakFlag;
}

void chislo::sdvig(int s)
{

	unsigned char* newrazr = new unsigned char[this->razmer + s]();
	for (int i = 0; i < this->razmer; i++)
	{
		newrazr[i + s] = this->razr[i];
	}

	delete[] this->razr;
	this->razr = newrazr;
	this->razmer += s;
	this->dellnull();
}


chislo chislo::plusmin(const chislo& left, const chislo& right) const
{
	chislo A = left, B = right; 
	A.znak = 0;
	B.znak = 0;
	if (A > B)
	{
		A.znak = left.znak;
		B.znak = right.znak;
	}
	else
	{
		A = right;
		B = left;
	}

	if (A.znak == B.znak)
	{

		chislo res;
		res.zad_razmer(A.razmer + 1);

		int cf = 0;

		for (int i = 0; i < A.razmer; i++)
		{
			int tmp = A[i] + cf;
			if (i < B.razmer)
				tmp += B[i];

			res[i] = tmp % 256;
			cf = tmp / 256;
		}

		res[A.razmer] = cf;
		res.znak = A.znak;
		res.dellnull();
		return res;
	}
	else
	{
		chislo res;
		res.zad_razmer(A.razmer);

		int cf = 0;
		for (int i = 0; i < A.razmer; i++)
		{
			int tmp = A[i] - cf;
			if (i < B.razmer)
				tmp -= B[i];

			cf = 0;
			if (tmp < 0)
			{
				cf = 1;
				tmp += 256;
			}
			res[i] = tmp;
		}

		res.znak = A.znak;
		res.dellnull();
		return res;
	}
}

chislo chislo::Umn(const chislo a, const chislo b) const
{
	chislo res;
	res.zad_razmer(a.razmer + b.razmer);
	int cf = 0;
	for (int i = 0; i < b.razmer; i++)
	{
		cf = 0;
		for (int j = 0; j < a.razmer; j++)
		{
			int tmp = (int) b[i] * (int) a[j] + (int) cf + (int) res[i + j];
			cf = tmp / 256;
			res[i + j] = tmp % 256;
		}
		res[i + a.razmer] = cf;
	}

	res.znak = (a.znak != b.znak);
	res.dellnull();
	return res;
}

chislo chislo::delen(const chislo& a, const chislo& b, chislo &rem) const
{
	rem = a;
	rem.znak = 0;

	chislo delitel = b;
	delitel.znak = 0;

	if (delitel == chislo((int)0))
	{
		throw divnull;
	}

	if (rem < delitel)
	{
		rem = a;
		return chislo((int)0);
	}

	chislo res;
	res.zad_razmer(a.razmer - b.razmer + 1);

	for (int i = a.razmer - b.razmer + 1; i; i--)
	{
		int verh = 256;
		int niz = 0;
		int Value = verh;


		while (verh - niz > 1)
		{
			Value = (verh + niz) / 2;

			
			chislo tmp = delitel * Value;
			tmp.sdvig(i - 1);	// умножение на 256^(i - 1)
			
			if (tmp > rem)
				verh = Value;
			else
				niz = Value;
		}
		chislo tmp = delitel * niz;
		tmp.sdvig(i - 1); // умножение на 256 ^ (i - 1)
		rem = rem - tmp;
		res[i - 1] = niz;
	}

	res.znak = (a.znak != b.znak);
	rem.znak = (a.znak != b.znak);
	rem.dellnull();
	res.dellnull();

	return res;
}


chislo Pow(const chislo& a, const chislo& b, chislo& mod)
{
	if (mod <= (int)0)
		return a ^ b;

	chislo osn = a % mod;
	chislo res = 1;

	for (chislo i = b; i > (int)0; i = i - 1)
		res = (res * osn) % mod;

	return res;
}

unsigned char & chislo::operator[](int i)
{
	if (i < 0)
		return this->razr[this->razmer + i];
	return this->razr[i];
}

unsigned char chislo::operator[](int i) const
{
	if (i < 0)
		return this->razr[this->razmer + i];
	return this->razr[i];
}


chislo& chislo::operator=(const chislo& right)
{
	if (this->razmer)
		delete[] this->razr;

	this->razmer = right.razmer;
	this->razr = new unsigned char[razmer];
	this->znak = right.znak;
	memcpy(razr, right.razr, razmer);
	return *this;
}

chislo chislo::operator-() const
{
	chislo res = *this;
	res.znak = !res.znak;
	return res;
}

chislo chislo::operator^(const chislo& right) const
{
	chislo res = 1;
	chislo base = *this;
	for (chislo i = right; i > (int)0; i = i - 1)
		res = res * base;
	return res;
}

chislo chislo::operator+(const chislo& right) const
{
	return plusmin(*this, right);
}

chislo chislo::operator-(const chislo& right) const
{
	return *this + (-right);
}

chislo chislo::operator*(const chislo& right) const
{
	return Umn(*this, right);
}

chislo chislo::operator/(const chislo& right) const
{
	chislo rem;
	return delen(*this, right, rem);
}

chislo chislo::operator%(const chislo& right) const
{
	chislo rem;
	delen(*this, right, rem);
	return rem;
}

bool chislo::operator>(const chislo& b)
{
	return this->sravn(b) > 0;
}

bool chislo::operator>=(const chislo& b)
{
	return this->sravn(b) >= 0;
}

bool chislo::operator<(const chislo& b)
{
	return this->sravn(b) < 0;
}

bool chislo::operator<=(const chislo& b)
{
	return this->sravn(b) <= 0;
}

bool chislo::operator==(const chislo& b)
{
	return this->sravn(b) == 0;
}

bool chislo::operator!=(const chislo& b)
{
	return this->sravn(b) != 0;
}

chislo chislo::operator++()
{
chislo value = *this;
*this = *this + 1;
return value;
}

chislo chislo::operator++(int)
{
*this = *this + 1;
return *this;
}
chislo chislo::operator--()
{
chislo value = *this;
*this = *this - 1;
return value;
}

chislo chislo::operator--(int)
{
*this = *this - 1;
return *this;
}
