#pragma once

struct VirtualDtor
{
	VirtualDtor() = default;
	virtual ~VirtualDtor() =default;
};

#define Interface(className)    struct className : public VirtualDtor
#define Pure(func)              virtual func = 0