//***********************************************************************************************************
//Programming Assignment 07
//Programmer: Dustin Sherer
//Completed: 03/31/2022
//Status: In Progress
//***********************************************************************************************************

#pragma once

// array Length constant to avoid magic number
const static int arrayLength = 15;
// array of weight thresholds to correlate with 
const static int weightArray[arrayLength] = { 1, 2, 3, 5, 7, 10, 13, 16, 20, 25, 30, 35, 40, 45, 50 };
const static float shipCostArray[arrayLength] = { 1.50, 2.10, 4.00, 6.75, 9.90, 14.95, 19.40, 24.20, 27.30, 31.90, 38.50, 43.50, 44.80, 47.40, 55.20 };

void transactionProcessing(int& accepted, int& rejected);
void enterBoxStats(int& weight, int& d1, int& d2, int& d3, int& accepted, int& rejected);
void printPackageInfo(int& weight, int& d1, int& d2, int& d3, int& accepted, int& rejected, int& transCount);
int searchCostIndex(int itemWeight);
bool packageSizeCheck(int d1, int d2, int d3);
bool packageWeightCheck(int itemWeight);
void sideSort(int dimensions[], int size);
void swap(int& a, int& b);
void formatToDollar(float dollarAmount);

struct Package
{
	int packageWeight = 0;
	int dimensionOne = 0;
	int dimensionTwo = 0;
	int dimensionThree = 0;
};