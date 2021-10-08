//
// Created by user on 2021-10-08.
//
#include <iostream>
#include <vector>

using namespace std;

//부분 행렬 원소 뒤집는 함수
void reverseMtx(int row, int col, vector<string> &matrix_a) {
    for (int i = row; i < row + 3; i++) { // 어떤 3x3 크기의 부분 행렬을 바꿔주는 것이므로 행 + 3까지만 반복
        for (int j = col; j < col + 3; j++) { // 마찬가지로 열도 열 + 3까지만 반복
            if (matrix_a[i][j] == '1') // 원소 값이 1이라면
                matrix_a[i][j] = '0'; // 0으로 변경
            else // 아니라면 (원소값이 0)
                matrix_a[i][j] = '1'; // 1로 변경
        }
    }
}

//마지막으로 A == B인지 확인하는 함수
int isPossible(int n, int m, vector<string> &matrix_a, vector<string> &matrix_b) {
    for (int i = 0; i < n; i++) { // 크기가 n X m인 행렬이므로 행은 n까지,
        for (int j = 0; j < m; j++) { // 열은 m까지 반복
            if (matrix_a[i][j] != matrix_b[i][j]) // A != B라면
                return false; // false 반환
        }
    }
    return true; // 아니라면 (A == B) true 반환
}

/**
 * (0, 0) 인덱스부터 부분행렬을 만들 수 있는 마지막 인덱스까지 검사하며 그리디하게 푸는 문제
 * A, B 행렬의 현재 인덱스 값이 서로 다르다면 A 행렬에서 현재 인덱스로 '시작'하는 3x3 크기만큼의 부분 행렬 원소 뒤집기
 * 검사가 모두 끝난 후, A와 B가 서로 다르다면 바꿀 수 없는 경우임
 * !주의! 입력이 공백없이 주어지므로 string으로 받음
 */

int main() {
    int n, m; // n: 행, m: 열

    //입력
    cin >> n >> m;
    vector<string> matrix_a(n); // 행렬 A 선언
    vector<string> matrix_b(n); // 행렬 B 선언
    for (int i = 0; i < n; i++)  // 행만큼 반복하면서
        cin >> matrix_a[i]; // 행렬 A 입력

    for (int i = 0; i < n; i++) // 행만큼 반복하면서
        cin >> matrix_b[i]; // 행렬 B 입력

    //연산
    int ans = 0; // 뒤집은 횟수
    for (int i = 0; i <= n - 3; i++) { // reverseMtx에서 i + 3까지 반복하기 때문에 3 빼준다.
        for (int j = 0; j <= m - 3; j++) { // j도 마찬가지
            if (matrix_a[i][j] != matrix_b[i][j]) { //(i, j)원소가 서로 다르다면
                reverseMtx(i, j, matrix_a); // 원소 뒤집기
                ans++; // 뒤집은 횟수 증가
            }
        }
    }

    //출력
    if (!isPossible(n, m, matrix_a, matrix_b)) // 두 행렬이 다르다면 (바꿀 수 없다면)
        ans = -1; // -1 출력
    cout << ans; // 정답 출력

    return 0; // 정상 종료
}
