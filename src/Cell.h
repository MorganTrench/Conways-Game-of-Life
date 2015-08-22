#ifndef CELL_HEADER
#define CELL_HEADER
    enum State {alive, dead};

    class Cell{

        /* Fields */
        State state;


      public:
        int alive_neighbours;
        /* Constructors */
        Cell();

        /* Setters */
		void setState(State s);

        /* Getters */
        State getState();

        /* Mutators */
		void incrementNeighbours();
		State step();
    };

#endif
