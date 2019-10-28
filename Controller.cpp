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

	// TASK 2
	// return sqrt((gravity * pow(enemyPos.x - tankPos.x, 2) / ((sin(2 * shotAngleRadians) * ((enemyPos.x - tankPos.x) - (-(enemyPos.y - tankPos.y) * (cos(shotAngleRadians) / sin(shotAngleRadians))))))));

	// TASK 3
	Vector2 s = enemyPos - tankPos;
	float x = s.x;
	float y = -s.y;
	float g = gravity;
	float w = wind;
	float alpha = (g * x + w * y) / (g * cos(shotAngleRadians) + w * sin(shotAngleRadians));
	float u = alpha * sqrt((w) / (2 * (x - cos(shotAngleRadians) * alpha)));
	return u;


}

// Calculate the shot angle to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotSpeed: the speed of the shot, in pixels per second
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind)
{
	Vector2 s = enemyPos - tankPos;
	float x = s.x;
	float y = s.y;
	float g = gravity;
	float u = shotSpeed;

	float a = (g * pow(x,2)) / (2*pow(u,2));
	float b = -x;
	float c = (a + y);

	return atan((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

