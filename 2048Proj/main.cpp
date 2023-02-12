#include <iostream>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
using namespace std;

int board[4][4] ;
bool boardcheck[4][4];
bool checkGameOver;

void Refillboard(){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
}

bool GameOver() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) count++;
        }
    }
    if (count == 16) return true;
    return false;
}
void createnumrandomly(int i, int j){
    board[i][j] = rand() % 10 + 1 == 9 ? 4 : 2;
    return;
}
void Random(){
    if (GameOver()) return;
    int i = rand() % 4;
    int j = rand() % 4;

    if (board[i][j] == 0)
        createnumrandomly(i, j);
    else
        return Random();
}
void Random2num(){
    Random();
    Random();
    return ;
}

void CheckAppearNumber(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (board[i][j] != 0) boardcheck[i][j] = 1;
}


bool CheckUp(int row){
    bool res = false;
    for (int column = 3; column >= 0; column--) {
        if (boardcheck[column][row] == 1)
            res = true;
        else
        if (res == true)
            return false;
    }
    return true;
}

void PushUp(int i, int j){
    if ((i == 0) )return;
    else
    {
        if (boardcheck[i][j] == 0) return PushUp(i-1, j);

        for(int k = i; k >= 1; k--){
            if (boardcheck[k-1][j] != 0)
                PushUp(k-1, j);
            if (boardcheck[k-1][j] == 0){
                board[k-1][j] = board[k][j];
                boardcheck[k-1][j] = 1;
                board[k][j] = 0;
                boardcheck[k][j] = 0;
            }
        }

    }
}

void UpProcess(int j) {
    if (j == 4) return;

    if (CheckUp(j) == 0)
        PushUp(3, j);
    for (int i = 0; i < 4; i++) {
        if (board[i][j] == 0) ++i;
        if (board[i][j] == board[i + 1][j]) {
            board[i][j] += board[i + 1][j];
            board[i + 1][j] = 0;
            boardcheck[i + 1][j] = 0;
            i++;
        }
    }
    checkGameOver = GameOver();
    if (CheckUp(j) == 0)
        PushUp(3, j);
    return UpProcess(j + 1);
}


bool CheckDown(int row){
    bool res = false;
    for (int column = 0; column <= 3; column++) {
        if (boardcheck[column][row] == 1)
            res = true;
        else
        if (res == true)
            return false;
    }
    return true;
}

void PushDown(int i, int j){
    if ((i == 3) )return;
    else
    {
        if (boardcheck[i][j] == 0) return PushDown(i + 1, j);

        for(int k = i; k <= 2; k++){
            if (boardcheck[k + 1][j] != 0)
                PushDown(k + 1, j);
            if (boardcheck[k + 1][j] == 0){
                board[k + 1][j] = board[k][j];
                boardcheck[k + 1][j] = 1;
                board[k][j] = 0;
                boardcheck[k][j] = 0;
            }

        }

    }
}

void DownProcess(int j) {
    if (j == 4) return;

    if (CheckDown(j) == 0)
        PushDown(0, j);
    for (int i = 3; i >= 0; i--) {
        if (board[i][j] == 0) i--;
        if (board[i][j] == board[i - 1][j]) {
            board[i][j] += board[i - 1][j];
            board[i - 1][j] = 0;
            boardcheck[i - 1][j] = 0;
            i--;
        }
    }
    checkGameOver = GameOver();
    if (CheckDown(j) == 0)
        PushDown(0, j);
    return DownProcess(j + 1);
}


bool CheckLeft(int column){
    bool res = false;
    for (int row = 3; row >= 0; row--) {
        if (boardcheck[column][row] == 1)
            res = true;
        else
        if (res == true)
            return false;
    }
    return true;
}

void PushLeft(int i, int j){
    if ((j == 0) )return;
    else
    {
        if (boardcheck[i][j] == 0) return PushLeft(i, j - 1);

        for(int k = j; k >= 1; k--){
            if (boardcheck[i][k - 1] != 0)
                PushLeft(i, k - 1);
            if (boardcheck[i][k - 1] == 0){
                board[i][k - 1] = board[i][k];
                boardcheck[i][k - 1] = 1;
                board[i][k] = 0;
                boardcheck[i][k] = 0;
            }
        }

    }
}

void LeftProcess(int i) {
    if (i == 4) return;

    if (CheckLeft(i) == 0)
        PushLeft(i, 3);
    for (int j = 0; j < 4; j++) {
        if (board[i][j] == 0) j++;
        if (board[i][j] == board[i][j + 1]) {
            board[i][j] += board[i][j + 1];
            board[i][j + 1] = 0;
            boardcheck[i][j + 1] = 0;
            j++;
        }
    }
    checkGameOver = GameOver();
    if (CheckLeft(i) == 0)
        PushLeft(i, 3);
    return LeftProcess(i + 1);
}

bool CheckRight(int column){
    bool res = false;
    for (int row = 0; row <= 3; row++) {
        if (boardcheck[column][row] == 1)
            res = true;
        else
        if (res == true)
            return false;
    }
    return true;
}

void PushRight(int i, int j){
    if ((j == 3) )return;
    else
    {
        if (boardcheck[i][j] == 0) return PushRight(i, j + 1);

        for(int k = j; k <= 2; k++){
            if (boardcheck[i][k + 1] != 0)
                PushRight(i, k + 1);
            if (boardcheck[i][k + 1] == 0){
                board[i][k + 1] = board[i][k];
                boardcheck[i][k + 1] = 1;
                board[i][k] = 0;
                boardcheck[i][k] = 0;
            }

        }

    }
}

void RightProcess(int i) {
    if (i == 4) return;

    if (CheckRight(i) == 0)
        PushRight(i, 0);
    for (int j = 3; j >= 0; j--) {
        if (board[i][j] == 0) j--;
        if (board[i][j] == board[i][j - 1]) {
            board[i][j] += board[i][j - 1];
            board[i][j - 1] = 0;
            boardcheck[i][j - 1] = 0;
            j--;
        }
    }
    checkGameOver = GameOver();
    if (CheckRight(i) == 0)
        PushRight(i, 0);
    return RightProcess(i + 1);
}
void show(){
    //ofstream f;
    //f.open("2048.out");
    system("cls");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    //f.close();
}
void input(){
    ifstream f;
    f.open("2048.inp");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j ++) {
            int x;
            f >> x;
            board[i][j] = x;
        }
    f.close();
}

void start(){
    char a;
    //input();
    Refillboard();
    srand(time(NULL));
    Random2num();
    CheckAppearNumber();
    checkGameOver = false;
    show();
    while (1){

        a = getch();
        if (a == 'q'){
            cout << "Quit Success";
            cout << endl << "Press any key to continue";
            getch();
            return;
        }
        if (checkGameOver) {
            cout << "Game Over!!!";
            cout << endl << "Press Q to Quit or R to Retry" << endl;
            char key = getch();
            if (key == 'r')
                return start();
            if (key == 'q')
                return;
        }
        else
            {
                switch(a)
                {
                    case 'w':
                        if (CheckUp){
                            CheckAppearNumber();
                            UpProcess(0);
                            Random2num();
                            show();
                        }
                        break;

                    case 's':
                        if (CheckDown){
                                CheckAppearNumber();
                            DownProcess(0);
                            Random2num();
                            show();
                            }
                        break;
                    case 'a':
                        if (CheckLeft){
                            CheckAppearNumber();
                            LeftProcess(0);
                            Random2num();
                            show();
                        }
                        break;
                    case 'd':
                        if (CheckRight){
                            CheckAppearNumber();
                            RightProcess(0);
                            Random2num();
                            show();
                        }
                        break;
                }
            }

    }
    return;
}
int main(){
    char start_key;
    cout << "################################" << endl;
    cout << "######WELCOME TO 2048 GAME######" << endl;
    cout << "################################" << endl;
    cout << "PRESS S TO START OR E TO EXIT" << endl;

        start_key = getch();
        while (start_key != 's' && start_key != 'e'){
            cout << "PRESS S TO START OR E TO EXIT" << endl;
            start_key = getch();

        }

        if (start_key == 's') {
            start();
        }
        if (start_key == 'e'){
            cout << "exitting...";
            return 0;
        }




}

