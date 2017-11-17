// This file defines the boid class. This includes the attributes found in
// boids -- speed, location on the board, acceleration, etc.
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Boid.h"
#include "utils.h"

// Global Variables for borders()
// desktopTemp gets screen resolution of PC running the program
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode(); 
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define w_height window_height
#define w_width window_width
#define PI 3.141592635

using namespace std;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

// Adds force Pvector to current force Pvector
void Boid::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector Boid::Separation(vector<Boid> boids)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	//if (predator == true)
	//{
	//	Pvector sum(0, 0);
	//	return flee(sum);
	//}



		// Distance of field of vision for separation between boids
		float desiredseparation = 20;

		Pvector steer(0, 0);
		int count = 0;
		// For every boid in the system, check if it's too close
		for (int i = 0; i < boids.size(); i++)
		{
			// Calculate distance from current boid to boid we're looking at
			float d = location.distance(boids[i].location);
			// If this is a fellow boid and it's too close, move away from it
			if ((d > 0) && (d < desiredseparation))
			{
				Pvector diff(0, 0);
				diff = diff.subTwoVector(location, boids[i].location);
				diff.normalize();
				diff.divScalar(d);      // Weight by distance
				steer.addVector(diff);
				count++;
			}
			// If current boid is a predator and the boid we're looking at is also
			// a predator, then separate only slightly 
			if ((d > 0) && (d < desiredseparation) && predator == true && boids[i].predator == true)
			{
				Pvector pred2pred(0, 0);
				pred2pred = pred2pred.subTwoVector(location, boids[i].location);
				pred2pred.normalize();
				pred2pred.divScalar(d);
				steer.addVector(pred2pred);
				count++;
			}
			// If current boid is not a predator, but the boid we're looking at is
			// a predator, then create a large separation Pvector
			else if ((d > 0) && (d < desiredseparation + 70) && boids[i].predator == true)
			{
				Pvector pred(0, 0);
				pred = pred.subTwoVector(location, boids[i].location);
				pred.mulScalar(900);
				steer.addVector(pred);
				count++;
			}
		}
		// Adds average difference of location to acceleration
		if (count > 0)
			steer.divScalar((float)count);
		if (steer.magnitude() > 0)
		{
			// Steering = Desired - Velocity
			steer.normalize();
			steer.mulScalar(maxSpeed);
			steer.subVector(velocity);
			steer.limit(maxForce);
		}
		return steer;
	
}

Pvector Boid::SeparationFromPredator(vector<Boid> boids)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = 20;

	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++)
	{
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(boids[i].location);
	
		 if ((d > 0) && (d < desiredseparation + 70) && boids[i].predator == true)
		{
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, boids[i].location);
			pred.mulScalar(900);
			steer.addVector(pred);
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;

}


// Alignment calculates the average velocity in the field of view and 
// manipulates the velocity of the Boid passed as parameter to adjust to that
// of nearby boids.
Pvector Boid::Alignment(vector<Boid> Boids)
{
	// If the boid we're looking at is a predator, do not run the alignment
	// algorithm



		float neighbordist = 50;

		Pvector sum(0, 0);
		int count = 0;
		for (int i = 0; i < Boids.size(); i++)
		{
			float d = location.distance(Boids[i].location);
			if ((d > 0) && (d < neighbordist)) // 0 < d < 50
			{
				sum.addVector(Boids[i].velocity);
				count++;
			}
		}
		// If there are boids close enough for alignment...
		if (count > 0)
		{
			sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
			sum.normalize();	   		// Turn sum into a unit vector, and
			sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
			// Steer = Desired - Velocity
			Pvector steer;
			steer = steer.subTwoVector(sum, velocity); //sum = desired(average)  
			steer.limit(maxForce);
			return steer;
		}
		else {
			Pvector temp(0, 0);
			return temp;
		}
	
}

// Cohesion finds the average location of nearby boids and manipulates the 
// steering force to move in that direction.
Pvector Boid::Cohesion(vector<Boid> Boids)
{
	// If the boid we're looking at is a predator, do not run the cohesion
	// algorithm

float neighbordist = 50;

		Pvector sum(0, 0);
		int count = 0;
		for (int i = 0; i < Boids.size(); i++)
		{
			float d = location.distance(Boids[i].location);
			if ((d > 0) && (d < neighbordist))
			{
				sum.addVector(Boids[i].location);
				count++;
			}
		}
		if (count > 0)
		{
			sum.divScalar(count);
			return seek(sum);
		}
		else {
			Pvector temp(0, 0);
			return temp;
		}
	
}

// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Pvector Boid::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;

}

Pvector Boid::flee(Pvector v)
{
	Pvector desired;
	location.subVector(v);
	desired.subVector(location);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

//Update modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void Boid::update()
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.4);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

//Run runs flock on the flock of boids for each boid.
//Which applies the three rules, modifies accordingly, updates data, checks is data is
//out of range, fixes that for SFML, and renders it on the window.
void Boid::run(vector <Boid> v)
{
	flock(v);
	update();
	borders();
}

void Boid::chase(vector<Boid>v)
{

}

//Applies all three laws for the flock of boids and modifies to keep them from
//breaking the laws.
void Boid::flock(vector<Boid> v) 
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);

}

// Checks if boids go out of the window and if so, wraps them around to the other side.
void Boid::borders()
{
	if (location.x < 0) location.x += w_width; 
	if (location.y < 440) location.y += w_height;
	if (location.x > 1000) location.x -= w_width;
	if (location.y > 1000) location.y -= 440;
}

// Calculates the angle for the velocity of a boid which allows the visual 
// image to rotate in the direction that it is going in.
float Boid::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

void Boid::swarm(vector <Boid> v)
{
	/*if (!predator)
	{*/
		Pvector	R;
		int A = 100;
		int B = 5000;
		int N = 1;
		int M = 2;
		int count = 0;
		float totalForce = 0;
		Pvector sum(0, 0);

		for (int i = 0; i < v.size(); i++)
		{
			R = R.subTwoVector(location, v[i].location);
			float D = R.magnitude();
			if (D > 0)
			{
				float U = -A / pow(D, N) + B / pow(D, M);
				R.normalize();
				R.mulScalar(U);
				sum.addVector(R);
			}

		}

		//Pvector sep = SeparationFromPredator(v);
		//sep.mulScalar(1.5);
		//applyForce(sep);
		sum.divScalar(v.size() - 1);
		applyForce(sum);
		update();
		borders();
	//}

	//else
	//{
	//	Pvector sep = Separation(v);
	//	Pvector ali = Alignment(v);
	//	Pvector coh = Cohesion(v);
	//	// Arbitrarily weight these forces
	//	sep.mulScalar(0);
	//	ali.mulScalar(50); // Might need to alter weights for different characteristics
	//	coh.mulScalar(50);
	//	// Add the force vectors to acceleration
	//	applyForce(sep);
	//	applyForce(ali);
	//	applyForce(coh);
	//	update();
	//	borders();
	//}
}



Pvector Boid::Wander(vector <Boid> v)
{
	

	//this behavior is dependent on the update rate, so this line must
	//be included when using time independent framerate.
	double JitterThisTimeSlice = m_dWanderJitter * 60;

	////first, add a small random vector to the target's position
	m_vWanderTarget.addVector(Pvector(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice));

	//reproject this new vector back on to a unit circle
	m_vWanderTarget.normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	m_vWanderTarget.mulScalar(m_dWanderRadius);

	////move the target into a position WanderDist in front of the agent
	Pvector target;
	m_vWanderTarget.addVector(Pvector(m_dWanderDistance, 0));
	target = m_vWanderTarget;
	////project the target into world space
	//Vector2D Target = PointToWorldSpace(target,
	//	m_pVehicle->Heading(),
	//	m_pVehicle->Side(),
	//	m_pVehicle->Pos());
	////and steer towards it
	return target;


}

void Boid::Evade(Boid v)
{
	float timePrediction;
	
	Pvector futurePosition;
	v.location.subVector(location);
	velocity = v.location;
	float distance = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
	if (maxSpeed <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else
	{
		timePrediction = distance / maxSpeed;
	}
	v.velocity.mulScalar(timePrediction);
	v.location.subVector(v.velocity);
	futurePosition = v.location;
	flee(futurePosition);

}

