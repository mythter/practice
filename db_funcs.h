/*
����: db_funcs.h
��������
�����: ������� �. �.
����: ��������� �������� ��� ������ � ������ ��� �����,
��������� ������������� �� ���������� ��������� �� � ��������� ����
*/


#ifndef DB_FUNCS_H
#define DB_FUNCS_H
#define STR_LENGH 100
#define LANG_LENGH 30

#define PUBLIC
#define PRIVATE static

//���������� ���������
typedef struct {
	int id;
	char author[STR_LENGH];
	char name[STR_LENGH];
	char language[LANG_LENGH];
	int amount;
	double price;
	int deleted;
} book;
// ��������� �� ���������� books ���� ������ struct book
book* books;

PUBLIC  void read(int id_num, char file_name[STR_LENGH]);
PUBLIC  void write(int id_num, char file_name[STR_LENGH]);
PUBLIC  int id_pos(FILE* fp, int id_num);
PUBLIC  void skip(void);

#endif