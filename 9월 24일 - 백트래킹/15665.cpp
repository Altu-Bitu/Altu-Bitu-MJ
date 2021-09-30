//
// Created by user on 2021-09-30.
//
/*
 * [백준] 15665번 - N과 M (11)
 * 입력: N: 주어지는 자연수의 개수, M: 수열의 길이 (N개의 자연수 중 M개를 고른 수열)
 * - 범위: 1 <= M <= N <= 7
 * 조건 1. 수열은 사전 순으로 증가하는 순서로 출력
 * 조건 2. 길이가 M인 수열
 * 조건 3. 같은 숫자는 되나 같은 수열은 불가능 (예: 8 8 가능, 1 8, 1 8 불가능)
 */
#define SIZE = 10001;
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int N, M;
int input[8]; // 입력할 수 있는 자연수(N)의 최대값은 7
vector<int> result; // 결과 저장 및 출력할 벡터
vector<bool> check; // 중복 방지를 위한 벡터

// pos: 위치, cnt: 길이
void backTracking(int pos, int cnt)
{
    if(cnt == M)
    {

    }
    for (int i = 0; i <= result.size(); i++)
    {
        input[pos] = i;
        backTracking(pos + 1, cnt + 1);
    }

}

int main(void)
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> input[i];

    }
    sort(result.begin(), result.end()); // 조건 1을 만족하기 위해 입력받은 수들 오름차순 정렬
    // backTracking();

    return 0;
}