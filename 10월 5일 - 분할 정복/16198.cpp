//
// Created by user on 2021-10-12.
// [백준] 16198 - 에너지 모으기
// 211005 - 분할 정복
//
#include <iostream>
#include <vector>

using namespace std;

vector<int> w; // 구슬
int ans;       // 최종 답

void backtracking(int sum) {
    if (w.size() == 2) { //에너지 구슬이 2개 -> 더 이상 고를 수 없음
        ans = max(ans, sum);    // 최종 답은 모을 수 있는 에너지 양의 최대값 -> max
        return;     // ans 구하고 종료
    }
    for (int i = 1; i < w.size() - 1; i++) { //처음과 마지막 선택 불가이므로
        int temp_w = w[i];  // 고른 에너지 구슬 (i 골랐다고 가정)
        int sum_w = w[i - 1] * w[i + 1];    // 고른 에너지 구슬에 대해 모을 수 있는 에너지
        w.erase(w.begin() + i); // 에너지 계산하고 i번째 구슬 제거
        backtracking(sum + sum_w);  // 에너지 양 누적해서 재귀
        w.insert(w.begin() + i, temp_w);    // i번째 구슬 사용 후 번호 다시 매기기
    }
}

/**
 * 가능한 모든 경우를 구해서 계산하자
 * 이때, 사용한 에너지는 따로 저장해 둔 후에 배열에서 지우고, 다시 돌아왔을 때 저장한 값을 배열에 넣는다.
 */
int main() {
    int n;  // n: 구슬의 개수

    //입력
    cin >> n;
    w.assign(n, 0); // 벡터 사이즈 n으로
    for (int i = 0; i < n; i++) // n만큼 반복하면서
        cin >> w[i];    // 에너지 구슬의 무게 입력

    //연산
    backtracking(0);

    //출력
    cout << ans << '\n';

    return 0;   // 시스템 정상 종료
}
