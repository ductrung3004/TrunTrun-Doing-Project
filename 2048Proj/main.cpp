#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

int board[4][4] ;
bool boardcheck[4][4];

void createnumrandomly(int i, int j){
    board[i][j] = rand() % 4 == 3 ? 4 : 2;
    return;
}
void Random2num(int count){

    int i = rand() % 4;
    int j = rand() % 4;

    if (board[i][j] == 0)
        createnumrandomly(i, j);
    else return Random2num(count);
    if (count < 2)
        return Random2num(count + 1);
    return;
}

void CheckAppearNumber(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (board[i][j] != 0) boardcheck[i][j] = true;
}


bool CheckUpColumn (int row){
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

void PushAllElementOnTop(int i, int j){
    if ((i == 0) )return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementOnTop(i-1, j);

        for(int k = i; k >= 1; k--){
            if (boardcheck[k-1][j] == 0){
                board[k-1][j] = board[k][j];
                boardcheck[k-1][j] = 1;
                board[k][j] = 0;
                boardcheck[k][j] = 0;
            }
            else{
                PushAllElementOnTop(k-1, j);
                if (boardcheck[k-1][j] == 0){
                    board[k-1][j] = board[k][j];
                    boardcheck[k-1][j] = 1;
                    board[k][j] = 0;
                    boardcheck[k][j] = 0;
                }
            }
        }

    }
}

void UpProcess(int j) {
    if (j == 4) return;

    if (CheckUpColumn(j) == 0)
        PushAllElementOnTop(3, j);
    for (int i = 0; i < 4; i++) {
        if (board[i][j] == board[i + 1][j]) {
            board[i][j] += board[i + 1][j];
            board[i + 1][j] = 0;
            boardcheck[i + 1][j] = 0;
            i++;
        }
    }
    if (CheckUpColumn(j) == 0)
        PushAllElementOnTop(3, j);
    return UpProcess(j + 1);
}
void show(){
    ofstream f;
    f.open("2048.out");

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            f << board[i][j] << " ";
        f << endl;
    }
    f.close();
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
int main(){
    input();
    srand(time(NULL));

    //Random2num(1);

    CheckAppearNumber();
    UpProcess(0);

    //Random2num(1);
    show();

    return 0;
}
