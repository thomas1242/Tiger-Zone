
#ifndef Board_h
#define Board_h


class Board {

public:
    Board();
    int  get(int col, int row);
    void set(int col, int row, int value);
    void printBoard();
    
private:
    int board[11][11];
};



#endif
