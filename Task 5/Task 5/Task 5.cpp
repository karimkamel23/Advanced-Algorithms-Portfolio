#include <iostream> 
#include <stack> 
#include <vector> 
#include <cmath> 
#include <string> 
#include <map> 
#include <memory> 
#include <stdexcept> 

using namespace std;

// definition of Node class to represent a number or operator in the expression tree
class Node {
public:
    string value; // The value of the node, can be an operator or number
    unique_ptr<Node> left; // Unique pointer to the left child
    unique_ptr<Node> right; // Unique pointer to the right child

    // Constructor to initialize node with a value and null children
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// define of ExpressionTree class
class ExpressionTree {
public:
    unique_ptr<Node> root; // unique pointer to the root

    // Constructor to initialize the root to a nullptr
    ExpressionTree() : root(nullptr) {}

    // the main function that constructs the tree from an expression string
    void constructTree(const string& exp) {
        root = buildTree(exp); // calls buildTree function in order to parse and construct the tree
    }

    //evaluates the expression tree and calculates its result
    double evaluate() {
        return evaluateNode(root); // uses evaluateNode starting from the root Node
    }

    //displays the tree in a top to bottom format starting from root
    void display() {
        int depth = treeDepth(root.get()); // calculate the depth of the tree
        int width = calculateWidth(depth); // calculate the width that will be used for display based on depth
        vector<string> displayLines(depth, string(width, ' ')); // create lines for displaying
        fillDisplay(displayLines, root.get(), 0, width / 2, depth); // Fill lines with node values
        for (const auto& line : displayLines) { // print each line
            cout << line << endl;
        }
    }

private:
    // helper function used to evaluate (calculate) nodes recursively
    double evaluateNode(const unique_ptr<Node>& node) {
        if (!node->left && !node->right) { // check if leaf node reached
            try {
                return stod(node->value); // Try converting the value to double
            }
            catch (const invalid_argument& ia) { // Catch and handle invalid argument exception
                cerr << "Invalid numeric format: " << ia.what() << '\n';
                return 0;
            }
            catch (const out_of_range& orr) { // Catch and handle out of range exception
                cerr << "Number out of range: " << orr.what() << '\n';
                return 0;
            }
        }
        // Recursively evaluate left and right children and calculate result for specific operator
        double leftVal = evaluateNode(node->left);
        double rightVal = evaluateNode(node->right);
        if (node->value == "+") return leftVal + rightVal;
        if (node->value == "-") return leftVal - rightVal;
        if (node->value == "*") return leftVal * rightVal;
        return leftVal / rightVal; 
    }

    // constructs the tree from the expression string
    unique_ptr<Node> buildTree(const string& expr) {
        stack<int> openStack; // stack created to handle open parenthesis
        vector<int> ops; // vector that stores the positions of the operators
        string cleanExpr = removeOuterParentheses(expr); // remove outer parentheses
        int len = cleanExpr.length(); // Length of clean expression
        map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} }; // Map to store operator precedence

        // Loop through expression to find the operators outside of any parenthesis
        for (int i = 0; i < len; i++) {
            if (cleanExpr[i] == '(') openStack.push(i);
            else if (cleanExpr[i] == ')') openStack.pop();
            else if (openStack.empty() && precedence.find(cleanExpr[i]) != precedence.end()) {
                ops.push_back(i);
            }
        }

        if (ops.empty()) return make_unique<Node>(cleanExpr); // If no operators, return node with value

        int opIndex = selectOperator(cleanExpr, ops, precedence); // Select operator with highest precedence
        auto node = make_unique<Node>(string(1, cleanExpr[opIndex])); // Create node for operator
        node->left = buildTree(cleanExpr.substr(0, opIndex)); // Recursively build left subtree
        node->right = buildTree(cleanExpr.substr(opIndex + 1)); // Recursively build right subtree
        return node;
    }

    // remove outer parentheses from the expression to clean it
    string removeOuterParentheses(const string& expr) {
        if (expr.front() == '(' && expr.back() == ')') return expr.substr(1, expr.length() - 2);
        return expr;
    }

    // selects the operator which has the highest precedence
    int selectOperator(const string& expr, const vector<int>& ops, const map<char, int>& precedence) {
        int maxPrecedence = 0;
        int selectedIndex = 0;
        for (int index : ops) {
            int prec = precedence.at(expr[index]);
            if (prec > maxPrecedence) {
                maxPrecedence = prec;
                selectedIndex = index;
            }
        }
        return selectedIndex;
    }

    // calculates the depth of tree
    int treeDepth(Node* node) {
        if (!node) return 0;
        return 1 + max(treeDepth(node->left.get()), treeDepth(node->right.get()));
    }

    // calculates the width needed for displaying based on depth
    int calculateWidth(int depth) {
        return (1 << depth) - 1; // 2^depth - 1
    }

    // function to fill lines with node values recursively to display the tree
    void fillDisplay(vector<string>& lines, Node* node, int row, int col, int depth) {
        if (!node || row >= depth) return;
        int branchLen = (1 << (depth - row - 2)); // calculate branch length for spacing
        lines[row][col] = node->value[0]; // place node value in the correct position
        if (node->left) fillDisplay(lines, node->left.get(), row + 1, col - branchLen, depth); //display left child recursively 
        if (node->right) fillDisplay(lines, node->right.get(), row + 1, col + branchLen, depth); //display right child recursively 
    }
};

int main() {
    ExpressionTree exprTree; // Create an instance of ExpressionTree
    string expression = "((6+7)*3)"; // Define the expression to be parsed and evaluated
    exprTree.constructTree(expression); // Build the expression tree
    cout << "Expression Tree Display:" << endl;
    exprTree.display(); // Display the tree
    cout << "Evaluated Result: " << exprTree.evaluate() << endl; // Evaluate and display the result
    return 0;
}