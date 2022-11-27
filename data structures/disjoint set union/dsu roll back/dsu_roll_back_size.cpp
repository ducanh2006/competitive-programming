#include<bits/stdc++.h>
using namespace std;

class dsu_roll_back_size
{
private :
    struct DATAA{ int u,v,lab_u,lab_v; };
    int *lab,comp;
    vector<DATAA>save;
public:
    dsu_roll_back_size(){ comp = 0; }
    dsu_roll_back_size(int n)
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
    int size(){ return save.size(); }
    int find_root(int u )
    {
        while( lab[u] > 0  ) u = lab[u];
        return u;
    }
    bool unite( int u, int v )
    {
        u = find_root(u); v = find_root(v);
        if( u == v ) return false;

        save.push_back({u,v,lab[u],lab[v]});
        if( lab[u] > lab[v] )swap(u,v);
        lab[u] += lab[v];
        lab[v] = u;
        --comp;
        return true;
    };
    void roll_back( int SIZE )
    {
        while( save.size() > SIZE )
        {
            lab[ save.back().u ] = save.back().lab_u;
            lab[ save.back().v ] = save.back().lab_v;
            save.pop_back();
            comp++;
        }
    }
    bool check_same_component( int u , int v  ){ return ( find_root(u) == find_root(v) ); }
};
int main()
{

}
