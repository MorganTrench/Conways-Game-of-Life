#ifndef CELL_HEADER
#define CELL_HEADER
    enum State {alive, dead};

    class Cell{

        /* Fields */
        State current_state;
        int alive_neighbours;


      public:
        /* Constructors */
        Cell();

        /* Setters */
		void setState(State s);

        /* Getters */
        State getState();

        /* Mutators */
		void incrementNeighbourCount();
		void step();
    };

#endif
