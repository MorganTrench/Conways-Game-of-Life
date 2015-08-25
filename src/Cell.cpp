#include "Cell.h"


/* Constructors */
Cell::Cell(){
	current_state = dead;
	alive_neighbours = 0;
	turns_alive = 0;
};

/* Setters */
void Cell::setState(State s){
	current_state = s;
};

/* Getters */
State Cell::getState(){
	return current_state;
}

int Cell::getLifeTime(){
	return turns_alive;
}

/* Mutators */
void Cell::incrementNeighbourCount(){
	alive_neighbours += 1;
}

void Cell::step(){
	// TODO
	// Increment alive_turns
	turns_alive += 1;
	// Reorder for performance or something, remove redunant assignments
	if ((current_state == alive) && (alive_neighbours < 2)){
		current_state = dead;
	} else if ((current_state == alive) && ((alive_neighbours == 2) || (alive_neighbours == 3))){
		current_state = alive;
	} else if ((current_state == alive) && (alive_neighbours >= 3)){
		current_state = dead;
	} else if ((current_state == dead) && (alive_neighbours == 3)){
		current_state = alive;
	}
	if (current_state == dead)
		turns_alive = 0;
	// Reset Neighbor Count
	alive_neighbours = 0;
}
