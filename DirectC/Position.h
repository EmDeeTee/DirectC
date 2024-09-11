#pragma once

#include <iostream>

namespace DirectC {
	struct Position {
		size_t x;
		size_t y;

		Position operator+(const Position& o) const {
			return Position{ x + o.x, y + o.y };
		}

		Position operator-(const Position& o) const {
			return Position{ x - o.x, y - o.y };
		}

		Position& AddX(const int32_t nX) {
			x += nX;
			return *this;
		}

		Position& AddY(const int32_t nY) {
			y += nY;
			return *this;
		}
	};
}