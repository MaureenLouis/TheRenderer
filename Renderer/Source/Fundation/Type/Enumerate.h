#pragma once

// STD
#include <stdint.h>

template <typename Base>
class Enum : public Base
{
public:
	using SelfType = Enum<Base>;
	using StorageType = typename Base::StorageType;

	Enum()
	{
		_val = (StorageType)(Base::e);
	}

	Enum(typename Base::Enum val)
	{
		_val = (StorageType)val;
	}

	Enum(StorageType val)
	{
		_val = val;
	}

	Enum(int val)
	{
		_val = (StorageType)val;
	}

	Enum(const SelfType& val)
	{
		_val = val._val;
	}


	SelfType operator&(SelfType another)
	{
		return SelfType(another._val & _val);
	}


	SelfType operator|(SelfType another)
	{
		return SelfType(another._val | _val);
	}

	bool operator == (SelfType another)
	{
		return _val == another._val;
	}

	bool operator != (SelfType another)
	{
		return _val == another;
	}

	operator bool() const
	{
		return !(!_val);
	}

	StorageType value() const
	{
		return _val;
	}


private:
	StorageType _val;
};



#define Enumerate(name, valueType, ...)        \
struct name##Enum                              \
{											   \
	using StorageType = valueType;			   \
											   \
	enum Enum								   \
	{										   \
         __VA_ARGS__                           \
	} e;									   \
};                                             \
using name = Enum<name##Enum>