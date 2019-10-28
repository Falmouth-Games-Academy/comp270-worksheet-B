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
	float inclineAngle = atanf(wind / gravity);
	Vector2 distanceBetweenTanks = enemyPos - tankPos;
	Vector2 windPosition = Vector2();
	windPosition.x = (distanceBetweenTanks.x * cos(inclineAngle)) - (distanceBetweenTanks.y * sin(inclineAngle));
	windPosition.y = (distanceBetweenTanks.y * cos(inclineAngle)) + (distanceBetweenTanks.x * sin(inclineAngle));

	float angledGravity = sqrt(pow(wind, 2) + pow(gravity, 2));
	float newAngle = shotAngleRadians - inclineAngle;
	float shotSpeed = sqrt((angledGravity * pow(windPosition.x, 2)) / ((windPosition.x * sin(2 * newAngle)) + windPosition.y * (cos(2 * newAngle ) + 1 )));
	
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
	// TODO: calculate the required shot angle (in radians) and return it
	return M_PI * 0.25f;
}

