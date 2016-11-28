#ifndef moves_h
#define moves_h

    class Moves {
    public:    
        int icoord;
        int jcoord;
        bool possibleorientations[4];    // 0=0, 1=90, 2=180, 3=270

        bool operator==(const Moves &other) const;
        Moves();
        Moves(int i, int j);
        ~Moves();
    };
#endif