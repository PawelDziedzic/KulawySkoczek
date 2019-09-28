#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<iostream>
#include<vector>
#include<deque>
#include<math.h>


using namespace std;

static int sevens[10] = { 1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607};

int getSeven(int n)
{
	return sevens[n];
}

void zero(vector<uint64_t> *v)
{
	for (int i = 0; i < v->size(); i++)
	{
		v->at(i) = 0;
	}
}

uint64_t getMaxUp(int ID, deque<vector<uint64_t>> *d, int depth)
{
	uint64_t max1=0, max2 = 0;
	if (ID > 0)
	{
		max1 = d->at(depth-2).at(ID - 1);
	}

	if (ID < d->at(depth-2).size() - 1)
	{
		max2 = d->at(depth-2).at(ID + 1);
	}

	if (max1 > max2)
		return max1;
	else
		return max2;
}

uint64_t getMaxDown(int ID, deque<vector<uint64_t>> *d, deque<vector<int>>*b, int row, int depth)
{
	uint64_t max1 = 0, max2 = 0;

	if (ID > 1)
	{
		max1 = b->at(row+1).at(ID-2) +getMaxUp(ID - 2, d, depth+1);
	}

	if (ID < d->at(0).size() - 2)
	{
		max2 = b->at(row+1).at(ID + 2) + getMaxUp(ID + 2, d, depth+1);
	}

	if (max1 > max2)
		return max1;
	else
		return max2;
}

int main()
{
	char memoryAddressOfInputString[10003];
	char *inputString = memoryAddressOfInputString;

	int strID = 0;
	int tempInt;
	int w = 0, k = 0;

	deque<vector<int>> board;
	vector<int> tempvector;
	uint8_t temp8bit;

	fgets(inputString, 17, stdin);
	while (inputString[strID] != ' '&& inputString[strID] != '\0')
	{
		tempInt = (int)inputString[strID] - 48;
		w = w * 10 + tempInt;
		strID++;
	}
	strID++;
	while (inputString[strID] != ' ' && inputString[strID] != '\0'&& inputString[strID] != '\n')
	{
		tempInt = (int)inputString[strID] - 48;
		k = k * 10 + tempInt;
		strID++;
	}


	for (int i = 0; i < w; i++)
	{
		fgets(inputString, k+2, stdin);
		for (int j = 0; j < k; j++)
		{
			temp8bit = (uint8_t)inputString[j] - 48;
			tempvector.push_back(getSeven(temp8bit));
		}
		board.push_back(tempvector);
		tempvector.clear();
	}


	vector<uint64_t> sumline(k);
	deque<vector<uint64_t>> sumTable;

	for (int i = 0; i < k; i++)
	{
		sumline.at(i) += board.at(0).at(i);
	}

	sumTable.push_back(sumline);
	zero(&sumline);

	for (int i = 0; i < k; i++)
	{
		sumline.at(i) += board.at(1).at(i) + getMaxDown(i, &sumTable, &board, 1, 1);
	}

	sumTable.push_back(sumline);
	zero(&sumline);

	for (int row = 2; row < w-2; row++)
	{
		uint64_t max, maxDown, maxUp;
		for (int i = 0; i < k; i++)
		{
			maxDown = getMaxDown(i, &sumTable, &board, row,2);
			maxUp = getMaxUp(i, &sumTable,2);

			if (maxUp > maxDown)
				max = maxUp;
			else
				max = maxUp;
			sumline.at(i) += board.at(row).at(i) + max;
		}
		sumTable.push_back(sumline);
		zero(&sumline);
		sumTable.pop_front();
	}

	int ultiMax = 0;
	for (int i = 0; i < k; i++)
	{
		sumline.at(i) += board.at(w-1).at(i) + getMaxUp(i, &sumTable,3);
		if (sumline.at(i) > ultiMax)
			ultiMax = sumline.at(i);
	}

	cout << ultiMax << endl;

	system("pause");
}