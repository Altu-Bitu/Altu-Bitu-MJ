//
// Created by user on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<double, double> ci;
typedef tuple<double, int, int> tp;

vector<int> parent;

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node;    // 입력한 노드가 루트 정점이므로 노드 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) {
    int xp = findParent(x); // x의 루트 정점
    int yp = findParent(y); // y의 루트 정점

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; // 할 수 없으므로 false 리턴하고 함수 종료
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];   // xp에 yp 트리 추가
        parent[yp] = xp;    // yp의 루트 정점을 xp로 설정
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];   // yp에 xp 추가
        parent[xp] = yp;    // xp의 루트 정점을 yp로 설정
    }
    return true;    // 유니온 가능하다고 반환
}

double kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq) {
    int cnt = 0;    // 사용한 간선 카운트
    double sum = 0; //  간선의 가중치

    while (cnt < v - 1) { //사용한 간선의 수가 v-1보다 적을 동안
        double cost = get<0>(pq.top()); // 가중치 추가
        int x = get<1>(pq.top());   // x의 좌표 저장
        int y = get<2>(pq.top());   // y의 좌표  저장

        pq.pop();   // 정보 입력한 간선 out
        if (unionInput(x, y)) { //유니온 했다면
            cnt++; //사용된 간선 증가
            sum += cost; //간선의 가중치
        }
    }
    return sum;
}

/**
 * 4386번 : 별자리 만들기의 응용 문제
 * 이미 연결된 정점들이 존재한다는 것을 제외하고는 4386번과 동일
 *
 * 1. 임의의 두 별에 대한 거리(간선) 모두 구하기
 * 2. 이미 존재하는 통로들 표시
 *    !주의! 통로의 개수가 m개라면 v-m-1개의 간선만 더 추가하면 될까?
 *          이미 연결된 통로들도 사이클을 이룰 수 있기 때문에 유니온 연산을 하며 사이클 없이 연결된 간선만 세기
 * 3. 이미 연결된 통로의 수를 k개라고 하면 v-k-1개의 간선을 추가로 선택
 */
int main() {
    int n, m, a, b, v = 0;
    // n: 우주신들의 개수, m: 이미 연결된 통로의 수
    priority_queue<tp, vector<tp>, greater<>> pq; // 우선순위 큐

    //입력
    cin >> n >> m;
    parent.assign(n + 1, -1);   // -1로 초기화
    vector<ci> stars(n + 1);    // 별 개수만큼 벡터 생성
    for (int i = 1; i <= n; i++)    // n개의 별에 대해
        cin >> stars[i].first >> stars[i].second;   //  우주신들의 좌표 적기


    //연산
    //임의의 두 별에 대한 거리(간선) 모두 구하기
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            double xd = stars[i].first - stars[j].first; //두 별사이 x축 거리
            double yd = stars[i].second - stars[j].second;  // 두 별 사이 y축 거리
            pq.push({sqrt(xd * xd + yd * yd), i, j});   // 두 별 사이 거리를 큐에 추가
        }
    }
    while (m--) {   // 연결된 통로들에 대해
        cin >> a >> b; // 통로 연결 정보 추가
        if (unionInput(a, b)) //이미 연결된 통로
            v++;
    }

    //연산 & 출력
    cout << fixed;
    cout.precision(2);  // 소수점 둘째자리까지 출력
    cout << kruskal(n - v, pq); // 최소의 통로 길이 출력
}