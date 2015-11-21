#pragma once

#ifndef _MY_STRATEGY_H_
#define _MY_STRATEGY_H_

#include "Strategy.h"

class MyStrategy : public Strategy {
public:
	bool back;
	int add;
	double sum_speed;
	double last_speed[10];
    MyStrategy();
    void move(const model::Car& self, const model::World& world, const model::Game& game, model::Move& move);
};

#endif
