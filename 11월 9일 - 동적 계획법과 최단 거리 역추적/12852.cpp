//
// Created by user on 2021-11-15.
// [백준] 12852번 - 1로 만들기 2
// dp에 기본값을 지정해놓고, 가능한 3가지 연산을 한 후와 dp값을 비교해서 더 작은 값을 i에 해당하는 값으로 갱신
//

#include <iostream>
#include <algorithm>
using namespace std;
int dp[1000001], N, path[1000001]; // dp: 횟수, path: 1로 만드는 방법에 포함되어 있는 수


int solution(int N) {
    /* for (int i = 1; i < N; i++) {
        dp[i] = i;
    } */
    dp[1] = 0; // 1을 1로 만드는데 드는 연산의 횟수는 0
    path[1] = -1;

    for (int i = 2; i <= N; ++i) { // i = 1이면 1이기 때문에 2부터 시작
        dp[i] = dp[i - 1] + 1;
        path[i] = i - 1;

        if(i % 3 == 0 && dp[i] > dp[i / 2] + 1) {
            // dp[i] = min(dp[i], dp[i / 3]) + 1;
            dp[i] = dp[i / 2] + 1;
            path[i] = i / 3;
        }
        if (i % 2 == 0 && dp[i] > dp[i / 2] + 1) {
            // dp[i] = min(dp[i], dp[i / 2]) + 1;
            dp[i] = dp[i / 2] + 1;
            path[i] = i / 2;
        }
    }
    return dp[N];
}

int main(void) {
    cin >> N;
    cout << solution(N) << endl;

    int i = N;
    // cout << N << endl;
    while(N != -1) {
        cout << N << ' ';
        N = path[N];
    }
    return 0;
}