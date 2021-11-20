//
// Created by user on 2021-11-15.
// [백준] 2615번 - 오목
//
//

#include <iostream>
#include <algorithm>
using namespace std;

int board[19][19];
// 구해야 하는 돌은 가장 왼쪽 => 그 돌을 중심으로 아래, 오른쪽, 오른쪽 아래 대각선, 오른쪽 위 대각선 4가지 방향만 검사하면 됨.
int dx[4] = {1, 1, 0, -1};
int dy[4] = {0, 1, 1, 1};
int result;
int nx, ny;

bool inbound(int x, int y) {
    return (x >= 0 && x < 19 && y >= 0 && y < 19);
}

int omok(int x, int y) {
    for (int i = 0; i < 4; i++) { // 상하좌우 방향 탐색
        nx = x + dx[i]; // x 좌표 리셋
        ny = y + dy[i]; // y 좌표 리셋
        int cnt = 1;

        /*if (!inbound(nx, ny)) //범위를 벗어나면 무시
            continue; // 코드 진행 */

        while(inbound(nx, ny)) {
            //if (board[nx][ny] != 1 && board[nx][ny] != 2)
            if (board[nx][ny] == 0)
                break;
            cnt++;
            nx = x + dx[i];
            ny = y + dy[i];
            cout << nx << ' ' << ny << endl;
        }

        if (cnt == 5) {
           // nx -= dx[i];
           // ny -= dy[i];
            return board[nx][ny];
        }

    }
}
int main(void) {
    // 오목판 입력. 검: 1, 흰: 2, 빈: 0
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            cin >> board[i][j];
            cout << omok(i, j) << endl;
            cout << "final " <<  nx << ' ' << ny << endl;
        }
    }
    return 0;
}
