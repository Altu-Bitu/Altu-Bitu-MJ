#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> ci; // pair를 사용하면 두 자료형 int와 int를 묶을 수 있다. 

int ans; //정답: 최대 이익

//얻을 수 있는 최대 이익 리턴하는 함수, cnt: 상담 시작 가능한 날, sum: 지금까지의 이익
void maxConsul(int n, vector<ci>& consulting, int start, int sum) { //vector<ci>& consulting: pass by reference(참조로 전달)
    if (start > n) //상담 끝나는 날이 퇴사일을 넘는다면 -> 상담할 수 없는 경우
        return; // 빠져나간다. 

    ans = max(ans, sum); // 지금까지의 이익과 최대 이익 중 더 큰 값을 새로운 최대 이익으로 만든다. 

    for (int i = start; i < n; i++) //i번째 날을 상담하는 경우
        maxConsul(n, consulting, i + consulting[i].first, sum + consulting[i].second); //재귀함수. 
    // 마지막 두 매개변수: i + consulting[i].first : 날짜 + 그 날짜의 상담을 완료하는데 걸리는 시간. 
    // sum + consulting[i].second: 지금까지의 이익 + i번째 상담으로 얻는 이익
}

/**
 * [백준] 14501반 - 퇴사
 * 상담을 적절히 했을 때, 얻을 수 있는 최대 수익을 구하는 프로그램
 *
 * [풀이]
 * 1일 부터 상담받는 경우에서 시작해서 할 수 있는 모든 경우의 수를 다 해보자
 * n = 15 이므로, 상담을 하는데 필요한 기간이 모두 1일이라 가정하면 최대 연산 횟수는
 * -> C(15,1) + C(15,2) + ... + C(15,15) <= C(15,7) * 15 = 96,525 이므로 충분히 브루트 포스 접근 가능!
 */

int main() {
    int n; //퇴사까지 남은 날

    //입력
    cin >> n;
    vector<ci> consulting(n); // 정수 두개로 이루어진 벡터 consulting 선언

    for (int i = 0; i < n; i++)
        cin >> consulting[i].first >> consulting[i].second; //first: 상담 시간, second: 이익

    //연산
    maxConsul(n, consulting, 0, 0); // 0,0 부터 시작해서 재귀함수로 시작날부터 퇴사까지 남은 날 반복문 돌고 최종 최대 이익 출력

    //출력
    cout << ans << '\n'; // maxConsul에서 받은 최대 이익 출력
     
    return 0; // 정상 종료
}