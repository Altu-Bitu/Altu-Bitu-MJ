//
// Created by user on 2021-12-06.
//

//
// Created by iw040 on 2021/11/30.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
const double INF = 1e3;
typedef pair<double, int> ci;

double prim(int v, int start, vector<vector<ci>> &graph) {
    double sum = 0;
    vector<double> dist(v, INF); //각 정점까지의 비용
    vector<bool> visited(v, false); //정점 방문 여부
    priority_queue<ci, vector<ci>, greater<>> pq;   // 우선순위 큐 선언

    //초기화
    dist[start] = 0;    // 거리 초기화
    pq.push({0, start});    // 우선순위 큐 초기화

    while (!pq.empty()) {
        double weight = pq.top().first; //간선 가중치
        int node = pq.top().second; //현재 정점
        pq.pop();   // 가장 위에 있는 que 값 out

        if (visited[node]) //이미 확인했던 정점
            continue; // pass
        sum += weight; //MST 간선 가중치 총합
        visited[node] = true; //방문 처리

        for (int i = 0; i < graph[node].size(); i++) {  // 그래프의 크기 동안 반복
            double next_weight = graph[node][i].first;  // 다음 간선 가중치
            int next_node = graph[node][i].second;   // 다음 정점
            if (!visited[next_node] && next_weight < dist[next_node]) { //미방문 정점이면서 더 짧은 간선을 통해 갈 수 있다면
                dist[next_node] = next_weight;  //  경로의 가중치 합계 계산
                pq.push({dist[next_node], next_node});  // 큐에 삽입
            }
        }
    }
    return sum; // 트리의 가중치 반환
}

int main() {
    int n;  // n: 별의 개수

    //입력
    cin >> n;
    vector<pair<double, double>> stars(n);  // 별의 좌표
    vector<vector<ci>> graph(n, vector<ci>(0)); // 별의 개수만큼의 크기를 가진 그래프 생성
    for (int i = 0; i < n; i++) // 별의 개수만큼 반복하면서
        cin >> stars[i].first >> stars[i].second;   // 별의 좌표 입력

    //연산
    //임의의 두 별에 대한 거리(간선) 모두 구하기
    for (int i = 0; i < n - 1; i++) { // 정점 i와 y 사이
        for (int j = i + 1; j < n; j++) {
            double xd = stars[i].first - stars[j].first;    // x 거리
            double yd = stars[i].second - stars[j].second;  // y 거리
            double dist = sqrt(xd * xd + yd * yd);  // 거리 계싼
            graph[i].emplace_back(dist, j); // i번 정점과 j번 정점이 가중치 dist인 간선으로 연결
            graph[j].emplace_back(dist, i); // j번 정점과 i번 정점이 가중치 dist인 간선으로 연결
        }
    }

    //연산 & 출력
    cout << fixed;
    cout.precision(2);
    cout << prim(n, 1, graph);
}