#include <iostream>
#include <ctime>

using namespace std; 

void revisedQuickSort(int array[], int first, int last, int& comparisons);
int revisedParition(int array[], int first, int last, int& comparisons);
void quicksort(int array[], int first, int last, int& comparisons);
int partition(int array[], int first, int last, int& comparisons);
void sortFirstMiddleLast(int array[], int first, int mid, int last, int& comparisons);
void insertionSort(int array[], int size, int& comparisons);
void merge(int array[], int first, int mid, int);
void mergeSort(int array[], int first, int last, int& comparisons);

const int MIN = 0;
const int MAX = 2;

int main()
{	
	
	{
		int array[MAX];

		double overallTime;
		clock_t start, finish;
		int icompare = 0;
		int icompare1 = 0;
		int revComparisons = 0;
		int regComparisons = 0;

		//Create an unsorted array
		for (int i = 0; i < MAX; i++)
			array[i] = (double)(MAX - i);

		//Insertion Sort
		start = clock();
		insertionSort(array, MAX, icompare1);
		finish = clock();
		overallTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
		cout << "Running time for insertion sort of n size " << MAX << " is " << overallTime << endl;
		cout << "Number of comparisons " << icompare1 << endl << endl;
		//Create an unsorted array
		for (int i = 0; i < MAX; i++)
			array[i] = (double)(MAX - i);

		//Merge Sort
		start = clock();
		mergeSort(array, 0, MAX - 1, icompare);
		finish = clock();
		overallTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
		cout << "Running time for merge sort of n size " << MAX << " is " << overallTime << endl;
		cout << "Number of comparisons " << icompare << endl << endl;

		//Create an unsorted array
		for (int i = 0; i < MAX; i++)
			array[i] = (double)(MAX - i);



		//////////////////
		//Revised Quicksort Method
		start = clock();
		revisedQuickSort(array, 0, MAX - 1, revComparisons);
		finish = clock();
		overallTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
		cout << "Running time for revised quicksort of n size " << MAX << " is " << overallTime << endl;
		cout << "Number of comparisons " << revComparisons << endl;


		//Create Unsorted Array
		for (int i = 0; i < MAX; i++)
		{
			array[i] = (double)(MAX - i);
		}

		cout << endl;

		start = clock();
		quicksort(array, 0, MAX - 1, regComparisons);
		finish = clock();
		overallTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
		cout << "Running time for quicksort of n size " << MAX << " is " << overallTime << endl;
		cout << "Number of comparisons " << regComparisons << endl;

	}
	

	system("pause");
	return 0;
}
//Calls revisedPartition, chooses first item as pivot instead of sortFirstMiddleLast
void revisedQuickSort(int array[], int first, int last, int& comparisons) {
	if (first < last) {
		int pivotIndex = revisedParition(array, first, last, comparisons);

		quicksort(array, first, pivotIndex - 1, comparisons);
		quicksort(array, pivotIndex + 1, last, comparisons);
	}
	comparisons++;
}

//Chooses first item as pivot
int revisedParition(int array[], int first, int last, int& comparisons) {
	//If smaller than 10 size in array, insertion sort
	if (last - first < MIN)
		insertionSort(array, last - 1, comparisons);
	comparisons++;

	int temp = array[first];
	array[first] = array[last];
	array[last] = temp;
	int pivotIndex = last;
	int pivot = array[pivotIndex];

	//Begin sort
	int left = first + 1;
	int right = last - 2;

	bool done = false;
	while (!done) {
		comparisons++;
		while (array[left] < pivot) {
			left++;
			comparisons++;
		}
		while (array[right] > pivot) {
			right--;
			comparisons++;
		}
		if (left < right) {
			comparisons++;
			temp = array[left];
			array[left] = array[right];
			array[right] = temp;

			left++;
			right--;
		}
		else done = true;
	}
	temp = array[pivotIndex];
	array[pivotIndex] = array[left];
	array[left] = temp;
	pivotIndex = left;

	return pivotIndex;

}

void quicksort(int array[], int first, int last, int& comparisons) {
	comparisons++;
	if (first < last) {
		int pivotIndex = partition(array, first, last, comparisons);

		quicksort(array, first, pivotIndex - 1, comparisons);
		quicksort(array, pivotIndex + 1, last, comparisons);
	}
}

int partition(int array[], int first, int last, int& comparisons) {
	//Choose pivot and reposition it
	int mid = first + (last - first) / 2;
	if (last - first < MIN) {
		insertionSort(array, last + 1, comparisons);
		comparisons++;
	}
	else sortFirstMiddleLast(array, first, mid, last, comparisons);

	int temp = array[mid];
	array[mid] = array[last - 1];
	array[last - 1] = temp;
	int pivotIndex = last - 1;
	int pivot = array[pivotIndex];

	//Begin sort
	int left = first + 1;
	int right = last - 2;

	bool done = false;
	while (!done) {
		comparisons++;
		while (array[left] < pivot) {
			left++;
			comparisons++;
		}
		while (array[right] > pivot) {
			right--;
			comparisons++;
		}
		if (left < right) {
			comparisons++;
			temp = array[left];
			array[left] = array[right];
			array[right] = temp;

			left++;
			right--;
		}
		else done = true;
	}
	temp = array[pivotIndex];
	array[pivotIndex] = array[left];
	array[left] = temp;
	pivotIndex = left;

	return pivotIndex;
}

void sortFirstMiddleLast(int array[], int first, int mid, int last, int& comparisons) {
	if (array[first] > array[mid]) {
		comparisons++;
		int temp = array[first];
		array[first] = array[mid];
		array[mid] = temp;
	}

	if (array[mid] > array[last]) {
		comparisons++;
		int temp = array[mid];
		array[mid] = array[last];
		array[last] = temp;
	}

	if (array[first] > array[mid]) {
		comparisons++;
		int temp = array[first];
		array[first] = array[mid];
		array[mid] = temp;
	}
}

void insertionSort(int array[], int size, int& comparisons) {
	for (int i = 1; i < size; i++) {
		comparisons++;
		int next = array[i];
		int loc = i;
		while (loc > 0 && array[loc - 1] > next) {
			comparisons = comparisons + 2;
			array[loc] = array[loc - 1];
			loc--;
		}
		array[loc] = next;
	}
}

void mergeSort(int array[], int first, int last, int& comparisons) 
{
	int counter = comparisons + 1;
	if (first < last) {
		int mid = first + (last - first) / 2;
		mergeSort(array, first, mid, counter);
		mergeSort(array, mid + 1, last, counter);
		merge(array, first, mid, last);
	}

}

void merge(int array[], int first, int mid, int last) {
	int tempArray[MAX];

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (array[first1] <= array[first2]) {
			tempArray[index] = array[first1];
			first1++;
		}
		else {
			tempArray[index] = array[first2];
			first2++;
		}
		index++;
	}

	while (first1 <= last1) {
		tempArray[index] = array[first1];
		first1++;
		index++;
	}

	while (first2 <= last2) {
		tempArray[index] = array[first2];
		first2++;
		index++;
	}

	for (index = first; index <= last; index++) {
		array[index] = tempArray[index];
	}
}

