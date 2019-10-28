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
	// Time for a fresh approach - Displacing and rotating the 'world' so that the acceleration will be one dimensional - this will require us to rotate our vectors (apart from acceleration)
	Vector2 s = enemyPos - tankPos;

	// Calculate angle between new gravity and initial gravity
	float _angle = atan(wind / gravity);

	// Calculate magnitude of new gravity
	float _gravity = sqrt(pow(gravity, 2) + pow(wind, 2));

	// Adjusted displacement
	Vector2 _s = Vector2(
		(s.x * cos(_angle)) - (s.y * sin(_angle)),
		(s.x * sin(_angle)) + (s.y * cos(_angle))
	);

	return sqrt( 0.5 *
		((_gravity * pow(_s.x, 2)) /
		((_s.x * tan(shotAngleRadians - _angle) + _s.y) * (pow(cos(shotAngleRadians - _angle), 2))))
	);
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

	return atan(
		(-x + sqrt(pow(x,2)-8*g*pow(x/u,2)*(1-y)))/
		(2*g*pow(x/u,2)*(1-y))
	);
}

