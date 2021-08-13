#pragma once



namespace Krabby {
	namespace Math {
		struct Vec4 {
			float x;
			float y;
			float z;
			float w;

			constexpr Vec4()
				: x(0), y(0), z(0), w(0) {}

			constexpr Vec4(float x, float y, float z, float w)
				: x(x), y(y), z(z), w(w) {}
		};

		struct Vec2 {
			float x;
			float y;

			constexpr Vec2()
				: x(0), y(0) {}

			constexpr Vec2(float x, float y)
				: x(x), y(y) {}
		};
	}
}