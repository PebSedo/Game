#pragma once

#include <GL/glew.h>

//The vertex definition

struct Position { //Position is the type
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV{
	float u, v;

};

struct Vertex {
	//This is the position struct. When you store a struct or class
	//inside of another struct or class, it is called composition. This is
	//layed out exactly the same in memory as if we had a float position[2],
	//but doing it this way makes more sense.

	 Position position; //position is the name of this particular instance

	//4 bytes for r g b a color.
	 Color color;

	 //UV Texture coordinates.
	 UV uv;

	 void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
		 color.r = r;
		 color.g = g;
		 color.b = b;
		 color.a = a;
	 }

	 void setUV(float u, float v){
		 uv.u = u;
		 uv.v = v;
	 
	 }
	 void setPosition(float x, float y){
		 position.x = x;
		 position.y = y;

	 }
};