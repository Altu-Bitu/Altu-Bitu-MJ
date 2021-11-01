//
// Created by user on 2021-11-01.
// 211012 - 투포인터(two pointer)
// [백준] 20922 - 겹치는 건 싫어
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int N, K; // 정수의 개수 N, 같은 정수가 있을 수 있는 최대 개수 K
// int ans = 0; //  ans: 최종 답

vector<int> num(200000 + 1);

int two_pointer(int n, int k, vector<int> num){
    vector<int> count(100000 + 1, 0); // 정수 n이 나온 횟수 (n, 횟수)
    int start = 0, end = 0; // 최장 연속 부분 수열의 시작(start)와 끝(end)
    int ans = 0; //  ans: 최종 답

    while(start <= end && end < n) { // 수열의 시작위치가 종료위치보다 작거나 같고, 종료 위치가 정수의 개수보다 작을 때
        if(count[num[end]] < k) { // 수열 끝에 있는 정수가 나온 수가 k보다 작다면
            count[num[end]]++; // 정수가 나온 횟수 증가하고
            end++; // 수열 길이 증가
            ans = max(end - start, ans);

        }
        else { // 정수가 나온 수가 k 이상이라면 (부분 수열 종료 조건)
            count[num[start]]--; // 포함 안 시킬거니까 나온 횟수 감소
            start++; // 수열 시작 위치 변경
        }

       // ans = max(end - start + 1, ans);
        // 반복문 돌면서 최대값 갱신

    }
    return ans;
}
int main(void) {
    // 입력
    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        cin >> num[i];
    }
    // two_pointer(N, K, num);
    // cout << ans << endl;
    cout << two_pointer(N, K, num) << endl;
    return 0;
}


