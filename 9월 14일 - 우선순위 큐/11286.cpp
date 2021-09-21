//
// Created by user on 2021-09-21.
//

#include <iostream>
#include <queue>

using namespace std;

/**
 * 우선순위 큐의 비교함수
 * sort 함수의 비교함수 형식과 비교해보기
 */
struct cmp { // 큐의 우선순위 설정
    bool operator()(int a, int b) {
        if (abs(a) == abs(b)) // 절대값이 같은 경우
            return a > b; // 더 작은 수에 우선순위 부여
        return abs(a) > abs(b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<int, vector<int>, cmp> pq; // 우선순위 큐
    // int형 변수들을 cmp 우선순위해 정렬하는 pq라는 이름의 우선순위 큐 선언
    // 어떤 원소가 push되면 주어진 우선순위에 맞춰 큐가 정정된다.
    int n, x;

    cin >> n; // 연산의 개수 n
    for (int i = 0; i < n; i++) { // n개의 줄에 연산에 대한 정보를 나타내는 정수 x 입력
        cin >> x;
        if (x == 0) { // x가 0일 경우
            if (pq.empty()) //런타임 에러 방지
                //우선순위큐가 비어있으면 true아니면 false 반환
                cout << 0 << '\n'; // 0 출력
            else { // 우선순위 큐가 비어있지 않은 경우
                // pq.top(): 큐 맨 앞에 있는 원소 반환
                cout << pq.top() << '\n';
                pq.pop(); // 맨 앞에 있는 원소 삭제
                // 반환 했으니 삭제해서 큐에서 지운다.
            }
        } else // x가 0이 아닐 경우 배열에 x라는 값을 추가(push)
            pq.push(x);
    }
}