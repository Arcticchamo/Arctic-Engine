#include "..\Headers\Bounds.h"

Bounds::Bounds()
{

}


Bounds::~Bounds()
{

}

void Bounds::CreateBounds(Vector3 _center, Vector3 _size)
{
	m_center = _center;
	m_size = _size; 
	m_extents = _size / 2.0f; 
	m_min = _center - m_extents;
	m_max = _center + m_extents;
}

void Bounds::RecalculateBounds(std::vector<Vector3> _vertex)
{
	if (_vertex.size() < 1)
	{
		CreateBounds(Vector3(0, 0, 0), Vector3(0, 0, 0));
	}

	float minx = _vertex.at(0).x;
	float miny = _vertex.at(0).y;
	float minz = _vertex.at(0).z;
	float maxx = _vertex.at(0).x;
	float maxy = _vertex.at(0).y;
	float maxz = _vertex.at(0).z;

	for (unsigned int i = 0; i < _vertex.size(); i++)
	{
		if (_vertex.at(i).x < minx) minx = _vertex.at(i).x;
		if (_vertex.at(i).x > maxx) maxx = _vertex.at(i).x;

		if (_vertex.at(i).y < miny) miny = _vertex.at(i).y;
		if (_vertex.at(i).y > maxy) maxy = _vertex.at(i).y;

		if (_vertex.at(i).z < minz) minz = _vertex.at(i).z;
		if (_vertex.at(i).z > maxz) maxz = _vertex.at(i).z;
	}

	float midx = (maxx + minx) / 2.0f;
	float midy = (maxy + miny) / 2.0f;
	float midz = (maxz + minz) / 2.0f;

	float sizex = maxx - minx;
	float sizey = maxy - miny;
	float sizez = maxz - minz;

	CreateBounds(Vector3(midx, midy, midz), Vector3(sizex, sizey, sizez));
}

Bounds* Bounds::GetBounds()
{
	return this;
}

Vector3 Bounds::GetSize()
{
	return m_size; 
}