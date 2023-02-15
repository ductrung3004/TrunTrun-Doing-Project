#include <iostream>
#include <fstream>
#include <vector>
#define inpfile ("file_input.txt")

using namespace std;

int Eratosthenes(){
    int N = 1000;
    bool check[N + 1];
    for (int i = 2; i <= N; i++) {
        check[i] = true;
    }
    for (int i = 2; i <= N; i++) {
        if (check[i] == true) {
            for (int j = 2 * i; j <= N; j += i) {
                check[j] = false;
            }
        }
    }
}

int HP, MaxHP, level, remedy, maidenkiss, phoenixdown, rescue = -1;
vector<int> EventID;
int Event;
int baseDamage[6];

void baseDamage_init(){
        baseDamage[1] = 1;
        baseDamage[2] = 1.5;
        baseDamage[3] = 4.5;
        baseDamage[4] = 7.5;
        baseDamage[5] = 9.5;
}
void input() {
    fstream f;
    f.open(inpfile);
    f >> MaxHP >> level >> remedy >> maidenkiss >> phoenixdown >> rescue;
    HP = MaxHP;
    int x;
    Event = 1;
    while (f >> x) {
        EventID.push_back(x);
        Event++;
    }
    f.close();
}
int shaman(int smaller_mode){
    if (smaller_mode != 0) return smaller_mode;
    if (HP < 5)
        HP = 1;
    else
        HP /= 5;
    if (remedy > 0) {
        remedy -= 1;
        HP *= 5;
        smaller_mode = 0;
    }
    return smaller_mode;
}
int duringShaman_check(int smaller_mode){
    if (smaller_mode == 3) {
        HP *= 5;
        return 0;
    }
    return smaller_mode + 1;
}

int Siren_Vajsh(int frog_mode){
    frog_mode = 1;
    level --;
    if (maidenkiss > 0){
        maidenkiss -= 1;
        level++;
    }
}
int adventureToKoopa(){
    int smaller_mode = 0, frog_mode = 0;
    for (int event = 1; event <= Event; ++event){
        if (EventID[event] == 0)
            return 1;
        if (smaller_mode != 0){
            duringShaman_check(smaller_mode);
        }
        if (frog_mode != 0) {
            if (frog_mode < 3)
                frog_mode += 1;
            else {
                frog_mode = 0;
                level++;
            }
        }
        if (EventID[event] <= 7) {
            if (event < level) {
                level++;
                if (EventID[event] > 5)
                    level++;
                if (level > 10)
                    level = 10;

            }
            if (event > level){
                if (EventID[event] <= 5) {
                    int b = event % 10;
                    int levelO = event > 6 ? (b > 5 ? b : 5) : b;
                    int damage = baseDamage[EventID[event]] * levelO * 10;
                    HP -= damage;
                }
                else
                    if (EventID[event] == 6){
                        smaller_mode = shaman(smaller_mode);
                    }
                    else
                        Siren_Vajsh(frog_mode);


            }
        }
        if (HP <= 0) {
            if (phoenixdown > 0) {
                phoenixdown -= 1;
                HP = MaxHP;
                if (smaller_mode != 0)
                    smaller_mode = 0;
            }
            else
                return 0;
        }
    }
    return 1;
}
int main(){

    return 0;
}