#pragma once

#define MIN_ALIGN_BYTES (4)
#define MAX_STATIC_ALIGN_BYTES (16)
#define ALIGN_TO_BOUNDARY(n) alignas(n)

constexpr inline int computeDefaultAlignmentHelper(int arrayBytes, int alignmentBytes)
{
	if (arrayBytes % alignmentBytes == 0)
	{
		return alignmentBytes;
	}
	else if (MIN_ALIGN_BYTES < alignmentBytes)
	{
		return computeDefaultAlignmentHelper(arrayBytes, alignmentBytes / 2);
	}
	else
	{
		return 0;
	}
	
}

template <typename T, int Count>
struct ComputeDefaultAlighment
{
	enum {
		value = computeDefaultAlignmentHelper(Count * sizeof(T), MAX_STATIC_ALIGN_BYTES)
	};
};

