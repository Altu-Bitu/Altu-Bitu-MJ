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
    visited[N] = 1; // 시작 위치에는 당연히 방문 했으니까 1로 초기화
    while(!q.empty()) {
        int N = q.front(); // 반복문 돌면서 수빈이의 위치 갱신
        q.pop();
        time = visited[N] - 1; // 걸린 시간은 수빈이의 위치의 값(visited[N]의 초기값이 1이었기 때문에 1 빼준다.)
        if (N == K) // 동생과 같은 위치에 도착했다면
            return time; // 걸린 시간 반환
        if(N > 0 && visited[N - 1] == 0) { // 만약 이전 칸으로 이동했고, 그 칸에 방문한 적이 없다면 (N - 1)이 음수가 될 수 없기 때문에 양수여야 한다.
            q.push(N - 1); // 큐에  추가
            visited[N - 1] = visited[N] + 1; // 해당 위치 방문 시간 기록
        }
        if (N < 100000 && visited[N + 1] == 0) { // 만약 이후 칸으로 이동했고, 그 칸에 방문한 적이 없다면  (N + 1이 최대값을 넘어갈 수 없기 때문에 제한 설정_
            q.push(N + 1); // 큐에 추가
            visited[N + 1] = visited[N] + 1; // 해당 위치 방문 시간 기록
        }
        if (N * 2 <= 100000 && visited[N * 2] == 0) { // 만약 순간이동을 했고, 그 칸에 방문한 적이 없다면  (마찬가지로 위치 범위 제한)
            q.push(N * 2); // 큐에 추가
            visited[N * 2] = visited[N] + 1; // 해당 위치에 방문한 시간 기록
        }
    }

    return time;
}
int main(void) {

    cin >> N >> K;
    cout << bfs() << endl;
    return 0;
}