//
// Created by user on 2021-11-16.
//

#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 19;

//범위와 돌의 종류가 유효한지 확인
bool promising(int r, int c, int stone, vector<vector<int>> &board) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == stone;
    // r과 c가 모두 오목판의 범위 내에 있고, 보드 값이 stone 값과 같을 때만 true 반환
}
// 육목 아니고, 확실히 이겼는지 확인하는 함수
bool validDir(int r, int c, int d, int stone, vector<vector<int>> &board) {
    // 구해야 하는 돌은 가장 왼쪽 => 가로, 세로, 우하향 대각선, 우상향 대각선
    int dr[4] = {0, 1, 1, -1}; // row 값
    int dc[4] = {1, 0, 1, 1}; // col 값

    //(r, c) 이전에 위치한 이어지는 돌이 있나? => (r, c) 왼쪽 방향
    bool is_six = promising(r - dr[d], c - dc[d], stone, board);

    int cnt = 0; // 돌이 연속하는 횟수
    while (cnt < 6 && promising(r, c, stone, board)) { //(r, c)를 가장 왼쪽으로 하는 이어지는 바둑알의 개수
        cnt++; // 연속 횟수 추가
        r += dr[d]; // r값 갱신
        c += dc[d]; // c값 갱신
    }
    return cnt == 5 && !is_six; // 오목이고, 육목이 아닐 경우 true 반환
}
// 이겼는지 판단하는 함수
bool isEnd(int r, int c, vector<vector<int>> &board) {
    for (int i = 0; i < 4; i++) { //가로, 세로, 우하향 대각선, 우상향 대각선
        if (validDir(r, c, i, board[r][c], board)) // true반환하면 이긴거임
            return true; // 이겼으니 true
    }
    return false; // 이기지 않음
}

/**
 * 1. 특정 좌표(r, c)를 가장 왼쪽으로 하는 가능한 모든 오목 배치에 대해 오목 여부 확인
 *    가능한 모든 배치 :  오른쪽, 아래, 우하향, 우상향
 * 2. 육목이상이 되는 경우 : (r, c) 왼쪽에 같은 돌이 있는 경우
 */
int main() {
    // 보드판 생성
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));

    //입력
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            // 오목판 입력. 검: 1, 흰: 2, 빈: 0
            cin >> board[i][j];
    }

    //연산 & 출력
    for (int i = 0; i < SIZE; i++) { // 오목판크기만큼 돌면서
        for (int j = 0; j < SIZE; j++) {
            if (!board[i][j]) //돌이 없음 (board값 == 0일때)
                continue;
            if (isEnd(i, j, board)) { //누군가 이겼나?
                cout << board[i][j] << '\n' << i + 1 << ' ' << j + 1;
                // 이겼다면 돌의 색 출력하고 i와 j가 0부터 시작하니까 둘에다가 1을 더한 값을 출력한다.
                return 0;
            }
        }
    }
    cout << 0;
}
