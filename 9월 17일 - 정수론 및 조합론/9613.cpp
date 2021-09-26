//
// Created by user on 2021-09-23.
// 

/*
 * [백준] 9613번 GCD 합
 * 최대공약수를 찾기 위해 유클리드호제법 이용
 */
#include <iostream>

using namespace std;
const int MAX = 100;
int arr[MAX];

int GCD(int a, int b) {
    if (b == 0)
        return a; // 예외처리 - b가 0일 경우 a 반환
    else if (a % b == 0) // a를 b로 나눈 나머지가 0이면 b가 최대공약수이므로 b 반환
        return b;
    else
        return GCD(b, a % b); // 재귀함수
    // a를 b로 나눈 나머지가 0이 아니라면 a는 b로, b는 a를 b로 나눈 나머지로 만들어주고 반복
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T, N; // (반복문에 사용되는 변수와 구분하기 위해 대문자로 설정)
    // T: 테스트 케이스의 개수, N: 각 테스트케이스마다 줭지는 숫자
    cin >> T;

    for (int i = 0; i < T; i++) { // 각 테스트케이스마다
        long long sum = 0; // 모든 쌍의 GCD의 합을 저장할 변수
        // 테스트 케이스마다 sum값은 리셋되야하기 때문에 반복문 안에서 호출
        cin >> N; // 숫자 몇개 입력할건지 입력
        for (int j = 0; j < N; j++) // N개 만큼 반복 돌면서 N개의 숫자 입력
            cin >> arr[j];

        // 중첩반복문 사용으로 배열 arr에 있는 모든 수의 조합에 대해 최대공약수 확인 후 sum에 더해주기
        for (int j = 0; j < N; j++)
            for (int k = j + 1; k < N; k++)
                sum += GCD(arr[j], arr[k]);

        cout << sum << "\n";
    }

    return 0;
}
