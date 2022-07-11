/*
Файл: main.c
Практика
Автор: Положий А. С.
Тема: Створення програми для роботи з даними про книги, 
присвячені програмуванню та подальшого виведення їх у текстовий файл
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "db_funcs.h"


extern book* books;

int main(void) {

    FILE* f1, * f2;
    int choice, num_books = 0, not_deleted = 0, k, number;
    char file_name[STR_LENGH], txt_name[STR_LENGH], db_name[STR_LENGH], letter, str[STR_LENGH], str1[STR_LENGH];

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_CTYPE, "rus"); // смена кодовой таблицы символов - включение русского языка
    books = (book*)malloc(sizeof(book));//выделение памяти для структуры
    choose:
    printf("Открыть существующий файл или создать новый? (0 - открыть / 1 - создать) ");
    scanf_s("%d", &choice);

    if (choice == 0) {
        printf("Введите имя текствого файла, который хотите открыть: ");
        scanf_s("%s", file_name, STR_LENGH);
        strcpy(txt_name, file_name);
        strcpy(db_name, file_name);
        strcat(txt_name, ".txt"); //имя текстового файла
        strcat(db_name, ".dat"); //имя базы данных
        // проверка на наличие файлов в каталоге
        if ((f1 = fopen(txt_name, "r")) == NULL || (f2 = fopen(db_name, "rb")) == NULL) {
            if ((f1 = fopen(txt_name, "r")) == NULL) {
                printf("Файл %s не найден в каталоге\n", txt_name);
            }
            if ((f2 = fopen(db_name, "rb")) == NULL) {
                printf("Файл %s не найден в каталоге\n", db_name);
            }
            goto choose;
        }
        else {
            printf("Файлы %s и %s успешно открыты\n", txt_name, db_name);
            f1 = fopen(txt_name, "w");
            f2 = fopen(db_name, "rb+");
            fseek(f2, 0, SEEK_SET);
            //подсчет книг	
            while ((fread(books, sizeof(book), 1, f2)) == 1) {
                num_books++;
                if (!books[0].deleted) not_deleted++;
            }
        }


    }
    else if (choice == 1) {
        printf("Введите имя текствого файла и базы данных для него: ");
        scanf_s("%s", file_name, STR_LENGH);
        strcpy(txt_name, file_name);
        strcpy(db_name, file_name); 
        strcat(txt_name, ".txt");  //имя текстового файла
        strcat(db_name, ".dat");  //имя базы данных
        //проверка на наличие уже созданных файлов с таким названием в каталоге
        if ((f1 = fopen(txt_name, "r")) != NULL || (f2 = fopen(db_name, "rb")) != NULL) {
            if ((f1 = fopen(txt_name, "r")) != NULL) {
                printf("Файл %s уже существует\n", txt_name);
                fclose(f1);
            }
            if ((f2 = fopen(db_name, "rb")) != NULL) {
                printf("Файл %s уже существует\n", db_name);
                fclose(f2);
            }
            goto choose;
        }
        else {
            printf("Файлы %s и %s успешно созданы\n", txt_name, db_name);
            f1 = fopen(txt_name, "w");
            f2 = fopen(db_name, "wb+");
        }
    }
    else {
        printf("Введите 0 или 1\n");
        goto choose;
    }
    commands:
    do {
        do {
            printf("\nДобавить книгу <a>, удалить книгу <d>, посмотреть информацию о книге(ах) <l>, изменить информацию о книге <c>,\n"
                "найти книги, посвящённые программированию на языке С <s>, завершить программу <e>: ");
            scanf_s(" %c", &letter, 1);
            skip();
        } while (letter != 'a' && letter != 'd' && letter != 'l' && letter != 'c' && letter != 'e' && letter != 's');
        switch (letter) {
        case 'a': {
            for (k = 1; k <= num_books; k++) {
                read(k, db_name);
                if (books[0].deleted == 1) break;
            }
            if (k > num_books) books[0].id = ++num_books;
            printf("Введите автора книги: ");
            gets(books[0].author);
            printf("Введите название книги: ");
            gets_s(books[0].name, sizeof(books[0].name));
            printf("Введите язык программирования, про который идёт речь в книге: ");
            gets_s(books[0].language, sizeof(books[0].language));
            printf("Введите тираж: ");
            scanf_s("%d", &books[0].amount);
            printf("Введите цену за книгу: ");
            scanf_s("%lg", &books[0].price);
            skip();
            books[0].deleted = 0;
            write(books[0].id, db_name);//добавление новой записи в базу данных
            printf("\nЗапись успешно добавлена с id: %d\n", books[0].id);
            not_deleted++;
            break;
        }
        case 'd': {
            printf("\nВведите id записи, которую хотите удалить: ");
            scanf_s("%d", &number);
            skip();
            if (k = id_pos(f2, number)) {
                read(k, db_name);
                books[0].deleted = 1;//пометка об удалении записи
                write(k, db_name);
                not_deleted--;
                printf("\nЗапись с id = %d успешно удалена.\n", books[0].id);
            }
            else printf("\nЗапись с id = %d не найдена\n", number);

            break;
        }
        case 'l': {
        look:
            if (num_books == 0) {
                printf("\nНе найдено ни одной записи\n");
                break;
            }
            printf("Информация о всех книгах или о конкретной книге? (0 - о всех / 1 - о конкретной) ");
            scanf_s("%d", &choice);
            skip();
            if (choice == 0) {
                for (k = 1; k <= num_books; k++) {
                    read(k, db_name);
                    if (books[0].deleted == 1) {
                        printf("\nid: %d\n", k);
                        printf("Запись удалена\n");
                        continue;
                    }
                    printf("\nid: %d\nАвтор: %s\nНазвание: %s\n"
                        "Тираж: %d\nЦена: %.2f\n", k, books[0].author, books[0].name, books[0].amount, books[0].price);
                }
            }
            else if (choice == 1) {
                printf("\nВведите id записи, которую хотите просмотреть: ");
                scanf_s("%d", &number);
                skip();
                //проверка, если запись удалена
                if (id_pos(f2, number) && books[0].deleted == 0) {
                    read(id_pos(f2, number), db_name);
                    printf("\nid: %d\nАвтор: %s\nНазвание: %s\n"
                        "Тираж: %d\nЦена: %.2f\n", number, books[0].author, books[0].name, books[0].amount, books[0].price);
                }
                else printf("\nТакой записи не существует или она удалена\n");
            }
            else {
                printf("Введите 0 или 1\n");
                goto look;
            }
           
            break;
        }
        case 'c': {
            while (1) {
                printf("\nВведите id записи, которую хотите изменить: ");
                scanf_s("%d", &number);
                if (number > 0 && number <= num_books) break;
                printf("Неверный id\n");
                goto commands;
            }
            read(number, db_name);//считывание записи из базы данных
            if (books[0].deleted == 1) {
                printf("Запись удалена\n");
                break;
            }
            char ch;
            do {
                do {
                    printf("\nИзменить автора <1>, название книги <2>, язык, которому посвящена книга <3>, "
                        "тираж <4>, цену <5>\n");
                    scanf_s(" %c", &ch, 2);
                    skip();
                } while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5');
                switch (ch) {
                case '1': {
                    printf("Введите нового автора: ");
                    gets(books[0].author);
                    break;
                }
                case '2': {
                    printf("Введите новое название: ");
                    gets_s(&books[0].name, STR_LENGH);
                    break;
                }
                case '3': {
                    printf("Введите новый язык, которому посвящена книга: ");
                    gets_s(books[0].language, LANG_LENGH);
                    break;
                }
                case '4': {
                    printf("Введите новый тираж: ");
                    scanf("%d", &books[0].amount);
                    break;
                }
                case '5': {
                    printf("Введите новую цену: ");
                    scanf_s("%f", &books[0].price);
                    break;
                }
                }
                while (1) {
                    printf("\nИзменить другое значение? (да/нет): ");
                    scanf_s("%s", &str, 4);
                    skip();
                    if (strcmp(str, "да") == 0 || strcmp(str, "нет") == 0) break;
                }
            } while (strcmp(str, "да") == 0);
            write(number, db_name);
            printf("Значения изменены\n");
            break;
        }
        case 's': {
            double sum = 0;
            int kol = 0;
            if (num_books == 0) {
                printf("\nНе найдено ни одной записи\n");
                break;
            }
            for (k = 1; k <= num_books; k++) {
                read(k, db_name);
                if (books[0].deleted) continue;
                if (strcmp(books[0].language, "C") == 0 || strcmp(books[0].language, "С") == 0) {
                    printf("\nid: %d\nАвтор: %s\nНазвание: %s\n"
                        "Тираж: %d\nЦена: %.2f\n", k, books[0].author, books[0].name, books[0].amount, books[0].price);
                    kol++;
                    sum += books[0].price;
                }
            }
            printf("\n");
            printf("Всего книг - %d, общая сумма за книги - %.2lf\n", kol, sum);
            break;
        }
        case 'e': {
            // запись в текстовый файл из базы данных
            for (k = 1; k <= num_books; k++) {
                if (k != 1) fputs("\n", f1);
                read(k, db_name);
                fputs("id: ", f1);
                fprintf(f1, "%d", books[0].id);
                fputs("\n", f1);
                fputs("Автор: ", f1);
                fputs(books[0].author, f1);
                fputs("\n", f1);
                fputs("Название: ", f1);
                fputs(books[0].name, f1);
                fputs("\n", f1);
                fputs("Язык: ", f1);
                fputs(books[0].language, f1);
                fputs("\n", f1);
                fputs("Тираж: ", f1);
                fprintf(f1, "%d", books[0].amount);
                fputs("\n", f1);
                fputs("Цена: ", f1);
                fprintf(f1, "%.2lf", books[0].price);
                fputs("\n", f1);
                fputs("Удалён: ", f1);
                fprintf(f1, "%d", books[0].deleted);
            }
            fclose(f1);//закрытие файла
            fclose(f2);//закрытие файла
            free(books);//освобождение памяти
            return 0;
        }
        }
    } while (letter != 'e'); //окончание работы файлом

    fclose(f1);//закрытие файла
    fclose(f2);//закрытие файла
    free(books);//освобождение памяти
    return 0;
}