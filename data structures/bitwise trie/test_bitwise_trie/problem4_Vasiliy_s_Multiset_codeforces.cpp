#include<bits/stdc++.h>
using namespace std;

template< const int num_bit >
class bitwise_trie
{
private :
    using type = long long int ;
    struct node
    {
        node *zero,*one;
        int cnt;
        node()
        {
            zero = one = nullptr;
            cnt = 0;
        }
    };
    void ____clear_trie( node * ptr  )
    {
        if( ptr->zero != nullptr  )
        {
            ____clear_trie( ptr->zero );
            delete( ptr->zero );
            ptr->zero = nullptr;
        }
        if( ptr->one  != nullptr  )
        {
            ____clear_trie( ptr->one );
            delete( ptr->one );
            ptr->one = nullptr;
        }
    }
    void ____print_trie( node *ptr  , type val , int depth, vector<type>&save )
    {
        if( depth == (-1) )
        {
            for( int k = 0; k < ptr->cnt ; k ++ ) save.push_back(val^xor_val);
            return;
        }
        if( ptr->zero != nullptr )  ____print_trie( ptr->zero, val , depth -1, save );
        if( ptr->one  != nullptr )  ____print_trie( ptr->one , val + (1<<depth) , depth -1 , save  );
    }
    #define ERROR_VALUE (-1);
    node *root;
    type xor_val;
public :

    bitwise_trie(){ assert( num_bit > 0 );xor_val = 0; root = new(node); }

    void xor_all_value( const type & val ){ xor_val ^= val; }
    type size(){ return root->cnt; }
    void clear()
    {
        ____clear_trie(root);
        root->cnt = xor_val = 0;
    }
    type xor_value() { return xor_val; }
    vector<type> print()
    {
        vector<type>save;
        ____print_trie(root,0,num_bit-1,save);
        return save;
    }
    type min()
    {
        if( root->cnt == 0 ) return ERROR_VALUE;
        node *ptr = root;
        type ans = 0;
        for( int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if( ptr->zero != nullptr ) ptr = ptr->zero;
            else
            {
                ans += (1<<idx);
                ptr = ptr->one;
            }
        }
        return ans;
    }
    type max()
    {
        if( root->cnt == 0 ) return ERROR_VALUE;
        node *ptr = root;
        type ans = 0;
        for( int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if( ptr->one != nullptr )
            {
                ans += (1<<idx);
                ptr = ptr->one;
            }
            else ptr = ptr->zero;
        }
        return ans;
    }

    void insert(  type val )
    {
        node *ptr = root;
        val ^= xor_val;
        for( short int idx = num_bit - 1 ; idx != (-1) ; --idx )
        {
            ++ptr->cnt;
            if( ((val>>idx)&1) )
            {
                if( ptr->one == nullptr ) ptr->one = new(node);
                ptr = ptr->one;
            }
            else
            {
                if( ptr->zero == nullptr ) ptr->zero = new( node );
                ptr = ptr->zero;
            }
        }
        ++ptr->cnt;
    }
    type find_max_xor( type val )
    {
        if( root->cnt == 0 ) return ERROR_VALUE;

        type ans = 0;
        node *ptr = root;
        val ^= xor_val;
        for( short int idx = num_bit-1 ; idx != (-1) ; --idx )
        {
            if( ((val>>idx)&1) )
            {
                if( ptr->zero != nullptr ) ptr = ptr->zero;
                else
                {
                    ans +=  (1<<idx);
                    ptr = ptr->one;
                }
            }
            else
            {
                if( ptr->one != nullptr )
                {
                    ans +=  (1<<idx);
                    ptr = ptr->one;
                }
                else ptr = ptr->zero;
            }
        }
        return ans;
    }
    type find_by_order( type k_th )
    {
        if( k_th > root->cnt || k_th <= 0 ) return ERROR_VALUE;

        node *ptr = root;
        type ans = 0;
        int countt;

        if( xor_val ==  0 )
        {
            for( short int idx = num_bit - 1 ; idx != (-1) ; --idx )
            {
                countt  =  (ptr->zero == nullptr) ? 0 : ptr->zero->cnt;
                if( countt >= k_th ) ptr = ptr->zero;
                else
                {
                    k_th -= countt;
                    ptr = ptr->one;
                    ans += (1<<idx);
                }
            }
        }
        else
        {
            for( short int idx = num_bit - 1 ; idx != (-1) ; --idx )
            {
                if ( ((xor_val>>idx)&1) )
                {
                    countt = (ptr->one  == nullptr) ? 0 : ptr->one->cnt;
                    if( countt >= k_th ) ptr = ptr->one;
                    else
                    {
                        k_th -= countt;
                        ptr = ptr->zero;
                        ans += (1<<idx);
                    }
                }
                else
                {
                    countt  =  (ptr->zero == nullptr) ? 0 : ptr->zero->cnt;
                    if( countt >= k_th ) ptr = ptr->zero;
                    else
                    {
                        k_th -= countt;
                        ptr = ptr->one;
                        ans += (1<<idx);
                    }
                }
            }
        }
        return ans;
    }
    type count( type val )
    {
        node * ptr = root;
        val ^= xor_val;
        for( short int idx = num_bit - 1 ; idx != (-1) ; --idx )
        {
            if( ((val>>idx)&1) )
            {
                if(  ptr->one == nullptr ) return 0;
                else ptr = ptr->one;
            }
            else
            {
                if( ptr->zero == nullptr ) return 0;
                else ptr = ptr->zero;
            }
        }
        return ptr->cnt;
    }
    type order_of_key( type val )
    {
        val ^= xor_val;
        type ans = 0;
        node *ptr = root;
        for( short int idx = num_bit - 1 ; idx != (-1) ; --idx )
        {
            if( ((val>>idx)&1) )
            {
                ans += ( ( ptr->zero == nullptr ) ? 0 : ptr->zero->cnt );
                ptr = ptr->one;
            }
            else ptr = ptr->zero;
            if( ptr == nullptr ) break;
        }
        return ans;
    }
    bool erase( type val )
    {
        if( root->cnt == 0 ) return false;
        val ^= xor_val;

        node ** pointer[num_bit];
        node *ptr = root;
        for( short int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if(  ((val>>idx)&1) )
            {
                pointer[idx] = &(ptr->one);
                if( (ptr = ptr->one) == nullptr ) return false;
            }
            else
            {
                pointer[idx] = &(ptr->zero);
                if( (ptr = ptr->zero) == nullptr ) return false;
            }
        }
        for( short idx = 0; idx < num_bit ; ++idx )
        {
            --(**pointer[idx]).cnt;
            if( (**pointer[idx]).cnt == 0 )
            {
                delete ( *pointer[idx] );
                *pointer[idx] = nullptr;
            }
        }
        --(root->cnt);
        return true;
    }
    type lower_bound( type val )
    {
        if( root->cnt == 0 ) return ERROR_VALUE;

        val ^= xor_val;
        node ** pointer[num_bit+1];
        node *ptr =  root;
        pointer[num_bit] = &root;

        type ans = 0;
        for( short int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if( ((val>>idx)&1) )
            {
                if( ptr->one != nullptr )
                {
                    ans += (1<<idx);
                    pointer[idx] = (&ptr->one);
                    ptr = ptr->one;
                }
                else
                {
                    short int index;
                    for( index = idx+1; index < num_bit; ++index )
                    {
                        if( !((ans>>index)&1) && (**pointer[index+1]).one  != nullptr  )
                        {
                            ans += (1<<index);
                            ptr = (**pointer[index+1]).one;
                            --index;
                            break;
                        }
                        else ans &= (~(1<<index));
                    }
                    if( index == num_bit ) return ERROR_VALUE;
                    for( ; index != (-1) ; -- index )
                    {
                        if( ptr->zero != nullptr ) ptr = ptr->zero;
                        else
                        {
                            ans += (1<<index);
                            ptr = ptr->one;
                        }
                    }
                    break;
                }
            }
            else
            {
                if( ptr->zero != nullptr )
                {
                    pointer[idx] = (&ptr->zero);
                    ptr = ptr->zero;
                }
                else
                {
                    ptr  = ptr->one;
                    ans += (1<<idx);
                    for( short int index = idx-1; index != (-1); --index )
                    {
                        if( ptr->zero != nullptr ) ptr = ptr->zero;
                        else
                        {
                            ptr = ptr->one;
                            ans += (1<<index);
                        }
                    }
                    break;
                }
            }
        }
        if( ans < val ) return -1;
        return ans;
    }
    type upper_bound( type val )
    {
        return lower_bound(val+1);
    }
    type find_less_or_equal( type val )
    {
        if( root->cnt == 0 ) return ERROR_VALUE;

        val ^= xor_val;
        node ** pointer[num_bit+1];
        node *ptr =  root;
        pointer[num_bit] = &root;

        type ans = 0;
        for( short int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if( ((val>>idx)&1) )
            {
                if( ptr->one != nullptr )
                {
                    ans += (1<<idx);
                    pointer[idx] = (&ptr->one);
                    ptr = ptr->one;
                }
                else
                {
                    ptr  = ptr->zero;
                    for( short int index = idx-1; index != (-1); --index )
                    {
                        if( ptr->one != nullptr )
                        {
                            ptr = ptr->one;
                            ans += (1<<index);
                        }
                        else ptr = ptr->zero;
                    }
                    break;
                }
            }
            else
            {
                if( ptr->zero != nullptr )
                {
                    pointer[idx] = (&ptr->zero);
                    ptr = ptr->zero;
                }
                else
                {
                    short int index;
                    for( index = idx+1; index < num_bit; ++index )
                    {
                        if( ((ans>>index)&1) && (**pointer[index+1]).zero  != nullptr  )
                        {
                            ans -= (1<<index);
                            ptr = (**pointer[index+1]).zero;
                            --index;
                            break;
                        }
                        else ans &= (~(1<<index));
                    }
                    if( index == num_bit ) return ERROR_VALUE;
                    for( ; index != (-1) ; -- index )
                    {
                        if( ptr->one != nullptr )
                        {
                            ptr = ptr->one;
                            ans += (1<<index);
                        }
                        else ptr = ptr->zero;
                    }
                    break;
                }
            }
        }
        if( ans > val ) return -1;
        return ans;
    }
    type find_less( type val )
    {
        if( val == 0 ) { return ERROR_VALUE; }
        else return find_less_or_equal(val-1) ;
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    bitwise_trie<31> trie;
    trie.insert(0);

    char c;
    int val, ans ,q;
    cin >> q;

    while(q--)
    {
        cin >> c >> val;
        if( c == '+' )
        {
            trie.insert(val);
        }
        else if( c == '-' )
        {
            trie.erase(val);
        }
        else
        {
            ans = trie.find_max_xor(val);
            cout << (ans^val) << '\n';
        }
    }
    return 0;
}
/*
link submission : https://codeforces.com/contest/706/submission/182757808
link ideone : https://ideone.com/VGSES7
status : accepted
*/
