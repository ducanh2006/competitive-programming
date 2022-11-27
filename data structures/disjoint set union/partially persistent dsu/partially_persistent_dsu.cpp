#include<bits/stdc++.h>
using namespace std;

class partially_persistent_dsu
{
private :
    int * lab, *time_unite,comp,max_time;
public:
    partially_persistent_dsu(){ comp = max_time = 0;}
    partially_persistent_dsu(int n)
    {
        comp = n;
        max_time = 0;
        lab = new( int[n+2] );
        time_unite = new( int[n+2] );
        for( int i = 1 ; i <= n; i ++ )
        {
            lab[i] = -1;
            time_unite[i] = INT_MAX;
        }
    }
    void assign( int n )
    {
        comp = n;
        max_time = 0;
        lab = new( int[n+2] );
        time_unite = new( int[n+2] );
        for( int i = 1 ; i <= n; i ++ )
        {
            lab[i] = -1;
            time_unite[i] = INT_MAX;
        }
    }
    void change_number_component( int num_component ){ comp = num_component; }
    int present_time() { return max_time; }
    void change_time( int new_time )
    {
        assert( new_time >= max_time );
        max_time = new_time;
    }
    int component(){ return comp; }

    int find_root(int u, int TIME )
    {
        while( time_unite[u] <= TIME ) u = lab[u];
        return u;
    }
    bool unite( int u, int v, int TIME )
    {
        assert(TIME >= max_time );

        max_time = TIME;
        u = find_root(u,TIME); v = find_root(v,TIME);
        if( u == v ) return false;
        if( lab[u] > lab[v] )swap(u,v);
        lab[u] += lab[v];
        lab[v] = u;
        time_unite[v] = TIME;
        --comp;
        return true;
    };
    bool check_same_component( int u , int v , int TIME ){ return ( find_root(u,TIME) == find_root(v,TIME) ); }
    int find_first_time_unite( int u , int v )
    {
        if( u == v ) return 0;
        int first = 1, last = max_time, mid , ans = -1;
        while( first <= last )
        {
            mid = ((first + last )>>1);
            if( check_same_component(u,v,mid) )
            {
                ans  = mid;
                last = mid-1;
            }
            else first = mid + 1;
        }
        return ans;
    }
    void clear()
    {
        delete []lab;
        delete []time_unite;
        comp = max_time = 0;
    }
};
int main()
{

}
