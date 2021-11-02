//
// Created by user on 2021-11-02.
//

#include <iostream>
#include <vector>

using namespace std;

int ans, n, m;
vector<vector<int>> board; // 보드판
int dr[4] = {-1, 1, 0, 0}; // 상 하
int dc[4] = {0, 0, -1, 1}; // 좌 우

//board[row][col]을 가운데로 하는 +모양 만들기
int horn(int row, int col) {
    int cnt = 0, min_block = 1001, sum = board[row][col]; // 입력으로 최대가 될 수 있는 수: 1000 -> min_block에서는 최솟값 찾기 때문에 최대값으로 먼저 초기화

    for (int i = 0; i < 4; i++) { // 상하좌우 방향 탐색
        int nr = row + dr[i]; // 상 하로 이동하며 row 좌표 리셋
        int nc = col + dc[i]; // 좌 우로 이동하며 col 좌표 리셋

        if (nr < 0 || nr >= n || nc < 0 || nc >= m) //범위를 벗어나면 무시
            continue; // 코드 진행
        min_block = min(min_block, board[nr][nc]); //가장자리 블럭 중 값이 가장 작은 블럭
        sum += board[nr][nc]; // 총합은 보드의 범위 내에 있는 좌표의 값 다 더한 것
        cnt++; // 반복문 한 번 돌 때마다 cnt 증가
    }

    if (cnt < 3) //가능한 가장자리가 최소 3개 이상이어야 함
        return 0; // 함수 종료
    if (cnt == 3) //ㅗㅏㅜㅓ
        return sum; // 보라색 조각 만들었으니 최종 전체합임.
    //+
    return sum - min_block; // 전체 합에서 최솟값 빼면 최대값
}

//한붓 그리기가 가능한 블럭들 백트래킹 탐색
void backtracking(int row, int col, int cnt, int sum) {
    if (cnt == 4) { //기저조건 : 4개의 블럭을 탐색함
        ans = max(ans, sum); // 최대값 갱신
        return; // 종료
    }

    for (int i = 0; i < 4; i++) { // 상하좌우 방향 탐색
        int nr = row + dr[i]; // row 좌표 갱신
        int nc = col + dc[i]; // col 좌표 갱신

        if (nr < 0 || nr >= n || nc < 0 || nc >= m || !board[nr][nc]) //범위를 벗어나거나, 이미 방문했다면
            continue; // 무시
        int save = board[nr][nc]; // 현재 블럭의 값 저장
        board[nr][nc] = 0; // 방문했으니까 0으로 리셋
        backtracking(nr, nc, cnt + 1, sum + save); // 갱신된 데이터로 재귀
        board[nr][nc] = save; // backtracking 함수 구현 후 다음 탐색을 위해 0이었던 값에서 저장해 둔 원래 블럭의 값 돌려두기
    }
}

/**
 * 1. 각 블럭을 백트래킹이 가능한 블럭과 불가능한 블럭으로 나누기
 *    -> 블럭을 한붓 그리기로 그릴 수 있으면 백트래킹이 가능 아니라면 불가능
 *    -> 보라색 블럭을 제외하면 모두 백트래킹 가능
 * 2. 보라색 블럭은 + 모양에서 가장자리를 하나 제거한 것과 같음
 *    -> 가운데 블럭을 중심으로 가장자리 블럭을 붙여보고 가능한 최댓값 구하기
 * 3. 각 블럭에 대해 깊이가 4인 백트래킹 함수를 수행하며 최댓값 갱신
 *
 * 해설 : https://myunji.tistory.com/297
 * *코드가 살짝 달라요(블로그 코드는 최적화 하기 전)
 */
int main() {
    //입력
    cin >> n >> m;
    board.assign(n, vector<int>(m, 0)); // 세로 n, 가로 m인 보드 세팅
    for (int i = 0; i < n; i++) { // 세로 만큼 반복문
        for (int j = 0; j < m; j++) // 가로만큼 반복문 돌면서
            cin >> board[i][j]; // 칸에 쓰인 수 입력
    }

    //연산
    for (int i = 0; i < n; i++) { // 세로 크기만큼
        for (int j = 0; j < m; j++) { // 가로 크기만큼 반복하면서
            ans = max(ans, horn(i, j)); //보라색 블럭 처리
            int save = board[i][j]; // 원래 블럭의 값 save에 저장

            board[i][j] = 0; // 방문했으니 값 0으로 만들어준다
            backtracking(i, j, 1, save); //나머지 모양 처리
            board[i][j] = save; // backtracking 끝났으면 다시 원래 블럭의 값 저장
        }
    }

    //출력
    cout << ans;
}