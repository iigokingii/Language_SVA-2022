#include"stdafx.h"
char** DivideTexT(char* source, int size) {
	char** words = new char* [MAX_NUMBER_OF_WORDS];
	int stroke = 0;
	int column = 0;
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
			while (source[i] != '\'')
			{
				words[stroke][column++] = source[i];
				i++;
			}
			words[stroke][column++] = source[i];
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
	words[stroke] = NULL;
	return words;
}