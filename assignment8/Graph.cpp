#include <iostream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

void Graph::addEdge(string v1, string v2)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == v1) // if the vertex with v1 is found, find v2
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j]->name == v2 && i != j) // if the vertex with v2 is found and it's not the same as v1, add the edge
                {
                    adjVertex vertA;
                    vertA.v = vertices[j];             // vertA is set to the vertex of the string containing the name of v2
                    vertices[i]->adj.push_back(vertA); // vertA is added to the adjacency list of the vertex of the string containing the name of v1
                    adjVertex vertB;
                    vertB.v = vertices[i];
                    vertices[j]->adj.push_back(vertB);
                }
            }
        }
    }
}

void Graph::addVertex(string name)
{
    bool found = false;
    for (int i = 0; i < vertices.size(); i++) // find if a vertex with that key already exists
    {
        if (vertices[i]->name == name)
        {
            found = true;
        }
    }
    if (found == false) // if not create a new vertex and add it to the vector of vertices
    {
        vertex *newVertex = new vertex;
        newVertex->name = name;
        vertices.push_back(newVertex);
    }
}

void Graph::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++) // print all edges from each vertex
    {
        cout << vertices[i]->name << " --> ";
        for (int j = 0; j < vertices[i]->adj.size(); j++) // print all edges from the vertex's adjacency list
        {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex)
{
    vertex *root;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == sourceVertex)
        {
            root = vertices[i];
            break;
        }
    }
    cout << "Starting vertex (root): " << root->name << "-> ";
    queue<vertex *> q;
    q.push(root);
    root->visited = true;
    vertex *n;
    int distance = 0;
    root->distance = distance;

    while (!q.empty())
    {
        n = q.front();
        q.pop();
        for (int x = 0; x < n->adj.size(); x++)
        {
            if (!n->adj[x].v->visited)
            {
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance + 1;
                q.push(n->adj[x].v);
                cout << n->adj[x].v->name << "(" << n->adj[x].v->distance << ")"
                     << " "; 
            }
        }
    }
}

int *helper(int *connectedComponents, vector<vertex *> vertices)
{
    for (int a = 0; a < vertices.size(); a++)
    {
        vertex *start = vertices[a];
        start->visited = true;
        queue<vertex *> q;
        q.push(start);
        vertex *check;
        while (!q.empty())
        {
            check = q.front();
            q.pop();
            for (int y = 0; y < check->adj.size(); y++)
            {
                if (!check->adj[y].v->visited)
                {
                    check->adj[y].v->visited = true;
                    q.push(check->adj[y].v);
                }
            }
        }
        connectedComponents++;
    }
    return connectedComponents;
}

int Graph::getConnectedBuildings()
{
    int connectedComponents = 0;
    for (int a = 0; a < vertices.size(); a++)
    {
        vertex * start = nullptr;
        for (int b = 0; b < vertices.size(); b++)
        {
            if (b == vertices.size()-1 && vertices[b]->visited == true)
            {
                return connectedComponents;
            }
            if (!vertices[b]->visited)
            {
                start = vertices[b];
                break;
            }
        }
        start->visited = true;
        queue<vertex *> q;
        q.push(start);
        vertex *check;
        while (!q.empty())
        {
            check = q.front();
            q.pop();
            for (int y = 0; y < check->adj.size(); y++)
            {
                if (!check->adj[y].v->visited)
                {
                    check->adj[y].v->visited = true;
                    q.push(check->adj[y].v);
                }
            }
        }
        connectedComponents++;
    }
    return connectedComponents;
}