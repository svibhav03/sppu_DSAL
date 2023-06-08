/*
You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different
amounts of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by
suggesting appropriate data structures.
*/

#include<bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;

class Graph {
    
    int **adjMatrix;
    int vertexCount;
    int edgeCount;
    map<string, int> cities;
    map<int, string> inv_cities;
    
    void add( string city1, string city2, int dist ) {
        adjMatrix[cities[city1]][cities[city2]] = dist;
        adjMatrix[cities[city2]][cities[city1]] = dist;
    }
    
    // minimum_key() method for finding the vertex that has minimum key-value and that is not added in MST yet
    int minimum_key(int key[], bool mst[])
    {
        int minimum  = INF, min, i;
          
        // iterate over all vertices to find the vertex with minimum key-value
        for (i = 0; i < vertexCount; i++)
            if (mst[i] == 0 && key[i] < minimum ) {
                minimum = key[i];
                min = i;
            }
        return min;
    }

public:

    Graph(){
        cout<<"Enter number of Vertices: ";
        cin>>vertexCount;
        cout<<"Enter number of edges: ";
        cin>>edgeCount;
        
        adjMatrix = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            adjMatrix[i] = new int[vertexCount];
            for(int j = 0; j < vertexCount; j++)
                adjMatrix[i][j] = 0;
        }

        cout<<"Add cities in order: "<<endl;
        for(int i = 0; i < vertexCount; i++) {
            string city;
            cin>>city;
            cities.insert(pair<string, int>(city, i));
            inv_cities.insert(pair<int, string>(i, city));
        }
        
        cout<<"Add the "<<edgeCount<<" edges"<<endl;
        
        for(int i = 0; i < edgeCount; i++) {
            string u,v;
            int d;
            cout<<"City 1: ";
            cin>>u;
            cout<<"City 2: ";
            cin>>v;
            cout<<"Distance: ";
            cin>>d;
            add(u, v, d);
        }
    }
    
    void prim(Graph g) {
        int n = g.vertexCount;
        
        int parent[n];  // Array to store constructed MST
        int key[n];     // Key values used to pick minimum weight edge in cut
        bool mst[n];    // To represent set of vertices not yet included in MST
        
        // Initialize all keys as infinite
        for (int i = 0; i < n; i++) {
            key[i] = INF;
            mst[i] = false;
        }
        
        // Always include the first vertex in MST
        key[0] = 0;         // Make key 0 so that this vertex is picked as the first vertex
        parent[0] = -1;     // First node is always the root of MST
        
        // The MST will have V vertices
        for (int count = 0; count < n-1; count++)
        {
            // Pick the minimum key vertex from the set of vertices not yet included in MST
            int u = minimum_key(key, mst);
            
            // Add the picked vertex to the MST set
            mst[u] = true;
            
            // Update key value and parent index of the adjacent vertices of the picked vertex
            for (int v = 0; v < n; v++)
            {
                // Update the key only if the current weight is smaller than the existing key
                if (adjMatrix[u][v] && mst[v] == false && adjMatrix[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }
        
        cout << "Minimum Spanning Tree (MST):" << endl;
        cout << "Edge \t\t Weight" << endl;
        int totalCost = 0;
        for (int i = 1; i < n; i++)
        {
            cout << inv_cities[parent[i]] << " - " << inv_cities[i] << "\t\t" << adjMatrix[i][parent[i]] << endl;
            totalCost += adjMatrix[i][parent[i]];
        }
        
        cout << "Total cost of the MST: " << totalCost << endl;
    }
};

int main() {
    
    Graph g;
    g.prim(g);
    
    return 0;
}