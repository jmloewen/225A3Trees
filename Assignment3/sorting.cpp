// File:        sorting.cpp
// Authors:     Geoffrey Tien (skeleton), Jonathan Loewen (principal coding).
// Date:        2016-02-17
// Description: Implementation of sorting functions for CMPT 225 Assignment 3

//Principal coding February 13th
//February 17th - integers work, need to make sure floats, strings work - update Template usage to make this happen.
//February 19th - Final fixes, Commenting.

//This is a simple Swap function.
//Takes in an array, two indices, and swaps the values within.
template <class T>
void SwapVals(T arr[], int i, int j)
{
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//Selection Sort
//A simple implementation of a Selection Sort.
//Takes in an array 'arr' to be sorted, and its length 'n'.
template <class T>
int SelectionSort(T arr[], int n)
{
	//if size <= 1, there is nothing to sort.
	if (n <= 1)
	{
		return 0; //barometer operation of the avg case never occurs.
	}
	//minpos is the index of the lowest known value in the array.  This is assumed to be 'i' until proven otherwise.
	int minpos = 0;
	int count = 0;//the number of operations.

	//iterate through every value in the array but the last one, swapping if we find a larger value.
	for (int i = 0; i < n - 1; i++)
	{
		//Assign minpos to i for our current iteration.
		minpos = i;

		//search for a value in the rest of the list that is larger than i.
		for (int j = i + 1; j < n; j++)
		{
			//if the current value of j is less than minpos, we have a new minimum value - assign it to minpos.
			if (arr[j] < arr[minpos])
			{
				minpos = j;
			}
			count++;	//iterate our barometer count.
		}

		//if our new value is different than the old value arr[i], swap.
		if (arr[minpos] != arr[i])
		{
			SwapVals(arr, i, minpos);
		}
	}
	return count;
}

// Quicksort
//A simple implementation of Quicksort.
//Takes in an array 'arr' to be sorted, and its length 'n'.
template <class T>
int Quicksort(T arr[], int n)
{
	//if size is <= 1, there is nothing to sort.  Return.
	if (n <= 1)
	{
		return 0; //barometer operation of the avg case never occurs.
	}

	//create an integer to hold the count and a pointer to it.
	int count = 0;
	int * pcount = &count;
  
	//send it n-1, since n is the length, but our max index is n-1.  Send the count pointer.
	QuicksortHelper(arr, 0, n-1, *pcount);
	return count;
}

//A function to help out the Quicksort and partition functions.
//Takes in an array to sort, and the indices between which it will be sorted.
template <class T>
void QuicksortHelper(T arr[], int low, int high, int& counter)
{
	//if the value of low is less than the value of high, enter to begin the partition and sort.
	if (low < high)
	{
		//taken from notes, adapted as is appropriate.  Partitions, then calls self until there is nothing left to partition.
		int partVal = QSPartition(arr, low, high, counter);
		QuicksortHelper(arr, low, partVal - 1, counter);
		QuicksortHelper(arr, partVal + 1, high, counter);
	}
}

//A Partition function to help the Quicksort.
//Takes in an array 'arr' to be sorted, and the values between which this array will be partitioned into 'low' and 'high' partitions.
template <class T>
int QSPartition(T arr[], int low, int high, int& counter)
{
	//the value to pivot around is the last value of the subarray.
	//Has a counter for low and high - takes the highest of these values and stores it in counter.  
	//This tells us what our highest barometer operation for the current cycle is.
	int tempCounterLow = 0;
	int tempCounterHigh = 0;
	T pivotval = arr[high];

	//while low is less than high, loop.  Low and high will continually pinch until they are equal.
	while (low < high)
	{
		//find a value in the 'low' part of the array that is higher than the pivot.
		while (arr[low] < pivotval)
		{
			tempCounterLow++;
			low++;
		}
		//find a value in the 'high' part of the array that is lower than the pivot.
		while (arr[high] > pivotval)
		{
			tempCounterHigh++;
			high--;
		}
		
		//if low is still less than high, we have found two values that are out of place.  Swap them.
		if (low < high)
		{
			SwapVals(arr, low, high);
		}
	}
	//if our high counter is more than the low counter, give counter this value.  Else, give it the low value. 
	if (tempCounterHigh > tempCounterLow)
	{
		counter += tempCounterHigh;
	}
	else
	{
		counter += tempCounterLow;
	}
	
	//return the value of 'high' to the caller.
	return high;
}

// Randomized Quicksort
//This is a copied and pasted version of the non-randomized quicksort function.
//Takes in an array to be sorted, and its length 'n'.
template <class T>
int RQuicksort(T arr[], int n)
{
	if (n <= 1)
	{
		return 0; //barometer operation of the avg case never occurs.
	}

	//establish count, create a pointer to it.
	int count = 0;
	int * pcount = &count;
  
	//send it n-1, since n is the length, but our max index is n-1.
	//this needs to exist since our qs is recursive.
	RQuicksortHelper(arr, 0, n-1, *pcount);
	return count;
}

//This is a copied and pasted version of the non-randomized quicksorthelper function.
//Takes in an array to be sorted, and the low and high values between which it will be sorted.
template <class T>
void RQuicksortHelper(T arr[], int low, int high, int& counter)
{
  	if (low < high)
	{
		//taken from notes, adapted as is appropriate.
		int partVal = RQSPartition(arr, low, high, counter);
		if (partVal > 1)
		{
			RQuicksortHelper(arr, low, partVal - 1, counter);
		}
		if (partVal + 1 < high)
		{
			RQuicksortHelper(arr, partVal + 1, high, counter);
		}
	}
}

//This is a copied and pasted version of the non-randomized quicksort function, with a random swap at the start.
//Takes in an array 'arr' to be sorted, and the values between which this array will be partitioned into 'low' and 'high' partitions.
template <class T>
int RQSPartition(T arr[], int low, int high, int& counter)
{
	//swap the end with a random value between low and high - this value is determined by low + rand() % (high-low).  This speeds up already sorted and reverse sorted arrays.
	SwapVals(arr, low + (rand() % (high - low)), high);

	//The rest of this code is identical to the non-randomized quicksort above.
	int tempCounterLow = 0;
	int tempCounterHigh = 0;
	T pivotval = arr[high];
	
	while (low < high)
	{
		while (arr[low] < pivotval)
		{
			tempCounterLow++;
			low++;
		}
		while (arr[high] > pivotval)
		{
			tempCounterHigh++;
			high--;
		}

		if (low < high)
		{
			SwapVals(arr, low, high);
		}
	}
	
	if (tempCounterHigh > tempCounterLow)
	{
		counter += tempCounterHigh;
	}
	else
	{
		counter += tempCounterLow;
	}
	
	return high;
}

// Mergesort
//A simple merge sort.
//Takes in an array to be sorted and its length 'n'.
template <class T>
int Mergesort(T arr[], int n)
{
	//if we have only one or no values, our sort is done.
	if (n <= 1)
	{
		return 0; //The barometer operation never happens.
	}

	//create count and a pointer to it.
	int count = 0;
	int * pcount = &count;

	MergesortHelper(arr, 0, n-1, n, *pcount);
	return count;
}

//A helper function for the merge sort.  Calls itself if there is more splitting to be done, then calls merge as is necessary.
//Receives an array, and the indicies between which this array will be sorted, and its length.
template <class T>
void MergesortHelper(T arr[], int low, int high, int n, int& counter)
{
	if (low < high)//if we have a valid list to sort, enter.  Note that when partitioned into single parts, low = high, so we will then climb back up the stack.
	{
		int mid = (high + low) / 2; //create a mid value that perfectly partitions the remaining list into two  pieces.
		MergesortHelper(arr, low, mid, n, counter);			//do the left side of our binary tree, then the right side.
		MergesortHelper(arr, mid + 1, high, n, counter);	//the right side of our binary tree
		//then merge the two halves of our tree.
		Merge(arr, low, mid, high, n, counter);
	}
}

//Merge low->mid, mid+1->high of the given arr.
//Merges two portions of an array into the source array, given a low, mid, and high index of this array.
template <class T>
void Merge(T arr[], int low, int mid, int high, int n, int& counter)
{
	//create a temporary array to hold the eventual low->high array.
	T * tempArr = new T[high + 1 - low];

	//we have to exhaust both the 'mid-low' and the 'high-mid' sides.  
	//These sides do not necessarily have to be of equal length, but will be within '1' of each other.
	//we can create an iterator for both sides that holds the number of values removed from each side of the merge.
	//l represents the lower half of the array,  represents the top half.
	int l = low;
	int h = mid + 1;

	//the current location of our tempArray.
	int cur = 0;

	//while low is less than or equal to the value of mid, and high is less than or equal to the value of high, iterate.
	while (l <= mid && h <= high)
	{
		//This is our barometer operation in all instances; iterate it.
		counter++;
		//if the value at low is less than or equal to the value at high, assign the value of low to our temp array and move l off of this value.
		if (arr[l] <= arr[h])
		{
			tempArr[cur] = arr[l];
			l++;
		}
		//otherwise, the value is equal to high, assign high to tempArray and move h off of this value.
		else
		{
			tempArr[cur] = arr[h];
			h++;
		}
		cur++;//move the current assigning position of tempArr.
	}
	
	//If we're out of the first loop, we may not be done filling in the array.  Ensure that tempArr is filled.
	if (l > mid)
	{
		//fill in values of high, since low is completed.
		for (int iter = h; iter <= high; iter++)
		{
			tempArr[cur] = arr[iter];
			cur++;
		}
	}
	else
	{
		//fill in values of low, since high is completed.
		for (int iter = l; iter <= mid; iter++)
		{
			tempArr[cur] = arr[iter];
			cur++;
		}
	}

	//take the values of tempArr and assign them to arr.
	for (int iter = 0; iter <= high-low; iter++)
	{
		arr[low+iter] = tempArr[iter];
	}
	//tempArr will delete itself since it was created here, and is not in heap memory.
}

// Shell Sort
// A simple implementation of Shell Sort.
// Reference: https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Shell_sort
//Receives an array and its length 'n'.
template <class T>
int ShellSort(T arr[], int n)
{
	//if size <= 1, there is nothing to sort.
	if (n <= 1)
	{
		return 0; //barometer operation of the avg case never occurs.
	}

	int count = 0;
	//gap = n/2 - no rounding.  This way we end up at an even value after one division of n.  Decrease gap on every iteration.
	for (int gap = n/2; gap > 0; gap = gap / 2)
	{
		//check values that are i values of 'gap' less than the current iteration i (find the next position where we can swap at the current gap length)
		for (int i = gap; i < n; i++)
		{
			int j;	//initialize j here so that we can use it post-loop.
			T curVal = arr[i];
			count++;
			//for every time we're able to swap, swap with the given gap while j is greater than this gap
			//decrease j and assign the value at j this value at an index 'gap' less than j.
			for (j = i; j >= gap && arr[j - gap] >= curVal; j-= gap)
			{
				arr[j] = arr[j - gap];//we specifically do not use the swap function, as classically, Shell does not use Stack memory.
			}
			arr[j] = curVal;//assign j to the current value.
		}
	}
	return count;
}