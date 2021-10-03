//
// Created by user on 2021-10-04.
//
/*
 * [백준] 20923번 - 숫자 할리갈리 게임
 * 입력: N: 카드의 갯수, M: 게임 진행 횟수
 * N개의 줄에는 각각 도도와 수연이가 가진 덱의 맨 아래의 위치한 카드에 적혀있는 수부터 입력 (범위: 1~5)
 * 이기는 경우:
 *  - 수연: 그라운드에 나와있는 각각의 카드 더미에서 가장 위에 위치한 숫자 합이 5가 되는 순간
 *  - 도도: 같은 조건에서 가장 위에 있는 숫자가 5가 나오는 순간
 *      (단, 그라운드가 비어있으면 안된다.)
 */

#include <iostream>
#include <deque>

using namespace std;

int N, M;
deque <int> deck[2], ground[2];
// 도도와 수연이의 덱과 그라운드 => 2개씩 (0: dodo, 1: suyeon)
int turn = 0; // 게임은 도도부터 시작

void card_check(int win) {
    int lose = 1 - win; // win = 0이면 lose = 1, win = 1이면 lose = 0
    while (!ground[win].empty())
    {
        deck[win].push_back(ground[win].back());
        ground[win].pop_back();
    }
    while (!ground[lose].empty())
    {
        deck[win].push_back(ground[lose].back());
        ground[lose].pop_back();
    }
}

void win_check() {
    // ground.size()가 0이 아니면 true + 맨 위에 있는 (front)가 5면 도도가 이긴다. (리턴값: 0)
    if (ground[0].size() && ground[0].front() == 5) card_check(0);
    if (ground[1].size() && ground[1].front() == 5) card_check(0);
    // 양 그라운드가 비어있지 않고 맨 위에 있는 카드의 숫자의 합이 5라면 수연이가 이긴다. (리턴값: 1)
    if (ground[0].size() && ground[1].size() && ground[0].front() + ground[1].front() == 5)
        card_check(1);
}

// 승리조건: 덱에 있는 카드 수가 많은 사람이 이긴다. (0이면 do, 1이면 su, 비기면 dosu)
string print_win() {
    if (deck[0].size() > deck[1].size())
        return "do";
    else if (deck[0].size() < deck[1].size())
        return "su";
    return "dosu";
}

string round(int m) {
    while (m--) {
        ground[turn].push_front(deck[turn].front());
        deck[turn].pop_front();
        if (deck[turn].empty())
            break;
        win_check();
        turn = 1 - turn;
    } // while문
    return print_win();
}


int main(void) {
    cin >> N >> M;
    int d, s; // d: 도도가 가진 카드의 숫자, s: 수연이가 가진 카드의 숫자
    for(int i = 0; i < N; i++) {
        cin >> d >> s;
        deck[0].push_front(d);
        deck[1].push_front(s);
    }

    cout << round(M) << endl;

    return 0;
}