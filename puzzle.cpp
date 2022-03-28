#include "puzzle.h"
#include <QVector>
#include <QRandomGenerator>

QVector < bool > check(16);
Puzzle::Puzzle()
{
    startGame();
}
void Puzzle::startGame()
{
    count = 0;
    do{
        for(int i = 0; i < 16; i++){
            check[i] = false;
        }
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int x = qrand() % (16);
                while(check[x]){
                    x = qrand() % (16);
                }
                table[i][j] = x;
                check[x] = true;
                cpyTable[i][j] = table[i][j];
            }
        }
    } while(!canBeSolved());
}
bool Puzzle::isFinished()
{
    int a = 1;
    bool ans = true;
    for(int i = 0; i < 4 && ans == true; i++){
        for(int j = 0; j < 4; j++){
            if(i == 3 && j == 3){
                continue;
            }
            if(table[i][j] != a){
                ans = false;
                break;
            }
            a++;
        }
    }
    return ans;
}

bool Puzzle::canBeSolved()
{
    int sum = 0;
    QVector < int > vec;
    int place = 4;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            vec.push_back(table[i][j]);
            if(table[i][j] == 0){
                place = i;
            }
        }
    }
    for(int i = 0; i < vec.size(); i++){
        for(int j = i + 1; j < vec.size(); j++){
            if(vec[i] > vec[j] && vec[j] != 0){
                sum++;
            }
        }
    }
    return ((sum + place + 1) % 2 == 0);
}

void Puzzle::reCalc(int r, int c)
{

    bool changed = false;
    int i = r, j = c;
    if(r - 1 >= 0 && table[r - 1][c] == 0){
        i = r - 1;
        changed = true;
    }else
    if(r + 1 < 4 && table[r + 1][c] == 0){
        i = r + 1;
        changed = true;
    }else
    if(c - 1 >= 0 && table[r][c - 1] == 0){
        j = c - 1;
        changed = true;
    }else
    if(c + 1 < 4 && table[r][c + 1] == 0){
        j = c + 1;
        changed = true;
    }
    int x = table[i][j];
    table[i][j] = table[r][c];
    table[r][c] = x;
    if(changed){
        count++;
    }
}

int Puzzle::getItem(int i, int j) const
{
    return table[i][j];
}

void Puzzle::restartGame()
{
    count = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            table[i][j] = cpyTable[i][j];
        }
    }
}

int Puzzle::getCount() const
{
    return count;
}

