//
// Created by user on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef pair<int, int> ci;

map<int, ci>::iterator delCandidate(map<int, ci> &candidate) {
    auto del = candidate.begin(); //처음 후보를 삭제한다 가정
    int cnt = candidate.begin()->second.first; //처음 후보의 추천 횟수
    int t = candidate.begin()->second.second; //처음 후보의 게시 시간
    for (auto iter = ++candidate.begin(); iter != candidate.end(); iter++) { // 후보 수만큼 반복
        int cur_cnt = iter->second.first;   // 후보의 추천 횟수
        int cur_t = iter->second.second;    // 후보의 게시 시간
        if (cur_cnt < cnt) { //추천 횟수가 가장 작은 후보 찾기
            cnt = cur_cnt;  // 현재 후보가 추천 횟수가 가장 작다면 cnt 수를 그 후보의 추천 횟수로 업데이트
            t = cur_t;  // 게시 시간도 업데이트
            del = iter; // 해당 후보를 삭제
        } else if (cur_cnt == cnt && cur_t < t) { //추천 횟수가 가장 작은 후보가 여러명이라면, 게시 시간이 오래된 후보 찾기
            t = cur_t;  // 게시 시간 업데이트하고
            del = iter; // 해당 후보를 삭제
        }
    }
    return del; // 삭제하는 후보 반환
}

/**
 * 1. 비어있는 사진틀이 없는 경우, 가장 추천수가 작은 학생 중 게시 시간이 오래된 학생을 삭제
 * 2. 후보 학생을 바로 찾기 위해 본 풀이는 map 컨테이너를 사용해 구현
 *
 * !주의! 게시 시간 정보 저장 시, 후보로 올라간 가장 첫 시간을 저장. 이미 후보에 있는데 게시 시간이 갱신되지 않도록 주의.
 */

int main() {
    int n, m, input;
    // n: 사진틀의 개수
    // m: 전체 학생의 총 추천 횟수

    //입력 & 연산
    cin >> n >> m;
    map<int, ci> candidate; //first: 후보 학생, second: {추천 횟수, 게시 시간}
    for (int i = 0; i < m; i++) {   // 추천 횟수만큼 반복하면서
        cin >> input;   // 추천받은 학생 번호 입력
        if (candidate.size() == n && candidate.find(input) == candidate.end()) //비어있는 사진틀이 없는 경우
            candidate.erase(delCandidate(candidate));   // 사진틀에서 조건에 맞는 후보를 삭제

        if (candidate.find(input) == candidate.end()) //첫 게시라면
            candidate[input].second = i;    // 후보 그냥 사진틀에 추가
        candidate[input].first++; //추천 횟수 증가
    }

    //출력
    for (auto iter = candidate.begin(); iter != candidate.end(); iter++)    // 후보 리스트 크기만큼 반복하면서
        cout << iter->first << ' ';
}