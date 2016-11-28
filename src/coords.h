#ifndef coords_h
#define coords_h

    class Coords {
    public:    
        int icoord;
        int jcoord;

        bool operator==(const Coords &other) const;
        bool operator==(const Coords* &other) const;
        Coords();
        Coords(int i, int j);
        ~Coords();
        void reassign(int i, int j);
    };
#endif