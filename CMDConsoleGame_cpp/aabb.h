#pragma once

// Axis-Aligned Bounding Box

#include "vector2.h"

class AABB
{
public:
	Vector2 min, max;

	bool Contains(Vector2 p)
	{
		if (p.x >= min.x && p.x < max.x
		&&  p.y >= min.y && p.y < max.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	AABB(Vector2 cornerA, Vector2 cornerB) {
		// TODO #define MIN, MAX
#define BIGR(a, b)	((a>b)?(a):(b))
#define SMAL(a, b)	((a<b)?(a):(b))
		min.x = SMAL(cornerA.x, cornerB.x);
		min.y = SMAL(cornerA.y, cornerB.y);
		max.x = BIGR(cornerA.x, cornerB.x);
		max.y = BIGR(cornerA.y, cornerB.y);
		// TODO #undef MIN, MAX
#undef BIGR
#undef SMAL
	}
};