#include<bits/stdc++.h>
using namespace std;

class disjoint_set_union
{
private :
    int * lab,comp;
public:
    disjoint_set_union(){ comp = 0; }
    disjoint_set_union(int n)
    {
        comp = n;
        lab = new( int[n+2] );
        memset( lab, -1, sizeof(int)*(n+2) );
    }
    void assign( int n )
    {
        comp = n;
        lab = new( int[n+2] );
        memset( lab, -1, sizeof(int)*(n+2) );
    }
    void change_number_component( int num_component ){ comp = num_component; }
    int component(){ return comp; }

    int find_root(int u )
    {
        if( lab[u] < 0 ) return u;
        else return ( lab[u] = find_root(lab[u]) );
    }
    bool unite( int u, int v )
    {

        u = find_root(u); v = find_root(v);
        if( u == v ) return false;
        if( lab[u] > lab[v] )swap(u,v);
        lab[u] += lab[v];
        lab[v] = u;
        --comp;
        return true;
    };
    bool check_same_component( int u , int v  ){ return ( find_root(u) == find_root(v) ); }
};
int main()
{

}
