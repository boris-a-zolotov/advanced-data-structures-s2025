#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>
#include <ctime>

using namespace std;

vector <pair <int, int>> pts;

void ptsOut () {
    for (auto p : pts) {
        cout << "  \\draw (" << p.first << ", " << p.second << ")\n"
             << "    node[circle,fill=black,inner sep=0.4mm]{}"
             << " node[anchor=south west]{\\((" << p.first << ", "
             << p.second << ")\\)};\n";
    }
}

int xMedian (vector <pair <int, int>> v) {
    vector <pair <int, int>> t;
    copy (v.begin(), v.end(), back_inserter(t));
    sort (t.begin(), t.end(),
          [](auto a, auto b) {return a.first < b.first;});
    
    int l = t.size();  l /= 2;  l -= 1;
    return t[l].first;
}

void vecOut (int x, int y, vector <pair <int, int>> v) {
    int l = v.size();
    cout << "  \\draw (" << x << ", " << y << ") grid ++(" << l <<", 1)"
         << " (" << x+0.5 << ", " << y+0.5 << ")";

    for (auto p : v) {
        cout << "\n    node{\\((" << p.first << ", "
             << p.second << ")\\)} ++(1,0)";
    }

    cout << ";\n";
}

void partition (int x, int y, vector <pair <int, int>> v) {
    
}

int main () {
    vector <int> perm;
    for (int i = 0; i < 16; i++) perm.push_back(i);

    srand(time(0));  mt19937 rng (rand());
    shuffle(perm.begin(), perm.end(), rng);

    for (int i = 0; i < 16; i++) pts.push_back({i, perm[i]});
    sort (pts.begin(), pts.end(),
          [](auto a, auto b) {return a.second < b.second;});

    vecOut (0, 10, pts);

    return 0;
}
