#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#define N 4

struct Fraction
{
	int chisl;
	int znam;
	double segment = (double)chisl/znam;
};

void OutputStruct(Fraction arr[], int& n)//вывод массива структуры
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", arr[n].chisl, arr[n].znam);
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
            printf("\nОшибка при вводе числителя! Повторите ввод: ");
        } while (1);

        printf("Введите знаменатель: ");
        do
        {
            scanf("%d", &znam);
            if (znam > 0)  break;
            printf("\nОшибка при вводе знаменателя! Повторите ввод: ");
        } while (1);
        return;
    } while (1);
}
void add_data(Fraction arr[], int num)// функция ввода данных о товаре.
{
    while (num < N)
    {
        check_input(arr[num].chisl, arr[num].znam);
        num++;
    }
    OutputStruct(arr, num);
}
int main()
{
	setlocale(LC_ALL, "");
    int n = 0;
	Fraction arr[N];
    add_data(arr, n);
}
