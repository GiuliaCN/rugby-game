// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/
/*
direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_position);
  UNUSED(attacker_spy);

  // TODO: Implement Defender logic here
  return (direction_t) DIR_LEFT;
}
*/

direction_t where_to (position_t defender_position, position_t attacker_position)
{
  int x_distance = defender_position.i - attacker_position.i;
  if (x_distance > 0) return (direction_t) DIR_UP;
  if (x_distance < 0) return (direction_t) DIR_DOWN;
  else return (direction_t) DIR_STAY;
}

bool same_direction (direction_t a, direction_t b)
{
  if (a.i == b.i && a.j == b.j) return true;
  return false;
}

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  //UNUSED(defender_position);
  //UNUSED(attacker_spy);

  // In C, static variables are kept between executions of the function
  // By construction, the attacker will never be in the INVALID_POSITION,
  // so this works to initialize the variable.
  static position_t previous_position = INVALID_POSITION;
  static position_t attacker_position = INVALID_POSITION;
  static direction_t best_direction = DIR_STAY;
  static int turn = 0;
  static int count_steps = 1;
  static bool spy_called = false;
  static bool en_garde = false;
  srand(time(NULL)); // randomize seed

  int random_number = rand() % 100 + 1; // random number between 1 and 100
  
  turn += 1;

  if (!spy_called && equal_positions(defender_position, previous_position)) {
    if (random_number <= turn*15 && !spy_called) {
      attacker_position = get_spy_position(attacker_spy);
      spy_called = true;
    }
  }

  if (spy_called){
    if (!en_garde){
      best_direction = where_to(defender_position,attacker_position);
      if (same_direction(best_direction, (direction_t) DIR_STAY)){
        en_garde = true;
      } 
    }

    else {
      count_steps+=1;
      if (count_steps%8 < 4) best_direction = (direction_t) DIR_UP;
      else best_direction = (direction_t) DIR_DOWN;

    }

  }

  previous_position = defender_position;
  return best_direction;
}

/*----------------------------------------------------------------------------*/
