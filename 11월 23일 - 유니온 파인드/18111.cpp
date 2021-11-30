//
// Created by user on 2021-11-29.
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void minecraft(int m, int n, int b, vector<vector<int>> &board) {
    // int min_time = INT_MAX, max_height = -1;    // 최소 시간을 갱신하기 위해 가장 큰 정수값으로, 최대 높이를 갱신하기 위해 -1로 초기화
    int min_time = 1e8, max_height = -1;
    for (int h = 0; h <= 256; h++) { // 땅의 높이는 256을 초과할 수 없다.
        int remove = 0, build = 0; // 1번 작업. remove: 2초, 2번. build: 1초,
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) { // 집터 만큼 가로, 세로 돌면서
                int height = board[i][j] - h; // 땅의 높이와 기본 높이의 차를 구한다.
                if (height < 0) build -= height; // 땅의 높이를 증가시켜야 하므로 더 증가시켜야 하는 높이 계산
                else remove += height;  // 땅의 높이를 줄여야 하므로 둘의 차이를 더해준다.
            }
        }
       // cout << remove << ' ' << build << '\n';

        if (remove + b >= build) {  // 새로 놓는 블록의 수가 제거하는 블럭의 수와 주어진 인벤토리의 블록 수의 합(사용 가능한 블록 수)보다 작다면
            int time = remove * 2 + build; // 시간 계산하고
            if (min_time >= time) {
                min_time = time; //최소 시간 갱신하고
                max_height = h; // 최대 높이 갱신
            }
       }
    }
    cout << min_time << ' ' << max_height << endl;
}

int main(void) {
    int m, n, b;
    cin >> n >> m >> b;
    vector<vector<int>> board(n, vector<int>(m, 0)); // 주어진 크기의 집터 만들기
    for (int i = 0; i < n; i++) { // 세로
        for (int j = 0; j < m; j++) { // 가로
            cin >> board[i][j]; // 땅의 높이
        }
    }
    minecraft(m, n, b, board);
    return 0;
}

