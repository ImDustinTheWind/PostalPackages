//***********************************************************************************************************
//Programming Assignment 07
//Programmer: Dustin Sherer
//Completed: 03/31/2022
//Status: Completed
// 
// Shipping requirements
//  -The package weight must not exceed 50 pounds.
//  -The package must not exceed 3 feet in length, width, or height.
//  -The girth of the package must not exceed 5 feet.The girth is the circumference around the two smallest sides of the package.If side1, side2, and side3 are the lengths of the three sides, and largest is the largest of the three sides, 
//          then the girth can be calculated using:        girth = 2 * (side1 + side2 + side3 - largest)
// 
// End Program on "-1" without user having to hit ENTER
// 
// Input Validation: 
//  - Weight and dimensions must be larger than zero, and an integer
//  - Shipping charge is based on table (Possibly Parallel Arrays)
//      - Weights are integers
//      - Costs are Floats
// 
//***********************************************************************************************************
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Postal.h"


int main()
{
    int acceptedPackages = 0;
    int rejectedPackages = 0;
    Package package;

    transactionProcessing(acceptedPackages, rejectedPackages);

    std::cout << std::endl;
    system("pause");
}

//***********************************************************************************************************
// Function for TransactionProcessing
// 
// Main transaction loop, asks user for package weight and 3 dimensions. 
//  - Takes valid input, then prints relevant package information
//      - For each transaction, print:
//          - the transaction number(start counting with 1)
//			- whether the package was accepted or rejected
//          - the package weight
//          - the cost for shipping(if applicable)
// 
// 
// 
//***********************************************************************************************************
void transactionProcessing(int& accepted, int& rejected)
{
    std::string status = "";
    int packageWeight = 0;
    float deliveryCost = 0;
    Package pack;
    pack.packageWeight = 0;

	// print "Enter package weight and 3 dimensions: "
	std::cout << "Enter package weight and 3 dimensions.\nEnter -1 to quit.\n\n";

    enterBoxStats(pack.packageWeight, pack.dimensionOne, pack.dimensionTwo, pack.dimensionThree, accepted, rejected);
	std::cout << std::endl;

    //when loop is complete (user quit)
    std::cout << "Number of accepted packages: " << accepted << std::endl;
    std::cout << "Number of rejected packages: " << rejected << std::endl;

    return;
}

//***********************************************************************************************************
// Function EnterBoxStats
// 
// handles input of weight and dimensions, gives error then resets if value of package characteristics <= 0.
//***********************************************************************************************************
void enterBoxStats(int& weight, int& d1, int& d2, int& d3, int& accepted, int& rejected)
{
    int transCount = 0;
    bool status = false;

    //do-while input !(-1), continue input loop
	do
	{
		//ask for box characteristics, check immediately for "-1"
		std::cout << "Enter package weight and 3 dimensions: ";
		std::cin >> weight;

		//do-while any weight/dimension <= 0
		do
		{
			//on "-1" immediately break out of loop
			if (weight == -1)
			{
				break;
			}

			//take in last 3 of the 4 integers as input
			std::cin >> d1 >> d2 >> d3;

            std::cout << std::endl;

            //when characteristic <= 0, output error message, then start function again
			if (weight <= 0 || d1 <= 0 || d2 <= 0 || d3 <= 0)
			{
                std::cout << "Error - package weight and dimensions must be larger than 0\n";
                std::cout << "Please re-enter transaction\n\n"; 

                //reset function
                enterBoxStats(weight, d1, d2, d3, accepted, rejected);
			}
            else
            {
				//increment transaction
				transCount++;

				//print package information
				printPackageInfo(weight, d1, d2, d3, accepted, rejected, transCount);
            }

	    //end 2nd do->while loop
		} while (weight <= 0 || d1 <= 0 || d2 <= 0 || d3 <= 0);

	//end 1st do->while loop
	} while (weight != (-1));

    return;
}

void printPackageInfo(int& weight, int& d1, int& d2, int& d3, int& accepted, int& rejected, int& transCount)
{
    int index = 0;
    float shipCost = 0;
    bool isRightSize = false;
    isRightSize = packageSizeCheck(d1, d2, d3);

	//"Transaction"
    //----------------------------------------
	std::cout << "Transaction: " << std::right << std::setw(8) << transCount << std::endl;

	//"Status"
    //----------------------------------------
	std::cout << "Status     : " << std::right << std::setw(8);
	if (packageWeightCheck(weight) && isRightSize)
	{
		std::cout << "Accepted" << std::endl;
        accepted++;
	}
	else {
		std::cout << "Rejected" << std::endl;
        rejected++;
	}

	//"Weight"
    //----------------------------------------
	std::cout << "Weight     : " << std::right << std::setw(8) << weight << std::endl;

	//"Cost"
    //----------------------------------------
	std::cout << "Cost       : " << std::right << std::setw(8);
	if (packageWeightCheck(weight) && isRightSize)
	{
        index = searchCostIndex(weight);
        shipCost = shipCostArray[index];
		formatToDollar(shipCost);
		std::cout << std::endl;
	}
	else {
		std::cout << "-" << std::endl;
	}
    std::cout << std::endl;

}


//***********************************************************************************************************
// Function for search for Cost
// 
// Takes the weight of package and searches for the array index that correlates with the shipping cost
//***********************************************************************************************************
int searchCostIndex(int itemWeight)
{
    int index = 0;
    int position = 0;
    bool costFound = false;

    while (index < arrayLength && !costFound)
    {
        if (itemWeight > weightArray[index])
        {
            index++;
        }
        else if (itemWeight <= weightArray[index])
        {
            costFound = true;
            position = index;
        }
    }
    //cost gets value of shipCostArray at index of position
    return position;
}

//***********************************************************************************************************
// Function for checking package size
// 
// Takes dimensions of the package, checks if package is too long, or has too much girth, then returns a bool
//***********************************************************************************************************
bool packageSizeCheck(int d1, int d2, int d3)
{
    bool isWithinSize = true;
    const int numDimensions = 3;
    int packageGirth = 0;
    int maxPackageGirth = 60;
    int maxPackLen = 36;
    int packDimensions[numDimensions] = { d1, d2, d3 };

    // sort array of box dimensions
    sideSort(packDimensions, numDimensions);

    // check if package is too long (36in), by checking longest side
    if (packDimensions[2] > maxPackLen)
    {
        isWithinSize = false;
        return isWithinSize;
    }

    // check package girth by calculating perimeter of 2 smallest sides
    packageGirth = (packDimensions[0] + packDimensions[1]) * 2;
    if (packageGirth > maxPackageGirth)
    {
        isWithinSize = false;
        return isWithinSize;
    }

    return isWithinSize;
}

//***********************************************************************************************************
// Function to verify package is within weight limits and standards
// 
//***********************************************************************************************************
bool packageWeightCheck(int itemWeight)
{
    bool isWithinWeight = false;

    if (itemWeight <= 50)
    {
        isWithinWeight = true;
    }
    return isWithinWeight;
}

//***********************************************************************************************************
// Function to sort side lengths of package in order from (min -> max) using bubble sort
// 
//***********************************************************************************************************
void sideSort(int dimensions[], int size)
{
    for (int max = size - 1; max > 0; max--)
    {
        for (int index = 0; index < max; index++)
        {
            if (dimensions[index] > dimensions[index + 1])
            {
                swap(dimensions[index], dimensions[index + 1]);
            }
        }
    }
}

//***********************************************************************************************************
// Function to swap values for bubble sort
// 
//***********************************************************************************************************
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

//**************************************************************************************************************************
// function to format floats To dollar
// 
// takes float and prints out in dollar format, then returns to function who called it
//**************************************************************************************************************************
void formatToDollar(float dollarAmount)
{
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	std::cout << dollarAmount;
	return;
}