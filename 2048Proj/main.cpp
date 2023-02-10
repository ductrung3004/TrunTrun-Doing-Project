#include <iostream>

using namespace std;

int board[4][4] = {{0, 2, 0, 4},
                   {2, 4, 0, 8},
                   {2, 0, 2, 4},
                   {2, 0, 4, 8}};
bool boardcheck[4][4];

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

    return UpProcess(j + 1);
}
void show(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}
int main(){
    cout << "The Matrix at first: " << endl;
    show();
    CheckAppearNumber();
    UpProcess(0);
    cout << "The Matrix after go up: " << endl;
    show();
    return 0;
}
