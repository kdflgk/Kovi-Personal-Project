#pragma once

class Vertex
{
public:
	float xPoint, yPoint, zPoint, w;
public:
	Vertex(float x, float y, float z) 
	{
		xPoint = x;
		yPoint = y;
		zPoint = z;
		w = 1;
	};
	~Vertex() {};

};
