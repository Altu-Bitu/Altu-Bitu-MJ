/*
 * [백준] 2841번 외계인의 기타 연주
 * stack의 top 값: 결국 입력된 프렛 넘버 중 가장 큰 값
 * 1. stack의 top값 < 현재 프렛: 현재 프렛 push (손가락 누르기 +1)
 * (더 높은 프렛을 누르는 음을 연주하려면 손을 뗄 필요가 없다.)
 * 2. stack의 top값 > 현재 프렛: 부등호가 반대방향이 될 때까지 pop해줘야 한다. (손가락 떼기 +1 * 반대 될 때까지 걸리는 횟수)
 * 그리고 현재 프렛 push (손가락 누르기 +1)
 * 예를 들어 5와 7을 누르고 있을 때 프렛 2를 눌렀다면 5도 7도 모두 빼줘야 함.
 * 3. stack의 top = 현재 프렛: 카운트 필요 x. 그냥 pass -> 코드 짤 필요 x
 */
#include <iostream>
#include <stack>

using namespace std;
stack <int> melody[7];

int main(void)
{
	// 입력 시간을 줄여주는 코드
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, P;
    // N: 멜로디에 포함되어 있는 음의 수
    // P: 한 줄에 있는 프렛의 수
    int n, p;
    // n: N개 줄 각각의 줄의 번호
    // p: N개 줄 각각의 줄에서 눌러야 하는 프렛의 번호
    long long count = 0;
    // count: 마지막에 반환할 손가락이 움직인 횟수

    cin >> N >> P;
    for (int i = 0; i < N; i++) // N개의 멜로디 각각의 줄에서 수행할 반복문
    {
        cin >> n >> p;
        if (melody[n].empty()) { // n번째 멜로디가 비어있다면 p값을 넣어준다. 넣을 때 손가락 짚으니까 +1
            melody[n].push(p);
            count++;
        }
        else {
            while (!melody[n].empty() && melody[n].top() > p) { // n번째 멜로디가 비어있지 않은 경우 2번 수행
                melody[n].pop();
                count++;
            }
            if (melody[n].empty() || melody[n].top() != p) {
                /*
                 * n번재 멜로디가 비어있고 top값 > p인 경우 => p값 push
                 * n번째 멜로디가 비어있고 top값 < p인 경우 => p값 push
                 * n번째 멜로디가 비어있지 않지만 top값 < p인 경우 => p값 push
                */
                melody[n].push(p);
                count++;
            }
        }
    }
    cout << count;

    return 0;
}
