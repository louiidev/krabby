#pragma once
#include <cstdint>
#include "kmath.h"

namespace Krabby {

	using u8 = uint8_t;
	using namespace Math;

	namespace Graphics {

		struct Color {
			u8 r;
			u8 g;
			u8 b;
			float a;

			constexpr Color()
				: r(0), g(0), b(0), a(0.0f) {}

			constexpr Color(u8 r, u8 g, u8 b)
				: r(r)
				, g(g)
				, b(b)
				, a(1.0f) {}

			constexpr Color(u8 r, u8 g, u8 b, float a)
				: r(r)
				, g(g)
				, b(b)
				, a(a) {}


			// Converts the Color to a Vec4 (RGBA)
			constexpr Vec4 normalize() const
			{
				return Vec4(r / 255.0f, g / 255.0f, b / 255.0f, a);
			}


			static const Color transparent;
			static const Color white;
			static const Color black;
			static const Color red;
			static const Color green;
			static const Color blue;
			static const Color yellow;
			static const Color orange;
			static const Color purple;
			static const Color teal;
		};

		void clear_framebuffer(Color color);
		void init();
		void draw_rect(Vec2 position, Vec2 size, Color color);

		inline const Color Color::transparent = Color(0, 0, 0, 0.0f);
		inline const Color Color::white = Color(255, 255, 255, 1.0f);
		inline const Color Color::black = Color(0, 0, 0, 1.0f);
		inline const Color Color::red = Color(255, 0, 0, 1.0f);
		inline const Color Color::green = Color(0, 255, 0, 1.0f);
		inline const Color Color::blue = Color(0, 0, 255, 1.0f);
		inline const Color Color::yellow = Color(255, 255, 0, 1.0f);
		inline const Color Color::purple = Color(255, 0, 255, 1.0f);
		inline const Color Color::teal = Color(0, 255, 255, 1.0f);

	}


}