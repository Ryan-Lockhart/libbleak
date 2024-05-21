#pragma once

#include "typedef.hpp"

#include <SDL_rect.h>
#include <cmath>
#include <format>
#include <string>
#include <utility>

#include <SDL.h>

#include "cardinal.hpp"

namespace Bleakdepth {
	template<typename T = i32> struct point_t {
		union {
			T x, w;
		};

		union {
			T y, h;
		};

		static const point_t Zero;

		static const point_t North;
		static const point_t South;
		static const point_t East;
		static const point_t West;

		static const point_t Northeast;
		static const point_t Northwest;

		static const point_t Southeast;
		static const point_t Southwest;

		static const point_t Central;

		constexpr point_t() noexcept : x { Zero.x }, y { Zero.y } {}

		constexpr point_t(T scalar) noexcept : x { scalar }, y { scalar } {}

		constexpr point_t(T x, T y) noexcept : x { x }, y { y } {}

		constexpr point_t(cref<point_t> other) noexcept : x { other.x }, y { other.y } {}

		constexpr point_t(rval<point_t> other) noexcept : x { std::move(other.x) }, y { std::move(other.y) } {}

		constexpr point_t(cardinal_t direction) noexcept : x {}, y {} {
			if (direction == cardinal_t::Central) {
				x = point_t<>::Zero.x;
				y = point_t<>::Zero.y;
			} else {
				if (direction & cardinal_t::North) {
					x += point_t<>::North.x;
					y += point_t<>::North.y;
				} else if (direction & cardinal_t::South) {
					x += point_t<>::South.x;
					y += point_t<>::South.y;
				}

				if (direction & cardinal_t::East) {
					x += point_t<>::East.x;
					y += point_t<>::East.y;
				} else if (direction & cardinal_t::West) {
					x += point_t<>::West.x;
					y += point_t<>::West.y;
				}
			}
		}

		template<typename U> constexpr explicit point_t(cref<point_t<U>> other) noexcept : x { static_cast<T>(other.x) }, y { static_cast<T>(other.y) } {}

		template<typename U>
		constexpr explicit point_t(rval<point_t<U>> other) noexcept : x { static_cast<T>(std::move(other.x)) }, y { static_cast<T>(std::move(other.y)) } {}

		constexpr point_t(cref<SDL_Point> other) noexcept : x { other.x }, y { other.y } {}

		constexpr point_t(rval<SDL_Point> other) noexcept : x { std::move(other.x) }, y { std::move(other.y) } {}

		constexpr explicit point_t(cref<SDL_FPoint> other) noexcept : x { static_cast<T>(other.x) }, y { static_cast<T>(other.y) } {}

		constexpr explicit point_t(rval<SDL_FPoint> other) noexcept : x { static_cast<T>(std::move(other.x)) }, y { static_cast<T>(std::move(other.y)) } {}

		constexpr ~point_t() = default;

		constexpr ref<point_t> operator=(cref<point_t> other) noexcept {
			x = other.x;
			y = other.y;

			return *this;
		}

		constexpr ref<point_t> operator=(rval<point_t> other) noexcept {
			x = std::move(other.x);
			y = std::move(other.y);

			return *this;
		}

		constexpr ref<point_t> operator=(cref<SDL_Point> other) noexcept {
			x = other.x;
			y = other.y;

			return *this;
		}

		constexpr ref<point_t> operator=(rval<SDL_Point> other) noexcept {
			x = std::move(other.x);
			y = std::move(other.y);

			return *this;
		}

		constexpr ref<point_t> operator=(cref<SDL_FPoint> other) noexcept {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);

			return *this;
		}

		constexpr ref<point_t> operator=(rval<SDL_FPoint> other) noexcept {
			x = static_cast<T>(std::move(other.x));
			y = static_cast<T>(std::move(other.y));

			return *this;
		}

		constexpr usize size() const noexcept { return (usize)x * y; }

		constexpr usize dot() const noexcept { return (usize)x * x + (usize)y * y; }

		template<typename L, typename = f32> constexpr L length() const noexcept;

		template<> constexpr f32 length() const noexcept { return std::sqrt(static_cast<f32>(dot())); }

		template<> constexpr f64 length() const noexcept { return std::sqrt(static_cast<f64>(dot())); }

		template<> constexpr i32 length() const noexcept {
			union {
				f32 f;
				i32 i;
			} v;

			v.f = (f32)dot();

			v.i -= 1 << 23;
			v.i >>= 1;
			v.i += 1 << 29;

			return (i32)((f32)v.i);
		}

		template<> constexpr i64 length() const noexcept {
			union {
				f64 f;
				i64 i;
			} v;

			v.f = (f64)dot();

			v.i -= 1LL << 52;
			v.i >>= 1;
			v.i += 1LL << 58;

			return (i64)((f64)v.i);
		}

		constexpr bool operator==(cref<point_t> other) const noexcept { return x == other.x && y == other.y; }

		constexpr bool operator!=(cref<point_t> other) const noexcept { return x != other.x || y != other.y; }

		constexpr bool operator<(cref<point_t> other) const { return x < other.x && y < other.y; }

		constexpr bool operator>(cref<point_t> other) const { return x > other.x && y > other.y; }

		constexpr bool operator<=(cref<point_t> other) const { return x <= other.x && y <= other.y; }

		constexpr bool operator>=(cref<point_t> other) const { return x >= other.x && y >= other.y; }

		constexpr point_t operator-() const noexcept { return { -x, -y }; }

		constexpr point_t operator+(cref<point_t> other) const noexcept { return { x + other.x, y + other.y }; }

		constexpr point_t operator-(cref<point_t> other) const noexcept { return { x - other.x, y - other.y }; }

		constexpr point_t operator*(cref<point_t> other) const noexcept { return { x * other.x, y * other.y }; }

		constexpr point_t operator/(cref<point_t> other) const noexcept { return { x / other.x, y / other.y }; }

		constexpr point_t operator%(cref<point_t> other) const noexcept { return { x % other.x, y % other.y }; }

		constexpr point_t operator+(cardinal_t direction) const noexcept {
			auto dir { static_cast<point_t<T>>(direction) };
			return point_t<> { x + dir.x, y + dir.y };
		}

		constexpr point_t operator-(cardinal_t direction) const noexcept {
			auto dir { static_cast<point_t<T>>(direction) };
			return point_t<> { x - dir.x, y - dir.y };
		}

		constexpr point_t operator*(cardinal_t direction) const noexcept {
			auto dir { static_cast<point_t<T>>(direction) };
			return point_t<> { x * dir.x, y * dir.y };
		}

		constexpr point_t operator/(cardinal_t direction) const noexcept {
			auto dir { static_cast<point_t<T>>(direction) };
			return point_t<> { x / dir.x, y / dir.y };
		}

		constexpr point_t operator%(cardinal_t direction) const noexcept {
			auto dir { static_cast<point_t<T>>(direction) };
			return point_t<> { x % dir.x, y % dir.y };
		}

		template<f32> point_t operator%(cref<point_t> other) const noexcept { return { ::fmodf(x, other.x), ::fmodf(y, other.y) }; }

		template<f64> point_t operator%(cref<point_t> other) const noexcept { return { ::fmodl(x, other.x), ::fmodl(y, other.y) }; }

		constexpr point_t operator+(T scalar) const noexcept { return { x + scalar, y + scalar }; }

		constexpr point_t operator-(T scalar) const noexcept { return { x - scalar, y - scalar }; }

		constexpr point_t operator*(T scalar) const noexcept { return { x * scalar, y * scalar }; }

		constexpr point_t operator/(T scalar) const noexcept { return { x / scalar, y / scalar }; }

		constexpr point_t operator%(T scalar) const noexcept { return { x % scalar, y % scalar }; }

		template<f32> point_t operator%(T scalar) const noexcept { return { ::fmodf(x, scalar), ::fmodf(y, scalar) }; }

		template<f64> point_t operator%(T scalar) const noexcept { return { ::fmodl(x, scalar), ::fmodl(y, scalar) }; }

		constexpr ref<point_t> operator+=(cref<point_t> other) noexcept {
			x += other.x;
			y += other.y;

			return *this;
		}

		constexpr ref<point_t> operator-=(cref<point_t> other) noexcept {
			x -= other.x;
			y -= other.y;

			return *this;
		}

		constexpr ref<point_t> operator*=(cref<point_t> other) noexcept {
			x *= other.x;
			y *= other.y;

			return *this;
		}

		constexpr ref<point_t> operator/=(cref<point_t> other) noexcept {
			x /= other.x;
			y /= other.y;

			return *this;
		}

		constexpr ref<point_t> operator%=(cref<point_t> other) noexcept {
			x %= other.x;
			y %= other.y;

			return *this;
		}

		template<f32> ref<point_t> operator%=(cref<point_t> other) noexcept {
			x = ::fmodf(x, other.x);
			y = ::fmodf(y, other.y);

			return *this;
		}

		template<f64> ref<point_t> operator%=(cref<point_t> other) noexcept {
			x = ::fmodl(x, other.x);
			y = ::fmodl(y, other.y);

			return *this;
		}

		constexpr ref<point_t> operator+=(T scalar) noexcept {
			x += scalar;
			y += scalar;

			return *this;
		}

		constexpr ref<point_t> operator-=(T scalar) noexcept {
			x -= scalar;
			y -= scalar;

			return *this;
		}

		constexpr ref<point_t> operator*=(T scalar) noexcept {
			x *= scalar;
			y *= scalar;

			return *this;
		}

		constexpr ref<point_t> operator/=(T scalar) noexcept {
			x /= scalar;
			y /= scalar;

			return *this;
		}

		constexpr ref<point_t> operator%=(T scalar) noexcept {
			x %= scalar;
			y %= scalar;

			return *this;
		}

		template<f32> ref<point_t> operator%=(T scalar) noexcept {
			x = ::fmodf(x, scalar);
			y = ::fmodf(y, scalar);

			return *this;
		}

		template<f64> ref<point_t> operator%=(T scalar) noexcept {
			x = ::fmodl(x, scalar);
			y = ::fmodl(y, scalar);

			return *this;
		}

		constexpr explicit operator SDL_Point() const noexcept { return SDL_Point { static_cast<i32>(x), static_cast<i32>(y) }; }

		template<i32> constexpr operator SDL_Point() const noexcept { return SDL_Point { x, y }; }

		template<i32> constexpr operator ptr<SDL_Point>() noexcept { return (ptr<SDL_Point>)&x; }

		template<i32> constexpr operator cptr<SDL_Point>() const noexcept { return (cptr<SDL_Point>)&x; }

		constexpr explicit operator SDL_FPoint() const noexcept { return SDL_FPoint { static_cast<f32>(x), static_cast<f32>(y) }; }

		template<f32> constexpr operator SDL_FPoint() const noexcept { return SDL_FPoint { x, y }; }

		template<f32> constexpr operator ptr<SDL_FPoint>() noexcept { return (ptr<SDL_FPoint>)&x; }

		template<f32> constexpr operator cptr<SDL_FPoint>() const noexcept { return (cptr<SDL_FPoint>)&x; }

		template<typename U> constexpr explicit operator point_t<U>() const noexcept { return { static_cast<U>(x), static_cast<U>(y) }; }

		constexpr operator std::string() const noexcept { return std::format("[{}, {}]", x, y); }

		template<i32> constexpr operator cardinal_t() const noexcept {
			if (x == point_t<>::Zero.x && y == point_t<>::Zero.x) {
				return cardinal_t::Central;
			} else {
				cardinal_t result = cardinal_t::Central;

				if (x != point_t<>::Zero.x) {
					result |= x < point_t<>::Zero.x ? cardinal_t::West : cardinal_t::East;
				}
				if (y != point_t<>::Zero.y) {
					result |= y < point_t<>::Zero.y ? cardinal_t::North : cardinal_t::South;
				}

				return result;
			}
		}

		constexpr void clamp_to(point_t<T> value, point_t<T> min, point_t<T> max) {
			x = value.x < min.x ? min.x : value.x > max.x ? max.x : value.x;
			y = value.y < min.y ? min.y : value.y > max.y ? max.y : value.y;
		}

		constexpr void clamp(point_t<T> min, point_t<T> max) {
			x = x < min.x ? min.x : x > max.x ? max.x : x;
			y = y < min.y ? min.y : y > max.y ? max.y : y;
		}

		static constexpr point_t clamp(point_t<T> value, point_t<T> min, point_t<T> max) {
			return {
				value.x < min.x ? min.x : value.x > max.x ? max.x : value.x,
				value.y < min.y ? min.y : value.y > max.y ? max.y : value.y
			};
		}
	};

	template<typename T = i32> using size_t = point_t<T>;

	template<> constexpr const point_t point_t<i32>::Zero = { 0 };

	template<> constexpr const point_t point_t<i32>::Central = point_t::Zero;

	template<> constexpr const point_t point_t<i32>::North = { 0, -1 };
	template<> constexpr const point_t point_t<i32>::South = { 0, 1 };

	template<> constexpr const point_t point_t<i32>::East = { 1, 0 };
	template<> constexpr const point_t point_t<i32>::West = { -1, 0 };

	template<> constexpr const point_t point_t<i32>::Northeast = { 1, -1 };
	template<> constexpr const point_t point_t<i32>::Northwest = { -1, -1 };

	template<> constexpr const point_t point_t<i32>::Southeast = { 1, 1 };
	template<> constexpr const point_t point_t<i32>::Southwest = { -1, 1 };

	template<> constexpr const point_t point_t<usize>::Zero = { 0ULL };

	template<> constexpr const point_t point_t<f32>::Zero = { 0.0f };

	template<> constexpr const point_t point_t<f32>::Central = point_t::Zero;

	template<> constexpr const point_t point_t<f32>::North = { 0.0f, -1.0f };
	template<> constexpr const point_t point_t<f32>::South = { 0.0f, 1.0f };

	template<> constexpr const point_t point_t<f32>::East = { 1.0f, 0.0f };
	template<> constexpr const point_t point_t<f32>::West = { -1.0f, 0.0f };

	template<> constexpr const point_t point_t<f32>::Northeast = { 1.0f, -1.0f };
	template<> constexpr const point_t point_t<f32>::Northwest = { -1.0f, -1.0f };

	template<> constexpr const point_t point_t<f32>::Southeast = { 1.0f, 1.0f };
	template<> constexpr const point_t point_t<f32>::Southwest = { -1.0f, 1.0f };
} // namespace Bleakdepth
