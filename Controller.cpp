#include "stdafx.h"
#include "Controller.h"

// Calculate the shot speed to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotAngleRadians: the angle of the shot, in radians from horizontal (positive angles are upwards)
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotSpeed(const Vector2& tankPos, const Vector2& enemyPos, float shotAngleRadians, float gravity, float wind)
{
	// TODO: calculate the required shot speed (in pixels per second) and return it
	
	// TASK 1
	// return sqrt((gravity * (enemyPos.x - tankPos.x)) / (sin(2 * shotAngleRadians)));
	// Used formula from the session: u = sqrt(x * g / sin(2* phi))

	// TASK 2
	return sqrt((gravity * pow(enemyPos.x - tankPos.x, 2) / ((sin(2 * shotAngleRadians) * ((enemyPos.x - tankPos.x) - (-(enemyPos.y - tankPos.y) * (cos(shotAngleRadians) / sin(shotAngleRadians))))))));
	// Used formula s = u * t + 1/2 * a * t^2
	// And split into separate equations using x components and y components
	// Considering u = (u * cos phi | u * sin phi) and a = (0 | gravity) we have:
	// x = u * t * cos phi => t = x / u * cos phi
	// y = u * t * sin phi + 1/2 * gravity * t^2
	// Solving for u, we have:
	// u = sqrt(gravity * x^2 / sin(2 * phi) * (x - y * cotan(phi))

	// TASK 3 - NEEDS REWORK
	//Vector2 s = enemyPos - tankPos;

	//float w = wind;
	//float g = gravity;
	//float x = s.x;
	//float y = s.y;
	//float alpha = g * x + w * y;
	//float beta = w * sin(shotAngleRadians) + g * cos(shotAngleRadians);
	//float f = alpha / beta;

	//return f * sqrt(w / (2 * (x - (cos(shotAngleRadians)*f))));

}

// Calculate the shot angle to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotSpeed: the speed of the shot, in pixels per second
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind)
{
	// TODO: calculate the required shot angle (in radians) and return it
	return M_PI * 0.25f;
}

