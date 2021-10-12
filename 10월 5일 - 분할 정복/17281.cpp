//
// Created by user on 2021-10-12.
// [백준] 17281 - 야구
// 211005 - 분할 정복 (conquer - divide - combine)
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> innings;
vector<int> order(10, 0); //타순
vector<bool> check(10, false); // 선수의 순서 정해졌는지
int n, ans; // n: 이닝 수. ans: 최종 답

//현재 배치의 점수
int calcScore() {
    int score = 0; //총 점수
    int idx = 1; //타순 저장된 order 인덱스 번호
    for (int i = 0; i < n; i++) { //i: 이닝
        vector<bool> baseman(4, 0); //각 루수마다 선수가 있는지
        int out = 0; //아웃 선수 카운트
        while (out < 3) {   // 3아웃 발생 전까지
            int state = innings[i][order[idx++]]; //현재 선수의 공격 상태
            if (idx == 10)  // 9번 타자까지 쳤는데 3 아웃 아직 안남
                idx = 1;    // -> 1번 타자 다시 타석
            switch (state) {    // 0: 아웃, 1: 안타, 2: 2루타, 3: 3루타, 4: 홈런
                case 0: // 아웃
                    out++;  // 아웃 수 증가
                    break;  // 종료
                case 1: //안타, 1루씩 진루
                    score += baseman[3]; //3루에 있는 선수있다면 홈 도착
                    for (int i = 3; i > 0; i--) //타자와 모든 주자가
                        baseman[i] = baseman[i - 1];    // 한 루씩 진루
                    baseman[1] = 1; //새로운 선수 1루에 도착
                    break;  // 종료
                case 2: //2루타, 2루씩 진루
                    score += baseman[3] + baseman[2]; //3루, 2루에 선수 있다면 홈 도착
                    baseman[3] = baseman[1]; //1루 -> 3루 이동
                    baseman[2] = 1; //새로운 선수 2루에 도착
                    baseman[1] = 0; //초기화
                    break;  // 종료
                case 3: //3루타, 3루씩 진루
                    for (int i = 3; i > 0; i--) { //3루, 2루, 1루에 선수 있다면 홈 도착
                        score += baseman[i];    // 홈 도착했으니 득점
                        baseman[i] = 0; // 초기화
                    }
                    baseman[3] = 1; //새로운 선수 3루에 도착 -> 아직 득점 x
                    break;  // 종료
                case 4: //홈런
                    for (int i = 3; i > 0; i--) { //3루, 2루, 1루에 선수 있다면 홈 도착
                        score += baseman[i];    // 홈 도착했으니 득점
                        baseman[i] = 0; // 초기화
                    }
                    score++; //새로운 선수도 홈 바로 도착
                    break;  // 종료
            } // end of switch
        } // end of while
    } // end of for(이닝 반복)

    return score;   // 리턴값 int -> score 반환
}   // end of calcScore

//가능한 배치 모두 구하기
void array(int cnt) { //cnt: 타자순서
    if (cnt == 4) { //4번 타자는 정해져 있으므로
        array(cnt + 1); // 아무것도 안 바꾸고 타자 순서 1 증가시키고 재귀
        return; // 종료
    }
    if (cnt == 10) { //9번 타자까지 정해짐 (기저조건)
        int score = calcScore(); //점수 계산
        ans = max(ans, score);  // 최대 점수 계산하고
        return; // 종료
    }
    for (int i = 2; i <= 9; i++) {  // 나머지 타순
        if (!check[i]) {    // check[i]의 상태가 false면 if문 실행
            order[cnt] = i; //cnt번 타자: i번 선수
            check[i] = true; //i번 선수 순서 정해짐
            array(cnt + 1); //다음 타자
            check[i] = false; // 상태 초기화
        }
    }
}

/**
 * 구현 + 브루트 포스, 백트래킹
 * 1. 우선 가능한 타순을 모두 구한다. (이때, 4번 타자는 항상 1번 선수여야 함) (브루트 포스, 백트래킹)
 * 2. 구한 타순에 대한 각각의 점수를 구하며 최대 점수를 갱신한다. (구현)
 */

int main() {
    //입력
    cin >> n; // 이닝 수 입력받기
    innings.assign(n, vector<int>(10, 0)); // 입력받은 이닝 수, 이닝에서 얻는 결과
    for (int i = 0; i < n; i++) {   // 이닝 수
        for (int j = 1; j < 10; j++) { // 이닝에서 얻는 결과 (9개의 정수)만큼 반복문 돌면서
            cin >> innings[i][j];   // 선수별 이닝 결과 입력받기
        }
    }

    //연산
    order[4] = 1; //4번 타자는 1번 선수
    check[1] = true; //1번 선수는 순서 정해짐
    array(1); // 1번 선수 부터 타순 정하기 (어차피 array 함수 내 for문에서 2부터 시작)

    //출력
    cout << ans << '\n';

    return 0;   // 시스템 정상 종료
}