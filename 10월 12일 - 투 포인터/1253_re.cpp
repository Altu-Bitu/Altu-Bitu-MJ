//
// Created by user on 2021-11-02.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//좋은 수인지 검사하는 함수(투 포인터)
bool isGood(vector<int> &num, int left, int right, int idx) { // n개 수가 저장된 정렬된 벡터, 왼쪽(벡터 시작점), 오른쪽(벡터 끝점), 현재 수 위치
    while (left < right) { // 양 끝에서 차례로 계산하기 때문에 left가 right보다 작을 경우만 계산하면 된다.
        if (left == idx) { //left가 현재 수 위치와 같은 경우
            left++; // left 위치 한칸 증가
            continue; // 계속
        }
        if (right == idx) { //right가 현재 수 위치와 같은 경우
            right--; // right 위치 한칸 감소
            continue; // 계속
        }

        if (num[left] + num[right] == num[idx]) // left와 right위치에 있는 수의 합이 현재 수와 같다면
            return true; // true 반환

        if (num[left] + num[right] > num[idx]) //만드려는 수보다 크다면
            right--; // 오른쪽 위치 감소 (이전 수가 무조건 더 작으니까(정렬되어있음))
        else // 만드려는 수보다 작다면
            left++; // 왼쪽 위치 증가 (다음 수가 무조건 더 크니까)
    } // end of while
    return false; // 조건 만족하지 않으면 false 리턴
}

/**
 * 1. 각 수마다 양 쪽 끝에서 포인터를 시작해서 좁혀오면서 어떤 '다른 두 수'가 현재 수를 만들 수 있는지 검사
 * 2. 포인터를 차례로 옮기며 검사하기 위해 미리 수를 오름차순 정렬함
 * 3. 현재 만드려는 수의 위치와 left, right 포인터 위치가 겹칠 경우 처리 주의
 */

int main() {
    int n, ans = 0;

    //입력
    cin >> n;
    vector<int> num(n, 0); // N개의 수 저장할 벡터 생성
    for (int i = 0; i < n; i++) // 반복문 돌아가면서
        cin >> num[i]; // n개의 수 입력받기

    //연산
    sort(num.begin(), num.end()); // 오름차순 정렬
    for (int i = 0; i < n; i++) { // n번만큼 반복문 돌면서
        if (isGood(num, 0, n - 1, i)) // 좋은 수라면
            ans++; // 정답 추가
    }

    //출력
    cout << ans << '\n';

    return 0;
}