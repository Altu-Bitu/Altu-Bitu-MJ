//
// Created by user on 2021-11-01.\
// 211015 - DFS & BFS
// [백준] 1697 - 숨바꼭질
// 수빈이가 n초에 위치 x에 있었다면 n+1초에는 x-1, x+1, x*2에 위치할 수 있다.

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, K; // N: 수빈이 시작 위치, K: 동생 시작 위치
int visited[100000 + 1]; // visited : 인덱스별 몇 초에 방문했는지
queue<int> q;
int bfs() {
    q.push(N);
    // int index = N;
    int time = 0;
    visited[N] = 1;
    while(!q.empty()) {
        int N = q.front();
        q.pop();
        if (N == K)
            return time;
        if(N > 0 && visited[N - 1] == 0) {
            q.push(N - 1);
            visited[N - 1] = visited[N] + 1;
        }
        if (N < 100000 && visited[N + 1] == 0) {
            q.push(N + 1);
            visited[N + 1] = visited[N] + 1;
        }
        if (N * 2 <= 100000 && visited[N * 2] == 0) {
            q.push(N * 2);
            visited[N * 2] = visited[N] + 1;
        }
        time++;
    }

    return time;
}
int main(void) {

    cin >> N >> K;
    cout << bfs() << endl;
    return 0;
}