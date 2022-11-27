#include<bits/stdc++.h>
using namespace std;
template< class type >
class fenwick_tree_1D_point_update
{
private :
    type *bit;
    int size_tree;
public :
    void update( int pos , const type & new_val )
    {
        for( ; pos <= size_tree ; pos += ( pos&(-pos)) ) bit[pos] += new_val;
    }
    template< class Pointer >
    void build( Pointer first , Pointer last )
    {
        int idx = 1;
        int nxt;
        while( first != last )
        {
            bit[idx] += (*first);
            nxt = ( idx + (idx&(-idx)) );
            if( nxt <= size_tree ) bit[nxt] += bit[idx];
            ++first; ++idx;
        }
    }
    type query( int left , int right )
    {
        type sum = 0;
        left--;
        for( ; right > 0 ; right -= ( right&(-right)) ) sum += bit[right];
        for( ; left > 0; left  -= ( left&(-left)) )   sum -= bit[left];
        return sum;
    }
    fenwick_tree_1D_point_update (){ size_tree = 0; }
    fenwick_tree_1D_point_update ( int num_element )
    {
        bit = new( type[num_element+1] );
        memset( bit, 0, sizeof(type)*(num_element+1) );
        size_tree = num_element;
    }

    void assign( int num_element )
    {
        bit = new( type[num_element+1] );
        memset( bit, 0, sizeof(type)*(num_element+1) );
        size_tree = num_element;
    }
    int size(){ return (size_tree); }
    void clear(){ delete []bit ; size_tree = 0; }
    void change_size( int new_size ){ size_tree = new_size; }
    void print(){ for( int i = 1; i <= size_tree; i ++ )cout << query(i,i) <<" ";}
};
int main()
{

}
