#ifndef RESOURCES_H
#define RESOURCES_H

#include "Global.h"
#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>

class Resources
{
private:
	static GLuint GlobalShader;

public:
	Resources();
	~Resources();
	static void Start(); 
	static std::string OpenFile(std::string _fileLocation);
	static GLuint GetShader() {return GlobalShader;}
};

#endif