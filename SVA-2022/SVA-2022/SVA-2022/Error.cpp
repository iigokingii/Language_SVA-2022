#include"ERROR.h"
namespace Error
{
	//�����	������:	0 - 99 - ��������� ������ 
	//				100 - 109 - ������ ���������� 
	//				110 - 119 - ������ �������� � ������ ������ 
	ERROR errors[ERROR_MAX_ENTRY] = //������� ������
	{
		ERROR_ENTRY(0, " ������������ ��� ������"), //��� ������ ��� ��������� 0-ERROR_MAX_ENTRY
		ERROR_ENTRY(1, " ��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100," �������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104," ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110," ������ ��� �������� ����� � ������� �����(-in)"),
		ERROR_ENTRY(111," ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112," ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120,"[LEX]#�������� ����������� ������ ������� ������"),
		ERROR_ENTRY(121,"[LEX]#������� ������ �����������"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160,"[LEX]#��������� ������������ ���������� ����� � ������� ���������������"),
		ERROR_ENTRY(161,"[LEX]#������� ��������������� �����������"),
		ERROR_ENTRY(162,"[LEX]#������ �������������� ������ ����������� �����������"),//TODO
		ERROR_ENTRY(163,"[LEX]#�� ������� ���������� �������"),
		ERROR_ENTRY(164,"[LEX]#������ �������� ������ ����������� �����������"),
		ERROR_ENTRY_NODEF(165), ERROR_ENTRY_NODEF(166),
		ERROR_ENTRY_NODEF(167), ERROR_ENTRY_NODEF(168),ERROR_ENTRY_NODEF(169),
		ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY(300,"[SEM]# ����������� ����� ����� main"),
		ERROR_ENTRY(301,"[SEM]# � ���������� �� ������ ��� ��������������"),
		ERROR_ENTRY(302,"[SEM]# � ���������� ����������� �������� ����� new"),
		ERROR_ENTRY(303,"[SEM]# ������������ �������� ��� �� ������������� ���� �������"),
		ERROR_ENTRY(304,"[SEM]# �������� �������� ���������"),
		ERROR_ENTRY(305,"[SEM]# ���� ������ � ��������� �� ���������"),
		ERROR_ENTRY(306,"[SEM]# ������� �� ����"),
		ERROR_ENTRY(307,"[SEM]# ������������� �������������"),
		ERROR_ENTRY(308,"[SEM]# ���������� ��������� ����� ����� � main"),
		ERROR_ENTRY(309,"[SEM]# ��������� \' . ��������, �� ������ ��������� �������"),
		ERROR_ENTRY(310,"[SEM]# � Symbol ���� �� ����� ���� ����� 1 �������"),
		ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"[SIN]# �������� ��������� ���������"),
		ERROR_ENTRY(601,"[SIN]# ������ � ���������� ����������"),
		ERROR_ENTRY(602,"[SIN]# ������ � ���������"),
		ERROR_ENTRY(603,"[SIN]# ������ � ���������� �������"),
		ERROR_ENTRY(604,"[SIN]# ������ � ���������� ���������� �������"),
		ERROR_ENTRY(606,"[SIN]# ������ � ���� �������"),
		ERROR_ENTRY(607,"[SIN]# ������ ��� �������������� ��������� ���������"),
		ERROR_ENTRY(608,"[SIN]# ������ � ���� ��������� ���������"),
		ERROR_ENTRY(609,"[SIN]# �� ������ ������ ���������� �������"),
		ERROR_ENTRY(610,"[SIN]# ������ � ������ �������"),
		ERROR_ENTRY(611,"[SIN]# ������ � �������������� ��������"),
		ERROR_ENTRY(612,"[SIN]# ��������� ������ ������� � ��������������"),
		ERROR_ENTRY_NODEF(613),ERROR_ENTRY_NODEF(614),ERROR_ENTRY_NODEF(615),
		ERROR_ENTRY_NODEF(616),ERROR_ENTRY_NODEF(617),ERROR_ENTRY_NODEF(618),ERROR_ENTRY_NODEF(619),
		/*
		ERROR_ENTRY(601, "[SYN]# �� ������ ������ ���������� �������"),
		
		ERROR_ENTRY(603, "[SYN]# ������ � ���� ���������"),
		
		ERROR_ENTRY(606, "[SYN]# ������ � ������ ����������� ���������� �������"),

		ERROR_ENTRY(608, "[SYN]# ������ � ���� �����/��������� ���������"),
		ERROR_ENTRY(609, "[SYN]# ������ � ������� �����/��������� ���������"),
		ERROR_ENTRY(610, "[SYN]# �������� �������� ��������"),
		ERROR_ENTRY(611, "[SYN]# �������� �������������� ��������"),
		ERROR_ENTRY(612, "[SYN]# �������� ���������. ��������� ������ ��������������/��������"),
		ERROR_ENTRY(613, "[SYN]# ������ � �������������� ���������"),
		ERROR_ENTRY(614, "[SYN]# ������������ �������������� �����������"),
		ERROR_ENTRY(615, "[SYN]# ������������ �������������� ����������� � ���� �����/��������� ���������"),*/

		ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
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