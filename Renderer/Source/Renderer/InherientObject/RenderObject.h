#pragma once

class RenderObject
{
public:
	virtual ~RenderObject() {};
	virtual void initialize() {};
	virtual void draw() {};
};


