#include<iostream>
extern "C" {

	int _stdcall Strlen(char arr[]) {//gtht
		return strlen(arr);
	}

	int _stdcall Rand(int range) {
		srand((unsigned)time(NULL));
		return rand() % range;
	}

	int _stdcall input(int i) {
		std::cin >> i;
		return i;
	}

	int _stdcall output(char* str) {
		if (str == NULL)
			std::cout << std::endl;
		for (int i = 0; str[i] != '\0'; i++)
			std::cout << str[i];
		return 0;
	}
}
