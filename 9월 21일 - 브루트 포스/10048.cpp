//
// Created by user on 2021-09-27.
//
/*
 * [백준] 10448- 유레카이론
 * Hint: 자연수 K의 최대범위는 1000이고, 삼각수는 정확히 3개만 사용 가능
 * 입력 - T: 테스트케이스의 개수, K: T개 만큼의 자연수
 * 출력 - 테스트 케이스가 삼각수의 합으로 표현될 수 있다면 1을, 그렇지 않다면 0 출력
 * 삼각수 T(n) = n(n+1)/2
 * n * (n+1) 이 2000이하여야 하므로 n의 최대값은 44
 * 삼각수를 구하는 함수와 3개의 삼각수의 합으로 구성되어있는지 판별하는 함수
 */
#include <iostream>
using namespace std;

const int SIZE = 45;

int triangleNum[SIZE];

void initTriNum() {
    for (int i = 0; i < SIZE; i++)
        triangleNum[i - 1] = ((i - 1) * i) / 2;
}

bool isEureka(int K) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            for (int k = 0; j < SIZE - 1; k++) {
                if (triangleNum[i] + triangleNum[j] + triangleNum[k] == K)
                    return true;
            }
        }
    }
    return false;
}

int main(void) {
    int T;
    cin >> T;
    initTriNum();

    for (int i = 0; i < T; i++) {
        int K;
        cin >> K;
        if (isEureka(K))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}