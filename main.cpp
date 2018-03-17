#include <iostream>
using namespace std;

void Show(int*, int, const string&);
void RestoreArray(int*, int*, int);
void InsertSort(int*, int);
void ShellSort(int*, int);
void BubbleSort(int*, int);
int  Partition(int*, int, int);
void QSort(int*, int, int);
void Merge(int*, int, int, int);
void MergePass(int*, int, int);
void MergeSort(int*, int);
void Sift(int*, int, int);
void HeapSort(int*, int);

int main()
{
	const int len = 10;
	int record[len] = {1, 3, 2, 6, 8, 4, 5, 9, 7, 10};
	int array[len] = {1, 3, 2, 6, 8, 4, 5, 9, 7, 10};
	Show(array, len, "Before Sort");

	InsertSort(array, len);
	Show(array, len, "InsertSort");
	RestoreArray(array, record, len);

	ShellSort(array, len);
	Show(array, len, "ShellSort");
	RestoreArray(array, record, len);

	BubbleSort(array, len);
	Show(array, len, "BubbleSort");
	RestoreArray(array, record, len);

	QSort(array, 0, len - 1);
	Show(array, len, "QSort");
	RestoreArray(array, record, len);

	MergeSort(array, len);
	Show(array, len, "MergeSort");
	RestoreArray(array, record, len);

	HeapSort(array, len);
	Show(array, len, "HeapSort");

	return 0;
}

void Show(int* array, int len, const string& type)
{
	cout << type << " : ";
	for(int i = 0; i < len; i++)
		cout << array[i] << " ";
	cout << endl;
}

void RestoreArray(int* des, int* src, int len)
{
	for(int i = 0; i < len; i++)
		des[i] = src[i];
}

void InsertSort(int* array, int len)
{
	for(int i = 1; i < len; i++)
	{
		int temp = array[i];
		int j    = i - 1;
		for(; j >= 0 && array[j] > array[i]; j--)
			array[j + 1] = array[j];
		array[j + 1] = temp;
	}
}

void ShellSort(int* array, int len)
{
	for(int d = len / 2; d >= 1; d /= 2)
	{
		for(int i = d; i < len; i++)
		{
			int temp = array[i];
			int j    = i - d;
			for(; j >= 0 && array[j] > temp; j -= d)
				array[j + d] = array[j];
			array[j + d] = temp;
		}
	}
}

void BubbleSort(int* array, int len)
{
	for(int i = 1; i < len; i++)
	{
		bool ifExchange = false;

		for(int j = 0; j < len - i; j++)
			if(array[j] > array[j + 1])
			{
				int temp;
				temp         = array[j];
				array[j]     = array[j + 1];
				array[j + 1] = temp;

				ifExchange = true;
			}

		if(!ifExchange)
			break;
	}
}

int Partition(int* array, int low, int high)
{
	int i = low, j = high;
	while(i < j)
	{
		while(array[i] < array[j] && i < j)
			j--;
		if(i < j)
		{
			int temp;
			temp     = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
		}

		while(array[i] < array[j] && i < j)
			i++;
		if(i < j)
		{
			int temp;
			temp     = array[i];
			array[i] = array[j];
			array[j] = temp;
			j--;
		}
	}

	return i;
}

void QSort(int* array, int low, int high)
{
	if(low < high)
	{
		int pivot = Partition(array, low, high);
		QSort(array, low, pivot - 1);
		QSort(array, pivot + 1, high);
	}
}

void Merge(int* array, int low, int mid, int high)
{
	int i = low;
	int j = mid + 1;
	int k = 0;

	int* temp = new int[high - low + 1];

	while(i <= mid && j <= high)
		if(array[i] < array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];

	while(i <= mid)
		temp[k++] = array[i++];
	while(j <= high)
		temp[k++] = array[j++];

	for(int a = low; a <= high; a++)
		array[a] = temp[a - low];
}

void MergePass(int* array, int gap, int len)
{
	int i;
	for(i = 0; i + 2 * gap - 1 < len; i += 2 * gap)
		Merge(array, i, i + gap - 1, i + 2 * gap - 1);
	if(i + gap - 1 < len)
		Merge(array, i, i + gap - 1, len - 1);
}

void MergeSort(int* array, int len)
{
	for(int gap = 1; gap < len; gap *= 2)
		MergePass(array, gap, len);
}

void Sift(int* array, int low, int high)
{
	int i = low, j = i == 0 ? 1 : 2 * i;
	while(j <= high)
	{
		if(j < high && array[j] < array[j + 1])
			j++;
		if(array[i] >= array[j])
			break;
		else
		{
			int temp;
			temp     = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		i = j;
		j = i * 2;
	}
}

void HeapSort(int* array, int len)
{
	for(int i = len / 2; i >= 0; i--)
		Sift(array, i, len - 1);
	for(int i = 0; i < len; i++)
	{
		int temp;
		temp               = array[0];
		array[0]           = array[len - i - 1];
		array[len - i - 1] = temp;
		Sift(num, 0, len - i - 2);
	}
}