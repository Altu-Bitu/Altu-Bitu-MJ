//
// Created by user on 2021-11-23.
//

#include <iostream>
#include <vector>

using namespace std;

int cntCleanRobot(int r, int c, int d, vector<vector<int>> &board) {
    //상, 우, 하, 좌
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    int step = 0, ans = 0;
    while (true) { //
        if (board[r][c] == 0) { // 빈 칸이라면
            board[r][c] = 2; // 청소했다고 표시
            ans++; // 정답 증가
        }

        if (step == 4) { // 상하좌우 다 살폈다면
            if (board[r - dr[d]][c - dc[d]] == 1) // 청소기가 있는 칸의 상태가 벽이라면
                return ans; // 정답 리턴
            r -= dr[d]; // 방향 변경
            c -= dc[d]; // 방향 변경
            step = 0; // step 0으로 초기화
        } else {
            d = (d + 3) % 4; // 방향 체크
            if (board[r + dr[d]][c + dc[d]]) { // 로봇이 바라보는 방향이 빈 칸이 아니라면
                step++; // step 증가하고
                continue; // 반복
            }
            r += dr[d]; // 북 -> 남
            c += dc[d]; // 동 -> 서 순서
            step = 0; // step 0으로 초기화
        }
    }
}

/**
 * board 정보 -> 0: 빈 칸, 1: 벽, 2: 청소한 공간
 * step: 회전 카운트. 4가 되면 한 바퀴 돌아 다시 제자리로 돌아왔음을 의미
 *
 * 항상 첫 행, 마지막 행, 첫 열, 마지막 열은 벽이라고 문제에서 주어졌으므로 범위 검사를 할 필요가 없음
 */

int main() {
    int n, m, r, c, d;

    //입력
    cin >> n >> m >> r >> c >> d;
    // n: 세로, m: 가로, r, c: 로봇청소기의 좌표, d: 로봇이 바라보는 방향
    vector<vector<int>> board(n, vector<int>(m, 0)); // 주어진 크기의 보드판 만들기
    for (int i = 0; i < n; i++) { // 세로
        for (int j = 0; j < m; j++) { // 가로
            cin >> board[i][j]; // 장소의 상태, 북->남, 서->동 순서. 0: 빈 칸, 1: 벽
        }
    }

    //연산 & 출력
    cout << cntCleanRobot(r, c, d, board);
    return 0;
}