#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Global.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class OBJLoader
{
public:
	static void GetOBJFile(
		std::vector<Vector3> &_vertex, 
		std::vector<Vector2> &_uv, 
		std::vector<Vector3> &_normal,
		std::vector<int> &_vertInd,
		std::vector<int> &_uvInd,
		std::vector<int> &_normInd,
		std::string _objName);

};
#endif