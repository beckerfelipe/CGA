#ifndef QUATERNION_H
#define QUATERNION_H

#include <glm/glm.hpp>
#include <iostream>

class Quaternion
{
	//real
	float w;
	//imaginary
	float x, y, z;

public:
	//create a quaternion from a point
	Quaternion(float angle, glm::vec3 axis);
	//(w) real, (x,y,z) imaginary
	Quaternion(float w, float x, float y, float z);
	void Normalize();
	float Magnitude();
	//Rotate the quaternion by an angle around an arbitrary axis
	Quaternion Rotate(float angle, glm::vec3 axis);
	Quaternion Rotate(Quaternion q);
	glm::vec3 GetPoint();	
	Quaternion Conjugate();
	glm::mat4 ToMatrix();
	Quaternion Inverse();
	Quaternion operator*(const Quaternion& q) const;
	Quaternion operator* (const float scale) const;
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;

	void Print();

	~Quaternion();
};

#endif // !QUATERNION_H
