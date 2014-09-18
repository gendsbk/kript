#pragma once

class chislo
{
private:
	int razmer; 
	unsigned char* razr; 
	int znak; 

public:
	
	chislo();
	chislo(const char* inputstr);
	chislo(const chislo& right);
	chislo(int right);

	~chislo(); 

	char* GetString(); 

	
	bool readText(const char* FileName);
	bool writeText(const char* FileName);
	bool ReadBin(const char* FileName);
	bool WriteBin(const char* FileName);






	bool operator>(const chislo& b);
	bool operator>=(const chislo& b);
	bool operator<(const chislo& b);
	bool operator<=(const chislo& b);
	bool operator==(const chislo& b);
	bool operator!=(const chislo& b);







	
	chislo operator++();
	chislo operator++(int);
	chislo operator--();
	chislo operator--(int);





	
	chislo& operator=(const chislo& right);
	chislo operator+(const chislo& right) const;
	chislo operator-() const;
	chislo operator-(const chislo& right) const;
	chislo operator*(const chislo& right) const;
	chislo operator/(const chislo& right) const;
	chislo operator%(const chislo& right) const;
	chislo operator^(const chislo& right) const;

private:
	void zad_razmer(int razmer); 
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void dellnull(); 
	int sravn(const chislo& b);
	void sdvig(int s);

	chislo plusmin(const chislo& LValue, const chislo& right) const;
	chislo Umn(const chislo a, const chislo b) const;
	chislo delen(const chislo& a, const chislo& b, chislo &rem) const;

};

chislo Pow(const chislo& a, const chislo& b, chislo& M);
