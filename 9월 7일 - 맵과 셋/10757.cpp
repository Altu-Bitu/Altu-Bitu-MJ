//
// Created by user on 2021-09-14.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

int main() {
    string a, b, temp;
    int N, sum;
    int num1[10001], num2[10001];
    vector<int> total;
    cin >> a >> b;

    if(a.size() < b.size()) {
        temp = a;
        a = b;
        b = temp;
        // 자릿수가 더 많은 수를 a로 지정한다.
    }

    for (int i = 0; i < a.size(); i++)
        num1[i + 1] = a[i] - '0';
    for (int i = 0; i < b.size(); i++)
        num2[i + 1 + (a.size() - b.size())] = b[i] - '0';
    // a가 6자리, b가 4자리라면 a.size() - b.size()를 추가로 더해 자릿수를 맞춘다

    for (int i = a.size(); i > 0; i--) {
        sum = num1[i] + num2[i];
        if(sum >= 10)
        {
            num1[i - 1]++;
            sum -= 10;
        }
        total.push_back(sum);
    }

    // 맨 앞자리수 출력
    if (num1[0] != 0) cout << 1;

    // total 벡터에 넣어둔 값 거꾸로 출력
    for(int i = total.size() - 1; i >= 0; i--){
        cout << total[i];
    }
}