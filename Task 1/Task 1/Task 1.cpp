#include <iostream>
#include <unordered_set>
using namespace std;


// function to remove duplicates from an array of chars
unordered_set<char> removeDuplicates(char chars[], int length) {
    unordered_set<char> set;

    // loop through the array and add each char to the set
    for (int i = 0; i < length; ++i) {
        char c = chars[i];
        set.insert(c);    // set has only unique elements so no duplicates will be added
        
    }

    return set;
}

int main() {
    char arr[] = { 'a', 'b', 'c', 'a', 'd', 'b', 'e', 'b', 'e' };
    int size = sizeof(arr) / sizeof(arr[0]);

    // call the removeDuplicates function to get unique characters
    unordered_set<char> noDuplicates = removeDuplicates(arr, size);

    // Print the unique characters
    for (char c : noDuplicates) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}


