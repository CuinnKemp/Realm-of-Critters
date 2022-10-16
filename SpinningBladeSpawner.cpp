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

 SpinningBladeSpawner::SpinningBladeSpawner(Enemies* enemies){
    this->enemies = enemies;
    
    this->sBladeCount = 0;
 }
 SpinningBladeSpawner::~SpinningBladeSpawner(){

 }

 bool SpinningBladeSpawner::updateAbility(){
    if (sBladeCount == 0){
        this->sBlades = new SpinningBlade[1];
        this->sBladeCount++;
    }

    else if (this->sBladeCount < (P1.sBladeLvl + 1)){
      
      SpinningBlade* sBladeHold = this->sBlades;
      this->sBlades = new SpinningBlade[sBladeCount + 1];
      for (int i = 0; i < sBladeCount; i++){
        this->sBlades[i] = sBladeHold[i];
      }
      this->sBladeCount++;
    }

    for (int i = 0; i < sBladeCount; i++){
      this->sBlades[i].movement(i,sBlades);
      this->sBlades[i].updateAbility();
      this->sBlades[i].hitEnemy(enemies);
    }

    return 1;
}