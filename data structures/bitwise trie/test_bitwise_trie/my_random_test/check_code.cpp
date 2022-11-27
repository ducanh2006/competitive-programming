#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.INP","r",stdin);
    freopen("output.ANS","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q,val,ans;
    string str;
    list<int>a;

    cin >> q;

    while(q--)
    {
        cin >> str;
        if( str == "size" ) cout << a.size() <<endl;
        else if( str == "clear" ) a.clear();
        else if( str == "insert" )
        {
            cin >> val;
            a.push_back(val);
        }
        else if( str == "print" )
        {
            if( a.size() == 0 ) continue;
            a.sort();
            for( auto i : a ) cout << i <<" ";
            cout <<endl;
        }
        else if( str == "find_max_xor" )
        {
            cin >> val;
            ans = -1;
            for( auto i : a ) ans = max( ans, (i^val) );
            cout << ans <<endl;
        }
        else if( str == "find_by_order" )
        {
            a.sort();
            cin >> val;
            ans = -1;
            for( auto i : a )
            {
                val--;
                if( val == 0 )
                {
                    ans = i;
                    break;
                }
            }
            cout << ans<< endl;
        }
        else if( str == "count" )
        {
            cin >> val;
            ans = 0;
            for( auto i : a ) ans += (i==val);
            cout << ans << endl;
        }
        else if ( str == "order_of_key" )
        {
            cin >> val;
            ans = 0;
            for( auto i : a ) ans += (i<val);
            cout << ans << endl;
        }
        else if( str == "erase" )
        {
            cin >> val;
            for( auto i = a.begin() ; i != a.end() ; )
            {
                if( (*i) == val )
                {
                    i = a.erase(i);
                    break;
                }
                else i++;
            }
        }
        else if( str == "lower_bound" )
        {
            cin >> val;
            ans = INT_MAX;
            for( auto i : a )
            {
                if( i >= val  )
                {
                    ans = min( ans , i );
                }
            }
            if( ans == INT_MAX ) cout << -1 <<endl;
            else cout << ans <<endl;
        }
        else if( str == "upper_bound" )
        {
            cin >> val;
            ans = INT_MAX;
            for( auto i : a )
            {
                if( i > val  )
                {
                    ans = min( ans , i );
                }
            }
            if( ans == INT_MAX ) cout << -1 <<endl;
            else cout << ans <<endl;
        }
        else if( str == "find_less_or_equal" )
        {
            cin >> val;
            ans = INT_MIN;
            for( auto i : a )
            {
                if( i <= val   )
                {
                    ans = max( ans , i );
                }
            }
            if( ans == INT_MIN ) cout << -1 <<endl;
            else cout << ans <<endl;
        }
        else if( str == "find_less" )
        {
            cin >> val;
            ans = INT_MIN;
            for( auto i : a )
            {
                if( i < val )
                {
                    ans = max( ans , i );
                }
            }
            if( ans == INT_MIN ) cout << -1 <<endl;
            else cout << ans <<endl;
        }
        else if ( str == "min" )
        {
            ans = INT_MAX;
            for( auto i : a ) ans = min( ans ,i );
            if( ans == INT_MAX ) cout << -1 <<endl;
            else cout << ans<< endl;
        }
        else if( str == "max" )
        {
            ans = INT_MIN;
            for( auto i : a ) ans = max( ans ,i );
            if( ans == INT_MIN ) cout << -1 <<endl;
            else cout << ans<< endl;
        }
    }
}
