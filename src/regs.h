
#ifndef regs_h
#define regs_h

class Trail {
    
public:
    Trail();
    ~Trail();
    void setId(int id);
    int getId();
    int owner;         // true if we own the region, false if un-owned
    int edgeConnects;   // number of edge connections
    
private:
    int id;
};

//=====================================================

class Lake {
    
public:
    Lake();
    ~Lake();
    void setId(int id);
    int getId();
    int owner;         // true if we own the region, false if un-owned
    int edgeConnects;   // number of edge connections
    
private:
    int id;			// which jungle is this
    
};

//=====================================================


class Jungle {
    
public:
    Jungle();
    ~Jungle();
    void setId(int id);
    int getId();
    int owner;         // true if we own the region, false if un-owned
    int edgeConnects;   // number of edge connections
    
private:
    int id;			// which jungle is this
    
};






#endif /* Header_h */
