//
// Created by user on 2021-12-21.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int INF = 1e9;

int dr[4] = {-1, 1, 0, 0}; // row
int dc[4] = {0, 0, -1, 1}; // col
// 순서대로 상, 하, 좌, 우

struct status { //행, 열, 방향, 비용
    int r, c, dir, cost;
};

int bfs(int n, vector<vector<int>> board) {
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(n, vector<int>(4, INF))); // 거리 저장
    queue<status> q; // 구조체 status의 형태를 가진 큐 생성

    //시작점 초기화 (시작점은 모든 방향일 수 있음)
    for (int i = 0; i < 4; i++) { // 방향 4개
        dist[0][0][i] = 0; // 거리는 0
        q.push({0, 0, i, 0}); // 초기값: 행, 열, 비용은 0
    }

    while (!q.empty()) { // 큐가 비어있지 않은 동안
        int row = q.front().r; // 행
        int col = q.front().c; // 열
        int dir = q.front().dir; // 방향
        int cost = q.front().cost; // 비용
        q.pop(); // 값을 저장한 큐의 요소는 pop

        for (int i = 0; i < 4; i++) { // 모든 방향에 대해
            int nr = row + dr[i]; // row 업데이트
            int nc = col + dc[i]; // col 업데이트
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || board[nr][nc]) // 방향이 보드 범위 내에 있지 않다면
                continue; // pass
            int nw = i == dir ? cost + 100 : cost + 600; //방향에 따른 비용
            if (nw < dist[nr][nc][i]) { //더 적은 비용으로 경주로를 건설할 수 있다면
                dist[nr][nc][i] = nw; // 더 적은 비용으로 업데이트 후
                q.push({nr, nc, i, nw}); // 해당 위치와 방향, 비용을 가진 값을 큐에 추가
            }
        }
    }
    int min_cost = INF; // 최소 비용 가장 큰 정수값으로 초기화
    for (int i = 0; i < 4; i++) //4개의 방향 중 가장 작은 값
        min_cost = min(min_cost, dist[n - 1][n - 1][i]); // 최소비용 업데이트
    return min_cost; // 최소비용 반환
}

int solution(vector<vector<int>> board) { // 정답 계산
    return bfs(board.size(), board); // 입력한 보드의 크기와 보드에 대해 bfs실행한 값 리턴
}

/**
 * 문제: https://programmers.co.kr/learn/courses/30/lessons/67259
 * 하나의 좌표에 대해 자동차는 4개의 방향을 통해 진입할 수 있음.
 * (행, 열) 정보만 저장했던 기존의 방식과 달리 (행, 열, 방향) 정보까지 저장! -> 3차원 배열
 * 배열에 저장되는 값은 해당 좌표와 방향으로 건설할 수 있는 경주로 중 가장 비용이 저렴한 것
 * !주의! 시작점은 방향이 따로 없으므로 초기화시 모든 방향에 대해 정보를 입력함
 *
 * 방향에 따른 비용에 차이를 두며 구현
 * 공식 풀이 : https://tech.kakao.com/2020/07/01/2020-internship-test/
 */
int main() {
    // 첫번째 입력 예
    vector<vector<int>> board = {{0, 0, 0},
                                 {0, 0, 0},
                                 {0, 0, 0}};
    cout << solution(board); // 첫번째 출력
}