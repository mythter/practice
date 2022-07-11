/*
����: main.c
��������
�����: ������� �. �.
����: ��������� �������� ��� ������ � ������ ��� �����, 
��������� ������������� �� ���������� ��������� �� � ��������� ����
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
    setlocale(LC_CTYPE, "rus"); // ����� ������� ������� �������� - ��������� �������� �����
    books = (book*)malloc(sizeof(book));//��������� ������ ��� ���������
    choose:
    printf("������� ������������ ���� ��� ������� �����? (0 - ������� / 1 - �������) ");
    scanf_s("%d", &choice);

    if (choice == 0) {
        printf("������� ��� ��������� �����, ������� ������ �������: ");
        scanf_s("%s", file_name, STR_LENGH);
        strcpy(txt_name, file_name);
        strcpy(db_name, file_name);
        strcat(txt_name, ".txt"); //��� ���������� �����
        strcat(db_name, ".dat"); //��� ���� ������
        // �������� �� ������� ������ � ��������
        if ((f1 = fopen(txt_name, "r")) == NULL || (f2 = fopen(db_name, "rb")) == NULL) {
            if ((f1 = fopen(txt_name, "r")) == NULL) {
                printf("���� %s �� ������ � ��������\n", txt_name);
            }
            if ((f2 = fopen(db_name, "rb")) == NULL) {
                printf("���� %s �� ������ � ��������\n", db_name);
            }
            goto choose;
        }
        else {
            printf("����� %s � %s ������� �������\n", txt_name, db_name);
            f1 = fopen(txt_name, "w");
            f2 = fopen(db_name, "rb+");
            fseek(f2, 0, SEEK_SET);
            //������� ����	
            while ((fread(books, sizeof(book), 1, f2)) == 1) {
                num_books++;
                if (!books[0].deleted) not_deleted++;
            }
        }


    }
    else if (choice == 1) {
        printf("������� ��� ��������� ����� � ���� ������ ��� ����: ");
        scanf_s("%s", file_name, STR_LENGH);
        strcpy(txt_name, file_name);
        strcpy(db_name, file_name); 
        strcat(txt_name, ".txt");  //��� ���������� �����
        strcat(db_name, ".dat");  //��� ���� ������
        //�������� �� ������� ��� ��������� ������ � ����� ��������� � ��������
        if ((f1 = fopen(txt_name, "r")) != NULL || (f2 = fopen(db_name, "rb")) != NULL) {
            if ((f1 = fopen(txt_name, "r")) != NULL) {
                printf("���� %s ��� ����������\n", txt_name);
                fclose(f1);
            }
            if ((f2 = fopen(db_name, "rb")) != NULL) {
                printf("���� %s ��� ����������\n", db_name);
                fclose(f2);
            }
            goto choose;
        }
        else {
            printf("����� %s � %s ������� �������\n", txt_name, db_name);
            f1 = fopen(txt_name, "w");
            f2 = fopen(db_name, "wb+");
        }
    }
    else {
        printf("������� 0 ��� 1\n");
        goto choose;
    }
    commands:
    do {
        do {
            printf("\n�������� ����� <a>, ������� ����� <d>, ���������� ���������� � �����(��) <l>, �������� ���������� � ����� <c>,\n"
                "����� �����, ����������� ���������������� �� ����� � <s>, ��������� ��������� <e>: ");
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
            printf("������� ������ �����: ");
            gets(books[0].author);
            printf("������� �������� �����: ");
            gets_s(books[0].name, sizeof(books[0].name));
            printf("������� ���� ����������������, ��� ������� ��� ���� � �����: ");
            gets_s(books[0].language, sizeof(books[0].language));
            printf("������� �����: ");
            scanf_s("%d", &books[0].amount);
            printf("������� ���� �� �����: ");
            scanf_s("%lg", &books[0].price);
            skip();
            books[0].deleted = 0;
            write(books[0].id, db_name);//���������� ����� ������ � ���� ������
            printf("\n������ ������� ��������� � id: %d\n", books[0].id);
            not_deleted++;
            break;
        }
        case 'd': {
            printf("\n������� id ������, ������� ������ �������: ");
            scanf_s("%d", &number);
            skip();
            if (k = id_pos(f2, number)) {
                read(k, db_name);
                books[0].deleted = 1;//������� �� �������� ������
                write(k, db_name);
                not_deleted--;
                printf("\n������ � id = %d ������� �������.\n", books[0].id);
            }
            else printf("\n������ � id = %d �� �������\n", number);

            break;
        }
        case 'l': {
        look:
            if (num_books == 0) {
                printf("\n�� ������� �� ����� ������\n");
                break;
            }
            printf("���������� � ���� ������ ��� � ���������� �����? (0 - � ���� / 1 - � ����������) ");
            scanf_s("%d", &choice);
            skip();
            if (choice == 0) {
                for (k = 1; k <= num_books; k++) {
                    read(k, db_name);
                    if (books[0].deleted == 1) {
                        printf("\nid: %d\n", k);
                        printf("������ �������\n");
                        continue;
                    }
                    printf("\nid: %d\n�����: %s\n��������: %s\n"
                        "�����: %d\n����: %.2f\n", k, books[0].author, books[0].name, books[0].amount, books[0].price);
                }
            }
            else if (choice == 1) {
                printf("\n������� id ������, ������� ������ �����������: ");
                scanf_s("%d", &number);
                skip();
                //��������, ���� ������ �������
                if (id_pos(f2, number) && books[0].deleted == 0) {
                    read(id_pos(f2, number), db_name);
                    printf("\nid: %d\n�����: %s\n��������: %s\n"
                        "�����: %d\n����: %.2f\n", number, books[0].author, books[0].name, books[0].amount, books[0].price);
                }
                else printf("\n����� ������ �� ���������� ��� ��� �������\n");
            }
            else {
                printf("������� 0 ��� 1\n");
                goto look;
            }
           
            break;
        }
        case 'c': {
            while (1) {
                printf("\n������� id ������, ������� ������ ��������: ");
                scanf_s("%d", &number);
                if (number > 0 && number <= num_books) break;
                printf("�������� id\n");
                goto commands;
            }
            read(number, db_name);//���������� ������ �� ���� ������
            if (books[0].deleted == 1) {
                printf("������ �������\n");
                break;
            }
            char ch;
            do {
                do {
                    printf("\n�������� ������ <1>, �������� ����� <2>, ����, �������� ��������� ����� <3>, "
                        "����� <4>, ���� <5>\n");
                    scanf_s(" %c", &ch, 2);
                    skip();
                } while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5');
                switch (ch) {
                case '1': {
                    printf("������� ������ ������: ");
                    gets(books[0].author);
                    break;
                }
                case '2': {
                    printf("������� ����� ��������: ");
                    gets_s(&books[0].name, STR_LENGH);
                    break;
                }
                case '3': {
                    printf("������� ����� ����, �������� ��������� �����: ");
                    gets_s(books[0].language, LANG_LENGH);
                    break;
                }
                case '4': {
                    printf("������� ����� �����: ");
                    scanf("%d", &books[0].amount);
                    break;
                }
                case '5': {
                    printf("������� ����� ����: ");
                    scanf_s("%f", &books[0].price);
                    break;
                }
                }
                while (1) {
                    printf("\n�������� ������ ��������? (��/���): ");
                    scanf_s("%s", &str, 4);
                    skip();
                    if (strcmp(str, "��") == 0 || strcmp(str, "���") == 0) break;
                }
            } while (strcmp(str, "��") == 0);
            write(number, db_name);
            printf("�������� ��������\n");
            break;
        }
        case 's': {
            double sum = 0;
            int kol = 0;
            if (num_books == 0) {
                printf("\n�� ������� �� ����� ������\n");
                break;
            }
            for (k = 1; k <= num_books; k++) {
                read(k, db_name);
                if (books[0].deleted) continue;
                if (strcmp(books[0].language, "C") == 0 || strcmp(books[0].language, "�") == 0) {
                    printf("\nid: %d\n�����: %s\n��������: %s\n"
                        "�����: %d\n����: %.2f\n", k, books[0].author, books[0].name, books[0].amount, books[0].price);
                    kol++;
                    sum += books[0].price;
                }
            }
            printf("\n");
            printf("����� ���� - %d, ����� ����� �� ����� - %.2lf\n", kol, sum);
            break;
        }
        case 'e': {
            // ������ � ��������� ���� �� ���� ������
            for (k = 1; k <= num_books; k++) {
                if (k != 1) fputs("\n", f1);
                read(k, db_name);
                fputs("id: ", f1);
                fprintf(f1, "%d", books[0].id);
                fputs("\n", f1);
                fputs("�����: ", f1);
                fputs(books[0].author, f1);
                fputs("\n", f1);
                fputs("��������: ", f1);
                fputs(books[0].name, f1);
                fputs("\n", f1);
                fputs("����: ", f1);
                fputs(books[0].language, f1);
                fputs("\n", f1);
                fputs("�����: ", f1);
                fprintf(f1, "%d", books[0].amount);
                fputs("\n", f1);
                fputs("����: ", f1);
                fprintf(f1, "%.2lf", books[0].price);
                fputs("\n", f1);
                fputs("�����: ", f1);
                fprintf(f1, "%d", books[0].deleted);
            }
            fclose(f1);//�������� �����
            fclose(f2);//�������� �����
            free(books);//������������ ������
            return 0;
        }
        }
    } while (letter != 'e'); //��������� ������ ������

    fclose(f1);//�������� �����
    fclose(f2);//�������� �����
    free(books);//������������ ������
    return 0;
}