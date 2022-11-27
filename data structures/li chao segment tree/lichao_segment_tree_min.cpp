#include<bits/stdc++.h>
using namespace std;

template< const long long range_left ,  const long long range_right >
class lichao_tree_min
{
private :
    struct line
    {
        long long a,b;
        line() { a = 0;  b  = LLONG_MAX; }
        line( const long long & aaaa , const long long  & bbbb ) { a = aaaa; b = bbbb; }
        long long get( const long long & x )  {  return ( (a*x) + b );  }
    };
    struct node
    {
        node *left, * right;
        line l;
        node() { left = right = nullptr; }
    };
    node *root;
    long long LEFT,RIGHT,mid;
public :
    lichao_tree_min() { root = new(node); }
    void insert( line LINE )
    {
        LEFT = range_left; RIGHT = range_right;
        node *ptr  = root;

        while(true)
        {
            if( LEFT == RIGHT )
            {
                if( ptr->l.get(LEFT) < LINE.get(LEFT) ) swap( ptr->l , LINE );
                return;
            }
            mid = (( LEFT + RIGHT )>>1);
            if( ptr->l.a > LINE.a ) swap( ptr->l, LINE );
            if( ptr->l.get(mid) < LINE.get(mid) )
            {
                if( ptr->left == nullptr ) ptr->left = new(node);
                RIGHT = mid;
                ptr = ptr->left;
            }
            else
            {
                swap( ptr->l , LINE );
                if( ptr->right == nullptr ) ptr->right = new(node);
                LEFT =  mid+1;
                ptr = ptr->right;
            }
        }
    }
    long long query( const long long & x)
    {
        LEFT  = range_left; RIGHT  = range_right;
        long long ans =  LLONG_MAX;
        node *ptr = root;
        while(true)
        {
            ans = min(  ans , ptr->l.get(x) );
            if( LEFT == RIGHT )  return ans;

            mid = (( LEFT + RIGHT )>>1);
            if( RIGHT < 1 )  --mid;

            if( x <= mid && ptr->left != nullptr )
            {
                RIGHT  = mid;
                ptr = ptr->left;
            }
            else if ( ptr->right != nullptr )
            {
                LEFT = mid+1;
                ptr = ptr->right;
            }
            else return ans;
        }
    }
};
int main()
{

}
