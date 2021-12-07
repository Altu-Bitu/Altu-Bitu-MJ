//
// Created by user on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;

map<ll, ll> parent; // 루트 정점 map

//Find 연산
ll findParent(ll node) {
    if (parent.find(node) == parent.end()) //parent에 존재하지 않는다면 -> 루트 정점
        return parent[node] = node + 1; // 루트 정점으로 만들어주기
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

vector<ll> assignRoom(vector<ll> &room_number) {    // 방 배정 함수
    vector<ll> answer(room_number.size(), 0);   // 정답 저장할 벡터 생성
    for (int i = 0; i < room_number.size(); i++)    // 방 번호 크기 만큼 반복하면서
        answer[i] = findParent(room_number[i]) - 1; //다음 방을 집합의 루트 정점으로 처리했기 때문에 현재 배정된 방은 1을 빼줌
    return answer;  // 정답 리턴
}

vector<ll> solution(ll k, vector<ll> room_number) { // 정답 저장 함수
    vector<ll> answer = assignRoom(room_number);    // 방 배정 함수 돌린 값을 정답에 저장
    return answer;  // 정답 값 리턴
}

/**
 * 백준의 10775와 매우 유사한 문제
 *
 * 방을 배정할 때마다 이번에 배정한 방의 다음 방을 집합의 루트 정점으로 만들어 바로 접근할 수 있도록 설정
 * parent를 벡터(혹은 배열)로 사용하면 전체 방 개수의 최대가 10^12이기 때문에 메모리 초과
 * 따라서 필요한 방의 parent정보만 저장하기 위해 map을 사용해야 함
 */

int main() {
    ll k = 10;  // 전체 방 개수 k
    vector<ll> room_number = {1, 3, 4, 1, 3, 1};    // 고객들이 원하는 방 번호가 들어있는 배열
    vector<ll> result = solution(k, room_number);   // assignRoom 돌린 함수를 결과 벡터에 저장
    for (int i = 0; i < result.size(); i++) // 결과 벡터 크기만큼 반복하면서
        cout << result[i] << ' ';   // 결과값 출력
}