#include<bits/stdc++.h>
using namespace std;

vector<string>save = {
                     "size", "clear","print","min","max","insert","find_max_xor","find_by_order",
                     "order_of_key","erase","lower_bound","upper_bound",
                     "find_less_or_equal","find_less"
                     };

inline int rand_val( int left, int right )
{
    return ( left + ( (rand()^rand())%(right-left+1) ) );
}


clock_t time_in,time_out;
long double time_brute_force, time_your_code;

ifstream inp;
ofstream out;

string input_file             = "input.INP";
string your_output            = "output.OUT";
string brute_force_output     = "output.ANS";
string your_file_name         = "test1";
string brute_force_file_name  = "test2";

void rand_test( const string & input_file_for_two_exe )
{
    out.open( input_file_for_two_exe.c_str() );

    int q = rand_val(8000,static_cast<int>(1e5)),f;
    out << q <<endl;

    while(q--)
    {
        f = rand_val(0,save.size()-1);
        if(  f >=  5 && f <= 13 )
        {
            out <<save[f] << " "<< rand_val(0,1111) <<endl;
        }
        else
        {
            if( f == 1 )
            {
                if( rand_val(0,26) == 0 ) out << save[f] <<endl;
                else
                {
                    q++;
                    continue;
                }
            }
            else out << save[f] <<endl;
        }
    }
}
void clear_input_output()
{
    inp.clear();
    inp.close();
    out.clear();
    out.close();
}
void compare_ans2( const string & your_exe, const string & your_output , const string & brute_force_exe , const string & brute_force_output )
{
    system( (your_exe+".exe").c_str() );
	system( (brute_force_exe+".exe").c_str() );

	string str = ("fc "+your_output+" "+brute_force_output);
	if( system( str.c_str() ) != 0 )
	{
		cout <<" WRONG ANS ";
		exit(0);
	}
	else  cout <<" ACCEPTED THIS TEST "<<endl<<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));

     int num_test = 100;
//    cout << num_test <<endl;

    while(num_test--)
    {
        rand_test(input_file);
        compare_ans2(your_file_name,your_output,brute_force_file_name,brute_force_output);
        clear_input_output();
    }
    return  0;

}
