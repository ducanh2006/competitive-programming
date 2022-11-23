#include<bits/stdc++.h>
using namespace std;
template< const int num_bit , class type >
class bitwise_trie
{
private :
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
    void ____clear_trie( node *ptr )
    {
        if( ptr->zero != nullptr ) ____clear_trie( ptr->zero );
        if( ptr->one  != nullptr  ) ____clear_trie( ptr->one );
        delete(ptr);
        ptr = nullptr;
    }
    void ___remove_val(  const type & val  )
    {
        node ** pointer[num_bit];
        node *ptr = root;
        for( short int idx = num_bit-1; idx != (-1) ; --idx )
        {
            if(  ((val>>idx)&1) )
            {
                pointer[idx] = &(ptr->one);
                ptr = ptr->one;
            }
            else
            {
                pointer[idx] = &(ptr->zero);
                ptr = ptr->zero;
            }
            --(**pointer[idx]).cnt;
        }
        for( short idx = 0; idx < num_bit ; ++idx )
        {
            if( (**pointer[idx]).cnt == 0 )
            {
                delete ( *pointer[idx] );
                *pointer[idx] = nullptr;
            }
        }
        --root->cnt;
    }
    void ____print_trie( node *ptr  , type val , int depth, vector<type>&save )
    {
        if( depth == (-1) )
        {
            save.push_back(val);
            return;
        }
        if( ptr->one != nullptr )  ____print_trie( ptr->one , val + (1<<depth) , depth -1 , save  );
        if( ptr->zero != nullptr ) ____print_trie( ptr->zero, val , depth -1, save );
    }
    node *root;
    type xor_val;


public :
    bitwise_trie(){assert( num_bit > 0 );xor_val = 0; root = new(node);}
    void xor_all_value( const type & val ){ xor_val ^= val; }
    type size(){ return root->cnt; }
    void clear()
    {
        ____clear_trie(root);
        root = new(node);
        xor_val = 0;
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
    void print()
    {
        vector<type>save;
        ____print_trie(root,0,num_bit-1,save);
        for( type & i : save ) i ^= xor_val;
        sort( save.begin(), save.end() );
        for( type & i : save )cout << i <<" ";
    }

    type find_max_xor( type val )
    {
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
        if( k_th > root->cnt || k_th <= 0 ) return -1;

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
    type count_frequency( type val )
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
    bool erase( const type & val , bool exist )
    {
        if( root->cnt == 0 ) return false;
        type val_after_xor = (val^xor_val);
        if( exist )
        {
            ___remove_val( val_after_xor );
            return true;
        }
        else
        {
            int freq = count_frequency(val);
            if( freq == 0 ) return false;
            else
            {
                ___remove_val( val_after_xor );
                return true;
            }
        }
    }
};
int main()
{

}
