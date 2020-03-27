#include <algorithm>
#include <vector>

#ifndef READER_H
#define READER_H

using namespace std;
typedef pair<double,int> P; // weight , id
double averageCost;

struct PT
{
    float x, y;
    PT() {}
    PT(float _x, float _y) : x(_x), y(_y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    double dist2(PT p) { return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); }
    string tostring() { return "(" + to_string(x) + "," + to_string(y) + ")"; }
    bool operator==(const PT &p) { return x == p.x && y == p.y; }
};

vector<PT> nodes; 

struct edge
{
    int u, v;
    double d;
    edge();
    edge(int _u, int _v, double _d): u(_u), v(_v), d(_d) {}
    string tostring() {return to_string(u) + "-" + to_string(v) + " " + to_string(d); }
    bool operator<(const edge& a) const { return d > a.d; }
};

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

vector<vector<P>> adjMatrixToList(vector <vector <double>> w)
{
    vector<vector<P>> adj(w.size());
    for(int i=0; i<w.size(); i++) for(int j=0; j<w.size(); j++)
        if(w[i][j] >0) adj[i].push_back(make_pair (w[i][j], j)); //note order
    return adj;
}

vector<vector<P>> generateGraph(int n, float densidad)
{ 
    int edgesN = (densidad)*((n*(n-1))/2), i; averageCost =0;
    if(edgesN < n-1) {cout << "Can't create a convex graph with this params" << endl; exit(0);}
    nodes = vector<PT>(n); float delta = 1/(float)n; float x[n],y[n];
    vector <vector<double>> w(n, vector <double >(n));
    for(int i = 0; i<n; ++i) x[i] = y[i] = (i+1)*delta;
    random_shuffle(&x[0], &x[n-1]);random_shuffle(&y[0], &y[n-1]);
    for(int i = 0; i<n; ++i) nodes[i] = PT(x[i],y[i]);
    for(int i = 0; i<n; ++i) for (int j = 0; j < n; ++j) w[i][j] = w[j][i] = i==j? 0: -1;
    for(i=0; i<n-1; ++i)  // convex grpah
    {
        w[i][i+1] = w[i+1][i] = nodes[i].dist2(nodes[i+1]);
        averageCost += w[i][i+1];
    }
    while (i<edgesN) 
    {
        int x = rand() % n;int y = rand() % n;
        if(x != y && w[x][y] < 0) 
        {
            w[x][y] = w[y][x] = nodes[x].dist2(nodes[y]); 
            w[x][x] = w[y][y] = 0; ++i; averageCost += w[y][x]; 
        }
    }
    averageCost /= edgesN;
    /*for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
            cout << w[i][j] << " ";
        cout << endl;
    }*/
    return adjMatrixToList(w);    
}
#endif 