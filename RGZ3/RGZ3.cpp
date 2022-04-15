#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#define N 10
#define L 100

struct Fraction
{
    int chisl;
    int znam;
    double segment = (double)chisl / znam;
};

struct result
{
    int chisl;
    int znam;
    double segment = (double)chisl / znam;
};
void Create(Fraction arr[], result mass[], const char* path, ...);
void SaveInFile(Fraction arr[], int& n);
void LoadFromFile(Fraction arr[], int& n);
void OutputStruct(Fraction arr[], int& n);
void check_input(int& chisl, int& znam);
void add_data(Fraction arr[], int& num);
void SaveToAdd(Fraction arr[], int& n);
//void copy(result mass[], Fraction arr[])
//{
//    int i = 0;
//    while ((mass[i] = arr[i]) != '\0') i++;
//}
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
void Create(Fraction arr[], result mass[], const char* path, ...) // вывод на экран содержимого бинарных файлов
{

    char tmp[L];
    int tmpi;
    FILE* f;
    int n;
    va_list path_ptr; //Объявление списка переменных аргументов
    const char* path_tmp = path; // инициализация указателя
    va_start(path_ptr, path); // инициализация списка переменных аргументов
    do
    {
        f = fopen(path_tmp, "rb"); // открытие очередного файла

        if (f == NULL)
        {
            printf("Не открылся файл");
            return;
        }

        fseek(f, 0L, 2); // Позиционируем указатель на конец файла
        n = ftell(f) / sizeof(Fraction); // Определяем количество записей в файле
        rewind(f); // Позиционируем указатель на начало файла
        fread(arr, sizeof(Fraction), n, f); // Копируем записи из файла
        if (feof(f)) break;
        SaveToAdd(arr, n);
        //OutputStruct(arr, n);
        fclose(f); //Закрываем файл

        path_tmp = va_arg(path_ptr, const char*); // переход к очередному аргументу 
    } while (path_tmp); // дошли до конца списка?

    va_end(path_ptr); // закрытие списка переменных аргументов
    puts("Сохранено в файл 'result' ");
}

void LoadFromFile(Fraction arr[], int& n)
{
    char fname[L];
    FILE* f;
    printf("Введите название файла с расширением: ");
    scanf("%s", &fname);
    if ((f = fopen(fname, "rb")) == NULL)
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
void Menu(Fraction arr[], int& n)
{
    int i, k, num;
    char c;
    void(*choise)(Fraction arr[], int& n);
    const char* ss[] = { " 0 - ВЫХОД"," 1 - Вывод дробей",  " 2 - Ввод данных", " 3 - сохранение в файл", \
    " 4 - загрузка из файл" };
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
        }
    }
}
int main()
{

    setlocale(LC_ALL, "");
    int n = 0;
    Fraction arr[N];
    result mass[N];
    FILE* f = fopen("result.dat", "wb"); fclose(f);
    Create(arr, mass, "first.dat", "second.dat", NULL);
    Menu(arr, n);
}


