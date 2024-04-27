#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// wrap text function to fit line width
// Passed string by reference to avoid making a copy and using unnecessary space
void wrapText(const string& text, int lineWidth) {
    vector<string> words; // Vector to store all words
    string word; // Variable to hold each word read from text
    istringstream iss(text); // input string stream to split text into words

    // splitting the sentence into words and storing them to vector
    while (iss >> word) {
        words.push_back(word);
    }

    int currentLineWidth = 0; // Variable to keep track of current line width

    // Loop over each word in the words vector
    for (const string& w : words) {
        // check if adding the length of the current word will exceed the desired line width
        if (currentLineWidth + w.length() + (currentLineWidth > 0 ? 1 : 0) <= lineWidth) {
            // If not the beginning of the line, add space
            if (currentLineWidth > 0) {
                cout << " ";
                currentLineWidth++;
            }
            // print current word and update line width
            cout << w;
            currentLineWidth += w.length();
        }
        else {
            // Start a new line and print current word and update line width
            cout << endl;
            cout << w;
            currentLineWidth = w.length(); // Update current line width to include length of the added word
        }
    }
    // Print newline character to end last line
    cout << endl;
}

int main() {
    string text = "Mary loves to sing and perform tapdancing.";
    int lineWidth = 10; // Line width
    wrapText(text, lineWidth); // Call the wrapText function
    return 0;
}
