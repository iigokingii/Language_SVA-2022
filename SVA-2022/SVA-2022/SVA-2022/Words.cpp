#include"stdafx.h"
char** DivideTexT(char* source, int size) {
	char** words = new char* [MAX_NUMBER_OF_WORDS];
	int stroke = 0;
	int column = 0;
	int countApostr = 0;
	In::IN letters;
	for (int i = 0; i < MAX_NUMBER_OF_WORDS; i++)
	{
		words[i] = new char[MAX_LENGTH_OF_WORD] {NULL};
	}
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (source[i] == '\'') {
			words[stroke][column++] = source[i++];
			countApostr++;
			while (source[i] != '\'')
			{
				words[stroke][column++] = source[i];
				i++;
			}
			words[stroke][column++] = source[i];
			countApostr++;
			words[stroke++][column] = '\0';
			column = 0;
			continue;
		}
		else if (letters.code[(int)source[i]] != In::IN::S) {
			words[stroke][column++] = source[i];
			flag = true;
		}
		else {
			if (source[i] != ' ' && flag) { //�������� �� �� �������� �� ��������� ������ ��������
				words[stroke++][column] = '\0';
				column = 0;
				words[stroke][column++] = source[i];
				words[stroke++][column] = '\0';
				column = 0;
			}
			else if (!flag && source[i] != ' ') { //���� ��
				words[stroke][column++] = source[i];
				words[stroke++][column] = '\0';
				column = 0;
			}
			else if (flag) {	//������
				words[stroke++][column] = '\0';
				column = 0;
			}
			flag = false;
		}
	}
	if (countApostr % 2 == 1) {
		throw ERROR_THROW(609);
	}
	words[stroke] = NULL;
	return words;
}


//#include"stdafx.h"
//char** DivideTexT(char* source, int size) {
//	char** words = new char* [MAX_NUMBER_OF_WORDS];
//	int stroke = 0;
//	int column = 0;
//	int countApostr = 0;
//	In::IN letters;
//	for (int i = 0; i < MAX_NUMBER_OF_WORDS; i++)
//	{
//		words[i] = new char[MAX_LENGTH_OF_WORD] {NULL};
//	}
//	bool flag = false;
//	int OtherSymb = 0;
//	bool f=false;
//	for (int i = 0; i < size; i++)
//	{
//		if (source[i] == '\'') {
//			words[stroke][column++] = source[i++];
//			countApostr++;
//			while (source[i] != '\n')
//			{
//
//				if (source[i] == ';')
//					break;
//				words[stroke][column++] = source[i];
//				if (source[i] == '\''||f) {
//					if (source[i] == '\'') {
//						countApostr++;
//						f = true;
//					}
//					else if (source[i] == ' ') {
//						i++;
//						continue;
//					}
//						
//					else
//						OtherSymb++;
//				}
//				i++;
//			}
//			if (countApostr >= 3||OtherSymb!=0 && countApostr==2) {
//				throw ERROR_THROW(309);
//			}
//			words[stroke++][column] = '\0';
//			column = 0;
//			words[stroke][column++] = source[i];
//			words[stroke++][column] = '\0';
//			column = 0;
//			countApostr = 0;
//			OtherSymb = 0;
//			f = false;
//			continue;
//			
//		}
//		else if (letters.code[(int)source[i]] != In::IN::S) {
//			words[stroke][column++] = source[i];
//			flag = true;
//		}
//		else {
//			if (source[i] != ' ' && flag) { //�������� �� �� �������� �� ��������� ������ ��������
//				words[stroke++][column] = '\0';
//				column = 0;
//				words[stroke][column++] = source[i];
//				words[stroke++][column] = '\0';
//				column = 0;
//			}
//			else if (!flag && source[i] != ' ') { //���� ��
//				words[stroke][column++] = source[i];
//				words[stroke++][column] = '\0';
//				column = 0;
//			}
//			else if (flag) {	//������
//				words[stroke++][column] = '\0';
//				column = 0;
//			}
//			flag = false;
//		}
//	}
//	if (countApostr % 2 == 1) {
//		throw ERROR_THROW(309);
//	}
//	words[stroke] = NULL;
//	return words;
//}