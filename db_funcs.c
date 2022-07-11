/*
����: db_funcs.c
��������
�����: ������� �. �.
����: ��������� �������� ��� ������ � ������ ��� �����,
��������� ������������� �� ���������� ��������� �� � ��������� ����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "db_funcs.h"

extern book* books;

/* ��������� �������� �� ���� ������
@param id_num - ����� ���������, ������� ���������� �������
@param file_name - ��� ����� ���� ������
*/
void read(int id_num, char file_name[STR_LENGH]) {
	FILE* fp;
	fp = fopen(file_name, "rb+");
	fseek(fp, (id_num - 1) * sizeof(book), SEEK_SET);//����������� ������� ��� ����������
	fread(books, sizeof(book), 1, fp);//���������� ���������
	fclose(fp);
}

/* ���������� �������� � ���� ������
@param id_num - ����� �����, ���� ���������� ��������
@param file_name - ��� ����� ���� ������
*/
void write(int id_num, char file_name[STR_LENGH]) {
	FILE* fp2;
	fp2 = fopen(file_name, "rb+");
	fseek(fp2, (id_num - 1) * sizeof(book), SEEK_SET);//����������� ������� ��� ������
	fwrite(books, sizeof(book), 1, fp2);//������ ��������� � ����
	fclose(fp2);
}

/* ��������� ������ ������� �� ������ */
void skip(void) {
	while (getchar() != '\n');//���������� ������ �������� �� ����� ������
}

/* ���������� ������� id � �����
@param fp - ��������� �� ���� ������
@return l - ���� id ������
@return 0 - ���� ������ id ���
*/
int id_pos(FILE* fp, int id_num) {
	int l = 0;
	fseek(fp, 0, SEEK_SET);//����������� ������� �� ������ �����
	//���������� ��������
	while ((fread(books, sizeof(book), 1, fp)) == 1) {
		l++;
		if (books[0].id == id_num) return l;//��������� id ��������� � ������ id
	}
	return 0;//���� ���������� �� �������
}