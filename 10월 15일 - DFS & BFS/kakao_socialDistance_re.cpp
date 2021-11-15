//
// Created by user on 2021-11-02.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
const int SIZE = 5;

//특정 응시자에 대해 거리두기가 지켜지는지 확인
bool bfs(vector<string> &place, int row, int col) {
    //상, 하, 좌, 우
    int dr[4] = {-1, 1, 0, 0}; // 상 하 (row)
    int dc[4] = {0, 0, -1, 1}; // 좌 우 (col)

    vector<vector<int>> dist(SIZE, vector<int>(SIZE, 0)); //방문 여부, 각 정점까지의 맨허튼 거리
    queue<pair<int, int>> q;

    dist[row][col] = 1; //초기값이 0이기 때문에 1로 초기화
    q.push(make_pair(row, col)); // row, col값 큐에 추가

    while (!q.empty()) { // 큐에 원소가 있는동안 반복
        int cr = q.front().first; // row값은 큐의 첫번째 원소의 첫번째 값
        int cc = q.front().second; // col: 큐의 첫번째 원소의 두번째 값
        q.pop(); // row와 col값 저장했으니 큐에서 빼준다.

        if (dist[cr][cc] == 3) //맨허튼 거리 2이하까지만 탐색
            continue;

        for (int i = 0; i < 4; i++) { // 상하좌우 방향 탐색
            int nr = cr + dr[i]; // 상 하로 이동하며 row 좌표 재설정
            int nc = cc + dc[i]; // 좌 우로 이동하며 col 좌표 재설정

            //범위를 벗어나거나, 방문했거나, 파티션이 있음
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE || dist[nr][nc] || place[nr][nc] == 'X')
                continue;
            if (place[nr][nc] == 'P') //응시자가 있으면 거리두기 지키지 못함
                return false;
            dist[nr][nc] = dist[cr][cc] + 1; // 맨해튼 거리 추가
            q.push(make_pair(nr, nc)); // 값 추가
        }
    }
    return true; //거리두기 지킴
}

//특정 대기실에 대해 거리두기가 지켜지는지 확인
bool socialDistance(vector<string> &place) {
    for (int i = 0; i < SIZE; i++) { // 5X5 크기 대기실에 있는 응시자에 대해
        for (int j = 0; j < SIZE; j++) {
            //응시자가 있다면, 거리두기 확인
            if (place[i][j] == 'P' && !bfs(place, i, j))
                return false; // 응시자 있는데 거리두기 안 지켰으면 false 반환
        }
    }
    return true; // 나머지는 true
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer; // 정답 저장할 벡터
    for (int i = 0; i < SIZE; i++) // 대기실 5개에 대해
        answer.push_back(socialDistance(places[i])); // 각 대기실에 대해 거리두기 지켜졌는지 여부 추가하고
    return answer; // answer 반환
}

/**
 * 맨허튼 거리가 2이하 == BFS 또는 DFS 했을 때의 거리가 2이하
 *
 * 각 대기실의 모든 응시자에 대해 거리두기를 지키고 있는지 확인
 * 5x5 크기의 대기실 5개이기 때문에 모든 응시자에 대해 bfs 또는 dfs를 수행해도 시간 초과 발생하지 않음
 */
int main() {
    // places 원소의 길이: 5, P: 응시자, O: 빈 테이블, X: 파티션
    vector<vector<string>> places = {{"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
                                     {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
                                     {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
                                     {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
                                     {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}}; // 각 행은 하나의 대기실 구조
    vector<int> ans = solution(places); // 대기실당 거리두기 지키는지 여부 저장할 벡터
    for (int i = 0; i < SIZE; i++)
        cout << ans[i] << ' '; // 각 대기실당 거리두기를 잘 지켰다면 1, 못 지켰다면 0
}