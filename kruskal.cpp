#include <iostream>
#include <vector>
#include <queue>
#include "utils.h"

using namespace std;
typedef pair<double,int> P;
int find(int C[], int x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); } 
//Runs in O(E*log(E)) time.
vector<edge> kruskal(vector<vector<P>> adj)
{
    int n = adj.size();
    double weight = 0;
    int C[n], R[n];
    vector <edge> T;
    priority_queue <edge, vector <edge>> E;
    
    for(int i=0; i<n; ++i) //initalize pq and  Union-Find // full anidated cilce O(E)
    {
        C[i] = i; R[i] = 0;
        for (int j = 0; j < adj[i].size(); ++j)      
            E.push(edge(i,adj[i][j].second, adj[i][j].first)); //O(log(E))
    } //O(E*Log(E))

    while(T.size() < n-1 && !E.empty()) //O(E) worst case, empty pq (O(E))
    {
        edge cur = E.top(); E.pop(); //(O(log(E)))
        int uc = find(C, cur.u), vc = find(C, cur.v); //find disjoint-set , (O(log(V)))
        if(uc != vc)
        {
            T.push_back(cur); weight += cur.d; //keep track of the path... and weights
            if(R[uc] > R[vc]) C[vc] = uc; //Union
            else if(R[vc] > R[uc]) C[uc] = vc;
            else { C[vc] = uc; R[uc]++; }
        }
    }
    return T;
    //return weight;
}

int main(int argc, char *argv[])
{
    vector<string> args(argv, argv + argc);
    bool v = false;
    int n, nrep; int offset = 0;
    float densidad; double _time=0; double avarageCost=0;
    if(args.size() == 5) offset = v = !(args[1].compare("[-v]"));
    n = stoi(args[1+offset]); densidad = stof(args[2 + offset]); nrep = stoi(args[3+offset]);
    for(int i=0; i<nrep; ++i)
    {
        vector<vector<P>> w = generateGraph(n,densidad); 
        vector<edge> path;
        clock_t begin,end; 
        begin = clock();
        path = kruskal(w);
        end = clock();
        _time += diffclock(end,begin);
        for(int i=0; i<path.size(); ++i)
        {   
            avarageCost += nodes[path[i].u].dist(nodes[path[i].v]);
            if(v) cout << nodes[path[i].u].tostring() << " "<< nodes[path[i].v].tostring() << " " << nodes[path[i].u].dist(nodes[path[i].v]) << endl;
        }    
    }
    cout << "Avagare executiom time: " << _time/nrep << endl;
    cout << "Avarage cost: " << avarageCost/nrep << endl;
    return 0;
}
