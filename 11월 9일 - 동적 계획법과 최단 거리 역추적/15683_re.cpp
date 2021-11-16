//
// Created by user on 2021-11-16.
//

#include <iostream>
#include <vector>

using namespace std;

int n, m, ans = 65; // n: 세로 개수, m: 가로 개수
vector<vector<int>> board; // 사무실 상태 표시할 보드

//cctv 범위 표시(체크)
void ray(int row, int col, int dir) {
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    // (r, c): (-1, 0): 상
    //         (0, 1): 우
    //         (1, 0): 하
    //         (0, -1): 좌
    while (row >= 0 && row < n && col >= 0 && col < m && board[row][col] != 6) { //dir 방향으로 뻗어나가며 cctv 표시
        if (board[row][col] == 0) //다른 cctv를 지우지 않기 위해 빈 공간일 때만 표시
            board[row][col] = 7; // 범위를 벗어나거나 벽을 만나면 visited 표시(여기선 7)
        row += dr[dir]; // row 갱신
        col += dc[dir]; // col 갱신
    }
}

//cctv 방향 지정
void install(int cctv, int row, int col, int dir) {
    // dir == 1일 경우 예시(블로그 참고)
    if (cctv >= 1) //1, 2, 3, 4, 5번 cctv
        ray(row, col, dir); // 위
    if (cctv >= 2 && cctv != 3) //2, 4, 5번 cctv
        ray(row, col, (dir + 2) % 4); // 위 아래
    if (cctv >= 3) //3, 4, 5번 cctv
        ray(row, col, (dir + 1) % 4); // 우측 추가
    if (cctv == 5) //5번 cctv
        ray(row, col, (dir + 3) % 4); // 좌측 추가
}

//사각지대 계산
int blindSpot() {
    int cnt = 0;
    for (int i = 0; i < n; i++) { // 모든 cctv 배치
        for (int j = 0; j < m; j++) {
            if (!board[i][j]) // board[i][j] == 0인 경우
                cnt++; // cnt 증가
        }
    }
    return cnt; // 사각지대 리턴
}

void backtracking(int idx) { // 백트래킹 함수
    if (idx == n * m) { //기저 조건 : 사무실의 모든 위치 확인
        ans = min(ans, blindSpot()); //사각지대 계산 후 최솟값 갱신
        return; // 함수 종료
    }
    // idx != n * m
    int row = idx / m;  // row값 초기화
    int col = idx % m; // col값 초기화
    int cur = board[row][col]; // 이번에 설치할 cctv
    if (cur == 0 || cur == 6 || cur == 7) //cctv가 없는 곳
        return backtracking(idx + 1); // 재귀 호출

    vector<vector<int>> save = board; //unvisited 처리용 board 상태 저장
    for (int i = 0; i < 4; i++) { //4개의 방향에 대해 cctv 설치
        install(cur, row, col, i); // visited 처리
        backtracking(idx + 1); // 재귀 호출
        board = save; // unvisited 처리

        //2번 cctv의 방향 종류는 2개, 5번 cctv의 방향 종류는 1개
        if ((cur == 2 && i == 1) || (cur == 5 && i == 0))
            break; // 체크 후 backtracking 종료
    }
}

/**
 * cctv가 설치될 수 있는 모든 경우를 고려하는 완전탐색 문제
 *
 * 1. 각 cctv에 대해 가능한 모든 방향을 고려하여 설치
 *    1, 3, 4번 cctv : 4방향
 *    2번 cctv : 2방향
 *    5번 cctv : 1방향
 * 2. install 함수에서 각 cctv의 빛이 뻗어나갈 방향을 잡음
 * 3. ray 함수에서 cctv의 감시 가능 범위 표시
 * 4. 모든 위치를 확인했으면 blindSpot 함수를 통해 사각지대 계산
 *
 * 풀이 : https://myunji.tistory.com/411
 * 해당 코드는 위 링크의 코드를 리팩토링한 코드입니다.
 * 말로는 풀이를 설명하기 어려우니 링크를 꼭 확인해주세요!
 */
int main() {
    //입력
    cin >> n >> m; // 사무실의 세로와 가로 입력받기
    board.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++) {  // 세로 만큼
        for (int j = 0; j < m; j++) // 가로 만큼
            cin >> board[i][j]; // 보드 값 입력
    }

    //연산
    backtracking(0);

    //출력
    cout << ans;
}
