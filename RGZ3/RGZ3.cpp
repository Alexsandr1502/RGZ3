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

void SaveInFile(Fraction arr[], int& n);
void LoadFromFile(Fraction arr[], int& n);
void OutputStruct(Fraction arr[], int& n);
void check_input(int& chisl, int& znam);
void add_data(Fraction arr[], int& num);

void SaveInFile(Fraction arr[], int& n)
{
    char filename[L];
    printf("Введите название файла с расширением: ");
    scanf("%s", filename);
    FILE *f;
    if ((f = fopen(filename, "wb")) == NULL)
    {
        printf("Ошибка открытия файла");
        return;
    }
    fwrite(arr, sizeof(Fraction), n, f);
    fclose(f);
}
void LoadFromFile(Fraction arr[], int& n)
{
    char filename[L];
    printf("Введите название файла с расширением: ");
    scanf("%s", filename);
    FILE* f;
    if((f = fopen(filename, "wb")) == NULL)
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
            if (chisl > 0)  break;
            else printf("\nОшибка при вводе числителя! Повторите ввод: ");
        } while (1);

        printf("Введите знаменатель: ");
        do
        {
            scanf("%d", &znam);
            if (znam > 0)  break;
            else printf("\nОшибка при вводе знаменателя! Повторите ввод: ");
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
void Menu(Fraction arr[], int n)
{
    void(*choise)();
    add_data(arr, n);
    SaveInFile(arr, n);
    LoadFromFile(arr, n);
    OutputStruct(arr, n);
}
int main()
{
	setlocale(LC_ALL, "");
    int n = 0;
	Fraction arr[N];
    Menu(arr, n);
}
