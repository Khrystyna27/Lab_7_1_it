// Lab_7_1_it.cpp
// Юнко Христина
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Ітераційний спосіб
// Варіант 30
 
#include <iostream>
#include <iomanip>
#include <time.h>
 
using namespace std;
 
// Формує матрицю випадковими цілими числами з діапазону [Low, High]
void Create(int** a, const int rowCount, const int colCount, const int Low,
                                                            const int High);
 
// Виводить матрицю на екран у вигляді таблиці (кожен елемент - 4 позиції)
void Print(int** a, const int rowCount, const int colCount);
 
// Впорядковує рядки матриці за ключами: ↓ ↑ ↓ (1-й, 2-й та 3-й стовпчики)
void Sort(int** a, const int rowCount, const int colCount);
 
// Міняє місцями рядки row1 та row2 матриці
void Change(int** a, const int row1, const int row2, const int colCount);
 
// Обчислює кількість k та суму S елементів, що задовольняють критерію
// (кратні 7 або хоча б один індекс непарний), і замінює їх нулями
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k);
 
int main()
{
   srand((unsigned)time(NULL));    // ініціалізація генератора випадкових чисел
 
   int Low = 16;                   // нижня межа діапазону значень елементів
   int High = 97;                  // верхня межа діапазону значень елементів
 
   int rowCount = 8;               // кількість рядків матриці
   int colCount = 6;               // кількість стовпчиків матриці
 
   int **a = new int*[rowCount];   // a - динамічна матриця цілих чисел
   for (int i=0; i<rowCount; i++)
       a[i] = new int[colCount];
 
   Create(a, rowCount, colCount, Low, High);
   Print(a, rowCount, colCount);
   Sort(a, rowCount, colCount);
   Print(a, rowCount, colCount);
 
   int S=0;                        // S - сума елементів, що задовольняють критерію
   int k=0;                        // k - кількість таких елементів
   Calc(a, rowCount, colCount, S, k);
   cout << "S = " << S << endl;
   cout << "k = " << k << endl;
   Print(a, rowCount, colCount);
 
   for (int i=0; i<rowCount; i++)  // знищуємо матрицю
       delete [] a[i];
   delete [] a;
 
   return 0;
}
 
void Create(int** a, const int rowCount, const int colCount, const int Low,
                                                            const int High)
{
   for (int i=0; i<rowCount; i++)
       for (int j=0; j<colCount; j++)
           a[i][j] = Low + rand() % (High-Low+1);
}
 
void Print(int** a, const int rowCount, const int colCount)
{
   cout << endl;
   for (int i=0; i<rowCount; i++)
   {
       for (int j=0; j<colCount; j++)
           cout << setw(4) << a[i][j];
       cout << endl;
   }
   cout << endl;
}
 
void Sort(int** a, const int rowCount, const int colCount)
{
   for (int i0=0; i0<rowCount-1; i0++)             // кількість проходів
   for (int i1=0; i1<rowCount-i0-1; i1++)          // порівняння сусідніх рядків
       if (( a[i1][0] < a[i1+1][0] )               // 1-й стовпчик - за спаданням
           ||
           ( a[i1][0] == a[i1+1][0] &&
             a[i1][1] > a[i1+1][1] )               // 2-й стовпчик - за зростанням
           ||
           ( a[i1][0] == a[i1+1][0] &&
             a[i1][1] == a[i1+1][1] &&
             a[i1][2] < a[i1+1][2] ))              // 3-й стовпчик - за спаданням
           Change(a, i1, i1+1, colCount);
}
 
void Change(int** a, const int row1, const int row2, const int colCount)
{
   int tmp;                        // tmp - допоміжна змінна для обміну
   for (int j=0; j<colCount; j++)
   {
       tmp = a[row1][j];
       a[row1][j] = a[row2][j];
       a[row2][j] = tmp;
   }
}
 
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k)
{
   S = 0;
   k = 0;
   for (int i=0; i<rowCount; i++)
       for (int j=0; j<colCount; j++)
           if (a[i][j] % 7 == 0 || i % 2 != 0 || j % 2 != 0)
           {
               S += a[i][j];       // додаємо елемент до суми
               k++;                // збільшуємо кількість
               a[i][j] = 0;        // замінюємо елемент нулем
           }
}
