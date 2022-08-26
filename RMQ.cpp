#include <bits/stdc++.h>

using namespace std;
ifstream fin("f.in");
ofstream fout("f.out");
    //rmq
    // rmq[i][j] - minimul care incepe pe pozitia i si are lungimea 2 ^ j
    int n, m;
    int lg[100003];
    int rmq[100003][18];
    void read(){
        fin >> n >> m;
        for(int i = 2;  i <= n; ++i)
            lg[i] = 1 + lg[i / 2];
        for(int i = 0; i < n; ++i)
            fin >> rmq[i][0];

    }
    void preprocess(){
        for(int j = 1; j <= lg[n]; ++j) // lungimi de 2 ^ j
            for(int i = 0; i + (1 << j) - 1 < n; ++i)
                rmq[i][j] = min(rmq[i + (1 << (j - 1))][j - 1], rmq[i][j - 1]);
    }
    void query(){
        int l, r;
        for(int i = 1; i <= m; ++i){
            fin >> l >> r;
            l --, r -- ;
            int len = lg[r - l + 1];
            //cout << len << " ";
            fout << min(rmq[l][len], rmq[r - (1 << len) + 1][len]) << "\n";
        }
    }

int main(){
    read();
    preprocess();
    query();
    return 0;
}