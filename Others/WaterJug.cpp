#include<bits/stdc++.h>
using namespace std;
using namespace chrono;
#define int long long           
const int mod=1e9+7;
const int INF = 1e18;

/*
Problem Statement :-
You are given with 2 Jugs, 4 Gallon and a 3 Gallon one. 
Neither of the jugs has any Measuring marks on it. 
There is a pump that can be used to fill the jugs with water. 
How can we get exactly 2 Gallons of water in 4 Gallon Jug?

Rules :-
1.Fill the first jug to its capacity.
2.Fill the second jug to its capacity.
3.Empty the first jug.
4.Empty the second jug.
5.Pour water from the first jug to the second jug until either the first jug is empty or the second jug is full.
6.Pour water from the second jug to the first jug until either the first jug is full or the second jug is empty.
*/



void printpath(map<pair<int,int>, pair<int,int>> mp, pair<int,int> u)
{
        if (u.first == 0 && u.second == 0)
        {
                cout << 0 << " " << 0 << endl;
                return;
        }
        printpath(mp, mp[u]);
        cout << u.first << " " << u.second << endl;
}
 

void solve(){

        int jug1, jug2, target;
        cin>>jug1>>jug2>>target;

        auto bfs = [&](int a, int b, int target) -> void {


                map<pair<int,int>, int> m; //Mark visited states
                bool isSolvable = false;
                map<pair<int,int>, pair<int,int>> mp; //For printing path

                queue<pair<int,int>> q;

                q.push(make_pair(0, 0));
                while (!q.empty())
                {
                        auto u = q.front();
                        q.pop();


                        if (m[u] == 1)
                                continue;

                        if ((u.first > a || u.second > b || u.first < 0 || u.second < 0))
                                continue;

                        m[{u.first, u.second}] = 1;

                        if (u.first == target || u.second == target)
                        {
                                isSolvable = true;
                                printpath(mp, u);
                                if (u.first == target)
                                {
                                        if (u.second != 0)
                                                cout << u.first << " " << 0 << endl;
                                }
                                else
                                {
                                        if (u.first != 0)
                                                cout << 0 << " " << u.second << endl;
                                }
                                return;
                        }

                        // Fill 1st Jug
                        if (m[{a, u.second}] != 1)
                        {
                                q.push({a, u.second});
                                mp[{a, u.second}] = u;
                        }

                        // Fill 2nd Jug
                        if (m[{u.first, b}] != 1)
                        {
                                q.push({u.first, b});
                                mp[{u.first, b}] = u;
                        }

                        // Empty 1st Jug
                        if (m[{0, u.second}] != 1)
                        {
                                q.push({0, u.second});
                                mp[{0, u.second}] = u;
                        }

                        // Empty 2nd Jug
                        if (m[{u.first, 0}] != 1)
                        {
                                q.push({u.first, 0});
                                mp[{u.first, 0}] = u;
                        }

                        // Pour from 1st jug to 2nd until it's full
                        int d = b - u.second;
                        if (u.first >= d)
                        {
                                int c = u.first - d;
                                if (m[{c, b}] != 1)
                                {
                                        q.push({c, b});
                                        mp[{c, b}] = u;
                                }
                        }
                        else
                        {
                                int c = u.first + u.second;
                                if (m[{0, c}] != 1)
                                {
                                        q.push({0, c});
                                        mp[{0, c}] = u;
                                }
                        }

                        // Pour from 2nd jug to 1st until it's full
                        d = a - u.first;
                        if (u.second >= d)
                        {
                                int c = u.second - d;
                                if (m[{a, c}] != 1)
                                {
                                        q.push({a, c});
                                        mp[{a, c}] = u;
                                }
                        }
                        else
                        {
                                int c = u.first + u.second;
                                if (m[{c, 0}] != 1)
                                {
                                        q.push({c, 0});
                                        mp[{c, 0}] = u;
                                }
                        }
                }
                if (!isSolvable)
                        cout << "No solution";
                        
                
        } ;

        bfs(jug1, jug2, target);
 
}

signed main(){

        
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        auto start1 = high_resolution_clock::now();

        int t;
        t=1;
        // cin >> t;
        // Hetu ka laptop
        
        while (t--) {
                solve();   
        }
        

        auto stop1 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop1 - start1);
        cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
        return 0;

}