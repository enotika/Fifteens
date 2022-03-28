#ifndef PUZZLE_H
#define PUZZLE_H


class Puzzle
{
public:
    Puzzle();
    void startGame();
    bool isFinished();
    bool canBeSolved();
    void reCalc(int r, int c);
    int getItem(int i, int j) const;
    void restartGame();
    int getCount() const;
private:
    int table [4][4];
    int cpyTable[4][4];
    int count;
};

#endif // PUZZLE_H
