//
// Created by user on 2021-09-23.
// 

/*
 * [백준] 11050번 이항 계수 1
 * 문제: 자연수 N과 정수 K가 주어졌을 때 이항계수를 (N K)를 구하는 프로그램 작성하기
 * 이항계수 공식: N! / {(N-K)!K!}
 */

#include <iostream>

using namespace std;

int factorial(int n) { // 팩토리얼 구하는 함수
    if(n <= 1) return (1); // n이 1 이하일 경우 1 반환
    else return (n * factorial(n-1)); // n이 1보다 클 경우 n * 재귀함수 반환
}

int main(void) {
    int N = 0, K = 0, result = 0;
    cin >> N >> K; // 자연수 N과 정수 K 입력받기
    result = factorial(N) / (factorial(K) * factorial(N - K));

    cout << result;

}