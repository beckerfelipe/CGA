#include "Quaternion.h"

Quaternion::Quaternion(float angle, glm::vec3 axis)
{
	float halfAngle = angle / 2;
	float s = sin(halfAngle);
	w = cos(halfAngle);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;

}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion Quaternion::operator*(const Quaternion& q2) const
{
	float ww = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
	float xx = x * q2.w + w * q2.x + y * q2.z - z * q2.y;
	float yy = y * q2.w + w * q2.y + z * q2.x - x * q2.z;
	float zz = z * q2.w + w * q2.z + x * q2.y - y * q2.x;
	return Quaternion(ww, xx, yy, zz);
}

Quaternion Quaternion::operator*(const float scale) const
{
	return Quaternion(w * scale, x * scale, y * scale, z * scale);
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

Quaternion Quaternion::Rotate(float angle, glm::vec3 axis)
{
	Quaternion q(angle,axis);
	return Rotate(q);
}

Quaternion Quaternion::Rotate(Quaternion q)
{
	Quaternion p = *this;
	return q * p * q.Inverse();
}

glm::mat4 Quaternion::ToMatrix()
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
	matrix[0][1] = 2 * x * y - 2 * w * z;
	matrix[0][2] = 2 * x * z + 2 * w * y;

	matrix[1][0] = 2 * x * y + 2 * w * z;
	matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
	matrix[1][2] = 2 * y * z - 2 * w * x;

	matrix[2][0] = 2 * x * z - 2 * w * y;
	matrix[2][1] = 2 * y * z + 2 * w * x;
	matrix[2][2] = 1 - 2 * x * x - 2 * y * y;

	return matrix;

}

float Quaternion::Magnitude()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

void Quaternion::Normalize()
{
	float length = sqrt(x * x + y * y + z * z + w * w);

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::Inverse()
{
	float length = Magnitude();
	if (length == 1)
	{
		return Conjugate();
	}
	length *= length;
	return Conjugate() * (1 / length);
}

glm::vec3 Quaternion::GetPoint()
{
	return glm::vec3(x, y, z);
}

void Quaternion::Print()
{
	std::cout << "w: " << w << " x: " << x << " y: " << y << " z: " << z << std::endl;
}

Quaternion::~Quaternion()
{
}