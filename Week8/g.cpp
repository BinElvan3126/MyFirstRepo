#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
vector<vector<int>> convertMatrixToList(const string &filename) {
    ifstream fin(filename);
    int nV;
    fin >> nV;
    vector<vector<int>> List(nV);
    for (int i = 0; i < nV; i++)
    {
        int count = 0;
        for (int j = 0; j < nV; j++)
        {
            int key;
            fin >> key;
            if (key == 1)
            {
                List[i].push_back(j);
                count++;
            }
        }
        List[i].insert(List[i].begin(), count);
    }
    return List;
}
vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream fin(filename);
    int nV;
    fin >> nV;
    vector<vector<int>> M(nV, vector<int>(nV));
    for (int i = 0; i < nV; i++)
    {
        int count = 0;
        fin >> count;
        for (int j = 0; j < count; j++)
        {
            int key;
            fin >> key;
            M[i][key] = 1;
        }
    }
    return M;
}
bool isDirected(const vector<vector<int>>& M) {
    if (M.empty()) return false;
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++){
            if (M[i][j] != M[j][i]) return true;
        }
    }
    return false;
}
int countVertices(const vector<vector<int>>& M) {
    return M.size();
}

int countEdges(const vector<vector<int>>& M) {
    if (M.empty()) return 0;
    int count = 0;
    if (isDirected(M)) {
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < M[i].size(); j++) {
                if (M[i][j] == 1) count++;
            }
        }
    }
    else {
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < M[i].size(); j++) {
                if (M[i][j] == 1) count++;
            }
        }
        count /= 2;
    }
    return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& M) {
    vector<int> res;
    for (int i = 0; i < M.size(); i++) {
        bool iso = true;
        for (int n = 0; n < M.size(); n++) {
            if (M[i][n] == 1) iso = false;
        }
        for (int d = 0; d < M.size(); d++) {
            if (M[d][i] == 1) iso = false;
        }
        if (iso) res.push_back(i);
    }
    return res;
}
bool isCompleteGraph(const vector<vector<int>>& M) {
    if (isDirected(M)) return false;
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            if (M[i][j] == 0 && i != j) return false;
        }
    }
    return true;
}
bool isBipartite(const std::vector<std::vector<int>>& M) {
    if (M.size() == 0) return true;
    vector<int> color(M.size(), -1);
    for (int node = 0; node < M.size(); node++) {
        if (color[node] == -1) {
            queue<int> q;
            q.push(node);
            color[node] = 0;
            while (!q.empty()){
                int u = q.front();
                q.pop();
                for (int v = 0; v < M.size(); v++) {
                    if (M[u][v] == 1) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                        else if (color[v] == color[u]) return false;
                    }
                }
            }
        }
    }
    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& M) {
    if (!isBipartite(M)) return false;
    if (M.size() == 0) return true;
    vector<int> color(M.size(), -1);
    for (int start_node = 0; start_node < M.size(); ++start_node) {
        if (color[start_node] == -1) {
            queue<int> q;
            q.push(start_node);
            color[start_node] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < M.size(); ++v) {
                    if (M[u][v] == 1) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                    }
                }
            }
        }
    }
    vector<int> p1;
    vector<int> p2;
    for (int i = 0; i < M.size(); ++i) {
        if (color[i] == 0) {
            p1.push_back(i);
        } else if (color[i] == 1) {
            p2.push_back(i);
        }
    }
    // cout << endl;
    // for (int i : p1) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // for (int i : p2) {
    //     cout << i << " ";
    // }
    // cout << endl;

    if (p1.empty() || p2.empty()) {
        return true;
    }

    for (int v1 : p1) {
        for (int v2 : p2) {
            if (M[v1][v2] == 0) {
                return false;
            }
        }
    }
    return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& M) {
    vector<vector<int>> res = M;
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            if (M[i][j] == 1) {
                res[i][j] = 1;
                res[j][i] = 1;
            }
            else if (M[j][i] == 1) {
                res[i][j] = 1;
                res[i][j] = 1;
            }
        }
    }
    return res;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& M) {
    vector<vector<int>> a = M;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (i == j) a[i][i] = 0;
            else {
                if (M[i][j] == 1 && i != j) a[i][j] = 0;
                else if (M[i][j] == 0 && i != j) a[i][j] = 1;
            }
        }
    }
    return a;
}
vector<int> findEulerCycle(const vector<vector<int>>& M) {

}
int main()
{
    vector<vector<int>> M = convertListToMatrix("test.txt");
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++){
            cout << M[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
    cout << "isDirected: " << (isDirected(M) ? "YES\n" : "NO\n");
    cout << "countVertices: " << countVertices(M) << endl;
    cout << "countEdges: " << countEdges(M) << endl;
    vector<int> iso = getIsolatedVertices(M);
    cout << "getIsolatedVertices: ";
    if(iso.empty()) {
        cout << "EMPTY\n";
    } else {
        for (int i : iso) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "isCompleteGraph:" << (isCompleteGraph(M) ? "YES\n" : "NO\n");
    cout << "isBipartite:" << (isBipartite(M) ? "YES\n" : "NO\n");
    cout << "isCompleteBipartite:" << (isCompleteBipartite(M) ? "YES\n" : "NO\n");

    cout << "convertToUndirectedGraph:\n"; vector<vector<int>> a = convertToUndirectedGraph(M);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++){
            cout << a[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
    cout << "isUndirected: " << (!isDirected(a) ? "YES\n" : "NO\n");

    vector<vector<int>> b = getComplementGraph(a);
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++){
            cout << b[i][j] << " "; 
        }
        cout << endl;
    }
//sdsads

    // vector<vector<int>> c = convertMatrixToList("test.txt");
    // for (int i = 0; i < c.size(); i++)
    // {
    //     for (int j = 0; j < c[i].size(); j++)
    //     {
    //         cout << c[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}

/*
M    0 1 2 3 4 5 6 7 8

0    0 0 1 0 0 1 0 0 0
1    0 0 0 0 0 0 1 0 0
2    0 0 0 0 0 0 1 0 0
3    0 0 0 0 1 0 0 0 0
4    0 0 0 0 0 1 0 0 0
5    0 0 0 1 0 0 0 1 0
6    0 0 0 0 0 0 0 0 0
7    0 0 1 0 0 0 0 0 1
8    0 0 0 0 0 0 0 0 0
*/