#include<bits/stdc++.h>
using namespace std;
template< class type >
class fenwick_tree_2D_point_update
{
private :
    int n,m;
    type **bit;
    type __get_val( int x, int y )
    {
        type sum  = 0;
        for( int i = x ; i > 0 ; i -= ( i &(-i) ) )
        {
            for( int j = y; j > 0 ; j -= ( j&(-j) ) ) sum += bit[i][j];
        }
        return sum;
    }
public :
    fenwick_tree_2D_point_update() { n =  m =  0; }
    fenwick_tree_2D_point_update( int row, int column )
    {
        n = row; m = column;
        bit =  new( type*[row+1] );
        ++column;
        for( int i = 1; i <= row; i ++ )
        {
            bit[i] = new( type[column] );
            memset( bit[i] , 0 , sizeof(type)*column );
        }
    }
    pair<int,int> size() { return {n,m}; };
    void update( int x, int y, type val )
    {
        for( int i =  x ; i <= n ; i += ( i&(-i) ) )
        {
            for( int j = y ; j <= m; j += ( j&(-j) ) ) bit[i][j] += val;
        }
    }
    type query( int x1, int y1, int x2, int y2 )
    {
        return( __get_val( x2,y2) -  __get_val( x1 - 1, y2 ) - __get_val( x2, y1-1 ) + __get_val(x1-1, y1-1 ) );
    }
    void print()
    {
        for( int i = 1; i <= n; i ++ )
        {
            for( int j = 1; j <= m; j ++ ) cout << query(i,j,i,j)<<" ";
            cout <<endl;
        }
    }
};
int main()
{

}
