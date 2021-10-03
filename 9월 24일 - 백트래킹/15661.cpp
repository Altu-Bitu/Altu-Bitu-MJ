//
// Created by user on 2021-10-03.
//

#include <iostream>
#include <algorithm>

using namespace std;

const int SIZE = 20; // 배열 크기 ( N의 최대값 )
const int INF = 10e8; // 정답 크기

int n;
int answer = INF; // 정답: 두 팀의 능력치 차이의 최솟값
int power[SIZE][SIZE]; // 사람 사이 능력치 관계
bool is_start[SIZE]; // 스타트팀이면 true, 링크팀이면 false
int start[SIZE], link[SIZE]; //스타트와 링크 팀에 속하는 사람

//각 팀의 능력치를 계산하는 함수
int calcPower(int arr[], int size) { // 정수형 반환하므로 반환 타입 int
    int result = 0; // 결과값 초기화

    //모든 Sij의 합
    for (int i = 0; i < size; i++) { // 중첩 돌면서
        for (int j = i + 1; j < size; j++) // 각 팀원의 능력치 관계 합을
            result += power[arr[i]][arr[j]] + power[arr[j]][arr[i]]; // result에 더해준다.
            // 예를들어 calcPower(link, idx)고 link에 들어있는 값이 1, 3이라면 index는 2겠지?
            // 그럼 idx만큼 중첩 돌면서 S[1][3] + S[3][1] 더해주기!
    }
    return result; //  그리고 더한 result값 반환
}

void backtracking(int cnt, int st) { // cnt: 현재까지 있는 인원수, st: 스타트팀 인원 수
    if (cnt == n) //n이면 팀 더 이상 꾸릴 수 x (기저조건)
        return; // 종료
    if (cnt > 0) { //최소 1명이 팀에 있어야 함
        int idx = 0; // 배열 시작 지점
        for (int i = 0; i < n; i++) { // n명 팀 배치
            if (!is_start[i]) //스타트 팀이 아니라면->링크팀
                link[idx++] = i; // 링크팀에 i 넣어준다.
        }
        int diff_value = abs(calcPower(link, idx) - calcPower(start, cnt)); //두 팀의 능력치 차이
        answer = min(answer, diff_value); //차이의 최솟값 저장
    }
    for (int i = st; i < n; i++) {
        is_start[i] = true; //링크 팀에 속하는 사람 추리기 위해 스타트 팀원 체크
        start[cnt] = i; //스타트 팀에 배치
        backtracking(cnt + 1, i + 1); // 매개변수 두 개 모두 1 증가시키고 재귀함수 돈다.
        if (i == 0) //1번 사람이 링크 팀이 됨 -> 어차피 스타트 팀이었던 경우와 값 같음 (왜 그런지 디버깅 해보자!)
            return; // 종료
        is_start[i] = false; // 추렸으니까 빼준다.

    }
}

/**
 * [백준] 15661번 - 링크와 스타트
 * [백트래킹 풀이] (84ms)
 * 오름차순 수열을 만드는 것을 활용하여 팀 조합
 * 오름차순 수열을 만들어가는 과정에서 길이가 1이상이 되면 팀배정 완료된 것 (최소 1명 이상이 팀원이므로)
 * 스타트 팀을 꾸려가는 것을 기준으로 풀이, 나머지는 링크 팀에 수동배정
 * ex. n = 4
 * 1 -> 1번 사람이 스타트 팀
 * 1 2 -> 1, 2번 사람이 스타트 팀
 * (생략)
 * 2 3 4 -> 2, 3, 4번 사람이 스타트 팀
 *
 * 팀 배정을 모두 끝낸 후, 능력치 차이 계산
 */

int main() {
    //입력
    cin >> n; // 인원수
    for (int i = 0; i < n; i++) { // 능력치는 n X n이기 때문에
        for (int j = 0; j < n; j++) { // 중첩반복문 돌면서 입력받는다.
            cin >> power[i][j]; //사람 사이의 능력치 관계
        }
    }

    //연산
    backtracking(0, 0);

    //출력
    cout << answer << '\n';

    return 0;
}