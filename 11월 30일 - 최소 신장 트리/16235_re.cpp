//
// Created by user on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef tuple<int, int, int> tp;

// 봄 - 나무가 자신의 나이만큼 양분을 먹는다.
queue<tp> spring(matrix &land, deque<tp> &tree, queue<pair<int, int>> &breeding_tree) {
    queue<tp> dead_tree; // 죽은 나무
    int size = tree.size(); // 나무 수
    while (size--) { //모든 나무 검사
        int age = get<0>(tree.front()); //나이
        int row = get<1>(tree.front()); //행
        int col = get<2>(tree.front()); //열
        tree.pop_front();   // 정보를 다 저장한 나무는 큐에서 제거

        if (land[row][col] < age) { //자신의 나이만큼 양분을 먹을 수 없다면
            dead_tree.push({age, row, col});    // 죽은 나무 큐에 정보와 함께 추가
            continue;   // 코드 계속
        }
        land[row][col] -= age;  // 나무가 먹은 만큼 땅에서 양분 제거
        tree.emplace_back(age + 1, row, col);   // 양분 먹고 나이 증가시켜서 큐에 추가
        if ((age + 1) % 5 == 0) //나이가 5의 배수라면
            breeding_tree.push({row, col}); // 번식하는 나무 큐에 추가
    }
    return dead_tree;   // 여름에 죽은 나무를 양분으로 변화시키기 위해 죽은 나무 큐 반환
}

// 여름 - 죽은 나무가 양분으로 변화한다.
void summer(queue<tp> &dead_tree, matrix &land) {
    while (!dead_tree.empty()) {    // 죽은 나무 큐에 있는 모든 나무에 대해서
        int age = get<0>(dead_tree.front()); //죽은 나무의 나이
        int row = get<1>(dead_tree.front()); //죽은 나무의 행 위치
        int col = get<2>(dead_tree.front()); //죽은 나무의 열 위치
        dead_tree.pop();    // 정보 저장된 죽은 나무는 큐에서 제거
        land[row][col] += (age / 2);
        // 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 자리에 양분으로 추가되고,
        // 소수점 아래는 버리기 때문에 몫 연산만
    }
}

void fall(int n, deque<tp> &tree, queue<pair<int, int>> &breeding_tree) {
    int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; // 인접한 8개의 칸에 대한 row 좌표
    int dc[8] = {0, 0, -1, 1, -1, 1, -1, 1}; // 인접한 8개의 칸에 대한 col 좌표

    while (!breeding_tree.empty()) {    // 번식하는 나무 큐에 있는 모든 나무에 대해서
        int row = breeding_tree.front().first; //번식할 나무의 행
        int col = breeding_tree.front().second; //번식할 나무의 열
        breeding_tree.pop(); // 정보 저장된 번식할 나무는 큐에서 제거

        for (int j = 0; j < 8; j++) {   // 8개의 칸에 대해
            int nr = row + dr[j]; // row 위치 이동
            int nc = col + dc[j]; // col 위치 이동
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) // 땅을 벗어나는 칸에는 나무 안 생김
                continue;   // 추가 과정 없이 계속
            tree.push_front({1, nr, nc}); //새로 생긴 나무
        }
    }
}
// 겨울 - 땅을 돌아다니면서 양분 추가
void winter(int n, matrix &a, matrix &land) {
    for (int i = 0; i < n; i++) // 상도의 모든 땅에
        for (int j = 0; j < n; j++) // 가로, 세로 반복하면서
            land[i][j] += a[i][j];  // 입력된 만큼의 양분 추가
}

/**
 * [문제 설명] - 단순 구현 문제
 * 봄: 하나의 칸마다 나이가 어린 나무부터 자신의 나이만큼 양분을 먹고, 나이가 1 증가함
 *    각 칸에 양분이 부족해 자신의 나이만큼 양분을 못 먹는 나무는 즉시 죽음
 * 여름: 봄에 죽은 나무가 양분으로 변함. 죽은 나무마다 나이를 2로 나눈 값이 양분으로 추가 (소수점 버림)
 * 가을: 나이가 5의 배수인 나무가 번식. 인접한 8개 칸에 나이가 1인 나무가 생김
 * 겨울: 로봇(S2D2)이 땅을 돌아다니면서 A[r][c]만큼 각 칸에 양분 추가
 *
 * K년이 지난 후 상도의 땅에 살아있는 나무의 개수
 *
 * [문제 풀이]
 * a: 로봇(S2D2)가 겨울에 주는 양분의 양
 * land: 땅의 양분
 * breeding_tree: 나이가 5의 배수인 트리 (번식할 트리)
 * tree: 땅에 심은 나무 나이, 행, 열 정보
 * -> deque 컨테이너를 활용해 번식한 나무를 앞에 넣어주면 입력 후에만 정렬해서 사용 가능
 *
 * 문제의 설명대로 계절별 연산을 진행
 */

int main() {
    int n, m, k, x, y, z;

    //입력
    cin >> n >> m >> k;
    // n: 땅의 한 변의 길이, m: 나무 개수, k: k년이 지난 후
    matrix a(n, vector<int>(n, 0)); // 추가되는 양분, 초기 값 0으로 설정
    matrix land(n, vector<int>(n, 5)); //처음 양분 모든 칸에 5
    queue<pair<int, int>> breeding_tree; //번식할 트리
    deque<tp> tree; // 나무의 정보를 담을 덱 생성
    for (int i = 0; i < n; i++) // 땅의 넓이만큼
        for (int j = 0; j < n; j++) // 반복하면서
            cin >> a[i][j]; // 추가되는 양분 정보 입력
    while (m--) {   // 나무 개수만큼 반복하면서
        cin >> x >> y >> z; // 나무의 정보 - x, y: 나무의 위치, z: 나무의 나이
        tree.emplace_back(z, x - 1, y - 1); //(0, 0)부터 시작하도록 구현하기위해 1을 빼준 인덱스에 접근
    }

    //연산
    sort(tree.begin(), tree.end()); //어린 나이 순으로 정렬
    while (k--) {   // 나무의 개수만큼 반복하면서
        queue<tp> dead_tree = spring(land, tree, breeding_tree); //봄이 지나고 죽은 나무
        summer(dead_tree, land);    // 여름: 양분을 추가할 죽은 나무 받아서 함수 수행
        fall(n, tree, breeding_tree);   // 가을: 나무 번식
        winter(n, a, land); // 겨울: 땅에 양분 추가
    }

    //출력
    cout << tree.size();
}