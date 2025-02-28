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
        cout << "  \\draw (" << p.first << ", " << p.second
             << ") \\nvs{" << p.first << "}{" << p.second
             << "} node[circle,fill=black,inner sep=0.4mm]{};\n";
    }
}


int xMedian (vector <pair <int, int>> v) {
    vector <pair <int, int>> t;
    copy (v.begin(), v.end(), back_inserter(t));
    sort (t.begin(), t.end(), [](auto a, auto b) {return a.first < b.first;});

    int l = t.size();  l /= 2;  l -= 1;
    return t[l].first;
}


void vecOut (float x, float y, vector <pair <int, int>> v) {
    int l = v.size();

    if (l==1) {
        cout << "  \\draw (" << x << ", " << y << ") rectangle ++(1, 1)";
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

    int xSplit = xMedian (v);
    vector <pair <int, int>> v1;  vector <pair <int, int>> v2;

    copy_if (v.begin(), v.end(), back_inserter(v1),
             [xSplit](auto p) {return p.first <= xSplit;});
    copy_if (v.begin(), v.end(), back_inserter(v2),
             [xSplit](auto p) {return p.first >  xSplit;});

    float tab = (float)l / 2;  float ofs = (float)l / 4;
    int l1 = v1.size();  int l2 = v2.size();  int j1 = 0;  int j2 = 0;

    for (int j=0; j < l; j++) {
        while (v1[j1].second < v[j].second && j1 < l1) {j1++;}
        while (v2[j2].second < v[j].second && j2 < l2) {j2++;}

        float x1out = x + j + 0.3;  float x2out = x + j + 0.7;
        float x1in = x - ofs + j1 + 0.5;  float x2in = x + tab + ofs + j2 + 0.5;

        if (j1 == l1) {
            cout << "  \\draw[very thick] (" << x1out << ", " << y << ") -- ++(0, -0.5) \\ns;\n";
        } else {
            cout << "  \\draw[very thick] (" << x1out << ", " << y << ") .. controls ("
                 << x1out << ", " << y-1 << ") and (" << x1in << ", " << y-1 << ") .. ("
                 << x1in << ", " << y-2 << ");\n";
        }

        if (j2 == l2) {
            cout << "  \\draw (" << x+j+0.7 << ", " << y << ") -- ++(0, -0.5) \\ns;\n";
        } else {
            cout << "  \\draw (" << x2out << ", " << y << ") .. controls ("
            << x2out << ", " << y-1 << ") and (" << x2in << ", " << y-1 << ") .. ("
            << x2in << ", " << y-2 << ");\n";
        }
    }

    rngOut (x-ofs, y-3, v1);  rngOut (x+tab+ofs, y-3, v2);
}


int main () {
    vector <int> perm;
    for (int i = 0; i < 16; i++) perm.push_back(i);

    srand(time(0));  mt19937 g (rand());
    shuffle(perm.begin(), perm.end(), g);

    for (int i = 0; i < 16; i++) pts.push_back({i, perm[i]});
    sort (pts.begin(), pts.end(), [](auto a, auto b) {return a.second < b.second;});

    ptsOut ();  cout << "\n\n\n\n";  rngOut (0, 0, pts);
    return 0;
}
