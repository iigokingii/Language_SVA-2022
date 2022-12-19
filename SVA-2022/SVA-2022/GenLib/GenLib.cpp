#include<iostream>

extern "C" {
	int _stdcall Rand(int range=1000) {
		srand((unsigned)time(NULL));
		return rand() % range;
	}

	int _stdcall Input(int i) {
		std::cin >> i;
		return i;
	}
	int _stdcall Printstroke(char* str) {
		setlocale(LC_CTYPE, "ru");
		if (str == NULL)
			std::cout<< std::endl;
		for (int i = 0; str[i] != '\0'; i++)
			std::cout << str[i];
		std::cout<< std::endl;
		return 0;
	}
	int _stdcall Strlen(char* str) {
		setlocale(LC_CTYPE, "ru");
		return strlen(str);
	}
	int _stdcall PrintNumb(int numb) {
		setlocale(LC_CTYPE, "ru");
		std::cout << numb<<std::endl;
		return 0;
	}
	int _stdcall Remainder(int numb1, int numb2) {
		return numb2 % numb1;
	}

}
