#include<bits/stdc++.h>
using namespace std;

struct node {
    int parent;
    int rank;
};

struct Edge {
    int src;
    int dst;
    int wt;
};

vector<node> dsuf;
vector<Edge> mst;

// FIND operation with path compression
int find(int v)
{
    if(dsuf[v].parent == -1)
        return v;
    return dsuf[v].parent = find(dsuf[v].parent);  // Path compression
}

void union_op(int fromP, int toP)
{
    // UNION by Rank: Attach the smaller tree to the larger one
    if(dsuf[fromP].rank > dsuf[toP].rank) {
        dsuf[toP].parent = fromP;
    }
    else if(dsuf[fromP].rank < dsuf[toP].rank) {
        dsuf[fromP].parent = toP;
    } else {
        dsuf[fromP].parent = toP;
        dsuf[toP].rank++;
    }
}

// Comparator to sort edges by their weight
bool comparator(Edge a, Edge b)
{
    return a.wt < b.wt;
}

// Kruskal's Algorithm to find the MST
void Kruskals(vector<Edge>& edge_List, int V, int E)
{
    sort(edge_List.begin(), edge_List.end(), comparator);  // Sort edges by weight

    int i = 0, j = 0;
    while(i < V - 1 && j < E)
    {
        int fromP = find(edge_List[j].src);  // Find the parent of the source vertex
        int toP = find(edge_List[j].dst);   // Find the parent of the destination vertex

        if(fromP != toP) {  // If they belong to different sets
            union_op(fromP, toP);  // Union the sets
            mst.push_back(edge_List[j]);  // Add edge to the MST
            i++;
        }
        j++;
    }
}

// Print the MST
void printMST(vector<Edge>& mst)
{
    cout << "MST formed is\n";
    int total = 0;
    for(auto p : mst){
        cout << "src: " << p.src << "  dst: " << p.dst << "  wt: " << p.wt << "\n";
        total = total + p.wt;
    }  
    cout<<"Total Cost for the MST is : "<<total;
}

int main()
{
    // Hardcoded input for edges and vertices
    int E = 5;  // Number of edges
    int V = 4;  // Number of vertices

    // Initialize the DSU structure
    dsuf.resize(V);  

    for(int i = 0; i < V; ++i) {
        dsuf[i].parent = -1;
        dsuf[i].rank = 0;
    }

    // Hardcoded edges in the form of (src, dst, weight)
    vector<Edge> edge_List = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Apply Kruskal's algorithm to find the MST
    Kruskals(edge_List, V, E);

    // Print the MST
    printMST(mst);

    return 0;
}
