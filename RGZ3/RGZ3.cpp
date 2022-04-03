#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#define N 4
#define L 15

struct Fraction
{
	int chisl;
	int znam;
	double segment = (double)chisl/znam;
};

void CheckForNegativity(Fraction arr[], int& n);
void SaveInFile(Fraction arr[], int& n);
void LoadFromFile(Fraction arr[], int& n);
void OutputStruct(Fraction arr[], int& n);
void check_input(int& chisl, int& znam);
void add_data(Fraction arr[], int& num);

void CheckForNegativity(Fraction arr[], int& n)
{
    for (int i = 0; i < n; i++)
    {
        if (((arr[i].chisl) || (arr[i].znam )) <= 0)
        {
            for (int j = i; j < n - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            n--;
        }
    }
}
void SaveInFile(Fraction arr[], int& n)
{
    char fname[L];
    CheckForNegativity(arr, n);
    FILE *f;
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
    scanf("%s", &fname);
    if((f = fopen(fname, "rb")) == NULL)
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
void OutputStruct(Fraction arr[], int &n)//вывод массива структуры
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", arr[i].chisl, arr[i].znam);
    }
}
void check_input(int &chisl, int &znam)//Проверка ввода данных
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
void add_data(Fraction arr[], int &num)// функция ввода данных о товаре.
{
    while (num < N)
    {
        check_input(arr[num].chisl, arr[num].znam);
        num++;
    }
}
void Menu(Fraction arr[], int& n)
{
    int i, k, num, c;
    void(*choise)(Fraction arr[], int& n);
    const char* ss[] = { " 0 - ВЫХОД"," 1 - Вывод дробей",  " 2 - Ввод данных", " 3 - сохранение в файл", \
    " 4 - загрузка из файл"};
    k = sizeof(ss) / sizeof(ss[0]);
    for (;;)
    {
        for (i = 0; i < k; i++) puts(ss[i]); // Вывод меню
        printf("Ввод: ");
        scanf("%d", &c);
        switch (c)
        {
        case 0: return;
        case 1: choise = OutputStruct; choise(arr, n); break;
        case 2: choise = add_data; choise(arr, n); break;
        case 3: choise = SaveInFile; choise(arr, n); break;
        case 4: choise = LoadFromFile; choise(arr, n); break;
        }
    }
}
int main()
{
	setlocale(LC_ALL, "");
    int n = 0;
	Fraction arr[N];
    Menu(arr, n);
}
