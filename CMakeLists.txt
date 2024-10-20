cmake_minimum_required(VERSION 3.29)
project(MemoryGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -finput-charset=UTF-8 -fexec-charset=UTF-8 --static")

add_executable(MemoryGame main.cpp
        game/user/User.cpp
        game/user/UserManager.cpp
        game/user/User.h
        game/user/UserManager.h
        game/board/BoardManager.h
        game/board/BoardManager.cpp
        game/board/card/Card.cpp
        game/board/card/Card.h
        game/board/Board.cpp
        game/board/Board.h
        game/board/difficulty/Difficulty.h
        game/board/card/CardTypeService.h
        game/board/difficulty/DifficultyProvider.h
        game/user/UserProvider.cpp
        game/user/UserProvider.h
        game/board/queue/TurnQueue.cpp
        game/board/queue/TurnQueue.h
        game/Game.cpp
        game/Game.h
        game/board/SizeProvider.h
        game/backup/BackupService.cpp
        game/backup/BackupService.h
)
