#include"ERROR.h"
namespace Error
{
	//серии	ошибок:	0 - 99 - системные ошибки 
	//				100 - 109 - ошибки параметров 
	//				110 - 119 - ошибки открытия и чтения файлов 
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок
	{
		ERROR_ENTRY(0, " Недопустимый код ошибки"), //код ошибки вне диапазона 0-ERROR_MAX_ENTRY
		ERROR_ENTRY(1, " Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100," Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104," Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110," Ошибка при открытии файла с иходным кодом(-in)"),
		ERROR_ENTRY(111," Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112," Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120,"[LEX]#Превышен максимльный размер таблицы лексем"),
		ERROR_ENTRY(121,"[LEX]#Таблица лексем переполнена"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160,"[LEX]#Превышено максимальное количество строк в таблице идентификаторов"),
		ERROR_ENTRY(161,"[LEX]#Таблица идентификаторов переполнена"),
		ERROR_ENTRY(162,"[LEX]#Размер идентификатора больше максимально допустимого"),//TODO
		ERROR_ENTRY(163,"[LEX]#Не удалось распознать цепочку"),
		ERROR_ENTRY(164,"[LEX]#Размер литерала больше максимально допустимого"),
		ERROR_ENTRY_NODEF(165), ERROR_ENTRY_NODEF(166),
		ERROR_ENTRY_NODEF(167), ERROR_ENTRY_NODEF(168),ERROR_ENTRY_NODEF(169),
		ERROR_ENTRY_NODEF(170),ERROR_ENTRY_NODEF(180),ERROR_ENTRY_NODEF(190),
		ERROR_ENTRY_NODEF(200),
		ERROR_ENTRY(300,"[SEM]# Отсутствует точка входа main"),
		ERROR_ENTRY(301,"[SEM]# В объявлении не указан тип идентификатора"),
		ERROR_ENTRY(302,"[SEM]# В объявлении отсутствует ключевое слово new"),
		ERROR_ENTRY(303,"[SEM]# Возвращаемый функцией тип не соответствует типу функции"),
		ERROR_ENTRY(304,"[SEM]# Неверное условное выражение"),
		ERROR_ENTRY(305,"[SEM]# Типы данных в выражении не совпадают"),
		ERROR_ENTRY(306,"[SEM]# Деление на ноль"),
		ERROR_ENTRY(307,"[SEM]# Необъявленный идентификатор"),
		ERROR_ENTRY(308,"[SEM]# Обнаружено несколько точек входа в main"),
		ERROR_ENTRY(309,"[SEM]# Обнаружен \' . Возможно, не закрыт строковый литерал"),
		ERROR_ENTRY_NODEF(310),ERROR_ENTRY_NODEF(320),ERROR_ENTRY_NODEF(330),ERROR_ENTRY_NODEF(340),ERROR_ENTRY_NODEF(350),
		ERROR_ENTRY_NODEF(360),ERROR_ENTRY_NODEF(370),ERROR_ENTRY_NODEF(380),ERROR_ENTRY_NODEF(390),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY(600,"[SIN]# Неверная структура программы"),
		ERROR_ENTRY(601,"[SIN]# Ошибочный оператор"),
		ERROR_ENTRY(602,"[SIN]# Ошибка в выражении"),
		ERROR_ENTRY(603,"[SIN]# Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"[SIN]# Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF(610),ERROR_ENTRY_NODEF(620),ERROR_ENTRY_NODEF(630),ERROR_ENTRY_NODEF(640),ERROR_ENTRY_NODEF(650),
		ERROR_ENTRY_NODEF(660),ERROR_ENTRY_NODEF(670),ERROR_ENTRY_NODEF(680),ERROR_ENTRY_NODEF(690),
		ERROR_ENTRY_NODEF(700),ERROR_ENTRY_NODEF(800),ERROR_ENTRY_NODEF(900),
	};
	ERROR geterror(int id) {
		if (0 > id || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	};
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		ERROR e;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			e = errors[0];
		else
		{
			e = errors[id];
			e.inext.line = line;
			e.inext.column = col;
		}
		return e;
	};
};