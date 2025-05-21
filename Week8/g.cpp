#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
vector<vector<int>> convertMatrixToList(const string &filename)
{
    ifstream fin(filename);
    int nV;
    fin >> nV;
    vector<vector<int>> adjList(nV);
    for (int i = 0; i < nV; i++)
    {
        int count = 0;
        for (int j = 0; j < nV; j++)
        {
            int key;
            fin >> key;
            if (key == 1)
            {
                adjList[i].push_back(j);
                count++;
            }
        }
        adjList[i].insert(adjList[i].begin(), count);
    }
    return adjList;
}
int main()
{
    vector<vector<int>> c = convertMatrixToList("test.txt");
    for (int i = 0; i < c.size(); i++)
    {
        for (int j = 0; j < c[i].size(); j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}