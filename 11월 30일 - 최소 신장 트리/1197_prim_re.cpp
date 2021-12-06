//
// Created by user on 2021-12-06.
//

//
// Created by iw040 on 2021/11/30.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int INF = 1e6;
typedef pair<int, int> ci;

int prim(int v, int start, vector<vector<ci>> &graph) {
    int sum = 0; // 가중치 변수
    //vector<int> dist(v + 1, INF); //각 정점까지의 비용 (없어도 상관없으나, 사용하면 메모리를 좀 더 아낄 수 있음)
    vector<bool> visited(v + 1, false); //정점 방문 여부 (다익스트라와 달리 프림에선 필요!)
    priority_queue<ci, vector<ci>, greater<>> pq; // 우선순위큐 선언

    //초기화
    //dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {   // 큐가 비어있지 않을 동안
        int weight = pq.top().first; //간선 가중치
        int node = pq.top().second; //현재 정점
        pq.pop();   // 맨 위에 있는 값 out

        if (visited[node]) //이미 확인했던 정점
            continue;   // pass
        sum += weight; //MST 간선 가중치 총 합에 더해줌
        visited[node] = true; //방문 처리

        for (int i = 0; i < graph[node].size(); i++) {  // 그래프의 크기 동안 반복
            int next_node = graph[node][i].first;   // 다음 정점
            int next_weight = graph[node][i].second;    // 다음 간선 가중치
            if (!visited[next_node]) { //미방문 정점(이면서 더 짧은 간선을 통해 갈 수 있다면)
                //dist[next_node] = next_weight;
                pq.push({next_weight, next_node});  // 큐에 삽입
            }
        }
    }
    return sum; // 트리의 가중치 반환
}

int main() {
    int v, e, a, b, c;
    // v: 정점의 개수, e: 간선의 개수
    // a, b, c: 간선에 대한 정보

    //입력
    cin >> v >> e; // 정점과 간선의 개수 입력
    vector<vector<ci>> graph(v + 1, vector<ci>(0)); // 정점 개수만큼의 크기를 가진 그래프 생성
    while (e--) { //무방향 그래프
        cin >> a >> b >> c; // 간선 정보 입력
        graph[a].emplace_back(b, c);    // a번 정점과 b번 정점이 가중치 c인 간선으로 연결
        graph[b].emplace_back(a, c);    // b번 정점과 a번 정점이 가중치 c인 간선으로 연결
    }

    //연산 & 출력
    cout << prim(v, 1, graph);
}