/*Разработайте программу, реализующую алгоритмы Прима и Крускала и сравните время выполнения алгоритмов на различных графах. Сделайте выводы.
*/

#include <iostream>
#include <ctime>

using namespace std;

int WeightMatrix[100][100] = 
{
  {0, 7, 9, 0, 0, 14},
  {7, 0, 10, 15, 0, 0},
  {9, 10, 0, 11, 0, 2},
  {0, 15, 11, 0, 6, 0},
  {0, 0, 0, 6, 0, 9},
  {14, 0, 2, 0, 9, 0},
}; 
int i, j;
int n = 6;

//алгоритм Прима
void Prim(int matrix[100][100])
{
	int mincost = 0;
	int no_edge = 0;
	int selected[100];
	memset(selected, false, sizeof(selected));
	selected[0] = true;
	int x, y;
	cout << "Минимальное остовное дерево: " << endl;
	while (no_edge < n - 1) {

		int min = INT_MAX;
		x = 0; y = 0;
		for (i = 0; i < n; i++)
		{
			if (selected[i])
			{
				for (j = 0; j < n; j++)
				{
					if (!selected[j] && matrix[i][j])
					{
						if (min > matrix[i][j])
						{
							min = matrix[i][j];
							x = i;
							y = j;
						}

					}
				}
			}
		}
		cout << x + 1 << " - " << y + 1 << ": " << matrix[x][y];
		cout << endl;
		selected[y] = true;
		no_edge++;
		mincost += matrix[x][y];
	}
	cout << "Минимальная стоимость: " << mincost << endl;
}

int parents[100];

int find(int i)
{
	while (parents[i] != i)
		i = parents[i];
	return i;
}

void union1(int i, int j)
{
	int a = find(i);
	int b = find(j);
	parents[a] = b;
}

//алгоритм Крускала
void Kruskal(int matrix[100][100])
{
	int mincost = 0;

	for (i = 0; i < n; i++)
		parents[i] = i;

	int no_edge = 0;
	while (no_edge < n - 1)
	{
		int min = INT_MAX, x, y;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (find(i) != find(j) && matrix[i][j] != 0 && matrix[i][j] < min)
				{
					min = matrix[i][j];
					x = i;
					y = j;
				}
			}
		}
		no_edge++;
		union1(x, y);
		cout << x + 1 << " - " << y + 1 << ": " << min << endl;
		mincost += min;
	}
	cout << "Минимальная стоимость: " << mincost << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << WeightMatrix[i][j] << "  ";      
		cout << endl;
	}
	cout << endl;
	
	cout << "Исходный граф: " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (WeightMatrix[i][j] != 0)
			{
				cout << i + 1<<" - "<<j+1<<": "<< WeightMatrix[i][j] << endl;    
			}

		}
	}
	cout << endl;
	
	clock_t time;

	while (true)
	{
		int c;
		cout << "Выберите действие: " << endl;
		cout << "1. Алгоритм Прима" << endl;
		cout << "2. Алгоритм Краскала" << endl;
		cin >> c;
		switch (c)
		{
		case 1:
			cout << endl;
			time = clock();
			Prim(WeightMatrix);
			time = clock() - time;
			cout << "Потрачено времени: " << (float)time / CLOCKS_PER_SEC << " секунд" << endl << endl;
			break;
		case 2:
			cout << endl;
			time = clock();
			Kruskal(WeightMatrix);
			time = clock() - time;
			cout << "Потрачено времени: " << (float)time / CLOCKS_PER_SEC << " секунд" << endl << endl;
			break;
		default:
			cout << endl;
			cout << "Неверный номер действия" << endl;
			cout << endl;
			break;
		}
	}
}