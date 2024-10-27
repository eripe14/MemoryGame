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