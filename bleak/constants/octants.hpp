#pragma once

#include <bleak/typedef.hpp>

#include <bleak/octant.hpp>

namespace bleak {
	constexpr const octant_t Octants[] {
		octant_t{ offset_2d_t{  0,  1 }, offset_2d_t{  1,  0 }},
		octant_t{ offset_2d_t{  1,  0 }, offset_2d_t{  0,  1 }},
		octant_t{ offset_2d_t{  0,  1 }, offset_2d_t{ -1,  0 }},
		octant_t{ offset_2d_t{ -1,  0 }, offset_2d_t{  0,  1 }},
		octant_t{ offset_2d_t{  0, -1 }, offset_2d_t{ -1,  0 }},
		octant_t{ offset_2d_t{ -1,  0 }, offset_2d_t{  0, -1 }},
		octant_t{ offset_2d_t{  0, -1 }, offset_2d_t{  1,  0 }},
		octant_t{ offset_2d_t{  1,  0 }, offset_2d_t{  0, -1 }}
	};
}
