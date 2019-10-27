#include "stdafx.h"
#include "Controller.h"
#include <math.h>
// Josh G


// Calculate the shot speed to hit the target, given the following information.
//   tankPos: the position from which the bullet will be fired, in pixels relative to the top left corner of the screen
//   enemyPos: the target position to hit, in pixels relative to the top left corner of the screen
//   shotAngleRadians: the angle of the shot, in radians from horizontal (positive angles are upwards)
//   gravity: the acceleration due to gravity in pixels/second^2 (positive is downwards)
//   wind: the acceleration due to wind in pixels/second^2 (positive is rightwards)
float Controller::calculateShotSpeed(const Vector2& tankPos, const Vector2& enemyPos, float shotAngleRadians, float gravity, float wind)
{
	Vector2 displacement = enemyPos - tankPos;

	float aaaaaangle = atanf(wind / gravity);  // angle between Y axis (gravity) and the gravity+wind combo vector
	float graaaavity = sqrt(pow(wind, 2) + pow(gravity, 2)); // magnitude of gravity+wind combo vector

	Vector2 displaaaaac = Vector2();
	displaaaaac.x = (displacement.x * cos(aaaaaangle)) - (displacement.y * sin(aaaaaangle)); // calculating X distance in new co-ord plane where graaaavity is directly downwards (y +ve)
	displaaaaac.y = (displacement.y * cos(aaaaaangle)) + (displacement.x * sin(aaaaaangle)); // calculating X distance in new co - ord plane
	
	float num = graaaavity * pow(displaaaaac.x, 2); // caluclating numerator of big equation, to make this all a tiny bit tidier
	float den = ((displaaaaac.x * tan(shotAngleRadians - aaaaaangle)) + displaaaaac.y) * (pow(cos(shotAngleRadians - aaaaaangle),2)); // calculating denominator
	
	float shotSpeed = sqrt(0.5 * (num/den));
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
	Vector2 displacement = enemyPos - tankPos;
	float aaaaaangle = atanf(wind / gravity);	// angle between Y axis (gravity) and the gravity+wind combo vector
	float graaaavity = sqrt(pow(wind, 2) + pow(gravity, 2));	// magnitude of gravity+wind combo vector

	Vector2 displac = Vector2();
	displac.x = (displacement.x * cos(aaaaaangle)) - (displacement.y * sin(aaaaaangle)); // calculating X distance in new co-ord plane where graaaavity is directly downwards (y +ve)
	displac.y = (displacement.y * cos(aaaaaangle)) + (displacement.x * sin(aaaaaangle)); // calculating X distance in new co - ord plane

	float angle = aaaaaangle + atan(
							((pow(shotSpeed, 2)) + 
							(sqrt(pow(shotSpeed, 4) - graaaavity * ((graaaavity*pow(displac.x, 2)) + (2 * -displac.y*pow(shotSpeed, 2)))))) / 
							(graaaavity*displac.x));		// it looks a slight bit less horrible when spaced like this.

	return angle;
}

