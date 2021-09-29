#include <iostream>
#include <vector>

using namespace std;

struct info { //내구도와 로봇 존재 여부를 알려주는 구조체
    int power; // 칸의 내구도
    bool is_on; // 로봇의 존재 여부
};

vector<info> belt;  //컨테이너 벨트 정보(내구도, 로봇 여부)
int zero_power;     //내구도가 0인 벨트 칸의 개수

// 1번: 벨트의 방향이 오른쪽이므로, 벨트 한 칸 회전 시 올리는 위치와 내리는 위치의 인덱스 값은 하나 감소
int minusPosition(int n, int pos) { //인덱스 감소
    if (--pos >= 0) // 위치 - 1이 0이상이면
        return pos;  // pos 반환
    return n * 2 - 1; // 올리는 위치/내리는 위치 인덱스 변경(-1)
}

// 2번: 가장 먼저 올라간 로봇부터 고려해야 하므로 (내리는 위치 - 1)부터 (올리는 위치)까지 검사 -> 로봇 옮기는 거 가능하면 존재여부 체크하고 내구도 감소
void second(int n, int start, int end) {
    int cur = end; // 현재 위치를 end로 설정
    while (cur != start) { //end - 1 부터 start 까지 검사
        cur = minusPosition(n, cur); // 벨트 회전 대신 cur가 위치 변경
        int next = (cur + 1) % (n * 2); //다음 위치
        if (belt[cur].is_on && !belt[next].is_on && belt[next].power) { //현재 위치에 로봇이 있고, 다음 위치에 로봇이 없으며 내구성 1이상인 경우 -> 로봇 옮김
            belt[cur].is_on = false; // 옮기고 나면 현재 위치에 로봇이 없기 때문에 false로 값 변경
            belt[next].power--; //옮긴다면 내구도 1 감소
            if (next != end) //내리는 위치 아닐 경우만
                belt[next].is_on = true; //로봇 옮기기
            if (belt[next].power == 0) // 내구도 0이면
                zero_power++; // 내구도가 0인 칸의 개수 + 1
        }
    }
}

// 3번: 올리는 위치 칸 내구도 0이 아니라면 해당 칸 로봇 존재 여부 체크 + 내구도 감소
void third(int start) { // start: 올리는 위치
    if (belt[start].power) { //올리는 위치의 내구도가 0이 아니라면 로봇 올림
        belt[start].is_on = true; // 현재 위치에 있음을 알리기 위해 true로 변경
        belt[start].power--; // 로봇 올리니까 내구도 1 감소
        if (belt[start].power == 0) // 내구도 0이면
            zero_power++; // 내구도가 0인 칸의 개수 1 증가
    }
}

/**
 * [백준] 20055번 - 컨베이어 벨트 위의 로봇 문제
 * 1. 벨트가 각 칸 위의 로봇과 함께 한 칸 회전
 * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트 회전 방향으로 한 칸 이동할 수 있다면 이동 (이동가능: 이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1 이상이어야 함)
 * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇 올림
 * 4. 내구도가 0인 칸의 개수가 k개 이상이라면 과정 종료. 그렇지 않다면 1로 돌아감
 * -> 1 ~ 3까지가 1단계
 *
 * [문제 풀이]
 * 벨트의 로봇을 옮기는 게 아니라, 올리는 위치와 내리는 위치의 인덱스 값을 바꿔서 접근
 * 필요한 컨테이너: 내구도와 로봇의 존재여부를 체크할 배열
 * 1번: 벨트의 방향이 오른쪽이므로, 벨트 한 칸 회전 시 올리는 위치와 내리는 위치의 인덱스 값은 하나 감소
 * 2번: 가장 먼저 올라간 로봇부터 고려해야 하므로 (내리는 위치 - 1)부터 (올리는 위치)까지 검사 -> 로봇 옮기는 거 가능하면 존재여부 체크하고 내구도 감소
 * 3번: 올리는 위치 칸 내구도 0이 아니라면 해당 칸 로봇 존재 여부 체크 + 내구도 감소
 */

int main() {
    // cin의 속도를 빠르게 해준다 
    ios_base::sync_with_stdio(false); // c와 c++ 입출력의 synchronization을 false로 바꿔준다 
    // c와 c++ 입출력 동기화를 꺼줘서 c++ 입출력시 독립된 버퍼 사용
    cin.tie(NULL); // cin이 묶여있는 것을 풀어준다. 

    int n, k; // n: 칸의 수, k: 내구도가 0인 칸의 개수의 최대값

    //입력
    cin >> n >> k;
    belt.assign(n * 2, { 0, false }); // 컨테이너 벨트의 칸을 n * 2로, 로봇 여부를 {0, false}로 변경
    for (int i = 0; i < n * 2; i++) // 2 * n만큼의 칸에 각각
        cin >> belt[i].power; // 내구도 입력

    //연산
    int start = 0;    //올리는 위치
    int end = n - 1;  //내리는 위치
    int step = 0;     //단계 수
    while (true) { // 조건 만족 전까지 무한 루프
        start = minusPosition(n, start); // 반복 돌며 올리는 위치 변경
        end = minusPosition(n, end); // 반복 돌며 내리는 위치 변경
        if (belt[end].is_on) //벨트 회전 후, 로봇이 내리는 위치에 있다면 내리기
            belt[end].is_on = false; // 내리고 false로 바꿔주기
        second(n, start, end); // 옮기는거 가능하면 존재여부 체크하고 내구도 감소
        third(start); // 올리는 위치의 칸의 내구도가 0이 아니라면 해당 칸의 로봇이 존재하는지 체크하고 없으면 로봇 올리고 내구도 감소
        step++; // 단계 한개 증가
        if (zero_power >= k) // 내구도가 0인 칸의 개수가 k 이상이면
            break;  // 반복문 탈출
    }

    // 단계 출력
    cout << step << '\n';

    return 0; // 정상 종료
}