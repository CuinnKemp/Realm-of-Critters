#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Player.h"
#include "Enemies.h"
#include "SpinningBlade.h"
#include "SpinningBladeSpawner.h"

extern Player P1;

// constructor
 SpinningBladeSpawner::SpinningBladeSpawner(Enemies* enemies){
  //set enemies as the pointer
    this->enemies = enemies;
    
    //set blade count to 0
    this->sBladeCount = 0;
 }
 SpinningBladeSpawner::~SpinningBladeSpawner(){

 }

 bool SpinningBladeSpawner::updateAbility(){
  // if the blade count is 0
    if (sBladeCount == 0){
      // create new blade
        this->sBlades = new SpinningBlade[1];

        // add 1 to the blade count
        this->sBladeCount++;
    }

    // if player has increased lvl of sblade then need to make new one
    else if (this->sBladeCount < (P1.sBladeLvl)){
      //create a temp holding array for sblades
      SpinningBlade* sBladeHold = this->sBlades;
      // create an incrementally larger array
      this->sBlades = new SpinningBlade[sBladeCount + 1];
      // copy values from previous array to new array
      for (int i = 0; i < sBladeCount; i++){
        this->sBlades[i] = sBladeHold[i];
      }
      // add 1 to the blade count
      this->sBladeCount++;
    }
    // update the blades for all blades 
    for (int i = 0; i < sBladeCount; i++){
      this->sBlades[i].movement(i,sBlades);
      this->sBlades[i].updateAbility();
      this->sBlades[i].hitEnemy(enemies);
    }

    return 1;
}

// resets all values
void SpinningBladeSpawner::resetSpawner(){
  this->sBladeCount = 0;
  delete[] this->sBlades;
}