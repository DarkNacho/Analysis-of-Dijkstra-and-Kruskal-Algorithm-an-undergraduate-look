#include <iostream>
#include <vector>
#include <queue>
#include "utils.h"

using namespace std;
const float INF = 0x00FFFFFF;
typedef pair<double,int> P;

vector<int> dijkstra(vector<vector<P>> edges, int s, int t)
{
    priority_queue<P, vector<P>, greater<P> > Q;
    vector<double> dist(edges.size(), INF); vector<int> dad(edges.size(), -1);
    Q.push (make_pair (0, s)); dist[s] = 0;
    while (!Q.empty())  //pq + for O(E+V)
    {
        P p = Q.top(); Q.pop();
        if (p.second == t) break;
        int here = p.second;
        for (int i = 0; i< edges[here].size(); ++i) 
        {
            if (dist[here] + edges[here][i].first < dist[edges[here][i].second])
            {
                dist[edges[here][i].second] = dist[here] + edges[here][i].first;
                dad[edges[here][i].second] = here;
                Q.push (make_pair (dist[edges[here][i].second], edges[here][i].second)); //O(Log(v)) 
            }
        }
    } //O(E+V(Log(V)))
    return dad;
    //return dist[t];
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
        vector<int> path; 
        clock_t begin,end; 
        begin = clock();
        path = dijkstra(w, 0, n-1);
        end = clock();
        _time += diffclock(end,begin);
        for(int i=n-1; path[i] !=-1; i=path[i]) 
        {
            avarageCost += nodes[i].dist(nodes[path[i]]);
            if(v) cout << nodes[i].tostring() << " "<< nodes[path[i]].tostring() << " " << nodes[i].dist(nodes[path[i]]) << endl;
        }
    }
    cout << "Avagare executiom time: " << _time/nrep << endl;
    cout << "Avarage cost: " << avarageCost/nrep << endl;
    return 0;
}