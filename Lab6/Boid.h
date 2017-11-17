#include "Pvector.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SFML\Graphics.hpp>
using namespace std;

#ifndef BOID_H_
#define BOID_H_

/*
Brief description of Boid Class:
//The boid class creates an object which has multiple vectors (location, velocity, acceleration)
//Boids are given certain properties and rules to follow when interacting with other boids.
//They are being used to simulate flocking patterns and properties

For predators:
Predators should act by themselves. Thus, their maxSpeed should be different,
and they should not adhere to the three laws. However, they should adhere to
cohesion -- how should they seek prey? Also, prey should be able to run away
from predators. There are several ways to do this. The easiest way:

	Predators are part of the flock. This means that when the boids check
	through the vector of other boids, the predators are included. Check if
	the boid being looked at is a predator, and if it is, calculate a Pvector
	that maximizes separation.


*/

//the radius of the constraining circle for the wander behavior
const double WanderRad = 1.2;
//distance the wander circle is projected in front of the agent
const double WanderDist = 2.0;
//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 80.0;


class Boid
{
public:
	bool predator;
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;

	Pvector m_vWanderTarget;

	//explained above
	double        m_dWanderJitter = 50000;
	double        m_dWanderRadius = 5;
	double        m_dWanderDistance = 5.0;
	//the current position on the wander circle the agent is
	//attempting to steer towards
	//Pvector     m_vWanderTarget;

	Boid() {}
	Boid(float x, float y)
	{
		acceleration = Pvector(0, 0);
		velocity = Pvector(rand()%3-2, rand()%3-2); // Allows for range of -2 -> 2
		location = Pvector(x, y);
		maxSpeed = 5;
		maxForce = 0.5;
		//stuff for the wander behavior
		//double theta = RandFloat() * TwoPi;

		////create a vector to a target position on the wander circle
		//m_vWanderTarget = Vector2D(m_dWanderRadius * cos(theta),
		//	m_dWanderRadius * sin(theta));
	}
	Boid(float x, float y, bool predCheck) 
	{
		predator = predCheck;
		if (predCheck == true) {
			maxSpeed = 7.5;
			maxForce = 0.5;
			velocity = Pvector(rand()%3-1, rand()%3-1);
		} else {
			maxSpeed = 2.5;
			maxForce = 0.5;
			velocity = Pvector(rand()%3-2, rand()%3-2); // Allows for range of -2 -> 2
		}
		acceleration = Pvector(0, 0);
		location = Pvector(x, y);
	}
/* 
Destructors are commented out for now. g++ throws errors if they are included.
   If compiling on Visual Studio, however, no errors are thrown.
	//Destructor
	Boid::~Boid()
	{
		//cout << "Boid is being deleted by destructor!" << endl;
	}
*/	
	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(vector<Boid> Boids);
	Pvector SeparationFromPredator(vector<Boid> Boids);
	Pvector Alignment(vector<Boid> Boids);
	Pvector Cohesion(vector<Boid> Boids);
	Pvector Wander(vector <Boid> v);
	void Evade(Boid v);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	Pvector flee(Pvector v);
	void run(vector <Boid> v);
	void update();
	void flock(vector <Boid> v);
	void chase(vector <Boid> v);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Boid> v);
	float maxTimePrediction = 0.8;
	float timePrediction = 0.8;
	float m_elapsedTime;
	float wanderAngle;
};

#endif