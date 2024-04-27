#include <iostream>     
#include <fstream>     
#include <chrono>      
#include <iomanip>     
using namespace std;

ofstream outputFile("task3.csv");    //output file 
// function to heapify a subtree rooted at rootIndex in the array
int heapify(int array[], int size, int rootIndex)
{
    int comparisonCount = 0;    // Initialize comparison counter
    int smallest = rootIndex;   // Initialize smallest as root
    int leftChild = 2 * rootIndex + 1;  // Left child
    int rightChild = 2 * rootIndex + 2; // Right child

    // if left child is smaller than root
    if (leftChild < size && array[leftChild] < array[smallest])
    {
        smallest = leftChild;
    }

    // if right child is smaller than smallest so far
    if (rightChild < size && array[rightChild] < array[smallest])
    {
        smallest = rightChild;
    }

    // if smallest is not root
    if (smallest != rootIndex)
    {
        comparisonCount++; // Increment comparison counter
        swap(array[rootIndex], array[smallest]); // Swap root and smallest
        comparisonCount += heapify(array, size, smallest); // Recursively heapify the affected subtree
    }

    return comparisonCount; // Return the total number of comparisons
}

// Function to perform heap sort on an array using min heap
int heapSortCount(int array[], int size)
{
    int comparisonCount = 0;    // Initialize comparison counter

    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        comparisonCount += heapify(array, size, i);
    }

    // One by one extract an element from heap
    for (int i = size - 1; i > 0; i--)
    {
        // Move current root to end
        swap(array[0], array[i]);

        // Call min heapify on the reduced heap
        comparisonCount += heapify(array, i, 0);
    }

    return comparisonCount; // Return the total number of comparisons
}


// function to perform bubble sort on an array
int bubbleSortCount(int array[], int size)
{
    int comparisonCount = 0;    // Initialize comparison counter
    bool swapped;

    // traverse through all array elements
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;

        // last i elements are already in place
        for (int j = 0; j < size - i - 1; j++)
        {
            // Traverse the array from 0 to size-i-1
            // Swap if the element found is greater
            // than the next element
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
            comparisonCount++; // Increment comparison counter
        }

        // if no two elements were swapped in the inner loop, then the array is already sorted
        if (!swapped)
        {
            break;
        }
    }

    return comparisonCount; // return the total number of comparisons
}

// function to perform selection sort on an array
int selectionSortCount(int array[], int size)
{
    int comparisonCount = 0;    // initialize comparison counter
    int minIndex;

    // one by one move boundary of unsorted subarray
    for (int i = 0; i < size - 1; i++)
    {
        // Find the minimum element in unsorted array
        minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
            comparisonCount++; // Increment comparison counter
        }
        // swap the minimum element with the first element
        swap(array[i], array[minIndex]);
    }

    return comparisonCount; // return the total number of comparisons
}

// function to perform insertion sort on an array
int insertionSortCount(int array[], int size)
{
    int comparisonCount = 0;    // Initialize comparison counter
    int key = 0;

    // start from the second element (index 1)
    for (int i = 1; i < size; i++)
    {
        key = array[i];
        for (int j = i - 1; j >= 0; j--)
        {
            comparisonCount++;
            if (key < array[j])
            {
                swap(array[j], array[j + 1]);
            }
            else
            {
                break;
            }
        }
    }

    return comparisonCount;
}

// function to copy the contents of array to temp
void copyArray(int temp[], int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        temp[i] = array[i];
    }
}

// Function to print a row in the table
void printTableRow(int size, string arrayType, string sortType, int comparisons, double executionTime)
{
    cout << left << setw(20) << size << left << setw(20) << arrayType << left << setw(20) << sortType << left << setw(25) << comparisons << left << setw(20) << executionTime << "\n";
}

// Function to execute sorting algorithms and print results
void executeSorts(int temp[], int array[], int size, string arrayType, string sortAlgorithm)
{
    // Copy the original array to a temporary array for sorting.
    copyArray(temp, array, size);

    // Record the start time of the sorting process.
    auto startTime = chrono::high_resolution_clock::now();

    // Declare a variable to store the number of comparisons performed during sorting.
    int comparisons;

    // Choose the sorting algorithm based on the specified sortAlgorithm parameter.
    if (sortAlgorithm == "Heap")
    {
        // Perform heap sort and store the number of comparisons.
        comparisons = heapSortCount(temp, size);
    }
    else if (sortAlgorithm == "Bubble")
    {
        // Perform bubble sort and store the number of comparisons.
        comparisons = bubbleSortCount(temp, size);
    }
    else if (sortAlgorithm == "Selection")
    {
        // Perform selection sort and store the number of comparisons.
        comparisons = selectionSortCount(temp, size);
    }
    else
    {
        // Perform insertion sort and store the number of comparisons for any other algorithm.
        comparisons = insertionSortCount(temp, size);
    }

    // Record the end time of the sorting process.
    auto endTime = chrono::high_resolution_clock::now();

    // Calculate the execution time of the sorting process in seconds.
    double executionTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() * 1e-9;

    // Write the sorting results (size, array type, sorting algorithm, number of comparisons, execution time) to the output file.
    outputFile << size << "," << arrayType << "," << sortAlgorithm << "," << comparisons << "," << executionTime << "\n";

    // Print the sorting results as a table row.
    printTableRow(size, arrayType, sortAlgorithm, comparisons, executionTime);
}


// Function to run all sorting algorithms on an array
void runSorts(int array[], string arrayType, int size)
{
    // Create a temporary array for sorting
    int* temp = new int[size];

    // Execute heap sort on the array and record the comparisons and execution time
    executeSorts(temp, array, size, arrayType, "Heap");

    // Execute bubble sort on the array and record the comparisons and execution time
    executeSorts(temp, array, size, arrayType, "Bubble");

    // Execute selection sort on the array and record the comparisons and execution time
    executeSorts(temp, array, size, arrayType, "Selection");

    // Execute insertion sort on the array and record the comparisons and execution time
    executeSorts(temp, array, size, arrayType, "Insertion");

    // Deallocate memory for the temporary array
    delete[] temp;
}

// Function to test and compare sorting algorithms on arrays of different sizes and types
void testComparisons()
{
    // Seed for random number generation
    srand(time(0));

    // Write header to output file
    outputFile << "Size of Array,Type of Array,Sorting Algorithm,Number of Comparisons,Execution Time\n";

    // Print header to console
    cout << left << setw(20) << "Size of Array" << left << setw(20) << "Type of Array"
        << left << setw(20) << "Sorting Algorithm" << left << setw(25) << "Number of Comparisons"
        << left << setw(20) << "Execution Time" << "\n";

    // Loop through array sizes from 1 to 30
    for (int s = 1; s < 31; s++)
    {
        // Create arrays for random, sorted, and inversely sorted values
        int* randomArray = new int[s];
        int* sortedArray = new int[s];
        int* inverseArray = new int[s];
        int num1 = 0;
        int num2 = 0;

        // Fill arrays with random, sorted, and inversely sorted values
        for (int i = 0; i < s; i++)
        {
            randomArray[i] = rand() % (s * 20);
            num1 += rand() % (s * 20);
            sortedArray[i] = num1;
            num2 += rand() % (s * 20);
            inverseArray[s - i - 1] = num2;
        }

        // Run sorting algorithms on each type of array
        runSorts(randomArray, "Random", s);
        runSorts(sortedArray, "Sorted", s);
        runSorts(inverseArray, "Inversely-sorted", s);

        // Deallocate memory for arrays
        delete[] randomArray;
        delete[] sortedArray;
        delete[] inverseArray;
    }
}


int main()
{
    testComparisons();  // Run the comparison tests
    outputFile.close(); // Close the output file
    return 0;           // Return 0 to indicate successful execution
}
