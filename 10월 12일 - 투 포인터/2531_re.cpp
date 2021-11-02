//
// Created by user on 2021-11-02.
//

#include <iostream>
#include <vector>

using namespace std;

int chooseSushi(vector<int> &belt, int n, int d, int k, int c) {
    vector<int> sushi(d + 1, 0); // 초밥 가짓수보다 하나 더 많은 크기의 벡터 생성

    //쿠폰으로 먹은 초밥
    int section_sushi = 1; // 쿠폰으로 먹은 초밥 우선 더해두기
    sushi[c]++; // 쿠폰으로 먹은 초밥 체크

    //윈도우 초기화
    for (int i = 0; i < k; i++) { // 연속해서 먹는 접시의 수만큼 반복하면서
        sushi[belt[i]]++; // 나오는 스시들 체크
        if (sushi[belt[i]] == 1) // 한 번 먹었다면 (전에 안나온 거니까)
            section_sushi++; // 그 종류로 먹는건 처음이니 증가
    }

    int ans = section_sushi; //
    int left = 0, right = k - 1; // 윈도우 양 끝 초기값 설정
    do { //원형태로 윈도우를 옮겨야 하기 때문에 종료조건은 left가 초기값(=0)이 됐을 때
        sushi[belt[left]]--; // 윈도우 시작에 있는 초밥 종류를 먹은 값 감소했는데
        if (!sushi[belt[left]]) // 0이면 윈도우에 이 초밥 종류가 없다는 의미니까
            section_sushi--; // 먹은 종류감소

        //윈도우의 양 끝 이동
        left = (left + 1) % n; // n 넘어갈 수 있을 수 있으니 모듈러 연산
        right = (right + 1) % n;

        sushi[belt[right]]++; // 윈도우 끝에 있는 초밥을 먹은 횟수를 증가했는데
        if (sushi[belt[right]] == 1) // 새로 먹은 초밥 종류라면
            section_sushi++; // 먹은 종류 증가

        ans = max(ans, section_sushi); // 최대값으로 갱신
    } while (left); // left가 0이면 종료
    return ans;
}

/**
 * 1. 연속해서 먹어야 할 접시가 k로 고정됐기 때문에 슬라이딩 윈도우
 * 2. 직선이 아니라 원 형태의 배열! 모듈러 연산을 통해 윈도우의 양 끝 위치 조절하기
 * 3. 쿠폰으로 먹은 초밥을 먼저 고려해놓기
 * 4. 초밥의 종류가 최대 3000개로 많지 않음. 보석 쇼핑 문제처럼 각 종류별 먹은 초밥의 개수를 세어주기
 *
 * 그림 참고: https://cocoon1787.tistory.com/280
 */
int main() {
    int n, d, k, c; // n: 벨트에 놓인 접시 수, d: 초밥의 가짓수, k: 연속해서 먹는 접시의 수, c: 쿠폰 번호

    //입력
    cin >> n >> d >> k >> c;
    vector<int> belt(n, 0); // 길이가 n인 벡터 생성
    for (int i = 0; i < n; i++) // n번만큼 반복하면서
        cin >> belt[i]; // 각 벨트 위치의 회전초밥의 종류를 나타내는 정수 입력

    //연산 & 출력
    cout << chooseSushi(belt, n, d, k, c);
}
