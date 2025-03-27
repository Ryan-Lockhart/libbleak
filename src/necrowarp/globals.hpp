#pragma once

#include <bleak.hpp>

namespace necrowarp {
	namespace globals {
		using namespace bleak;

		constexpr std::string GameName{ "Necrowarp" };
		constexpr std::string GameVersion{ "0.0.1" };
		constexpr std::string GameAuthor{ "Ryan Lockhart" };

		const std::string GameTitle{ std::format("{} v{} by {}", GameName, GameVersion, GameAuthor) };

		constexpr sdl::window_flags WindowFlags{ static_cast<sdl::window_flags>(SDL_WINDOW_SHOWN) };
		constexpr sdl::renderer_flags RendererFlags{ static_cast<sdl::renderer_flags>(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };

		constexpr u32 FrameLimit{ 60u };
		constexpr f32 FrameTime{ 1000.0f / FrameLimit };

		constexpr bool UseFrameLimit{ true };

		constexpr extent_t WindowSize{ 1280, 720 };

		constexpr extent_t UIGridSize{ WindowSize / 8 };
		constexpr extent_t GameGridSize{ WindowSize / 16 };
		constexpr extent_t IconGridSize{ WindowSize / 32 };

		constexpr extent_t GlyphsetSize{ 16, 16 };
		constexpr extent_t TilesetSize{ 16, 5 };
		constexpr extent_t IconsetSize{ 3, 2 };

		constexpr extent_t MapSize{ 64, 32 };

		constexpr offset_t MapCenter{ MapSize / 2 };

		constexpr extent_t BorderSize{ 4, 4 };

		constexpr extent_t IconSize{ 32, 32 };
		constexpr extent_t CellSize{ 16, 16 };
		constexpr extent_t GlyphSize{ 8, 8 };

		constexpr f32 CellToGlyphRatio{ 2.0f };
		constexpr f32 GlyphToCellRatio{ 0.5f };

		constexpr offset_t convert_cell_to_glyph(cref<offset_t> position) noexcept {
			return offset_t{ offset_t::scalar_cast(position.x * CellToGlyphRatio), offset_t::scalar_cast(position.y * CellToGlyphRatio) };
		}

		constexpr offset_t convert_glyph_to_cell(cref<offset_t> position) noexcept {
			return offset_t{ offset_t::scalar_cast(position.x * GlyphToCellRatio), offset_t::scalar_cast(position.y * GlyphToCellRatio) };
		}

		constexpr offset_t CursorOffset{ CellSize / 4 };

		constexpr extent_t CameraExtent{ MapSize - globals::GameGridSize };
		constexpr offset_t::scalar_t CameraSpeed{ 2 };

		constexpr f64 FillPercent{ 0.425 };
		constexpr u32 AutomotaIterations{ 128 };
		constexpr u32 AutomotaThreshold{ 4 };

		constexpr u32 ViewDistance{ 8 };
		constexpr f64 ViewSpan{ 135.0 };

		constexpr i16 NumberOfUpLadders{ 8 };
		constexpr i16 NumberOfDownLadders{ 4 };
		constexpr i16 MinimumLadderDistance{ 16 };

		constexpr i16 StartingAdventurers{ 8 };

		constexpr i16 StartingSkulls{ 16 };
		constexpr i16 MinimumSkullDistance{ 16 };

		constexpr i16 SpawnDistributionLow{ 0 };
		constexpr i16 SpawnDistributionHigh{ 99 };

		constexpr i16 SmallWaveSize{ 8 };
		constexpr i16 MediumWaveSize{ 16 };
		constexpr i16 LargeWaveSize{ 32 };
		constexpr i16 HugeWaveSize{ 64 };

		constexpr i16 MinimumWaveSize{ 4 };
		constexpr i16 MaximumWaveSize{ 64 };

		constexpr i16 KillsPerPopulation{ 8 };

		constexpr i16 KillsPerEnergySlot{ 16 };
		constexpr i16 KillsPerArmorSlot{ 8 };
		constexpr i16 KillsPerDivinityTurn{ 64 };

		constexpr i16 MinimumReinforcements{ 0 };
		constexpr i16 MaximumReinforcements{ 4 };

		constexpr i16 FloorsPerReinforcement{ 8 };

		constexpr bool CheatsAllowed{ true };
	} // namespace globals
} // namespace necrowarp
