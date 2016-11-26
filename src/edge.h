//#include "trail.h"
//#include "jungle.h"
//#include "lake.h"
#include "regs.h"


class Edge {
    
	public:
		Edge();	
		Edge(char type);	
		~Edge();
		char getType();
        void setEdgePointers(char type);
    
        // an edge can have.. 1 jungle OR 1 lake OR 1 trail and 2 jungles
        Jungle * j1, * j2;
        Trail  * t1;
        Lake   * l1;    // these pointers are used to point at a card's jungle/trail/lake region(s)
    
                        
	private:
		char type;	// type of edge. T,J,L

};
