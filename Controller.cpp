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
	//float force = dif.x * gravity / sinf(angle * 2.0f);	// good flat (correct)
  //float force = (dif.x + (dif.x * (-dif.y / dif.x))) * gravity / sinf(angle * 2.0f);
  //float force = (dif.x + (dif.x * tanf(-dif.y / dif.x) )) * gravity / sinf(angle * 2.0f);	// a lil closer? (higher hit rate)
  //float force = (dif.x + (dif.x * (sinf(-dif.y / dif.x) * sinf(angle*2.f)) )) * gravity / sinf(angle * 2.0f); // (higher hit rate)
  //float force = (dif.x + (dif.x * (tanf(-dif.y / dif.x) * sinf(angle*2.f)) )) * gravity / sinf(angle * 2.0f); // (higher hit rate)
	//float force = (dif.x + ((dif.x/gravity) * ((tanf(dif.y / dif.x) * sinf(angle*2.0f))) )) * gravity / sinf(angle * 2.0f); // 
	//float force = (powf(dif.x, 2.0f) * gravity) / ( dif.x * sinf(angle * 2.f) ) - ( 2.f * -dif.y *  powf(cosf( angle ), 2.f) );
	float force = (dif.x * dif.x * gravity) /  (dif.x * sinf(angle * 2.f)  -  2.f * -dif.y * cosf( angle ) * cosf(angle) );
	//float force = (dif.x + (dif.x * -sinf(dif.y / dif.x))) * gravity / sinf(angle * 2.0f);
	//force -= (-dif.y / dif.x) * powf((0.5f * gravity), 2.0f) / tanf(angle * 2.f);

	//force -= (-powf(dif.y, 2.0f)) / powf((0.5f * gravity), 2.0f) * tanf(angle * 2.f);

	float w_force = 0;// -wind * cosf((-wind / (dif.x)) * 2.f); ;// dif.x * (-wind / gravity) / sinf(angle * 2.0f);

	force += w_force;

	std::cout << "wind: " << wind << " w_wind " << w_force << " x: " << (w_force * cosf(angle)) << " y: " << (w_force * -sinf(angle)) << " w/g " << (-wind / gravity) << " || " << ((-wind * (-wind / (gravity)))) << std::endl;
	std::cout << "force: " << force << " x: " << (force * cosf(angle)) << " y: " << (force * -sinf(angle)) << std::endl;



	force = sqrtf(force);

	Vector2 force_vect2 = force * Vector2(cosf(angle), -sinf(angle));
	float flightLength = GetFlightLength(dif.y, force, angle, gravity);

	//force -= (-dif.y + ((force_vect2.y/gravity)*force_vect2.y)) / (gravity) * ( sinf(angle * 2.0f) ) ;
	//force += ((2.0f * dif.y) + ((force_vect2.y/gravity)*force_vect2.y)) / (gravity) * ( sinf(angle * 2.0f) ) ;
	//force += (dif.y + (-force_vect2.y * flightLength));

	std::cout << -dif.y << " * " << gravity << " / " << sinf(angle * 2.f) << std::endl;

	std::cout << (flightLength) << " || " << force << std::endl;

	/*
	std::cout << (dif.x) * -wind / cos(angle * 2.0f) << std::endl;

	//float force = sqrt( (gravity * pow(dif.x, 2.0f)) / sin(angle * 2.0f) / (dif.x+dif.y * (1.0f/tan(angle))));
	Vector2 force_vect2 = force * Vector2(cosf(angle), -sinf(angle));

	std::cout << "force / grav " << force_vect2.y << "/"<<gravity << "||" << (force_vect2.y * GetFlightLength(dif.y, force, angle, gravity)) <<"||" << (force_vect2.x * GetFlightLength(dif.y, force, angle, gravity)) << "=="<< dif.x << std::endl;
	std::cout << "flight Length " << GetFlightLength(dif.y, force, angle, gravity) << std::endl;
	std::cout << "wind " << (-wind * GetFlightLength(dif.y, force, angle, gravity)) << std::endl;
	std::cout << "x" << force_vect2.x << " (finalVel) s " << (0.5f * (force_vect2.x + (force_vect2.x - (-wind * GetFlightLength(dif.y, force, angle, gravity)))) ) << std::endl;
	std::cout << "x" << force_vect2.x << " (finalVel) s " << ( force_vect2.x - (0.5f * wind * pow(1.0f, 2)) ) << std::endl;
	std::cout << "height dif " << dif.y << " x dif: "<< dif.x << " gravity " << gravity << " angle " << angle << std::endl;
	std::cout << "force" << force << "fv.x: "<< force_vect2.x << "fv.y: " << force_vect2 .y << std::endl;
	*/
	//Vector2 velocity = force_vect2;
	//float flightLength = GetFlightLength(dif.y, force, angle, gravity);

	//velocity.x = (dif.x * flightLength);

	//std::cout << "flight Length X " << velocity.y << std::endl;

	return  force;// velocity.magnitude();

}

float Controller::WindCounterForce(float wind, float force)
{

	return 0.0f;

}

float Controller::GetFlightLength(float heightDif, float force, float angle, float gravity)
{

	Vector2 velocity = force * Vector2(cosf(angle), sinf(angle));
	
	// float fall_len = 1 - (-heightDif / ((velocity.y / gravity) * velocity.y));

	return (velocity.y / gravity) * 2.0f;// *(1 + fall_len);

}