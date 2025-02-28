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

void vecOut (float x, float y, vector <pair <int, int>> v) {
    int l = v.size();

    if (l==1) {
        cout << "  \\draw (" << x << ", " << y << ") rectangle ++(1,1)";
    } else {
        cout << "  \\draw (" << x << ", " << y << ") grid ++(" << l <<", 1)";
    }
    cout << " (" << x+0.5 << ", " << y+0.5 << ")";

    for (auto p : v) {
        cout << "\n    node{\\vs{" << p.first << "}{"
             << p.second << "}} ++(1,0)";
    }

    cout << ";\n";
}

void rngOut (float x, float y, vector <pair <int, int>> v) {
    vecOut (x, y, v);  int l = v.size();  if (l==1) return;
    float tab = (float)l / 2;  float ofs = (float)l / 4;
    
    int xSplit = xMedian (v);
    vector <pair <int, int>> v1;  vector <pair <int, int>> v2;

    copy_if (v.begin(), v.end(), std::back_inserter(v1),
             [xSplit](auto p) {return (p.first <= xSplit);});
    copy_if (v.begin(), v.end(), std::back_inserter(v2),
             [xSplit](auto p) {return (p.first > xSplit);});

    rngOut (x-ofs, y-2, v1); 
    rngOut (x+tab+ofs, y-2, v2);
}

int main () {
    vector <int> perm;
    for (int i = 0; i < 16; i++) perm.push_back(i);

    srand(time(0));  mt19937 rng (rand());
    shuffle(perm.begin(), perm.end(), rng);

    for (int i = 0; i < 16; i++) pts.push_back({i, perm[i]});
    sort (pts.begin(), pts.end(), [](auto a, auto b) {return a.second < b.second;});

    rngOut (0, 0, pts);

    return 0;
}
