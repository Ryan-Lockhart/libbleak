#pragma once

#include <necrowarp/entities/entity.hpp>

#include <necrowarp/game_state.hpp>

namespace necrowarp {
	using namespace bleak;

	struct priest_t {
		offset_t position;
		u8 health;

		static constexpr u8 MaximumHealth{ 4 };
		static constexpr u8 MaximumDamage{ 2 };

		inline priest_t(cref<offset_t> position) noexcept : position{ position }, health{ MaximumHealth } {}

		inline entity_command_t think() const noexcept;

		inline void draw() const noexcept { game_atlas.draw(EntityGlyphs[entity_type_t::Priest], position); }

		inline void draw(cref<offset_t> offset) const noexcept { game_atlas.draw(EntityGlyphs[entity_type_t::Priest], position + offset); }

		inline void draw(cref<camera_t> camera) const noexcept { game_atlas.draw(EntityGlyphs[entity_type_t::Priest], position + camera.get_offset()); }

		inline void draw(cref<camera_t> camera, cref<offset_t> offset) const noexcept { game_atlas.draw(EntityGlyphs[entity_type_t::Priest], position + camera.get_offset() + offset); }

		constexpr operator entity_type_t() const noexcept { return entity_type_t::Priest; }

		struct hasher {
			static constexpr usize operator()(cref<priest_t> priest) noexcept { return offset_t::hasher::operator()(priest.position); }

			static constexpr usize operator()(cref<offset_t> position) noexcept { return offset_t::hasher::operator()(position); }
		};

		struct comparator {
			static constexpr bool operator()(cref<priest_t> lhs, cref<priest_t> rhs) noexcept { return offset_t::hasher::operator()(lhs.position) == offset_t::hasher::operator()(rhs.position); }

			static constexpr bool operator()(cref<priest_t> lhs, cref<offset_t> rhs) noexcept { return offset_t::hasher::operator()(lhs.position) == offset_t::hasher::operator()(rhs); }

			static constexpr bool operator()(cref<offset_t> lhs, cref<priest_t> rhs) noexcept { return offset_t::hasher::operator()(lhs) == offset_t::hasher::operator()(rhs.position); }
		};
	};

	template<> struct is_entity<priest_t> {
		static constexpr bool value = true;
	};

	template<> struct is_entity_type<priest_t, entity_type_t::Priest> {
		static constexpr bool value = true;
	};
} // namespace necrowarp

#include <necrowarp/entity_state.hpp>

namespace necrowarp {
	inline entity_command_t priest_t::think() const noexcept {
		for (crauto offset : neighbourhood_offsets<distance_function_t::Chebyshev>) {
			const offset_t current_position{ position + offset };

			if (entity_registry.at(current_position) != entity_type_t::Player) {
				continue;
			}

			return entity_command_t{ command_type_t::Clash, position, current_position };
		}

		cauto descent_pos{ good_goal_map.descend<zone_region_t::Interior>(position, entity_registry) };

		if (!descent_pos.has_value()) {
			return entity_command_t{ command_type_t::None };
		}

		return entity_command_t{ command_type_t::Move, position, descent_pos.value() };
	}
} // namespace necrowarp
