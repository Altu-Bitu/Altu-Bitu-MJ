// 브랜치 수정
// Created by user on 2021-09-21.
//

#include <iostream>
#include <queue>

using namespace std;
typedef long long ll;

//카드들의 점수 총합
ll sum(priority_queue<ll, vector<ll>, greater<>> &pq) {
    ll result = 0; // 최종 점수
    while(!pq.empty()) { //pq가 비어있다면 반복문 탈출
        // pq가 비어있지 않다면 맨 위에 있는 값(pq.top())을 결과에 더해준 뒤 삭제(pq.pop())
        result += pq.top();
        pq.pop()
    }
}

/*
 * 매번 숫자가 가장 작은 카드 2장을 뽑아야 최종 결과가 최솟값이 된다.
 */

int main() {
    int n, m, input;
    priority_queue<ll, vector<ll>, greater<>> pq; // 최소 힙

    // 입력
    cin >> n >> m; // n: 카드의 개수, m: 카드 합체를 몇 번 하는지
    while (n--) {
        cin >> input; // 맨 처음 카드의 상태를 나타내는 수
        pq.push(input);
    }

    // 연산
    whlie (m--) {
        vector<ll> num(2); //크기가 2인 벡터 생성
        //카드의 총 수량은 변하지 않고, 카드의 개수 최솟값은 2이기 때문에 empty 체크를 하지 않아도 된다.
        for(int i = 0; i < 2; i++) { //가장 숫자가 작은 카드 2장 뽑기
            num[i] = pq.top(); // 맨 위에 있는 값(가장 숫자가 작은 값)을 num[0],두번째에 있는 값을 num[1]에 대입
            pq.pop(); // 대입한 두 숫자 삭제
        }
        for (int i = 0; i < 2; i++) //계산 한 값을 덮어쓰기
            pq.push(num[0] + num[1]); //가장 숫자가 작은 카드 2장을 더한 값을 최소 힙에 대입
    }

    //출력
    cout << sum(pq); // pq의 합 출력
}