# 🚀 Dokumentacja projektu / Project Documentation

<details>
<summary>🇵🇱 Polski</summary>

# Jak zaimplementować projekt?
Aplikacja została napisana w środowisku **CLion** i zaleca się jej uruchamianie bezpośrednio w tym środowisku. Aplikacja implementuje jedną bibliotekę: [nlohmann/json](https://github.com/nlohmann/json), która jest dodana w pliku ```CMakeLists.txt```.

## Jak uruchomić projekt?
Należy utworzyć pusty folder, w którym będzie znajdować się plik wykonywalny. Następnie wystarczy uruchomić plik wykonywalny ```.exe``` (zaleca się korzystanie z aplikacji w trybie pełnoekranowym).

## Opis aplikacji
Po uruchomieniu gry użytkownikowi wyświetla się menu główne, w którym może wybrać jedną z pięciu opcji:
1. Nowa gra - rozpoczęcie nowej gry.
2. Wczytaj grę - wczytanie zapisanej gry.
3. Statystyki graczy - wyświetlenie statystyk graczy oraz odblokowanych przez nich osiągnięć. **Pojawią się tam tylko użytkownicy zapisani - tacy, którzy zagrali już w grę.**
4. Osiągnięcia - wyświetlenie wszystkich osiągnięć wraz z ich opisem.
5. Wyjście - wyjście z gry.

## Funkcjonalność
Do gry dodano kilka dodatkowych funkcji, które urozmaicają rozgrywkę:
1. Odblokowywanie osiągnięć.
2. Gra z komputerem - włącza się automatycznie, gdy wprowadzony zostanie tylko jeden gracz.
3. Zapisywanie użytkowników wraz z ich osiągnięciami i statystykami.
4. Poziomy trudności - gracz może wybrać poziom trudności, na którym chce grać.
5. Wyświetlanie statystyk graczy.
6. Wyświetlanie osiągnięć.
7. Możliwość wyboru rozmiaru planszy.
8. Możliwość grania w trybie hot-seat, aż do 10 graczy.
9. Zapisywanie gry w dowolnym momencie poprzez wpisanie ```!zapisz```. Grę można wczytać w menu głównym. Gra obsługuję wiele zapisów, które są zapisywane w folderze ```resources```.

## Dodatkowe informacje
- Aplikacja sama generuje folder ```resources``` w katalogu, w którym została uruchomiona gra.
- Cała gra jest napisana w języku C++ z wykorzystaniem biblioteki ```JSON``` do zapisu danych.
- Aplikacja zawiera 3200 linii kodu, a jej napisanie zajęło prawie 27 godzin.

## Autor
- **Autorem aplikacji jest Karol Dronia.**
</details>

<details>
<summary>🇬🇧 English</summary>

# How to implement the project?
The application was written in the **CLion** environment, and it is recommended to run it directly in this environment. The application implements one library: [nlohmann/json](https://github.com/nlohmann/json), which is added in the ```CMakeLists.txt``` file.

## How to run the project?
Create an empty folder where the executable file will be located. Then simply run the ```.exe``` executable file (it is recommended to use the application in full-screen mode).

## Application description
After launching the game, the main menu is displayed to the user, where they can choose one of five options:
1. New game - start a new game.
2. Load game - load a saved game.
3. Player statistics - display player statistics and achievements they have unlocked. **Only saved users will appear there - those who have already played the game.**
4. Achievements - display all achievements along with their descriptions.
5. Exit - exit the game.

## Functionality
Several additional functions have been added to the game to enhance gameplay:
1. Unlocking achievements.
2. Playing against the computer - automatically enabled when only one player is entered.
3. Saving users along with their achievements and statistics.
4. Difficulty levels - the player can choose the difficulty level they want to play at.
5. Displaying player statistics.
6. Displaying achievements.
7. Ability to choose the board size.
8. Ability to play in hot-seat mode with up to 10 players.
9. Saving the game at any time by typing ```!save```. The game can be loaded from the main menu. The game supports multiple saves, which are stored in the ```resources``` folder.

## Additional information
- The application automatically generates a ```resources``` folder in the directory where the game was launched.
- The entire game is written in C++ using the ```JSON``` library for data storage.
- The application contains 3,200 lines of code, and it took almost 27 hours to write.

## Author
- **The author of the application is Karol Dronia.**
</details>
