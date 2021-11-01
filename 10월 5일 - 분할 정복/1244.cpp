//
// Created by user on 2021-10-12.
// [백준] 1244 - 스위치 켜고 끄기
// 211005 - 분할 정복
//

#include <iostream>
#include <vector>

using namespace std;

//남학생의 스위치 바꾸기
vector<int> changeSwitchBoy(int n, int number, vector<int> switches) {
    for (int i = number; i <= n; i += number) //배수에 있는 스위치 바꾸기
        switches[i] = !switches[i]; // 반대로 -> 1이면 0으로, 0이면 1로

    return switches;        // 변경된 결과 리턴
}

//여학생의 스위치 바꾸기
vector<int> changeSwitchGirl(int n, int number, vector<int> switches) {
    switches[number] = !switches[number];       // 일단 받은 수의 스위치는 상태 변경
    for (int i = 1; i < number; i++) {  // 좌우 대칭인 구간 동안
        if ((number + i > n) || (switches[number - i] != switches[number + i])) //스위치 범위 넘어가거나 좌우 대칭이 아니면
            break;      // 여학생 스위치 바꾸기 종료
        // 이 외: 스위치 범위 내 && 좌우 대칭
        switches[number - i] = !switches[number - i];   // 받은 수 이전 스위치 상태 변경
        switches[number + i] = !switches[number + i];   // 받은 수 이후 스위치 상태 변경
    }

    return switches;      // 변경된 결과 리턴
}

/**
 * 남학생 -> 해당 번호의 배수에 해당하는 스위치 상태 바꾸기
 * 여학생 -> 해당 번호를 중심으로 좌우 대칭이면서 가장 많은 스위치 포함하는 구간의 상태 모두 바꾸기
 *
 * 좌우 대칭 검사 시, 스위치 범위 주의 (주어진 스위치 범위 넘어가지 않도록)
 * 스위치 20개씩 출력하는 부분 주의
 */
int main() {
    int n, m;   // n: 스위치 개수, m: 학생 수
    int student, number;    // student: 학생의 성별, number: 학생이 받은 수

    //입력
    cin >> n;   // 스위치 개수 입력받기
    vector<int> switches(n + 1, 0); // 반복문 1부터 시작이니까 크기는 n + 1
    for (int i = 1; i <= n; i++)    // n번만큼 반복문 돌면서
        cin >> switches[i];         // 스위치 상태 입력받기

    //입력 & 연산
    cin >> m;   // 학생 수 입력받기
    while (m--) {   // m이 0이 될 때까지 1씩 줄여가면서
        cin >> student >> number;   // 학생의 성별과 받은 수 입력받기
        if (student == 1)   // 1 -> 학생이 남자면
            switches = changeSwitchBoy(n, number, switches);    // 남학생의 스위치 바꾸기
        else    // 2 -> 학생이 여자면
            switches = changeSwitchGirl(n, number, switches);   // 여학생의 스위치 바꾸기
    }

    //출력
    for (int i = 1; i <= n; i++) {
        cout << switches[i] << ' '; // 변경된 스위치 값 출력
        if (i % 20 == 0)    // 한 줄에 20개씩 출력하니까 20의 배수일 때마다
            cout << '\n';   // 줄 구분
    }
    return 0;
}