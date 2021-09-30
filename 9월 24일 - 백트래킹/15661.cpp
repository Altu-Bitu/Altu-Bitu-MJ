//
// Created by user on 2021-09-30.
//
/*
 * [백준] 15661번 - 링크와 스타트
 * 입력 - N: 사람 수, S: 능력치
 * - S의 수는 N^2
 * 1. 링크팀에 a, b 스타트팀에 c, d가 있다면
 * - 능력치: 링크: S[a][b] + S[b][a], 스타트: S[c][d] + S[d][c]
 * - 능력치 차이의 최솟값을 출력
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
const int MAX = 20; // N의 범위: 4 ~ 20

using namespace std;
int N; // 몇 명인지
int S[MAX + 1][MAX + 1]; // 각 능력치
vector<int> link;
vector<int> start;

// N: 인원 수, index: 크기, link: 링크팀, start: 스타트팀
int score(int N, int index, vector<int>& link, vector<int>& start)
{
    //
    if (index == N)
    {
        if (link.size() == 0 || start.size() == 0) // 링크팀과 스타트팀 중 한 팀이라도 인원이 없는 경우
            return -1; // 비정상 종료
        int tL = 0; //각 팀의 점수는 0으로 초기 세팅
        int tS = 0;
        int diff = -1; // 팀 능력치 차

        // 링크팀 능력치 합
        for (int i = 0; i < link.size(); i++) {
            for (int j = 0; j < link.size(); j++) {
                if (i == j) continue; // i == j의 경우 능력치 0이기 때문에 패스
                tL += S[link[i]][link[j]]; // 능력치 누적
            }
        } // Team link

        // 스타트팀 능력치 합
        for (int i = 0; i < start.size(); i++) {
            for (int j = 0; j < start.size(); j++) {
                if (i == j) continue;
                tS += S[start[i]][start[j]];
            }
        } // Team start

        diff = tL - tS; // 두 팀의 능력치 차
        if (diff < 0) diff = (-1) * diff; // 차가 음수일 경우 양수로 변경

        return diff;
    } // sum of S
    int ans = -1;
    link.push_back(index); // index번째 사람을 링크팀에 배치하는 경우
    int resultL = score(N, index + 1, link, start); // 재귀함수. 크기만 1 증가
    if (ans == -1 || (resultL != -1 && resultL < ans))
        ans = resultL;
    cout << ans << '\n';
    link.pop_back(); // 한 명 out

    start.push_back(index); // index번째 사람을 스타트팀에 배치하는 경우
    int resultS = score(N, index + 1, link, start);
    if (ans == -1 || (resultS != -1 && resultS < ans))
        ans = resultS;
    cout << ans << '\n';
    start.pop_back(); // 한 명 out

    return ans;
}


int main(void)
{
    // 입력 최적화
    cin.tie(NULL);
    ios::sync_with_stdio(0);
    cin >> N; // 몇 명인지
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> S[i][j]; // N X N만큼의 능력치 입력받기
        }
    }

    int ans = score(N, 0, link, start);
    cout << ans << endl;


    return 0;
}