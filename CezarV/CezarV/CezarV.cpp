// CezarV.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <clocale>
#include <windows.h>
#include "conio.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

	char menu;
	int key1=0;
	int i;
	int dlin=0;
	string key;
	string s[4096];

	int p=0;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_ALL,"Russian") ;
	setlocale (LC_ALL, "rus");

	
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);


	do
	{
		printf("\n1.Шифр. Цезаря\n2.Шифр. Вижнера\n0.Выход\n");
		menu=_getch();
		switch (menu)
		{
			case '1':
				{	
					printf("\nВведите ключ: ");
					scanf("%d",&key1);

					
					while(!ifst.eof())
					{	
						getline(ifst,s[i]);
						dlin+=s[i].length();
						i++;					
					}
					int ddlin;

					for(int i=0;i<dlin; i++)
					{
						ddlin=s[i].length();
						for(int j=0; j<ddlin;j++)
						{
							s[i][j]+=(key1+256)%256;
						}
					}
						i=0;
						while(i!=dlin)
						{
							ofst<<s[i]<<endl;
							i++;
						}
					
					break;
				}
			case '2':
				{
				
					printf("\nВведите ключ: ");
					cin>>key;
					int dddlin=key.length();
					
					while(!ifst.eof())
					{	
						getline(ifst,s[i]);
						dlin+=s[i].length();
						i++;					
					}
					int ddlin;

					for(int i=0;i<dlin; i++)
					{
						ddlin=s[i].length();
						for(int j=0; j<ddlin;j++)
						{
							s[i][j]+=key[p]+255%255;
							if(p<key.length()-1) ++p;else p=0;
							/*if((s[i][j]>=97)&&(s[i][j]<=122))
							{
							if((s[i][j]+key[p]-97)<=122) s[i][j]+=key[p]-97; else
							s[i][j]+=key[p]-123;
							if(p<key.length()-1) ++p;else p=0;
							}*/
							
						}
					}
						i=0;
						while(i!=dlin)
						{
							ofst<<s[i]<<endl;
							i++;
						}
					
					break;
				}
			
		}

	}while(menu!='0');

	return 0;
}

