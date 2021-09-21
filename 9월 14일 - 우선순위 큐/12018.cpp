//
// Created by user on 2021-09-21.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//가장 마일리지가 적게드는 과목부터 수강
int maxClass(int m, priority_queue<int, vector<int>, greater<>> &pq) {
    int result = 0;
    while (!pq.empty() && pq.top() <= m) { //더이상 들을 과목이 없거나, 마일리지가 모자르면 반복문 탈출
        m -= pq.top();  // pq.top(): 큐 맨 앞에 있는 원소 반환
        pq.pop(); // 원소 반환 후 삭제
        result++; // 수강 가능하니까 result에 1 추가
    }
    return result;
}

/**
 * 수강 인원이 미달일 때 필요한 마일리지는 0이 아니라 1
 * 1. 각 과목을 듣기 위해 필요한 최소 마일리지를 계산 (정렬)
 * 2. 가장 마일리지가 적게 드는 과목부터 수강 신청 (우선순위 큐 or 정렬)
 */
int main() {
    int n, m, p, l;
    priority_queue<int, vector<int>, greater<>> pq; //최소 힙

    cin >> n >> m; // n: 과목 수, m: 주어진 마일리지
    while (n--) { // 각 과목마다 2줄의 입력이 주어진다.
        //입력
        cin >> p >> l; // p: 과목을 신청한 사람, l: 과목의 수강 인원
        vector<int> arr(p);
        for (int i = 0; i < p; i++)
            cin >> arr[i]; // 각 사람이 마일리지를 얼마나 넣었는지

        //연산
        if (p < l) { //수강인원이 미달이라면 마일리지를 1만 넣어도 됨
            pq.push(1);
            continue;
        }
        sort(arr.begin(), arr.end(), greater<>()); //내림차순 정렬
        pq.push(arr[l - 1]); //l번째로 마일리지를 많이 넣은 사람과 같은 양의 마일리지를 넣어야 수강 가능
    }

    //출력
    cout << maxClass(m, pq);  // 정렬된 pq를 maxClass에 대입해서 result 반환
}