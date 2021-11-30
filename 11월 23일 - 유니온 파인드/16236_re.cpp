//
// Created by user on 2021-11-30.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 401;    // 공간의 최대
typedef pair<int, int> ci;  // 상어의 위치

pair<int, ci> nextPos(int n, int shark_size, ci &shark, vector<vector<int>> &board) {
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    // 순서대로 상, 하, 좌, 우

    int min_dist = INF; // 최소 값의 초기값은 최대로 설정
    queue<ci> q; //상어가 갈 수 있는 곳
    vector<vector<int>> visited(n, vector<int>(n, 0)); //상어의 방문 여부
    vector<ci> list; //상어가 먹을 수 있는 물고기들의 위치

    visited[shark.first][shark.second] = 1;
    q.push(shark);  // 방문했다고 표시하고 상어가 갈 수 있는 곳으로 추가
    while (!q.empty()) {    // 상어가 갈 수 있는 곳이 존재하는 동안
        int row = q.front().first;  // 행 설정
        int col = q.front().second; // 열
        int dist = visited[row][col];   // 거리
        q.pop();    // 큐 상단에 있는 값 pop

        if (dist >= min_dist) //최단거리 이상은 탐색할 필요 없음
            continue;
        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];   // 위치 바꿔가면서
            int nc = col + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc] || board[nr][nc] > shark_size)
                // 이동 불가하다면(보드의 범위 밖이거나 아무것도 없다면)
                continue;   // 탐색할 필요 없다

            visited[nr][nc] = visited[row][col] + 1;    // 범위 내라면 상어의 위치 + 1
            if (board[nr][nc] && board[nr][nc] < shark_size) { //먹을 수 있는 물고기 발견
                list.emplace_back(nr, nc);  // 먹을 수 있는 물고기들의 위치에 추가
                min_dist = visited[nr][nc]; // 최소 거리 갱신
                continue;
            }
            q.push({nr, nc});   // 먹을 수 있는 물고기를 찾았다면 더 나갈 필요 없다
        }
    }

    if (list.empty()) //상어가 갈 수 있는 곳이 없음
        return {min_dist, {-1, -1}};    //

    sort(list.begin(), list.end(), [](const ci &p1, const ci &p2) { //정렬
        if (p1.first != p2.first)   // 조건에 맞는 물고기의 좌표가 맨 앞으로 올 수 있게 정렬
            return p1.first < p2.first; // 위로 먼저 이동
        return p1.second < p2.second;   // 왼쪽으로 먼저 이동
    });
    return {min_dist - 1, list[0]}; // 조건에 맞는 물고기의 좌표 넘겨줌
}

int simulation(int n, pair<int, int> &shark, vector<vector<int>> &board) {
    int ans = 0, size = 2, cnt = 0; // size: 상어의 크기 (초기값 2로 설정), cnt: 먹은 물고기의 수
    while (true) {
        pair<int, ci> result = nextPos(n, size, shark, board); // 위치 get
        if (result.first == INF) //더 이상 먹을 수 있는 물고기가 공간에 없음
            break;  // 반복문 종료
        ans += result.first; // 먹을 수 있다면 정답에 추가
        cnt++;  // 먹은 물고기 수 증가
        if (cnt == size) { //상어 크기 증가
            cnt = 0;    // 계산했으니 cnt 0으로 초기화
            size++; // 크기 증가
        }

        //상어 이동
        ci pos = result.second;
        board[shark.first][shark.second] = 0;   // 그 위치에 있는 물고기를 먹었읜 그 위치는 이제 빈 칸
        shark = pos;     // 상어 위치 재설정
    }
    return ans;
}

/**
 * 1. 상어로부터 가장 가까운 거리에 있는 모든 물고기 탐색 (BFS)
 * 2. 우선순위 조건에 맞추어 먹으러 갈 물고기 확정
 *    탐색하는 방향에 우선순위를 두는 걸로 해결되지 않음! (예제 입력 4) 정렬 필요
 * 3. 상어가 이동할 수 있는 곳이 없을 때까지 BFS 탐색 반복
 *
 * 입력 범위가 작기 때문에 매번 BFS 탐색을 반복해도 시간 초과 X
 * 가능한 물고기의 최대 마리 수 : 399마리
 * 최대 BFS 탐색 횟수 : 399회, 1회 탐색마다 while 문은 최대 400회 미만으로 순회
 * 총 연산 횟수 약 160000번으로 충분히 가능
 *
 * 해설 : https://myunji.tistory.com/378
 * *글 자체는 별로 도움이 안되고...그냥 리팩토링하면 코드가 이렇게 되는구나 정도만 봐주세요
 */
int main() {
    int n;  // 공간의 크기: n X n
    pair<int, int> shark_pos;   // 상어의 위치

    //입력
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));   // n X n만큼의 공간 생성
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j]; // 각 칸의 상태 입력받기
            if (board[i][j] == 9) //상어의 초기 위치
                shark_pos = make_pair(i, j);    // 초기 위치를 벡터값으로 저장
        }
    }

    //연산 & 출력
    cout << simulation(n, shark_pos, board);
}