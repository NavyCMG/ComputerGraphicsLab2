#pragma once
#include "MyMath.h"
#include <algorithm>
#include <cmath>

void TranslateCube(Cube *c, float x = 0, float y = 0, float z = 0)
{
	float t[3]{ x, y, z };
	for (int i = 0; i < 3; ++i)
	{
		c->local[3][i] += t[i];
	}
}

void RotateCubeY(float deg, Cube *c) //responsible for doing the math for rotating the cube in space
{
	double rad = deg * (pi / 180);
	float yRot[4][4]{ {std::cos(rad), 0, std::sin(rad), 0}, {0,1,0,0}, {-std::sin(rad), 0, std::cos(rad), 0}, {0,0,0,1} };
	SqrMtrxMult(c->local, yRot);
}

void RotateCameraX(float deg, Camera* c)
{
	double rad = deg * (pi / 180);
	float xRot[4][4]{ {1,0,0,0},{0, std::cos(rad), -std::sin(rad), 0}, {0, std::sin(rad), std::cos(rad), 0}, {0,0,0,1} };
	SqrMtrxMult(c->local, xRot);
}

void TransposeCamera(Camera* c, float x = 0, float y = 0, float z = 0, float w = 0)
{
	float t[3]{ x, y, z };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
			c->local[3][i] += t[j] * c->local[j][i];
	}
}

Vertex VertShader(Vertex v, float m[4][4], Camera* c)
{
	Vertex res = VecMtrxMult(v, m);
	Vertex invres = VecMtrxMult(res, c->inverse);
	Vertex persres = VecMtrxMult(invres, c->perspectivePorj);
	for (int i = 0; i < 3; ++i)
	{
		persres.xyzw[i] = (persres.xyzw[i] / persres.xyzw[3]);
	}
	return persres;
}