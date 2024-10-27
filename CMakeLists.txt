cmake_minimum_required(VERSION 3.29)
project(MemoryGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -finput-charset=UTF-8 -fexec-charset=UTF-8 --static")

include(FetchContent)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(MemoryGame
        src/main.cpp
        src/game/user/User.cpp
        src/game/user/UserManager.cpp
        src/game/user/User.h
        src/game/user/UserManager.h
        src/game/board/BoardManager.h
        src/game/board/BoardManager.cpp
        src/game/board/card/Card.cpp
        src/game/board/card/Card.h
        src/game/board/Board.cpp
        src/game/board/Board.h
        src/game/board/difficulty/Difficulty.h
        src/game/board/card/CardTypeService.h
        src/game/board/difficulty/DifficultyProvider.h
        src/game/user/UserProvider.cpp
        src/game/user/UserProvider.h
        src/game/board/queue/TurnQueue.cpp
        src/game/board/queue/TurnQueue.h
        src/game/Game.cpp
        src/game/Game.h
        src/game/board/SizeProvider.h
        src/game/backup/BackupService.cpp
        src/game/backup/BackupService.h
        src/game/backup/LoadHandler.h
        src/game/backup/LoadHandler.cpp
        src/game/user/UserRepository.cpp
        src/game/user/UserRepository.h
        src/game/user/UserStatistics.h
        src/game/user/UserStatistics.cpp
        src/game/GameState.h
        src/game/CardSelector.h
        src/game/score/ScoreManager.h
        src/game/CardSelector.cpp
        src/game/GameState.cpp
        src/game/score/ScoreManager.cpp
        src/game/achievement/Achievement.h
        src/game/achievement/AchievementManager.h
        src/game/user/UserGameStats.cpp
        src/game/user/UserGameStats.h
        src/game/Menu.cpp
        src/game/Menu.h
)

target_link_libraries(MemoryGame PRIVATE nlohmann_json::nlohmann_json)
