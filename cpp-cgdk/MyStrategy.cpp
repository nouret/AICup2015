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
    vector<vector<int> > Waypoints = world.getWaypoints();

    Waypoints[(self.getNextWaypointIndex() + 1) % (int) Waypoints.size()];

    double nextWaypointX = (self.getNextWaypointX() + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (self.getNextWaypointY() + 0.5) * game.getTrackTileSize();
    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
    sum_speed += speedModule;
    add = max(0, add - 1);
    sum_speed -= last_speed[0];
    for (int i = 0; i < 4; ++i){
        last_speed[i] = last_speed[i + 1];
    }
    last_speed[4] = speedModule;

    if (world.getTick() > 50 && world.getTick() % 50 == 0 && sum_speed + add < 1){
        back = not back;
        add = 20;
    }

    if (back){
    	move.setWheelTurn(-1 * angleToWaypoint * 10 / PI);
    	move.setEnginePower(-1.0);
    	return;
    }
    move.setWheelTurn(angleToWaypoint * 10 / PI);
    if (angleToWaypoint < 0.3){
    	move.setEnginePower(2.0);
        move.setUseNitro(true);
    }
    else{
    	move.setEnginePower(0.5);
    }
    //move.setEnginePower(1.0);
    if (speedModule * speedModule * abs(angleToWaypoint) > 2 * 2 * PI) {
        move.setBrake(true);
    }

    vector<Car> exterminate = world.getCars();
    Car now_car;
    for (int i = 0; i < 4; ++i){
        now_car = exterminate[i];
        if (now_car.isTeammate()){
            continue;
        }
        if (self.getDistanceTo(now_car) < game.getTrackTileSize()){
            if (self.getAngleTo(now_car) < 0.3){
                move.setThrowProjectile(true);
            }
        }
    }

    if (world.getTick() > game.getInitialFreezeDurationTicks()) {
        move.setSpillOil(true);
        //move.setThrowProjectile(true);
    }
}

MyStrategy::MyStrategy() {
	back = false;
    add = 0;
    for (int i = 0; i < 10; ++i){
        last_speed[i] = 0;
    }
}
