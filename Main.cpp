#include <iostream>
#include <time.h>
#include <stdlib.h> 
#include <random>
#include <chrono>
using namespace std;
typedef chrono::high_resolution_clock Clock;

//---------------------------------------------------------------------------------------------
// This is our bubblesort function definition. It accepts int type array and int type for size 
// of the array. This function will minplaute the user given array to be sorted on asending order.
// The return type is void since the array are passed by raferance so we don't return anything
// back.
//---------------------------------------------------------------------------------------------
void bubblesort(int array[],int size) {
	for (int i = 0; i < size; i++)
	{
		bool indcator = false;                 // This will tell us when all are sorted and not futher check are required
		for (int j = 0; j < (size-i-1); j++)
		{
			if (array[j] > array[j + 1])		// This is where comparision happens
			{
				indcator = true;
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
		if (indcator == false)
		{
			break;
		}
	}
}

//---------------------------------------------------------------------------------------------
// This is our insertion sort function definition. It accepts int type array and int type for 
// size of the array. This function goes through populated array passed from user and 
// sort each elements in the array in ascending order. The return type is void.
//---------------------------------------------------------------------------------------------
void insertionsort(int array[],int size)
{
	int temp;
	int j = 0;
	for (int i = 1; i < size; i++)
	{
		temp = array[i];
		j = i;
		while (j > 0 && temp < array[j - 1])
		{
			array[j] = array[j - 1];
			j = j - 1;
		}
		array[j] = temp;
	}
}

// This is our quicksort function
//---------------------------------------------------------------------------------------------
// This is a helper functio for the quicksort. This function has return type of int. It will
// return the piviot where largest and smallest array of number are divide onto.
//---------------------------------------------------------------------------------------------
int part(int array[], int start, int end)
{
	int piv = array[end];
	int index = start;
	for (int i = start; i < end; i++)
	{
		if (array[i] < piv)
		{
			int temp = array[i];
			array[i] = array[index];
			array[index] = temp;
			index++;
		}
	}
	int temp = array[end];
	array[end] = array[index];
	array[index] = temp;
	return index;
}
//---------------------------------------------------------------------------------------------
// This is our main function for quicksort. It accepts int type array, int type starting index,
// and int type end index. This function is used recursivly to sort the array that user passes.
// When the function is done, we will have the sorted in ascending order of the int array user
// passed at the beginning. This also have the return type of void.
//---------------------------------------------------------------------------------------------
void Quicksort(int array[], int start, int end)
{
	if (start<end)
	{
		int partnum = part(array, start, end);
		Quicksort(array, start, (partnum - 1));
		Quicksort(array, (partnum + 1), end);
	}
}

//---------------------------------------------------------------------------------------------
// This is our function definition for counting sort. It acceps int type array and int type for 
// the size of the array. This function sorts the given array in ascending order and has return
// type of void since array are passed by refereance.
//---------------------------------------------------------------------------------------------
void countingsort(int array[], int size)
{
	int* out;
	int* count;
	int max = array[0];

	// Finding the max
	for (int i = 1; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	count = new int[max + 1];
	out = new int[max + 1];

	// Populate the array with 0's
	for (int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}

	for (int  i = 0; i < size; i++)
	{
		count[array[i]]++;
	}
	for (int i = 1; i <= max; i++)
	{
		count[i] += count[i - 1];
	}
	for (int i = size-1; i >= 0; i--)
	{
		out[count[array[i]] - 1] = array[i];
		count[array[i]]--;
	}
	for (int i = 0; i < size; i++)
	{
		array[i] = out[i];
	}
}

//---------------------------------------------------------------------------------------------
// This is our function definition for radix sorting. This function accepts int type array and 
// int type size for the size of the array. This funciton has void return type.
//---------------------------------------------------------------------------------------------
void radixsort(int  array[], int size)
{
	int max = array[0];
	// Finding the max
	// Finding the max
	for (int i = 1; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}

	for (int j = 1; max/j >0; j *= 10)
	{
		int* out;
		int* count;
		count = new int[10];
		out = new int[size];
		for (int i = 0; i < 10; i++)
		{
			count[i] = 0;
		}

		for (int i = 0; i < size; i++)
		{
			count[(array[i] / j) % 10]++;
		}
		for (int i = 1; i <10; i++)
		{
			count[i] += count[i - 1];
		}
		for (int i = size - 1; i >= 0; i--)
		{
			out[count[(array[i]/ j) % 10] - 1] = array[i];
			count[(array[i] / j) % 10]--;
		}
		for (int i = 0; i < size; i++)
		{
			array[i] = out[i];
		}
	}
}

// Merge sort functions 
//---------------------------------------------------------------------------------------------
// This is the helper function definition for mergesort. This accepts int type array, int type
// first (first index of array), int type mid (middle index of array), and int type last ( last
// index of array). This function divided the orgional array in two section and merge the sorted 
// array.
//---------------------------------------------------------------------------------------------
void merge(int array[], int first, int mid, int last)
{
	// temp variable
	int a, b, c,subsize1,subsize2;
	subsize1 = mid - first + 1;				// This is our size of the first sub array to be sorted
	subsize2 = last - mid;					// These is our size of the second sub array 

	// Temp array that will hold the first half and second half of the orginal array
	int *subarray1, *subarray2;
	subarray1 = new int[subsize1];
	subarray2 = new int[subsize2];
	// This loop copies first half of the array to the temp array we created 
	// populate our temp arrys 
	for (int i = 0; i < subsize1; i++)
	{
		subarray1[i] = array[first + i];
	}
	for (int i = 0; i < subsize2; i++)
	{
		subarray2[i] = array[mid + 1 + i];
	}

	// This loops will short through the loops
	a = b = 0;
	c = first;

	while (a < subsize1 && b < subsize2)
	{
		if (subarray1[a] <= subarray2[b])
		{
			array[c] = subarray1[a];
			a++;
		}
		else
		{
			array[c] = subarray2[b];
			b++;
		}
		c++;
	}
	while (a < subsize1)
	{
		array[c] = subarray1[a];
		a++;
		c++;
	}
	while (b < subsize2)
	{
		array[c] = subarray2[b];
		b++;
		c++;
	}
}
//---------------------------------------------------------------------------------------------
// This is our main function defination for merge sort. This accepts int type array, int type first
// and int type last. This function calls the helper function mergesort and sorts the user given 
// array in ascending order;
//---------------------------------------------------------------------------------------------
void mergesort(int array[], int first, int last)
{
	if (first < last)
	{
		int mid = first + (last - first) / 2;
		mergesort(array, first, mid);
		mergesort(array, mid + 1, last);
		merge(array, first, mid, last);
	}
}

int main() {	
	srand(time(NULL));
	int arrsize,randnum;
	int* myArray = 0;
	cout << "Enter the size of array: ";
	cin >> arrsize;

	double total = 0;
	double average;
	for (int i = 0; i < 10; i++)
	{
		myArray = new int[arrsize];
		for (int i = 0; i < arrsize; i++)
		{
			randnum = rand() % (2 * arrsize);
			myArray[i] = randnum;
		}
		//cout << "Before sorting................................" << endl;
		//for (int i = 0; i < arrsize; i++)
		//{
		//	cout << i + 1 << ". " << myArray[i] << endl;
		//}


		auto t1 = Clock::now();
		//bubblesort(myArray,arrsize);
		//insertionsort(myArray, arrsize);
		//Quicksort(myArray,0,(arrsize-1));
		countingsort(myArray, arrsize);
		//radixsort(myArray, arrsize);
		//mergesort(myArray, 0, arrsize - 1);
		auto t2 = Clock::now();

		total = total + chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
		//cout << "After sorting................................"<< endl;
		//for (int i = 0; i < arrsize; i++)
		//{
		//	cout << i + 1 << ". " << myArray[i] << endl;
		//}
	}
	average = total / 10;
	cout << "The average time is: " << average << endl;
	//cout << "The total time(nanosecond) : " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " Nanoseconds" << endl;
	return 0;
}