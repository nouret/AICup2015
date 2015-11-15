#pragma once

#ifndef _MY_STRATEGY_H_
#define _MY_STRATEGY_H_

#include "Strategy.h"

class MyStrategy : public Strategy {
public:
	int _time;
	double X_10timesago;
	double Y_10timesago;
    MyStrategy();
    void move(const model::Car& self, const model::World& world, const model::Game& game, model::Move& move);
};

#endif
