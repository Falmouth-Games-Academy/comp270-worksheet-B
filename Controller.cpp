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
	// TODO: calculate the required shot speed (in pixels per second) and return it

	Vector2 displacement = enemyPos - tankPos;

	float rotation = atan2(wind, gravity);
	float newGravity = sqrt((pow(abs(wind), 2) + pow(abs(gravity), 2)));


	Vector2 rotatDisplac = Vector2();
	rotatDisplac.x = (displacement.x * cos(rotation)) + (displacement.y * sin(rotation));
	rotatDisplac.y = (displacement.y * cos(rotation)) - (displacement.x * sin(rotation));


	float shotSpeed = sqrt(((newGravity * pow(rotatDisplac.x, 2)) / (sin(2 * shotAngleRadians))) / (rotatDisplac.x + (rotatDisplac.y * 1 / (tan(shotAngleRadians)))));   // this is horrible to look at
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

