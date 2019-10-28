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
	Vector2 _displacement = enemyPos - tankPos;
	// Calculate an intermediary for easier writing
	float alpha = (gravity * _displacement.x + wind * (-_displacement.y)) / (gravity * cos(shotAngleRadians) + wind * sin(shotAngleRadians));
	float shotSpeed = alpha * sqrt(abs((wind) / (2 * (_displacement.x - cos(shotAngleRadians) * alpha))));

	// Note: it has been observed that the square root can return null values 

	return shotSpeed;
}

// Calculate the shot angle to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotSpeed: the speed of the shot, in pixels per second
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotAngle(const Vector2& tankPos, const Vector2& enemyPos, float shotSpeed, float gravity, float wind)
{
	Vector2 _displacement = enemyPos - tankPos;

	// Solve for tangent of angle in a quadratic formula - using mathematic notations for these variables to ease writing
	float a = (gravity * pow(_displacement.x,2) + wind * pow(-_displacement.y, 2)) / (2*pow(shotSpeed,2));
	float b = -_displacement.x;
	float c = (a - _displacement.y);

	return atan((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

