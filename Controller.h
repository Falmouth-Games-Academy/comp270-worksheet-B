#pragma once

#include "Vector2.h"

class Controller
{
public:
	float calculateShotSpeed(const Vector2& tankPos, const Vector2& enemyPos, float shotAngleRadians, float gravity, float wind);
	float calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind);

	float calculateVelocity(const Vector2& x_dif, float gravity, float angle, float wind);
	float WindCounterForce(float wind, float force);
	float GetFlightLength(float force, float angle, float gravity);

	const float c_canHandleHeightDifference = false;// false;
	const float c_canHandleWind = true;
	const float c_doCalculateAngle = false;

	
};
