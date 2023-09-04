#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <limits>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

// Define the data structure to represent a graph node
struct GraphNode
{
    string vertex;
    char color;
    char type;
    GraphNode(string v, char c, char t) : vertex(v), color(c), type(t) {}
};

// Define the data structure to store the distances and previous vertices for each vertex
struct VertexInfo
{
    string previous;
    char color;
    char type;
};

vector<string> startingNodes;



vector<vector<string>> shortest_paths;
void bfs(unordered_map<string, vector<GraphNode>> graph, string start, string end)
{

    queue<pair<string, vector<string>>> q;
    unordered_map<string, bool> visited;
    //vector<vector<string>> shortest_paths;

    // for (int g = 0; g < startingNodes.size(); ++g)
    // {
    //     string start = startingNodes[g];

    //     std::stringstream test(start);
    //     std::string segment;
    //     std::vector<std::string> seglist;

    //     while (std::getline(test, segment, '-'))
    //     {
    //         seglist.push_back(segment);
    //     }

    //     q.push({start, {seglist[0]}});
    //     visited[start] = true;
    // }

  

    std::stringstream test(start);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(test, segment, '-'))
    {
        seglist.push_back(segment);
    }

    q.push({start, {seglist[0]}});
    visited[start] = true;

    while (!q.empty())
    {
        string node = q.front().first;
        //cout << node << endl;
        vector<string> path = q.front().second;
        q.pop();

        std::stringstream test(node);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(test, segment, '-'))
        {
            seglist.push_back(segment);
        }

        if (seglist[seglist.size() - 1] == end)
        {
            // If we've reached the end node, add the current path to the list
            // cout << "FOUND IT" << endl;
            shortest_paths.push_back(path);
        }
        seglist.clear();

        vector<GraphNode> ron = graph[node];
        for (auto const &bob : ron)
        {
            if (!visited[bob.vertex])
            {
                // If we haven't visited this neighbor before, add it to the queue
                // and mark it as visited, and add the current node to the path
                vector<string> new_path = path;

                new_path.push_back(bob.vertex);
                q.push({bob.vertex, new_path});
                visited[bob.vertex] = true;
            }
        }
    }
    //cout << shortest_paths.size() << endl;

    // if (shortest_paths.empty())
    // {
    //     cout << "NO PATH";
    // }
    // else
    // {
    //     // cout << "Shortest path(s) found: " << endl;
    //     for (const auto &path : shortest_paths)
    //     {
    //        // allPaths.push_back(path);
    //         for (string node : path)
    //         {
                

    //             std::stringstream test(node);
    //             std::string segment;
    //             std::vector<std::string> seglist;

    //             while (std::getline(test, segment, '-'))
    //             {
    //                 seglist.push_back(segment);
    //             }
                
    //             if (node == path.back())
    //             {
    //                 cout << seglist[0] << " " << end;
    //                 // finalPath += finalPath + node;

    //                 break;
    //             }
    //             //++n;
    //             // finalPath += finalPath + node + " ";
            
    //             cout << seglist[0] << " ";
    //         }
    //         // cout << n;
    //         //cout << endl;
    //     }
    //     // cout << finalPath;
    // }
}

void printPath(string end){

    sort(shortest_paths.begin(), shortest_paths.end());
    //cout << shortest_paths.size();
    
    if (shortest_paths.empty())
    {
        cout << "NO PATH";
    }
    else
    {   
        vector<string> finalPath = shortest_paths[0];
        int smallSize = shortest_paths[0].size();
        for (const auto &path : shortest_paths)
        {
            if(path.size() < smallSize){
               smallSize = path.size();
                finalPath = path;
            }
        }
        // cout << "Shortest path(s) found: " << endl;
        // for (const auto &path : shortest_paths)
        // {
           // allPaths.push_back(path);
            for (string node : finalPath)
            {
                

                std::stringstream test(node);
                std::string segment;
                std::vector<std::string> seglist;

                while (std::getline(test, segment, '-'))
                {
                    seglist.push_back(segment);
                }
                
                if (node == finalPath.back())
                {
                    cout << seglist[0] << " " << end;
                    // finalPath += finalPath + node;

                    break;
                }
                //++n;
                // finalPath += finalPath + node + " ";
            
                cout << seglist[0] << " ";
            }
            // cout << n;
            //cout << endl;
        //}
        // cout << finalPath;
    }
}

unordered_map<string, vector<GraphNode>> adjacencyList;

int main(int argc, char *argv[])
{
    // Open the input file
    ifstream inputFile(argv[1]);
    //ifstream inputFile("maze_input.txt");
    //ifstream inputFile("Test2.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error: could not open input file" << endl;
        return 1;
    }

    // Read the number of vertices, number of lines, start vertex, and end vertex from the first line
    int numVertices, numLines;
    string start, end;
    inputFile >> numVertices >> numLines >> start >> end;

    // Create an unordered map to store the adjacency list

    // Read in each line of the input file and add edges to the graph
    string vertex1, vertex2;
    char color, type;

    for (int i = 0; i < numLines; ++i)
    {
        inputFile >> vertex1 >> vertex2 >> color >> type;
        adjacencyList[vertex1].push_back(GraphNode(vertex2, color, type));
        adjacencyList[vertex2].push_back(GraphNode(vertex1, color, type));
    }

    // Close the input file
    inputFile.close();

    // bfs(adjacencyList,start);

    // for (auto const &pair: adjacencyList) {
    //     vector<GraphNode> ron = pair.second;
    //     cout << pair.first << ": ";
    //     for (auto const &bob: ron){
    //         cout << bob.vertex << " ";
    //     }
    //     cout << endl;
    // }

    unordered_map<string, vector<GraphNode>> megaGraph;
    for (auto const &pair : adjacencyList)
    {
        vector<GraphNode> ron = pair.second;
        string mom = pair.first;
        // cout << mom << ": ";
        string edgeNode = "";

        for (auto const &bob : ron)
        {
            string thing = bob.vertex;
            edgeNode = mom + "-" + thing;
            //cout << edgeNode << ": "; 
            if (mom == start)
            {
                startingNodes.push_back(edgeNode);
            }

            vector<GraphNode> met = adjacencyList[thing];

            for (auto const &tom : met)
            {
                if (tom.vertex == mom)
                {
                    continue;
                }

                if ((tom.color == bob.color) || (tom.type == bob.type))
                {
                    string what = thing + "-" + tom.vertex;
                    //cout << what << " ";
                    GraphNode temp(what, tom.color, tom.type);
                    megaGraph[edgeNode].push_back(temp);
                    
                }
                
            }
            //cout << endl;
            // cout << mom << "-" << bob.vertex << " ";
        }
        //cout << endl;
    }

    for (int g = 0; g < startingNodes.size(); ++g)
    {
     
       bfs(megaGraph, startingNodes[g], end);
    }

    printPath(end);

    //bfs(megaGraph, startingNodes, end);


}