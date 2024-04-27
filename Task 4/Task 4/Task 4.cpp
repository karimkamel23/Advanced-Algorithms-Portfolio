// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;


// swap function to swap 2 indicies in the array
void swap(int arr[], int index1, int index2) {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}


//Check for elements before the key element and placing them in the correct position
void beforeCheck(int arr[], int size, int key, int index, int pos = 0) {

    //base condition if index of key is reached
    if (pos >= size || pos == index) return;

    if (arr[pos] == key && (index - 1) != pos) { // places repeated key before main key
        swap(arr, pos, index - 1);
    }

    int* newArr = new int[size]; // create a temporary array to transfer the elements to in order
    if (arr[pos] > key) { // pos is the current position, if the value is greater to the key it will:
        copy(arr, arr + pos, newArr); // transfers everything before the position to the new array
        copy(arr + pos + 1, arr + size, newArr + pos); // transfers everything after the position to the new array
        copy(arr + pos, arr + pos + 1, newArr + size - 1); // transfers the pos element to the new array so now it is the last element
        copy(newArr, newArr + size, arr); // replaces the array with the edited one
        index--; // changes the index of the key to the correct one
        beforeCheck(arr, size, key, index, pos);  //recursive call with the same pos to check the new item in that position
    }
    else beforeCheck(arr, size, key, index, pos + 1); //recursive call with the next pos to check the next item in the array

}


//Check for elements after the key element and placing them in the correct position
void afterCheck(int arr[], int size, int key, int index, int pos = -1) {

    //base condition if index of key is reached
    if (size + pos < 0 || size + pos == index) return;

    if (arr[size + pos] == key && (index + 1) != (size + pos)) {  // places repeated key after main key
        swap(arr, size + pos, index + 1);

    }

    if (arr[size + pos] < key) { // pos is the current position, if the value is less than or equal to the key it will:
        int temp = arr[size + pos]; // store the current position in a temp variable
        copy_backward(arr, arr + size + pos, arr + size + pos + 1); // shifting all elements to the right (one index)
        arr[0] = temp; // placing the saved position element in the first position (leftmost)
        index++; //adjusting the index of the key to the correct one
        afterCheck(arr, size, key, index, pos); //recursive call with the same pos to check the new item in that position
    }
    else afterCheck(arr, size, key, index, pos - 1); //recursive call with the previous pos to check the previous item in the array
}


// main function to rearrange the array
void rearrange(int arr[], int key, int size) {

    // if and else if statements which correct places the key element in the middle if it is found in beginning or end of array.
    if (arr[0] == key) {
        swap(arr, 0, int(size / 2));
    }
    else if (arr[size - 1] == key) {
        swap(arr, size - 1, int(size / 2));

    }

    int* result = find(arr, arr + size, 3);  // find index of key
    int index = result - arr;

    
    beforeCheck(arr, size, key, index); // checks elements before as stated
    afterCheck(arr, size, key, index); // checks elements after

}

// loops and prints the result array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

int main()
{
    int arr[] = { 2,3,4,5,2,4,5,3,2 };
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, 3, size);
    printArray(arr, size);

    return 0;
}

