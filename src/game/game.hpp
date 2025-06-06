/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file game.hpp Base functions for all Games. */

#ifndef GAME_HPP
#define GAME_HPP

#include "game_scanner.hpp"

#include "../script/api/script_event_types.hpp"

/**
 * Main Game class. Contains all functions needed to start, stop, save and load Game Scripts.
 */
class Game {
public:
	/**
	 * Called every game-tick to let Game do something.
	 */
	static void GameLoop();

	/**
	 * Initialize the Game system.
	 */
	static void Initialize();

	/**
	 * Start up a new GameScript.
	 */
	static void StartNew();

	/**
	 * Uninitialize the Game system.
	 */
	static void Uninitialize(bool keepConfig);

	/**
	 * Suspends the Game Script and then pause the execution of the script. The
	 * script will not be resumed from its suspended state until the script
	 * has been unpaused.
	 */
	static void Pause();

	/**
	 * Resume execution of the Game Script. This function will not actually execute
	 * the script, but set a flag so that the script is executed by the usual
	 * mechanism that executes the script.
	 */
	static void Unpause();

	/**
	 * Checks if the Game Script is paused.
	 * @return true if the Game Script is paused, otherwise false.
	 */
	static bool IsPaused();

	/**
	 * Queue a new event for a Game Script.
	 */
	static void NewEvent(class ScriptEvent *event);

	/**
	 * Get the current GameInfo.
	 */
	static class GameInfo *GetInfo() { return Game::info; }

	static void Rescan();
	static void ResetConfig();

	/**
	 * Save data from a GameScript to a savegame.
	 */
	static void Save();

	/** Wrapper function for GameScanner::GetConsoleList */
	static void GetConsoleList(std::back_insert_iterator<std::string> &output_iterator, bool newest_only);
	/** Wrapper function for GameScanner::GetConsoleLibraryList */
	static void GetConsoleLibraryList(std::back_insert_iterator<std::string> &output_iterator);
	/** Wrapper function for GameScanner::GetInfoList */
	static const ScriptInfoList *GetInfoList();
	/** Wrapper function for GameScanner::GetUniqueInfoList */
	static const ScriptInfoList *GetUniqueInfoList();
	/** Wrapper function for GameScannerInfo::FindInfo */
	static class GameInfo *FindInfo(const std::string &name, int version, bool force_exact_match);
	/** Wrapper function for GameScanner::FindLibrary */
	static class GameLibrary *FindLibrary(const std::string &library, int version);

	/**
	 * Get the current active instance.
	 */
	static class GameInstance *GetInstance() { return Game::instance.get(); }

	/**
	 * Reset the current active instance.
	 */
	static void ResetInstance();

	/** Wrapper function for GameScanner::HasGame */
	static bool HasGame(const struct ContentInfo *ci, bool md5sum);
	static bool HasGameLibrary(const ContentInfo *ci, bool md5sum);
	/** Gets the ScriptScanner instance that is used to find Game scripts */
	static GameScannerInfo *GetScannerInfo();
	/** Gets the ScriptScanner instance that is used to find Game Libraries */
	static GameScannerLibrary *GetScannerLibrary();

private:
	static uint frame_counter; ///< Tick counter for the Game code.
	static std::unique_ptr<GameInstance> instance; ///< Instance to the current active Game.
	static std::unique_ptr<GameScannerInfo> scanner_info; ///< Scanner for Game scripts.
	static std::unique_ptr<GameScannerLibrary> scanner_library; ///< Scanner for GS Libraries.
	static GameInfo *info; ///< Current selected GameInfo.
};

#endif /* GAME_HPP */
