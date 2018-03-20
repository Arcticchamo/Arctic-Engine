#include "..\Headers\OBJLoader.h"

void OBJLoader::GetOBJFile(
		std::vector<Vector3> &_vertex, 
		std::vector<Vector2> &_uv, 
		std::vector<Vector3> &_normal,
		std::vector<int> &_vertInd,
		std::vector<int> &_uvInd,
		std::vector<int> &_normInd,
		std::string _objName)
{
	std::ifstream File; 
	std::string LineBeginning;

	File.open("Assets/Objects/" + _objName + ".txt"); //Load obj file
	if (File.fail()) //If the file doesnt exist, load default object
	{
		std::cout << "Failed to load " << _objName << std::endl << "Loading Cube..."; 
		File.open("Assets/Objects/cube.txt"); 
	}
	else std::cout << _objName << " opening " << std::endl;

	while (!File.eof()) //Until the end of the file
	{
		File >> LineBeginning;
		if (LineBeginning == "v") //Vertex
		{
			Vector3 Temp;
			File >> Temp.x >> Temp.y >> Temp.z;
			_vertex.push_back(Temp);
		}
		else if (LineBeginning == "vt") //UV
		{
			Vector2 Temp;
			File >> Temp.x >> Temp.y;
			Temp.y = (1 - Temp.y);
			_uv.push_back(Temp);
		}
		else if (LineBeginning == "vn") // Normal
		{
			Vector3 Temp;
			File >> Temp.x >> Temp.y >> Temp.z;
			_normal.push_back(Temp);
		}
		else if (LineBeginning == "f") //Faces
		{
			char Filler;
			int Vertind[3], UVInd[3], NormInd[3];

			File >> Vertind[0] >> Filler >> UVInd[0] >> Filler >> NormInd[0] >> 
					Vertind[1] >> Filler >> UVInd[1] >> Filler >> NormInd[1] >> 
					Vertind[2] >> Filler >> UVInd[2] >> Filler >> NormInd[2]; 

			for (int i = 0; i < 3; i++)
			{
				_vertInd.push_back(Vertind[i]);
				_uvInd.push_back(UVInd[i]);
				_normInd.push_back(NormInd[i]);
			}
		}
		LineBeginning == "";
	}
	File.close();
	//All obj data has been recieved

	std::vector<Vector3> VertCopy; 
	std::vector<Vector2> UVCopy;
	std::vector<Vector3> NormCopy;

	//Sort the data into the correct order
	for (unsigned int i = 0; i < _vertInd.size(); i++)
	{
		VertCopy.push_back(_vertex.at((_vertInd.at(i) - 1)));
	}

	for (unsigned int i = 0; i < _uvInd.size(); i++)
	{
		UVCopy.push_back(_uv.at((_uvInd.at(i) - 1)));
	}

	for (unsigned int i = 0; i < _normInd.size(); i++)
	{
		NormCopy.push_back(_normal.at((_normInd.at(i) - 1)));
	}

	_vertex = VertCopy;
	_uv = UVCopy;
	_normal = NormCopy;
}