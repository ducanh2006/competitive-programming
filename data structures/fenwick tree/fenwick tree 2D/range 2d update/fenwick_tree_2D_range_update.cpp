#include<bits/stdc++.h>
using namespace std;

template< class type >
class fenwick_tree_2D_range_update
{
private :
    int n,m;
    type **table[4];
    inline void ___update_table( type X, type Y, type val )
    {
        for( int i = X ; i <= n ; i += (i&(-i)) )
        {
            for( int j = Y ; j <= m ; j += (j&(-j)) )
            {
                table[0][i][j] += val;
                table[1][i][j] += val*X;
                table[2][i][j] += val*Y;
                table[3][i][j] += val*X*Y;
            }
        }
    }
    inline type ___query_table( type X, type Y )
    {
        type sum = 0;
        type xx = X+1, yy = Y+1;
        for( int i = X ; i > 0  ; i -= (i&(-i)) )
        {
            for( int j = Y ; j > 0  ; j -= (j&(-j)) )
            {
                sum += table[0][i][j]*xx*yy;
                sum -= table[1][i][j]*yy;
                sum -= table[2][i][j]*xx;
                sum += table[3][i][j];
            }
        }
        return sum;
    }
public :
    fenwick_tree_2D_range_update()
    {
        n =  m =  0;
    }
    fenwick_tree_2D_range_update( int row, int column )
    {
        n = row;
        m = column;

        table[0] =  new( type*[row+1] );
        table[1] =  new( type*[row+1] );
        table[2] =  new( type*[row+1] );
        table[3] =  new( type*[row+1] );

        ++column;
        for( int i = 0; i < 4; i ++ )
        {
            for( int j = 1; j <= row; j++ )
            {
                table[i][j] = new( type[column] );
                memset( table[i][j], 0, sizeof(type)*column );
            }
        }
    }
    inline void update( int x1, int y1, int x2, int y2, type val )
    {
        ___update_table(x1,y1,val);
        ___update_table(x2+1,y1,-val);
        ___update_table(x1,y2+1,-val);
        ___update_table(x2+1,y2+1,val);
    }
    inline type query( int x1, int y1, int x2, int y2 )
    {
        return( ___query_table(x2,y2) - ___query_table(x2,y1-1) - ___query_table(x1-1,y2) + ___query_table(x1-1,y1-1) );
    }
    void print()
    {
        for( int i = 1; i <= n; i ++ )
        {
            for( int j = 1; j <= m; j ++ ) cout << query(i,j,i,j)<<" ";
            cout <<endl;
        }
    }
    pair<int,int> size()
    {
        return {n,m};
    }
};
int main()
{

}
