//
// Created by user on 2021-12-20.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 51
char board[MAX][MAX];
int N;
using namespace std;
int change(int N) {
    int result = 1; // 가로 결과 저장할 변수
    int count = 1; // 같은 값이 몇 개인지 셀 변수

    for (int i = 0; i < N; i++) {
        count = 1;
        for (int j = 1; j < N; j++) {
            if (board[i][j - 1] == board[i][j])
                count++;
            else {
                result = max(count, result);
                count = 1; // count값 초기화
            }
            // swap(board[i][j], board[i][j+1]);
        }
         // cout << "resultH: " << result << " countH: " << countH << "\n";
         result = max(count, result); // 마지막에 안 쪽 if문이 실행되었을 경우를 위해
    }

    // int resultV = 1; // 가로 결과 저장할 변수
    // int count = 1; // 같은 값이 몇 개인지 셀 변수

    for (int i = 0; i < N; i++) {
        count = 1; // 같은 값이 몇 개인지 셀 변수
        for (int j = 1; j < N; j++) {
            if (board[j - 1][i] == board[j][i])
                count++;
            else{
                result = max(count, result);
                count = 1;
            }
        }
        result = max(count, result);
        // cout << "resultV: " << result << " countV: " << countV << "\n";

    }
    // cout << "H: " << result << " V: " << result << "\n";
    return result;
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    int result = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            swap(board[i][j], board[i][j - 1]);
            result = max(result, change(N));
            swap(board[i][j], board[i][j - 1]);
            swap(board[j][i], board[j - 1][i]);
            result = max(result, change(N));
            swap(board[j][i], board[j - 1][i]);

        }
    }
    cout << result << endl;
    return 0;
}

/*
 * https://gdlovehush.tistory.com/300
 * https://1-7171771.tistory.com/39
 * https://javaju.tistory.com/131
 * https://guiyum.tistory.com/27
 * https://jaimemin.tistory.com/1068
 * https://velog.io/@josuncom/C-%EB%B0%B1%EC%A4%80-3085-%EC%82%AC%ED%83%95%EA%B2%8C%EC%9E%84
 */