
#ifndef regs_h
#define regs_h

class Trail {
    
public:
    Trail();
    ~Trail();
    void setId(int id);
    int getId();
    
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
    
private:
    int id;			// which jungle is this
    
};






#endif /* Header_h */
