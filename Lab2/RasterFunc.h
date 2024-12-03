#pragma once
#include "Shaders.h"

void DrawPxl(int currentPos, unsigned int newColor)
{
	if (currentPos > 500)
	{
		curPxl = screen[currentPos];
		screen[currentPos] = ColorBlend(curPxl, newColor);
	}
}

void LinePara(Point2D start, Point2D end, unsigned int color)
{
	int curX = start.x;
	int curY = start.y;
	int length = max(std::abs(end.x - start.x), std::abs(end.y - start.y));

	for (int i = 0; i < length; ++i)
	{
		float ratio = (float)i / (float)length;
		curX = Lerp(start.x, end.x, ratio);
		curY = Lerp(start.y, end.y, ratio);
		DrawPxl(TwoDtoOneD(curX, curY), color);
	}
}

Point2D NDCtoScreen(Vertex v)
{
	Point2D result;
	result.x = (v.xyzw[0] + 1) * (screenWidth / 2);
	result.y = ((1 - v.xyzw[1]) * (screenHeight / 2));
	return result;
}

void DrawGrid(Grid g, Camera* c)
{
	for (int i = 0; i < g.tops.size(); ++i)
	{
		LinePara(NDCtoScreen(VertShader(g.tops[i], g.local, c)), NDCtoScreen(VertShader(g.bottoms[i], g.local, c)), g.tops[i].color);
	}
	for (int j = 0; j < g.lefts.size(); ++j)
	{
		LinePara(NDCtoScreen(VertShader(g.lefts[j], g.local, c)), NDCtoScreen(VertShader(g.rights[j], g.local, c)), g.lefts[j].color);
	}
}

void DrawCube(Cube c, Camera* cam)
{
	LinePara(NDCtoScreen(VertShader(c.vertsChange[0], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[2], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[0], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[1], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[0], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[4], c.local, cam)), c.vertsChange[0].color);

	LinePara(NDCtoScreen(VertShader(c.vertsChange[3], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[2], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[3], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[1], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[3], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[7], c.local, cam)), c.vertsChange[0].color);

	LinePara(NDCtoScreen(VertShader(c.vertsChange[6], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[7], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[6], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[4], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[6], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[2], c.local, cam)), c.vertsChange[0].color);
	
	LinePara(NDCtoScreen(VertShader(c.vertsChange[5], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[4], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[5], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[7], c.local, cam)), c.vertsChange[0].color);
	LinePara(NDCtoScreen(VertShader(c.vertsChange[5], c.local, cam)), NDCtoScreen(VertShader(c.vertsChange[1], c.local, cam)), c.vertsChange[0].color);
}