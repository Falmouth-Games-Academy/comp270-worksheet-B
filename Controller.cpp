#include "stdafx.h"
#include "Controller.h"
#include <math.h>

// Calculate the shot speed to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotAngleRadians: the angle of the shot, in radians from horizontal (positive angles are upwards)
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotSpeed(const Vector2& tankPos, const Vector2& enemyPos, float shotAngleRadians, float gravity, float wind)
{

	Vector2 posDif = enemyPos - tankPos;


	std::cout << posDif.y << std::endl;
	// TODO: calculate the required shot speed (in pixels per second) and return it
	return calculateVelocity(posDif, gravity, shotAngleRadians, wind);// 700;
}

// Calculate the shot angle to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotSpeed: the speed of the shot, in pixels per second
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind)
{
	// get our x and y difs
	float x_dif = enemyPos.x - tankPos.x;
	float y_dif = -(enemyPos.y - tankPos.y);

	//find angle
	float feta = powf(shotSpeed, 4.0f) - gravity * (gravity * x_dif * x_dif + 2.0f * y_dif * powf(shotSpeed, 2.0f));
	feta = sqrtf(feta);
	float rad = atan2f(powf(shotSpeed, 2.0f) + feta, gravity*x_dif);		// this can be +/- feta; '-' is more direct while '+' goes really high :D
																			// if both + and - give the same answser then it is the lowest possible
																			// velocity that can be applied to hit the target.
	return rad;
}

float Controller::calculateVelocity(const Vector2& dif, float gravity, float angle, float wind)
{

	//caculate the inital force.
	float force = (dif.x * dif.x * gravity) /  (dif.x * sinf(angle * 2.f)  -  2.f * -dif.y * cosf( angle ) * cosf(angle) );

	force = sqrtf(force);

	return  force;

}

float Controller::WindCounterForce(float wind, float force)
{

	return 0.0f;

}

float Controller::GetFlightLength(float heightDif, float force, float angle, float gravity)
{

	Vector2 velocity = force * Vector2(cosf(angle), sinf(angle));

	return (velocity.y / gravity) * 2.0f;// *(1 + fall_len);

}