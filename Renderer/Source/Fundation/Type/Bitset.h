#pragma once
#include <cstdint>


namespace Internal
{
	template <size_t N>
	struct BitsetHelper
	{
		
	};

	template <>
	struct BitsetHelper<8>
	{

		using type = uint8_t;
	};
}

template <size_t N>
class Bitset
{
	using SelfType = Bitset<N>;
	using StorageType = typename Internal::BitsetHelper<N>::type;
public:
	Bitset()
	{
		_bitset = (StorageType)0;
	}

	Bitset& operator = (const SelfType& another)
	{
		_bitset = another._bitset;
	}

	void set(int bit)
	{
		_bitset |= BIT(bit);
	}

	bool isSet(int bit)
	{
		return _bitset & (1 << bit);
	}

private:	
	StorageType _bitset;
};


