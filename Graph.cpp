#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph()
{
    graphNodes = nullptr;
    cout << "This is a directed graph : ";
    cout << endl << "Enter number of nodes in the graph : ";
    cin >> numberOfNodes;
    graphNodes = new Vertex[numberOfNodes];
    negativeCycles = false;
}

void Graph::inputVertices()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        int temp;
        cout << "Enter the value of ID = " << i << " Node : ";
        cin >> temp;
        cout << endl;
        graphNodes[i].setValue(temp);
        graphNodes[i].setID(i);
    }
    cout << "Enter the ID of the source vertex : ";
    cin >> sourceVertexID;
}

void Graph::inputEdges()
{
    char c = 'n';
    do {
        int sourceID, destinationID,weight;
        cout << endl << "Enter the source vertex ID and destination vertex ID of the edge : ";
        cin >> sourceID >> destinationID;
        cout << endl << "Enter the weight of the edge : ";
        cin >> weight;
        graphNodes[sourceID].addNeighbour(&graphNodes[destinationID],weight);
        cout << endl << "Do you want to enter another edge ? ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}

Vertex* Graph::getGraphNodes()
{
    return graphNodes;
}

int Graph::getNumberOfNodes()
{
    return numberOfNodes;
}

int Graph::getSourceVertexID()
{
    return sourceVertexID;
}

void Graph::traverseUsingBellmanFord()
{
    (graphNodes + sourceVertexID)->setDistanceFromSource(0);
    for (int i = 0; i < numberOfNodes - 1; i++)//no. of passes = number of nodes - 1
    {
        for (int j = 0; j < numberOfNodes; j++)//relax all edges
        {
            Vertex* currentVertex = &graphNodes[j];
            for (int k = 0; (int)k < currentVertex->adjList.size(); k++)
            {
                Vertex* kthNeighbour = currentVertex->adjList[k].destinationVertex;
                int u = currentVertex->getDistanceFromSource();
                int v = kthNeighbour->getDistanceFromSource();
                int w = currentVertex->adjList[k].weight;
                if (u + w < v)
                {
                    kthNeighbour->setDistanceFromSource(u + w);
                    kthNeighbour->setParent(currentVertex);
                }
            }
        }
    }

    for (int j = 0; j < numberOfNodes; j++)//last iteration of relaxation to check for negative weight cycles
    {
        Vertex* currentVertex = &graphNodes[j];
        for (int k = 0; (int)k < currentVertex->adjList.size(); k++)
        {
            Vertex* kthNeighbour = currentVertex->adjList[k].destinationVertex;
            int u = currentVertex->getDistanceFromSource();
            int v = kthNeighbour->getDistanceFromSource();
            int w = currentVertex->adjList[k].weight;
            if (u + w < v)
            {
                negativeCycles = true;
            }
        }
    }
}

void Graph::printDistanceFromSource()
{
    if (negativeCycles == false)
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            cout << "ID = " << i;
            cout << " Value = " << graphNodes[i].getValue();
            cout << " Distance from source = " << graphNodes[i].getDistanceFromSource();
            if (graphNodes[i].getParent() != nullptr)
            {
                cout << " Parent ID = " << graphNodes[i].getParent()->getID();
            }
            else
            {
                cout << " No parent";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Graph contains negative weight cycles!" << endl;
    }
}

Graph::~Graph()
{
    delete[] graphNodes;
}