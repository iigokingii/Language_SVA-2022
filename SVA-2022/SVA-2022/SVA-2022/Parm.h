#pragma once

#define PARM_IN L"-in:"// ключ дл€ файла исходного кода
#define PARM_OUT L"-out:"// ключ дл€ файла объектного кода
#define PARM_LOG L"-log:"// ключ дл€ файла журнала
#define PARM_IT L"-IT:"//ключ дл€ файла индентификаторов
#define PARM_LT L"-LT:"//ключ дл€ файла лексем
#define PARM_PARS L"-pars:"//ключ дл€ файла дерева разбора
#define PARM_MAX_SIZE 300// максимальна€ длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out"// расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"// расширение файла протокола по умолчанию
#define PARM_IT_DEFAULT_EXT L".IT"// расширение файла индентификаторов по умолчанию
#define PARM_LT_DEFAULT_EXT L".LT"// расширение файла лексем по умолчанию
#define PARM_PARS_DEFAULT_EXT L".pars"// расширение файла дерева разбора по умолчанию

namespace Parm// обработка входных параметров
{
	struct PARM		// входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];	// -in: им€ файла исходного кода
		wchar_t out[PARM_MAX_SIZE];	// -out: им€ файла объектного кода
		wchar_t log[PARM_MAX_SIZE];	// -log: им€ файла протокола
		wchar_t IT[PARM_MAX_SIZE];//-IT:им€файлаиндентификаторов
		wchar_t LT[PARM_MAX_SIZE];//-LT:им€файлалексем
		wchar_t greibach[PARM_MAX_SIZE];//-greibach:им€файлалексем
	};
	//(int argc, _TCHAR* argv[])
	PARM getparm(int argc, wchar_t* argv[]); //int argc, _TCHAR* argv[] 
	// сформировать struct PARM на основе параметров функции main
}
