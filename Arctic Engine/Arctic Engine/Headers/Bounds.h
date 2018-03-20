#ifndef BOUNDS_H
#define BOUNDS_H

#include "Component.h"
#include <iostream>
#include <vector>

class Bounds : public Component
{
private:
	Vector3 m_center; 
	Vector3 m_size; 
	Vector3 m_extents; 
	Vector3 m_min;
	Vector3 m_max; 

public: 
	Bounds();
	~Bounds(); 
	void CreateBounds(Vector3 _center, Vector3 _size);
	void RecalculateBounds(std::vector<Vector3> _vertex);
	Bounds* GetBounds();
	Vector3 GetSize();
};

#endif
