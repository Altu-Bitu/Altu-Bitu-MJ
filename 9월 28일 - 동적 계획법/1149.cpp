//
// Created by user on 2021-10-04.
//
/*
 * [백준] 1149번 - RGB 거리
 * 입력 - N : 집의 수,
 * - N개의 줄에는 각 집을 빨강(R, 0), 초록(G, 1), 파랑(B ,2)으로 칠하는 비용
 * 출력 - 모든 집을 칠하는 비용의 최솟값
 * 조건: N번째 집의 색은 (N - 1)번째의 집의 색과 달라야 한다.
*/
#include <iostream>
#define MAX 1001 // N과 비용의 최대값
//각 색깔 (R = 0, G = 1, B = 2)

using namespace std;
int N; // 집의 수
int MAP[MAX][3]; // 각 집을 칠하는데 드는 비용
int DP[MAX][3]; // 이전 비용 저장
int finalMin = 0; // 최종 값 저장

int Min(int A, int B) { // 최솟값 출력 함수
    if (A < B)
        return A;
    return B;
}

int totalCost()
{
    // DP[i][0] = min(DP[i-1][1], DP[i-1][2]) + MAP[i][0]

    for (int i = 1; i <= N; i++)
    {
        DP[i][0] = Min(DP[i-1][1], DP[i-1][2]) + MAP[i][0];
        DP[i][1] = Min(DP[i-1][0], DP[i-1][2]) + MAP[i][1];
        DP[i][2] = Min(DP[i-1][0], DP[i-1][1]) + MAP[i][2];
    }
    // cout << "Debuging " << DP[N][0] << "\n" << DP[N][1] << "\n" << DP[N][2] << "\n";
    // 모든 비용의 최솟값
    finalMin = Min(Min(DP[N][0], DP[N][1]), DP[N][2]);
    return finalMin;
}


int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) { // N개의 집에
        for (int j = 0; j < 3; j++) // 각각의 RGB 비용 입력받기
        {
            cin >> MAP[i][j];
            // 0번째는 사용 안하므로(0번째에는 칠할 집이 없으니까!)  0으로 초기화
            DP[0][j] = 0;
            MAP[0][j] = 0;
        }
    }
    cout << totalCost() << endl;
    return 0;
}
