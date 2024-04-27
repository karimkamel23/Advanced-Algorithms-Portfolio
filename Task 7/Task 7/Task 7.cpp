#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int vertices;                 // Num of vertices in graph
    list<int>* adjacencyList;     // Adjacency list to store the edges
    void fillStackWithVertices(int v, bool visited[], stack<int>& Stack);  // helper function for DFS
    void DFS(int v, bool visited[]);  // depth-first search traversal

public:
    Graph(int V);                 
    void addEdge(int v, int w);   //add edge to graph
    void getStronglyConnectedComponents();  // print strongly connected components
    Graph transpose();         // get transpose of the graph
};

// Constructor to initialize the graph
Graph::Graph(int V) {
    this->vertices = V;
    adjacencyList = new list<int>[V];  // Creates an array of adjacency lists
}

// Depth-first search traversal
void Graph::DFS(int v, bool visited[]) {
    visited[v] = true;  // Mark the current vertex as visited
    cout << v << " ";   // Print the current vertex

    // Recursively go through all the vertices adjacent to the current vertex
    list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}

// get the transpose of the graph
Graph Graph::transpose() {
    Graph transposedGraph(vertices);  // Create a new graph with the same number of vertices
    for (int v = 0; v < vertices; v++) {
        list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i) {
            transposedGraph.adjacencyList[*i].push_back(v);  // Add reverse edges to transposed graph
        }
    }
    return transposedGraph;
}

// add an edge to the graph
void Graph::addEdge(int v, int w) {
    adjacencyList[v].push_back(w);  // Add vertex w to vertex v's adjacency list
}

// Helper function for DFS as it fills the stack with vertices
void Graph::fillStackWithVertices(int v, bool visited[], stack<int>& Stack) {
    visited[v] = true;  // Marks the current vertex as visited

    // Recursively goes through all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
            fillStackWithVertices(*i, visited, Stack);

    // after all vertices reachable from v are processed, push v to stack
    Stack.push(v);
}

// prints the strongly connected components
void Graph::getStronglyConnectedComponents() {
    stack<int> Stack;  // Create a stack to store vertices

    bool* visited = new bool[vertices];  // Mark all vertices as not visited initially
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for (int i = 0; i < vertices; i++)
        if (visited[i] == false)
            fillStackWithVertices(i, visited, Stack);

    // Create a the transposed graph
    Graph transposedGraph = transpose();

    // Mark all vertices as not visited for second DFS traversal
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    // process all vertices in order defined by Stack
    while (Stack.empty() == false) {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false) {
            transposedGraph.DFS(v, visited);  // print the  strongly connected components
            cout << endl;
        }
    }
}

int main() {
    Graph graph(7);  // Create a graph with 7 vertices
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);
    graph.addEdge(5, 6);

    cout << "Strongly Connected Components:\n";
    graph.getStronglyConnectedComponents();  // Print the strongly connected components of the graph
    return 0;
}
