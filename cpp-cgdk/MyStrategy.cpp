#include "MyStrategy.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>

using namespace model;
using namespace std;
/*
void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    move.setEnginePower(2.0);
    move.setThrowProjectile(true);
    move.setSpillOil(true);
    _time++;
    move.setWheelTurn(0.6);

    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
        move.setUseNitro(true);
    }
}
*/
void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    double nextWaypointX = (self.getNextWaypointX() + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (self.getNextWaypointY() + 0.5) * game.getTrackTileSize();
    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
    if (world.getTick() % 20 == 0){
    	X_10timesago = self.getX();
    	Y_10timesago = self.getY();
    }
    if (world.getTick() % 20 >= 15){
    	if (self.getDistanceTo(X_10timesago, Y_10timesago) < game.getTrackTileSize() * 0.1){
    		move.setWheelTurn(-1 * angleToWaypoint * 10 / PI);
    		move.setEnginePower(-1.0);
    		return;
    	}
    }
    move.setWheelTurn(angleToWaypoint * 10 / PI);
    if (angleToWaypoint < 0.3){
    	move.setEnginePower(2.0);
    }
    else{
    	move.setEnginePower(0.5);
    }
    //move.setEnginePower(1.0);
    if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI) {
        move.setBrake(true);
    }
}

MyStrategy::MyStrategy() {
	_time = 0;
}
