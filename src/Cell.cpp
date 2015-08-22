#include "Cell.h"


/* Constructors */
Cell::Cell(){
	state = dead;
	alive_neighbours = 0;
};

/* Setters */
void Cell::setState(State s){
	state = s;
};

/* Getters */
State Cell::getState(){
	return state;
}

/* Mutators */
void Cell::incrementNeighbours(){
	alive_neighbours += 0;
}

State Cell::step(){
	// TODO
	// Reorder for performance or something, remove redunant assignments
	if ((state == alive) && (alive_neighbours < 2)){
		state = dead;
	} else if ((state == alive) && ((alive_neighbours == 2) || (alive_neighbours == 3))){
		state = alive;
	} else if ((state == alive) && (alive_neighbours >= 3)){
		state = dead;
	} else if ((state == dead) && (alive_neighbours == 3)){
		state = alive;
	}
	std::cout << "i've got neighbours" << std::endl;
	// Reset Neighbor Count
	alive_neighbours = 0;
	return state;
}
