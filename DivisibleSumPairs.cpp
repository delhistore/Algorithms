// Q. Given size of array n and a number k, iterate through array and return number of pair
// elements whose sum is equal to k.

"""
The idea is that you separate elements into buckets depending on their mod k. For example, you have the elements: 1 3 2 6 4 5 9 and k = 3

mod 3 == 0 : 3 6 9
mod 3 == 1 : 1 4
mod 3 == 2 : 2 5
Now, you can make pairs like so: Elements with mod 3 == 0 will match with elements with (3 - 0) mod k = 0, so other elements in the mod 3 == 0 list, like so:

(3, 6) (3, 9) (6, 9)
There will be n * (n - 1) / 2 such pairs, where n is length of the list, because the list is the same and i != j. Elements with mod 3 == 1 will match with elements with (3 - 1) mod k = 2, so elements in the mod 3 == 2 list, like so:

(1, 2) (1, 5) (4, 2) (4, 5)
There will be n * k such elements, where n is the length of the first list, and k of the second.

Because you don't need to print the actual pairs, you need to store only the number of elements in each list.
"""

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the divisibleSumPairs function below.
int divisibleSumPairs(int n, int k, vector<int> ar) {
    
    vector<int> helper;
    for(int i =0; i<k; i++) {
        helper.push_back(0);
    }
    
    for(int i =0; i<ar.size(); i++) {
        int rem = ar[i]%k;
        helper[rem]++;
    }
    
    int ans = 0;
    
    // nC2 ways of selecting 2 multiples of k
    ans += helper[0] * (helper[0]-1) / 2;
    
    // helper[i] * helper[j] ways that rems will add up to k
    for(int i =1, j=(k-1) ; i<=j; i++,j--) {
        if(i==j) {
            ans += helper[i] * (helper[i]-1) / 2;
            continue;
        }
        ans += helper[i] * helper[j];
    }
    
    return ans;
    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string ar_temp_temp;
    getline(cin, ar_temp_temp);

    vector<string> ar_temp = split_string(ar_temp_temp);

    vector<int> ar(n);

    for (int i = 0; i < n; i++) {
        int ar_item = stoi(ar_temp[i]);

        ar[i] = ar_item;
    }

    int result = divisibleSumPairs(n, k, ar);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
