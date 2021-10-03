#include <iostream>
#include <algorithm>

using namespace std;

const int SIZE = 7; //배열 크기

int n, m;// n: 주어지는 자연수의 개수, m: 수열의 길이
int num[SIZE], ans[SIZE]; // num: 자연수 입력받을 배열, ans: 정답 저장할 배열

void backtracking(int cnt) {
    if (cnt == m) { //길이 m이라면 (기저조건)
        for (int i = 0; i < m; i++) // 배열의 길이가 m인 정답 출력
            cout << ans[i] << ' '; // 공백으로 구분해서 정답 출력
        cout << '\n'; // 한 줄에 정답 하나씩
        return; // 종료
    }
    int value = -1; //이전에 선택한 값
    for (int i = 0; i < n; i++) { // 입력한 자연수만큼 돌면서
        if (value != num[i]) { //이전에 탐색한 값이 아니라면(=해당 수 사용 가능하다면)
            value = num[i]; // value 값 지금 입력한 값으로 바꿔주고 (다음 숫자에서는 이전에 선택한 값이 되니까)
            ans[cnt] = num[i]; // 이전에 탐색 안했으므로 ans배열의 cnt 번째에 해당 값 넣어주고
            backtracking(cnt + 1); // 매개변수 cnt+1로 바꾸고 재귀함수 호출
        }
    }
}

/**
 * [백준] 15665번 - N과 M(11)
 * [백트래킹 풀이] (184ms)
 * 해설 : https://myunji.tistory.com/309
 */
int main() {
    //입력
    cin >> n >> m;
    for (int i = 0; i < n; i++) // n개 만큼의 자연수를
        cin >> num[i]; // num 배열에 입력

    //연산
    sort(num, num + n); // 수열을 사전 순으로 증가하는 순서로 출력해야 하기 때문에 sort 해준다.

    //연산 + 출력
    backtracking(0); // 0입력하면 재귀함수 돌면서 backtracking(m) 됐을 때 최종 답 출력.
}//
// Created by user on 2021-10-03.
//

