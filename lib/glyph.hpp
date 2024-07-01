#pragma once

#include "typedef.hpp"

#include "array/row.tpp"
#include "color.hpp"
#include <initializer_list>

namespace Bleakdepth {
	struct glyph_t {
		color_t color;
		u16 index;

		constexpr glyph_t() noexcept : color {}, index {} {}

		constexpr glyph_t(u16 index, color_t color) noexcept : color { color }, index { index } {}
	};

	template<usize Length> struct animated_glyph_t {
	  private:
		row_t<u16, Length> indices;
		usize frame;

		constexpr inline void wrap() noexcept { frame %= length; }

	  public:
		static constexpr usize length { Length };

		static constexpr usize first { 0 };
		static constexpr usize last { length - 1 };

		using iterator = fwd_iter_t<u16>;
		using const_iterator = fwd_iter_t<const u16>;

		using reverse_iterator = rev_iter_t<u16>;
		using const_reverse_iterator = rev_iter_t<const u16>;

		color_t color;

		constexpr animated_glyph_t() = delete;

		constexpr animated_glyph_t(std::initializer_list<u16> indices) noexcept : indices { indices }, frame { 0 }, color {} {}

		constexpr animated_glyph_t(std::initializer_list<u16> indices, color_t color) noexcept : indices { indices }, frame { 0 }, color { color } {}

		constexpr animated_glyph_t(rval<row_t<u16, Length>> indices) noexcept : indices { indices }, frame { 0 }, color {} {}

		constexpr animated_glyph_t(rval<row_t<u16, Length>> indices, color_t color) noexcept : indices { indices }, frame { 0 }, color { color } {}

		constexpr animated_glyph_t(cref<animated_glyph_t> other) noexcept : indices { other.indices }, frame { other.frame }, color { other.color } {}

		constexpr animated_glyph_t(rval<animated_glyph_t> other) noexcept :
			indices { std::move(other.indices) },
			frame { other.frame },
			color { other.color } {}

		constexpr ref<animated_glyph_t> operator=(cref<animated_glyph_t> other) noexcept {
			if (this == &other) {
				return *this;
			}

			indices = other.indices;
			frame = other.frame;
			color = other.color;

			return *this;
		}

		constexpr ref<animated_glyph_t> operator=(rval<animated_glyph_t> other) noexcept {
			if (this == &other) {
				return *this;
			}

			indices = std::move(other.indices);
			frame = other.frame;
			color = other.color;

			return *this;
		}

		constexpr ~animated_glyph_t() = default;

		constexpr u16 operator[](usize index) const noexcept { return indices[index]; }

		constexpr u16 at(usize index) const {
			if (index >= length) {
				throw std::out_of_range { "index out of range!" };
			}

			return indices[index];
		}

		constexpr void advance() noexcept {
			++frame;
			wrap();
		}

		constexpr void retreat() noexcept {
			--frame;
			wrap();
		}

		constexpr void reset() noexcept { frame = 0; }

		constexpr void set(usize index) { frame = index % length; }

		constexpr usize current_frame() const noexcept { return frame; }

		constexpr operator glyph_t() const noexcept { return { indices[frame], color }; }

		constexpr u16 front() const noexcept { return indices.front(); }

		constexpr u16 back() const noexcept { return indices.back(); }

		constexpr iterator begin() noexcept { return indices.begin(); }

		constexpr iterator end() noexcept { return indices.end(); }

		constexpr const_iterator begin() const noexcept { return indices.begin(); }

		constexpr const_iterator end() const noexcept { return indices.end(); }

		constexpr const_iterator cbegin() const noexcept { return indices.cbegin(); }

		constexpr const_iterator cend() const noexcept { return indices.cend(); }

		constexpr reverse_iterator rbegin() noexcept { return indices.rbegin(); }

		constexpr reverse_iterator rend() noexcept { return indices.rend(); }

		constexpr const_reverse_iterator rbegin() const noexcept { return indices.rbegin(); }

		constexpr const_reverse_iterator rend() const noexcept { return indices.rend(); }

		constexpr const_reverse_iterator crbegin() const noexcept { return indices.crbegin(); }

		constexpr const_reverse_iterator crend() const noexcept { return indices.crend(); }

		constexpr bool operator==(cref<animated_glyph_t> other) const noexcept = delete;
		constexpr bool operator!=(cref<animated_glyph_t> other) const noexcept = delete;

		constexpr bool operator<(cref<animated_glyph_t> other) const noexcept = delete;
		constexpr bool operator>(cref<animated_glyph_t> other) const noexcept = delete;

		constexpr bool operator<=(cref<animated_glyph_t> other) const noexcept = delete;
		constexpr bool operator>=(cref<animated_glyph_t> other) const noexcept = delete;

		template<u16 Start, u16 End> constexpr static row_t<u16, Length> generate_contiguous_indices() noexcept {
			row_t<u16, Length> indices {};

			static_assert(End - Start + 1 == Length, "lengths of indices and range are not equal!");

			for (usize i = 0; i < Length; ++i) {
				indices[i] = Start + i;
			}

			return indices;
		}
	};
} // namespace Bleakdepth
