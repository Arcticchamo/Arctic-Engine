#ifndef OBJECTS_H
#define OBJECTS_H

class Objects
{
protected:


public:
	virtual void Awake(){};
	virtual void Start(){};
	virtual void Update(){};
	virtual void Destroy(){};
	virtual void Render(){};
};

#endif