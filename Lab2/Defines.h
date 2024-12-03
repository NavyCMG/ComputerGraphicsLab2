#pragma once
#include <vector>
#include <math.h>

#define screenWidth 600
#define screenHeight 500
#define numPxls (screenWidth * screenHeight)
#define pi 3.14159265358979323846
#define aspectratio (screenWidth/ screenHeight)
#define yscale (std::cos(.785)/ std::sin(.785))
#define xscale (yscale * aspectratio)
#define znear .1
#define zfar 10
unsigned int screen[numPxls];
float screenDepth[numPxls];
unsigned int curPxl = 0;
float test1[4][4]{ {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
float test2[4][4]{ {17,18,19,20},{21,22,23,24},{25,26,27,28},{29,30,31,32} };
float testInv[4][4]{ {1,0,0,0},{0,.309,.951,0}, {0, -.951, .309, 0}, {7, -2.282, 9.513, 1} };
float Identity[4][4]{ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };


struct Vertex
{
	Vertex(float x = 0, float y = 0, float z = 0, float w = 1, unsigned int clr = 0xffffffff)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = w;
		color = clr;
	}
	float xyzw[4];
	unsigned int color;
};
struct Point2D
{
	int x, y;
};
struct Grid //color white
{
	float local[4][4] { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };;
	//total size should go from -.5 to .5
	std::vector<Vertex> bottoms = {
		Vertex(-.5, 0,-.5, 1, 0xffffffff),
		Vertex(-.4, 0, -.5, 1, 0xffffffff),
		Vertex(-.3, 0, -.5, 1, 0xffffffff),
		Vertex(-.2, 0, -.5, 1, 0xffffffff),
		Vertex(-.1, 0, -.5, 1, 0xffffffff),
		Vertex(0, 0, -.5, 1, 0xffffffff),
		Vertex(.1 , 0, -.5, 1, 0xffffffff),
		Vertex(.2, 0, -.5, 1, 0xffffffff),
		Vertex(.3, 0, -.5, 1, 0xffffffff),
		Vertex(.4, 0, -.5, 1, 0xffffffff),
		Vertex(.5, 0, -.5, 1, 0xffffffff)
	};
	std::vector<Vertex> lefts = {
		Vertex(-.5, 0, -.5, 1, 0xffffffff),
		Vertex(-.5, 0, -.4, 1, 0xffffffff),
		Vertex(-.5, 0, -.3, 1, 0xffffffff),
		Vertex(-.5, 0, -.2, 1, 0xffffffff),
		Vertex(-.5, 0, -.1, 1, 0xffffffff),
		Vertex(-.5, 0, 0, 1, 0xffffffff),
		Vertex(-.5, 0, .1, 1, 0xffffffff),
		Vertex(-.5, 0, .2, 1, 0xffffffff),
		Vertex(-.5, 0, .3, 1, 0xffffffff),
		Vertex(-.5, 0, .4, 1, 0xffffffff),
		Vertex(-.5, 0, .5, 1, 0xffffffff)
	};
	std::vector<Vertex> tops = {
		Vertex(-.5, 0, .5, 1, 0xffffffff),
		Vertex(-.4, 0, .5, 1, 0xffffffff),
		Vertex(-.3, 0, .5, 1, 0xffffffff),
		Vertex(-.2, 0, .5, 1, 0xffffffff),
		Vertex(-.1, 0, .5, 1, 0xffffffff),
		Vertex(0, 0, .5, 1, 0xffffffff),
		Vertex(.1, 0, .5, 1, 0xffffffff),
		Vertex(.2, 0, .5, 1, 0xffffffff),
		Vertex(.3, 0, .5, 1, 0xffffffff),
		Vertex(.4, 0, .5, 1, 0xffffffff),
		Vertex(.5, 0, .5, 1, 0xffffffff)
	};
		std::vector<Vertex> rights = {
		Vertex(.5, 0, -.5, 1, 0xffffffff),
		Vertex(.5, 0, -.4, 1, 0xffffffff),
		Vertex(.5, 0, -.3, 1, 0xffffffff),
		Vertex(.5, 0, -.2, 1, 0xffffffff),
		Vertex(.5, 0, -.1, 1, 0xffffffff),
		Vertex(.5, 0, 0, 1, 0xffffffff),
		Vertex(.5, 0, .1, 1, 0xffffffff),
		Vertex(.5, 0, .2, 1, 0xffffffff),
		Vertex(.5, 0, .3, 1, 0xffffffff),
		Vertex(.5, 0, .4, 1, 0xffffffff),
		Vertex(.5, 0, .5, 1, 0xffffffff)
	};
};
struct Cube //color green
{
	float local[4][4]{ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };;
	//total size should go from -.25 to .25
	std::vector<Vertex> vertsOrig{ 
		Vertex(-.25, .25, .25, 1, 0xff00ff00),	//top left close	sub 0
		Vertex(-.25, .25, -.25, 1, 0xff00ff00), //top left far		sub 1
		Vertex(.25, .25, .25, 1, 0xff00ff00),	//top right close	sub 2
		Vertex(.25, .25, -.25, 1, 0xff00ff00),	//top right far		sub 3
		Vertex(-.25, -.25, .25, 1, 0xff00ff00),	//bottom left close	sub 4
		Vertex(-.25, -.25, -.25, 1, 0xff00ff00),//bottom left far	sub 5
		Vertex(.25, -.25, .25, 1, 0xff00ff00),	//bottom right close sub 6
		Vertex(.25, -.25, -.25, 1, 0xff00ff00)  //bottom right far	sub 7
	};
	std::vector<Vertex> vertsChange{
		Vertex(-.25, .25, .25, 1, 0xff00ff00),	//top left close	sub 0
		Vertex(-.25, .25, -.25, 1, 0xff00ff00), //top left far		sub 1
		Vertex(.25, .25, .25, 1, 0xff00ff00),	//top right close	sub 2
		Vertex(.25, .25, -.25, 1, 0xff00ff00),	//top right far		sub 3
		Vertex(-.25, -.25, .25, 1, 0xff00ff00),	//bottom left close	sub 4
		Vertex(-.25, -.25, -.25, 1, 0xff00ff00),//bottom left far	sub 5
		Vertex(.25, -.25, .25, 1, 0xff00ff00),	//bottom right close sub 6
		Vertex(.25, -.25, -.25, 1, 0xff00ff00)  //bottom right far	sub 7
	};
};
struct Camera
{
	float local[4][4]{ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	float inverse[4][4]{ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	float perspectivePorj[4][4]{
		{(float)xscale, 0,0,0}, 
		{0, (float)yscale, 0,0}, 
		{0,0, (float)(zfar / (zfar - znear)), 1},
		{0,0, (float)-(zfar * znear) / (zfar - znear), 0} };
};