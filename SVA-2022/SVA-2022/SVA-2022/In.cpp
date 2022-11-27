#include "stdafx.h"
namespace In
{
	IN getin(wchar_t infile[])
	{
		IN f;
		static unsigned char l[1024] = "";
		int amount = 0;
		int line = 0, position = 0, size = 0, ignor = 0, i = 0, pr = 0;
		bool expres = false;
		std::ifstream in(infile);

		if (in.fail() == 0)
		{
			char c;  in.get(c);
			unsigned char ch = c;
			while (pr <= IN_MAX_LEN_TEXT)
			{
				if (in.eof())
				{
					l[i] = '\0';
					break;
					amount = 0;
				}
				if (ch == ('\n'))
				{
					position = 0;
					line++;
					l[i] = '\n';
					i++;
				}
				else if (f.code[int((unsigned char)ch)] == IN::T || f.code[int((unsigned char)ch)] == IN::S)
				{
					if (ch == '\'' && expres == true) {//если втрой раз встретим то true=>она закрыв 
						expres = false;
					}

					if (ch == '\'') {
						expres = true;
					}
					if (ch != (' ') || expres == true) {
						amount = 0;
						l[i] = ch;
						position++;
						i++;
					}
					else
					{
						amount++;
						if (amount == 1) {
							l[i] = ch;
							position++;
							i++;
						}
					}
				}
				else if (f.code[int((unsigned char)ch)] == IN::F)
				{
					throw ERROR_THROW_IN(111, line + 1, position + 1);
				}
				else if (f.code[int((unsigned char)ch)] == IN::I)
				{
					amount = 0;
					ignor++;
					amount = 0;
				}
				else
				{
					l[i] = f.code[ch];
					i++;
					amount = 0;
				}
				ch = in.get();
			}
			in.close();

			f.size = i; //количесвто символов
			f.text = l;
			f.lines = line;
			f.ignor = ignor;

			std::ofstream in(infile);
			in << l;
			in.close();
		}
		else
		{
			throw ERROR_THROW(110);
		}
		return f;
	}
};
