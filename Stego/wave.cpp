#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int code(char* ffile, char* out, char* text); 
int decode(char* ffile, char* out); 

int bitSemp(unsigned char semp);

vector<unsigned char> readf(char* fName);

int main(int argc, char* argv[])
{
	if (argc != 4 && argc != 3)
	{
		cout << "in.wav out.wav text.txt" << endl << endl;
		cout << "in.waw out.txt>" << endl;
		return 0;
	}

	if (argc == 4)
		return code(argv[1], argv[2], argv[3]);
	else
		return decode(argv[1], argv[2]);
}
int bitSemp(unsigned char semp)
{
	int bytesSemp = 0;
	switch (semp)
	{
	case 8:
		bytesSemp = 1;
		break;
	case 16:
		bytesSemp = 2;
		break;
	case 24:
		bytesSemp = 3;
		break;
	case 32:
		bytesSemp = 4;
		break;
	default:
		bytesSemp = 1;
	}
	return bytesSemp;
}


int code(char* ffile, char* out, char* text)
{
	vector<unsigned char> in = readf(ffile);

	vector<unsigned char> intext = readf(text);

	if (intext.size() > 65536 ||
		intext.size() * 8 + 16 > (in.size() - 44) / bitSemp(in[34]) )
	{
		cout << text << " so many" << endl;
		return 1;
	}

	
	vector<unsigned char> data; 
	
	int fileSize = intext.size();
	for (int i = 0; i < 16; i++)
	{
		data.push_back(fileSize % 2);
		fileSize /= 2;
	}

	for (int i = 0; i < intext.size(); i++)
	{
		unsigned char b = intext[i];
		for (int j = 0; j < 8; j++)
		{
			data.push_back(b % 2);
			b /= 2;
		}
	}

	int bytesSemp = bitSemp(in[34]);

	for (int i = 0, pos = 44; i < data.size(); i++, pos += bytesSemp)
	{
		if (in[pos] % 2 == 1) 
		{
			if (data[i] == 0) 
				in[pos]++; 
		}
		else 
		{
			if (data[i] == 1) 
				in[pos]++; 
		}
	}

	ofstream outStream(out, ios::binary);
	outStream.write((char*)&in.front(), in.size());
	outStream.close();
	return 0;
}

int decode(char* ffile, char* out)
{
	vector<unsigned char> in = readf(ffile);

	int pos = 44; 
	int bytesSemp = bitSemp(in[34]);

	int fileSize = 0;
	int pow2 = 1; 
	for (int i = 0; i < 16; i++)
	{
		fileSize += (in[pos] % 2) * pow2;
		pow2 *= 2;
		pos += bytesSemp;
	}

	vector<unsigned char> output;
	for (int i = 0; i < fileSize; i++)
	{
		unsigned char b = 0;
		for (int j = 0, pow2 = 1; j < 8; j++, pow2 *= 2, pos += bytesSemp)
		{
			b += (in[pos] % 2) * pow2;
		}
		output.push_back(b);
	}

	ofstream outStream(out, ios::binary);
	outStream.write((char*)&output.front(), output.size());
	outStream.close();
	return 0;
}

vector<unsigned char> readf(char* fileName)
{
	vector<unsigned char> input;
	ifstream ifst(fileName, ios::binary);
	if (ifst.fail())
		return input;

	ifst.seekg(0, ios::end);
	int size = ifst.tellg();
	ifst.seekg(0, ios::beg);

	input.resize(size);
	ifst.read((char*)&input.front(), size);
	ifst.close();

	return input;
}



