//
// Created by user on 2021-10-07.
//

/*
 * [백준] 1448번 - 삼각형 만들기
 * 입력 - N: 빨대의 개수, 다음줄부터 N개만큼의 빨대의 길이
 * 출력 - 삼각형 세 변의 길이의 합의 최대값. 삼각형 안되면 -1
 *
 * 1. 삼각형 되는지 확인 - 가장 큰 변의 길이가 나머지 두 변의 길이의 합보다 작아야 한다.
 * 2. 정렬하고 뒤에서부터 구하기( 최대값 구해야 하니까)
 */
#include <iostream>
#include <algorithm>
using namespace std;

int straw[1000001]; // 빨대의 길이 저장할 배열
int n; // 빨대의 개수

int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> straw[i];
    }

    sort(straw, straw + n); // 정렬하기

    for (int i = n - 1; i >= 2; i--) { // n, n-1, n-2를 활용할 것이기 때문에 i는 2이상이어야 한다.
        int a = straw[i - 2];
        int b = straw[i - 1];
        int c = straw[i]; // 가장 큰 변의 길이
        if (c < a + b) { // 삼각형 성립하면
            cout << a + b + c << endl; // 최대값 출력하고 종료
            return 0;
        }
    }
    // 입력한 수 중 삼각형이 되는 최대값이 없다면 -1 출력
    cout << -1 << endl;
}
