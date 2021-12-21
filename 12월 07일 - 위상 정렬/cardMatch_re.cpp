//
// Created by user on 2021-12-21.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, int> ci;
const int SIZE = 4;

int dr[4] = {-1, 1, 0, 0}; // row
int dc[4] = {0, 0, -1, 1}; // col
// 순서대로 상, 하, 좌, 우

vector<vector<ci>> findCard(vector<vector<int>> &board) { //존재하는 모든 카드의 위치를 리턴하는 함수
    vector<vector<ci>> card_pos(7, vector<ci>(0)); //최대 카드 수
    int cnt = 0; // 카드 개수 초기화
    for (int i = 0; i < SIZE; i++) {    // 보드의 크기만큼 좌 우로 반복문 돌면서
        for (int j = 0; j < SIZE; j++) {
            cnt = max(cnt, board[i][j]);    // 최대값으로 cnt값 업데이트
            if (board[i][j]) //카드라면 위치 저장
                card_pos[board[i][j]].emplace_back(i, j); // i, j위치에 카드 았다고 표시
        }
    }
    card_pos.resize(cnt + 1); //실제 존재하는 카드의 수만큼 크기 조절
    return card_pos;    // 카드 수 리턴
}

pair<int, int> ctrl(int row, int col, int dir, vector<vector<int>> &tmp) { //컨트롤로 이동하는 좌표를 리턴하는 함수
    while (true) {
        row += dr[dir]; // 입력한 방향으로 row값 재설정
        col += dc[dir]; // 입력한 방향으로 col값 재설정
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) //해당 방향에 카드가 하나도 없다면 그 방향의 가장 마지막 칸으로 이동
            return make_pair(row - dr[dir], col - dc[dir]); // 마지막칸으로 이동해서 그 위치를 pair로 만들어준다
        if (tmp[row][col] != 0) //누른 키 방향에 있는 가장 가까운 카드
            return make_pair(row, col); // 해당 위치 pair로 만들어서 반환
    }
}

int bfs(int r1, int c1, int r2, int c2, vector<vector<int>> &tmp) { //현재 커서에서 목표 카드로 이동하는 가장 적은 비용을 리턴하는 함수
    vector<vector<int>> visited(SIZE, vector<int>(SIZE, 0)); // 방문 여부 체크
    queue<pair<int, int>> q;    // 위치 저장하고 반복문 실행할 큐
    visited[r1][c1] = 1; //반드시 엔터를 누르게 될 것. 엔터를 미리 눌렀다 가정하고 1로 표시
    q.push({r1, c1}); // 1로 만든 위치 큐에 push

    while (!q.empty()) {    // 큐가 비어있지 않을동안
        int row = q.front().first;  // 큐 맨 앞 값의 첫 번째 값 = row
        int col = q.front().second; // 큐 맨 앞 값의 두 번째 값 = col
        int dist = visited[row][col]; // 거리 업데이트(초기값은 1일 것)
        q.pop();    // 계산한 위치의 값은 pop시켜준다.

        if (row == r2 && col == c2) //목표 카드에 도달했다면
            return dist;    // 거리 반환

        for (int i = 0; i < 4; i++) { //컨트롤 입력 이동
            pair<int, int> np = ctrl(row, col, i, tmp); // 컨트롤 한 위치 pair형태로 받아서 np에 저장
            if (visited[np.first][np.second])   // 이미 방문한 위치라면
                continue;   // pass
            visited[np.first][np.second] = dist + 1; // 방문 전이라면 distance 업데이트
            q.push(np); // np 위치 큐에 push
        }

        for (int i = 0; i < 4; i++) { //방향키 입력 이동
            int nr = row + dr[i], nc = col + dc[i]; // 방향 업데이트
            if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4 || visited[nr][nc])  // 이동한 방향이 보드 범위 내가 아니라면
                continue;   // pass
            visited[nr][nc] = dist + 1; // 범위 내라면 distance 업데이트
            q.push({nr, nc});   // 해당 위치 큐에 push
        }
    }
    return -1; //목표 카드에 도달하지 못함 (실제로는 일어나지 않는 일)
}

int matchCard(int bit, int num, int r, int c, vector<int> &seq, vector<vector<ci>> &cards, vector<vector<int>> tmp){ //조합에 대해 카드를 매칭하는 함수
    int ans = 0;    // 정답 저장할 값
    for (int i = 0; i < num; i++) { // 카드 개수만큼 반복하면서
        int cur = seq[i]; //이번에 매칭할 캐릭터
        int now = 0; //해당 캐릭터의 0번째 카드부터 선택한다고 가정
        if (bit & (1 << i)) //만약 해당 위치의 비트가 1을 표시했다면 1번째 카드부터 선택
            now = 1;    // 1번째 카드 선택

        for (int j = 0; j < 2; j++) {   // 뒤집는 카드는 항상 2장이므로 범위 <2로 설정
            now = (now + j) % 2; //이번에 매칭할 카드 인덱스
            int nr = cards[cur][now].first, nc = cards[cur][now].second; //이번에 매칭할 카드 위치
            ans += bfs(r, c, nr, nc, tmp); //현재 커서에서 목표 카드까지 이동하는 비용

            //카드 삭제 + 커서 이동
            tmp[nr][nc] = 0;
            r = nr; // row 커서 이동
            c = nc; // col 커서 이동
        }
    }
    return ans; // 정답 리턴
}

int solution(vector<vector<int>> board, int r, int c) { // 보드와 커서의 위치를 매개변수로 받는다.
    int answer = 1e9; // min 함수를 실행할 것이기 때문에 answer 초기값을 가능한 수 중 가장 큰 수로 지정

    vector<vector<ci>> cards = findCard(board); //존재하는 모든 카드의 위치
    int card_cnt = cards.size() - 1; //카드의 개수

    vector<int> seq(card_cnt); //순열을 위한 배열
    for (int i = 0; i < card_cnt; i++)  // 카드 수만큼 반복하면서
        seq[i] = i + 1; // 순차 배열 실행

    do { //가능한 모든 카드 순서에 대해
        for (int bit = 0; bit < (1 << card_cnt); bit++) { //0, 1번째 카드 중 어떤 카드를 먼저 뒤집을지 결정
            answer = min(answer, matchCard(bit, card_cnt, r, c, seq, cards, board)); // 정답 값 최소값으로 업데이트
        }
    } while (next_permutation(seq.begin(), seq.end())); // 가능한 모든 카드의 순서일동안 실행
    return answer; // 정답(최소값) 반환
}

/**
 * 문제: https://programmers.co.kr/learn/courses/30/lessons/72415
 * 아이디어
 * 1. 범위가 크지 않음
 * 2. 존재하는 모든 카드의 종류는 6개, 카드 2장이 한 쌍을 이룬다.
 * 3. 뒤집을 카드 순서를 정하는 모든 경우의 수는 6!(카드 순서) * 2^6(2개의 카드 중 어떤 카드를 먼저 뒤집을지) -> 브루트포스 가능
 * 4. 이번에 목표로 하는 카드에 대해 현재 커서에서 목표 카드까지 가는 최단 경로를 구하며 이동 횟수 전부 구하고 최솟값 갱신
 *
 * 구현
 * 1. 존재하는 모든 카드의 위치를 저장하며 카드의 개수 세기 (findCard)
 * 2. 가능한 모든 카드의 순서(next_permutation)와 각 카드를 뒤집을 순서(bitmask)를 결정
 *    ex) seq = {3, 1, 2}, bit = 011 일 때
 *        3번, 1번, 2번 카드의 순서로 뒤집는다.
 *        3번 카드는 1번째 카드부터, 1번 카드는 0번째 카드부터, 2번 카드는 1번째 카드부터 뒤집는다.
 *        bit의 011이 앞에서부터 각각 1, 2, 3번 카드와 대응함
 * 3. 현재 카드 순서와 각 카드를 뒤집는 순서에 대한 커서 이동 횟수 계산 (matchCard)
 *    현재 커서 위치와 목표 카드 위치에 대해 bfs 함수 실행
 *    컨트롤 입력을 고려해야 하기 때문에 4방향에 대한 방향 이동에 추가로 컨트롤 입력도 처리한다.(ctrl)
 * 4. 매 조합에 따라 board가 갱신되므로 board를 복사한 tmp 사용
 * 공식 풀이 : https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/
 */
int main() {
    // 첫번째 예제
    vector<vector<int>> board = {{1, 0, 0, 3},
                                 {2, 0, 0, 0},
                                 {0, 0, 0, 2},
                                 {3, 0, 1, 0}};
    cout << solution(board, 1, 0);  // 입력값 - row: 1, col: 0가 커서의 최초 위치
}