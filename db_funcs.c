/*
Файл: db_funcs.c
Практика
Автор: Положий А. С.
Тема: Створення програми для роботи з даними про книги,
присвячені програмуванню та подальшого виведення їх у текстовий файл
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "db_funcs.h"

extern book* books;

/* Считывает струтуру из базы данных
@param id_num - номер структуры, которую необходимо считать
@param file_name - имя файла базы данных
*/
void read(int id_num, char file_name[STR_LENGH]) {
	FILE* fp;
	fp = fopen(file_name, "rb+");
	fseek(fp, (id_num - 1) * sizeof(book), SEEK_SET);//выставление позиции для считывания
	fread(books, sizeof(book), 1, fp);//считывание структуры
	fclose(fp);
}

/* Записывает струтуру в базу данных
@param id_num - номер места, куда необходимо записать
@param file_name - имя файла базы данных
*/
void write(int id_num, char file_name[STR_LENGH]) {
	FILE* fp2;
	fp2 = fopen(file_name, "rb+");
	fseek(fp2, (id_num - 1) * sizeof(book), SEEK_SET);//выставление позиции для записи
	fwrite(books, sizeof(book), 1, fp2);//запись структуры в файл
	fclose(fp2);
}

/* Считывает лишние символы из потока */
void skip(void) {
	while (getchar() != '\n');//считывание лишних символов до конца строки
}

/* Возвращает позицию id в файле
@param fp - указатель на базу данных
@return l - если id найден
@return 0 - если такого id нет
*/
int id_pos(FILE* fp, int id_num) {
	int l = 0;
	fseek(fp, 0, SEEK_SET);//выставление позиции на начало файла
	//считывание структур
	while ((fread(books, sizeof(book), 1, fp)) == 1) {
		l++;
		if (books[0].id == id_num) return l;//сравнение id структуры с нужным id
	}
	return 0;//если совпадений не найдено
}