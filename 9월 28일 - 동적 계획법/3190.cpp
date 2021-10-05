//
// Created by user on 2021-10-05.
//
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;
typedef pair<int, int> ci;

// dir: 원활한 방향전환을 위해 사용
ci dir[4] = {{0,  1},  //우
             {-1, 0},  //상
             {0,  -1}, //좌
             {1,  0}}; //하


//게임을 진행하는 함수 - 뱀 있는 자리 1, 사과 있는 자리: 2, 빈 자리: 0
int playGame(int n, vector<vector<int>> &board, map<int, char> &cmd) {
    //뱀 초기화
    deque<ci> snake; // 뱀의 head, tail 위치 표현 위해 deque 사용
    snake.push_front(ci(0, 0)); // 시작은 (0, 0)에서
    board[0][0] = 1; // 뱀이 시작하는 곳의 값 1으로 설정

    int t = 0, head = 0; //시간, 뱀의 머리 방향
    while (true) { // 게임 종료 조건 만나기 전까지 반복
        t++; // 이동 한번에 시간 증가
        //뱀의 머리가 위치하게될 칸. (행, 열)이므로 first가 행, second가 열
        // 행: 뱀의 머리의 행 위치 + 뱀의 머리방향 x좌표
        int nr = snake.front().first + dir[head].first;
        // 열: 뱀 머리의 열 위치 + 뱀 머리방향 y좌표
        int nc = snake.front().second + dir[head].second;

        //게임 종료 조건 : 벽에 부딪히거나, 자기자신의 몸과 부딪힘 (borad위치 == 1)
        // 벽은 행, 열 각각 0, n번째에 위치해있기 때문에 아래와 같은 조건
        if (nr < 0 || nr >= n || nc < 0 || nc >= n || board[nr][nc] == 1)
            break;

        if (board[nr][nc] != 2) { //이동한 칸에 사과가 없다면 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다
            board[snake.back().first][snake.back().second] = 0; // 보드에 뱀의 꼬리 위치를 0으로 바꾼다.
            snake.pop_back(); // 몸 길이 줄이기
        }

        //뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다
        snake.push_front(ci(nr, nc));
        board[nr][nc] = 1; // 위치시킨 후 뱀 있다고 표시하기 위해 1 대입

        //이번에 방향을 변환하는지 확인
        if (cmd[t] == 'L') //왼쪽 회전
            head = (head + 1) % 4; // 예를 들어, 방향이 '상'(2)이었다면 왼쪽 회전 시 '좌'(3 % 4 = 3)
        if (cmd[t] == 'D') //오른쪽 회전
            head = (head + 3) % 4; // 예를 들어, 방향이 '상'(2)이었다면 오른쪽 회전 시 '우'(5 % 4 = 1)
    }
    return t; // 시간 반환
}

/**
 * 0 0 1
 * 0 2 1
 * 0 0 1
 *
 * 편의를 위해 문제와 달리 (0, 0)부터 시작
 *
 * 보드의 상태가 위와 같을 때
 * 뱀의 몸은 (0, 2)~(2, 2)에 걸쳐 있고, 사과는 (1, 1)에 위치하고 있음
 * -> 뱀의 꼬리와 머리 위치를 알기 위해 덱 사용
 * -> 덱의 front : 머리, 덱의 back : 꼬리
 *
 * 원활한 방향 변환을 위해 dir 배열 사용
 */
int main() {
    // n: 보드크기, k: 사과 개수, row: 사과 위치(행), col: 사과 위치(열)
    // l: 방향 변환 횟수, x: 몇 초 뒤에 방향 바뀌는지
    // c: 방향 변환 정보 (L: 왼쪽으로, D: 오른쪽으로 90도 회전)
    int n, k, row, col, l, x;
    char c;

    //입력
    cin >> n >> k;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < k; i++) { // k개만큼의 사과의 개수 반복문 돌면서
        cin >> row >> col; // 사과의 위치 입력받기
        board[row - 1][col - 1] = 2; //사과 표시
    }
    cin >> l; // 방향 변환 횟수
    map<int, char> cmd; // int: 몇 초 뒨지, char: 왼쪽/오른쪽
    for (int i = 0; i < l; i++) { //회전 정보
        cin >> x >> c; // 입력
        cmd[x] = c; // 입력받은 정보 대입
    }

    //연산 & 출력
    cout << playGame(n, board, cmd);
}
