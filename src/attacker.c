// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/
direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_spy);

  const direction_t best_direction[] = {DIR_DOWN_RIGHT, DIR_UP_RIGHT, DIR_RIGHT};

  // In C, static variables are kept between executions of the function
  // By construction, the attacker will never be in the INVALID_POSITION,
  // so this works to initialize the variable.
  static position_t previous_position = INVALID_POSITION;
  //static direction_t best_direction = DIR_DOWN_RIGHT;
  static int index_best_direction = 0;
  

  if (equal_positions(attacker_position, previous_position)) {
    index_best_direction += 1;
    //best_direction = (direction_t) DIR_UP_RIGHT;
  }

  previous_position = attacker_position;
  return best_direction[index_best_direction%3];
}
/*----------------------------------------------------------------------------*/
