#pragma once
#include "Defines.h"

//absolutely awful custom math library that intentionally does things in a ridiculous way so I didnt get hit for plagarism

unsigned int Lerp(unsigned int start,unsigned int end, float ratio = -1)
{
	if (ratio == -1)
	{
		ratio = (float)start / (float)end;
	}
	end = ((int)end - (int)start) * ratio + start;
	return end;
}
unsigned int ColorBlend(unsigned int currentColor, unsigned int newColor)
{
	unsigned int newAlpha = (newColor & 0xff000000);
	if (newAlpha != 0xff000000)
	{
		float ratio = float(newAlpha) / float(0xff000000);
		/*currentColor = (currentColor & 0x00ffffff);
		newColor = (newColor & 0x00ffffff);
		newColor = (int(newColor) - int(currentColor)) * ratio + currentColor;*/
		unsigned int curRed = (currentColor & 0x00ff0000) >> 16;
		unsigned int curGrn = (currentColor & 0x0000ff00) >> 8;
		unsigned int curBlu = (currentColor & 0x000000ff);
		unsigned int newRed = (newColor & 0x00ff0000) >> 16;
		unsigned int newGrn = (newColor & 0x0000ff00) >> 8;
		unsigned int newBlu = (newColor & 0x000000ff);

		newRed = (int(newRed) - int(curRed)) * ratio + curRed;
		newGrn = (int(newGrn) - int(curGrn)) * ratio + curGrn;
		newBlu = (int(newBlu) - int(curBlu)) * ratio + curBlu;

		newColor = (newAlpha | newRed << 16 | newGrn << 8 | newBlu);
	}
	return newColor;
}

int TwoDtoOneD(int x, int y, int arrWidth = screenWidth)
{
	int result = (y * arrWidth) + x;
	return result;
}

void UpdateMatrix(float m[4][4], float u[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = u[i][j];
		}
	}
}
Vertex VecMtrxMult(Vertex v, float m[4][4])
{
	Vertex result = Vertex(0, 0, 0, 0, v.color);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.xyzw[i] += v.xyzw[j] * m[j][i];
		}
	}
	return result;
}

void SqrMtrxMult(float a[4][4], float b[4][4])
{
	float result[4][4]{ 0 };
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	UpdateMatrix(a, result);
}

float* OrthogAffinInverse(float m[4][4])
{
	
	float result[4][4]{ 0 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			result[i][j] = m[j][i];
		}
	}
	Vertex posVert = Vertex(0, 0, 0, 0);
	for (int k = 0; k < 4; ++k)
	{
		posVert.xyzw[k] = m[3][k];
	}
	Vertex posVertr = VecMtrxMult(posVert, result);
	for (int l = 0; l < 3; ++l)
	{
		result[3][l] -= posVertr.xyzw[l];
	}
	result[3][3] = 1;
	return reinterpret_cast<float*>(result);
}

void OrthogAffinInverseCam(Camera *c)
{

	float temp[4][4]{ 0 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			c->inverse[i][j] = c->local[j][i];
		}
	}
	Vertex posVert = Vertex(0, 0, 0, 0);
	for (int k = 0; k < 4; ++k)
	{
		posVert.xyzw[k] = c->local[3][k];
	}
	Vertex posVertr = VecMtrxMult(posVert, c->inverse);
	for (int l = 0; l < 3; ++l)
	{
		c->inverse[3][l] -= posVertr.xyzw[l];
	}
	c->inverse[3][3] = 1;
}