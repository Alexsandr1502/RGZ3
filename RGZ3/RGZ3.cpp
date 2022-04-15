#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <malloc.h>
#define N 10
#define L 101

struct Fraction
{
    int chisl;
    int znam;
    double segment = (double)chisl / znam;
};

//void Create(Fraction arr[], result mass[], const char* path, ...);
void SaveInFile(Fraction arr[], int& n);
void LoadFromFile(Fraction arr[], int& n);
void OutputStruct(Fraction arr[], int& n);
void check_input(int& chisl, int& znam);
void add_data(Fraction arr[], int& num);
void SaveToAdd(Fraction arr[], int& n);
void SortFiles(Fraction arr[], const char* filename, const char* path, ...);
/* двухфазная сортировка, параметр - имя файла  */
int vnsort1(const char* ff); // фаза разделения серий
int vnsort2(const char* ff); // фаза слияния


void SaveToAdd(Fraction arr[], int& n)
{
    char fname[L] = { "result.dat" };
    FILE* f;

    if ((f = fopen(fname, "ab")) == NULL)
    {
        printf("Ошибка открытия файла");
        return;
    }
    fwrite(arr, sizeof(Fraction), n, f);
    fclose(f);
}

void SaveInFile(Fraction arr[], int& n)
{
    char fname[L];
    FILE* f;
    printf("Введите название файла с расширением: ");
    scanf("%s", &fname);
    if ((f = fopen(fname, "wb")) == NULL)
    {
        printf("Ошибка открытия файла");
        return;
    }
    fwrite(arr, sizeof(Fraction), n, f);
    fclose(f);
}

void LoadFromFile(Fraction arr[], int& n)
{
    char fname[L];
    FILE* f;
    printf("Введите название файла с расширением: ");
    scanf("%s", fname);
    f = fopen(fname, "rb");
    if (f == NULL)
    {
        printf("Ошибка загрузки файла");
        return;
    }
    fseek(f, 0L, 2); // Позиционируем указатель на конец файла
    n = ftell(f) / sizeof(Fraction); // Определяем количество записей в файле
    rewind(f); // Позиционируем указатель на начало файла
    fread(arr, sizeof(Fraction), n, f); // Копируем записи из файла
    fclose(f); // Закрываем файл
}

void OutputStruct(Fraction arr[], int& n)//вывод массива структуры
{
    for (int i = 0; i < n; i++)
    {
        printf("%d/%d\n", arr[i].chisl, arr[i].znam);
    }
}

void check_input(int& chisl, int& znam)//Проверка ввода данных
{
    do
    {
        printf("Введите числитель: ");
        do
        {
            scanf("%d", &chisl);
            if ((chisl > 0) || (chisl < 0))  break;
        } while (1);

        printf("Введите знаменатель: ");
        do
        {
            scanf("%d", &znam);
            if ((znam > 0) || (znam < 0))  break;
        } while (1);
        return;
    } while (1);
}

void add_data(Fraction arr[], int& num)// функция ввода данных о товаре.
{
    while (num < N)
    {
        check_input(arr[num].chisl, arr[num].znam);
        num++;
    }
}

int vnsort1(const char* ff)// фаза разделения серий
{
    FILE* A, * B, * C; /* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    int a1, a2; /* для чтения из исходного файла */
    int pb, pc; /* признаки записи в файлы разделения */
    int p; /* p=1 - признак достижения конца исходного файла */
    while (1)  /* цикл 1, цикл повторения фаз разделения и слияния */
    /* Подготовительные операции */
    {
        if ((A = fopen(ff, "rb")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            system("pause");
            return -1;
        }
        if ((B = fopen("B", "wb")) == NULL)
        {
            printf("\n Файл B не открывается");
            system("pause");
            return -1;
        }
        if ((C = fopen("C", "wb")) == NULL)
        {
            printf("\n Файл C не открывается");
            system("pause");
            return -1;
        }
        p = 0;
        pb = 0;
        pc = 0;
        if (fscanf(A, "%d", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            system("pause");
            return -1;
        }
        else
        {
            fprintf(B, " %d", a1);
            pb = 1;
        }
        while (1) /* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1) /* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1; break; /* выход из цикла 3 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле В */
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else /* запишем первую запись новой серии в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        break; /* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;  /* выход из цикла 2 */
            while (1) /* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1;
                    break; /* выход из цикла 4 */
                }
                else
                {
                    if (a2 >= a1)  /* запишем в серию в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        break; /* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break; /* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)  /* исходный файл записан в оба файла разделения */
            vnsort2(ff);  /* вызов функции слияния */
        else
        { /* Удаление вспомогательных файлов */
            remove("B"); remove("C");
            return 0;  /* конец сортировки */
        }
    }
}

int vnsort2(const char* a)// фаза слияния
{
    bool flag;
    FILE* A, * B, * C; /* файловые переменные */
    int b1, b2, c1, c2; /* для считывания данных из файлов В и С */
    int rb, rc; /* коды завершения операции считывания из файлов В и С*/
    /* Подготовительные операции */
    if ((A = fopen(a, "wb")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        system("pause");
        return -1;
    }
    if ((B = fopen("B", "rb")) == NULL)
    {
        printf("\n Файл B не открывается");
        system("pause");
        return -1;
    }
    if ((C = fopen("C", "rb")) == NULL)
    {
        printf("\n Файл C не открывается");
        system("pause");
        return -1;
    }
    rb = fscanf(B, "%d", &b2);
    rc = fscanf(C, "%d", &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))    // файл С закончился
        {
            fprintf(A, " %d", b2);
            while (fscanf(B, "%d", &b2) > 0)
                fprintf(A, " %d", b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc > 0)) // файл B закончился
        {
            fprintf(A, " %d", c2);
            while (fscanf(C, "%d", &c2) > 0)
                fprintf(A, " %d", c2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else if ((rb <= 0) && (rc <= 0)) // оба файла закончились
        {
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }

        if ((b2 >= b1) && (c2 >= c1)) /* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fprintf(A, " %d", b2); b1 = b2;
                rb = fscanf(B, "%d", &b2);
                continue;
            }
            else
            {
                fprintf(A, " %d", c2);
                c1 = c2;
                rc = fscanf(C, "%d", &c2);
                continue;
            }
        }

        if ((b2 >= b1) && (c2 < c1)) // серия файла C кончилась
        {
            c1 = c2;
            flag = false;
            do
            {
                fprintf(A, " %d", b2);
                b1 = b2;
                rb = fscanf(B, "%d", &b2);
                if (rb <= 0)
                {
                    flag = true;
                    break;
                }
                if (b2 < b1)
                {
                    b1 = b2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
        if ((b2 < b1) && (c2 >= c1)) // серия файла B кончилась
        {
            b1 = b2;
            flag = false;
            do
            {
                fprintf(A, " %d", c2);
                c1 = c2;
                rc = fscanf(C, "%d", &c2);
                if (rc <= 0)
                {
                    flag = true;
                    break;
                }
                if (c2 < c1)
                {
                    c1 = c2;
                    flag = true;
                    break;
                }
                if (flag == true)
                    break;
            } while (1);
            if (flag == true)
                continue;
        }
    }
}

//void Create(Fraction arr[], result mass[], const char* path, ...) // вывод на экран содержимого бинарных файлов
//{
//
//    char tmp[L];
//    int tmpi;
//    FILE* f;
//    int n;
//    va_list path_ptr; //Объявление списка переменных аргументов
//    const char* path_tmp = path; // инициализация указателя
//    va_start(path_ptr, path); // инициализация списка переменных аргументов
//    do
//    {
//        f = fopen(path_tmp, "rb"); // открытие очередного файла
//
//        if (f == NULL)
//        {
//            printf("Не открылся файл");
//            return;
//        }
//
//        fseek(f, 0L, 2); // Позиционируем указатель на конец файла
//        n = ftell(f) / sizeof(Fraction); // Определяем количество записей в файле
//        rewind(f); // Позиционируем указатель на начало файла
//        fread(arr, sizeof(Fraction), n, f); // Копируем записи из файла
//        if (feof(f)) break;
//        SaveToAdd(arr, n);
//        fclose(f); //Закрываем файл
//
//        path_tmp = va_arg(path_ptr, const char*); // переход к очередному аргументу 
//    } while (path_tmp); // дошли до конца списка?
//
//    va_end(path_ptr); // закрытие списка переменных аргументов
//    puts("Сохранено в файл 'result' ");
//}

void SortFiles(Fraction arr[], const char* filename, const char* path, ...)
{
    FILE *f, *result;
    va_list path_ptr;
    int n;
    const char* path_tmp = path;
    va_start(path_ptr, path);

    result = fopen(filename, "wb+");
    if (result == NULL)
    {
        puts("Файл-результат не открылся");
        return;
    }

    do
    {
        f = fopen(path_tmp, "rb"); // Открытие очередного файла
        if (f == NULL)
        {
            puts("Файл не открылся");
            return;
        }

        fseek(f, 0L, 2); // Позиционируем указатель на конец файла
        n = ftell(f) / sizeof(Fraction); // Определяем количество записей в файле
        rewind(f); // Позиционируем указатель на начало файла
        fread(arr, sizeof(Fraction), n, f); // Копируем записи из файла
        if (feof(f)) break;
        fclose(f);
        fwrite(arr, sizeof(Fraction), n, result);
        path_tmp = va_arg(path_ptr, const char*);

    } while (path_tmp);
    va_end(path_ptr);
    fclose(result);

    vnsort1(filename);
    return;
}

void Menu(Fraction arr[], int& n)
{
    int i, k;
    char c;
    void(*choise)(Fraction arr[], int& n);
    const char* ss[] = { " 0 - ВЫХОД"," 1 - Вывод дробей",  " 2 - Ввод данных", " 3 - сохранение в файл", \
    " 4 - загрузка из файл", " 5 - Сортировка"};
    k = sizeof(ss) / sizeof(ss[0]);
    for (;;)
    {
        for (i = 0; i < k; i++) puts(ss[i]); // Вывод меню
        c = _getch();
        switch (c)
        {
        case '0': puts("\nЗаврешение работы"); exit(0);
        case '1': choise = OutputStruct; choise(arr, n); break;
        case '2': choise = add_data; choise(arr, n); break;
        case '3': choise = SaveInFile; choise(arr, n); break;
        case '4': choise = LoadFromFile; choise(arr, n); break;
        case '5': SortFiles(arr, "result.dat", "first.dat", "second.dat", NULL); break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int n = 0;
    Fraction arr[N];
    /*FILE* f = fopen("result.dat", "wb"); fclose(f);*/
    Menu(arr, n);
}
