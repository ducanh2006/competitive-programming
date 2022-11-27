#include<bits/stdc++.h>
using namespace std;
class fenwick_tree_1D_range_update
{
private :
    struct ft
    {
        type *a;
        int size_tree;
        void __assign( int SIZE )
        {
            a = new( type[SIZE+2] );
            memset(a , 0, ( sizeof(type)*(SIZE+2) ) );
            size_tree = SIZE;
        }
        void __update(int i, type x)
        {
            for(; i<= size_tree; i+=i&-i) a[i]+=x;
        }
        type __query(int i)
        {
            type res=0;
            for(; i; i-=i&-i) res+=a[i];
            return res;
        }
        void __clear(){ delete []a; size_tree = 0; }
    } bit1,bit2;

public :

    fenwick_tree_1D_range_update (){ bit1.size_tree = bit2.size_tree = 0; }
    fenwick_tree_1D_range_update ( int num_element )
    {
        bit1.size_tree = bit2.size_tree = num_element;
        bit1.__assign(num_element); bit2.__assign(num_element);
    }
    void assign( int num_element )
    {
        bit1.size_tree = bit2.size_tree = num_element;
        bit1.__assign(num_element); bit2.__assign(num_element);
    }
    void update( int left, int right , const type & new_val )
    {
        bit1.__update(left,new_val);
        bit1.__update(right+1,-new_val);
        bit2.__update(left,(new_val*(left-1)));
        bit2.__update(right+1,-new_val*right);
    }
    type query( int left , int right )
    {
        return (  ( right*bit1.__query(right) - bit2.__query(right) ) - ( (left-1)*bit1.__query(left-1) - bit2.__query(left-1) )  );
    }
    int size(){ return (bit1.size_tree); }
    void clear(){ bit1.__clear() ; bit2.__clear() ; }
    void change_size( int new_size ){ bit1.size_tree = bit2.size_tree = new_size; }
    void print(){ for( int i = 1; i <= bit1.size_tree; i ++ )cout << query(i,i) <<" ";}
};
int main()
{

}
