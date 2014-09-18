#pragma once

class chislo
{
private:
	int razmer; // размер числа
	unsigned char* razr; // знаки числа
	int znak; //знак - 0 положительный , 1 - отрицательный

public:
	//Конструкторы
	chislo();
	chislo(const char* inputstr);
	chislo(const chislo& right);
	chislo(int right);

	~chislo(); // деструктор

	char* GetString(); // функция получения строки в 10-й записи

	// Операции с файлами
	bool readText(const char* FileName);
	bool writeText(const char* FileName);
	bool ReadBin(const char* FileName);
	bool WriteBin(const char* FileName);





	//Операторы сравнения
	bool operator>(const chislo& b);
	bool operator>=(const chislo& b);
	bool operator<(const chislo& b);
	bool operator<=(const chislo& b);
	bool operator==(const chislo& b);
	bool operator!=(const chislo& b);







	//Операторы инкриментирования и декриментирования
	chislo operator++();
	chislo operator++(int);
	chislo operator--();
	chislo operator--(int);





	//Арифметические операторы
	chislo& operator=(const chislo& right);
	chislo operator+(const chislo& right) const;
	chislo operator-() const;
	chislo operator-(const chislo& right) const;
	chislo operator*(const chislo& right) const;
	chislo operator/(const chislo& right) const;
	chislo operator%(const chislo& right) const;
	chislo operator^(const chislo& right) const;

private:
	void zad_razmer(int razmer); // устанавливает размер
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void dellnull(); // Название функции говорит само за себя
	int sravn(const chislo& b);
	void sdvig(int s);

	chislo plusmin(const chislo& LValue, const chislo& right) const;
	chislo Umn(const chislo a, const chislo b) const;
	chislo delen(const chislo& a, const chislo& b, chislo &rem) const;

};

chislo Pow(const chislo& a, const chislo& b, chislo& M);