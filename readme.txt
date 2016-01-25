AAL projekt 
zima 2015/2016

Andrzej Roguski


TREŚĆ ZADANIA:
Dany jest zbiór miast i dróg między nimi. Czas potrzebny na przebycie danej drogi zależy od pory dnia
i zmienia się co 6 godzin, przy czym liczy się wyłącznie godzina wjazdu na drogę. Czas liczony jest z
rozdzielczością godzinową.
Opracować algorytm wyznaczający godzinę wyjazdu oraz trasę pozwalające na jak najkrótsze przebycie
drogi od miasta A do miasta B.


KOMPILACJA
w katalogu z projektem
$ make


URUCHAMIANIE
./main -f nazwa_pliku  -  wczytanie grafu z testowego pliku


Niestety, jedynym testem jest graf zawarty w pliku "test". W pliku test.png pokazana jest struktura tego grafu.
Krawędzie skierowane mają wagi 1 1 1 1 w kierunku niepokazanym na rysunku.
Test wyszukuje najlepszej ścieżki od 0 do 3.


./main -t min max num  -  generuje num grafów o liczbie wierzcholków od min do max
                          liczba wierzchołków kolejnych grafów jest równomiernie rozłożona w przedziale
przykład:
./main -t 10 50 5 generuje grafy o 10, 20, 30, 40 i 50 wierzchołkach

jeśli num == 1, generowany jest jeden graf o liczbie wierzchołków == min


WYJŚCIE PROGRAMU
Program wypisuje najlepszą ścieżkę oraz godzinę wyruszenia z wierzchołka startowego. 


METODA ROZWIĄZANIA
Zastosowanie algorytmu dijkstry dla każdej możliwej godziny opuszczenia miasta.


FUNKCJONALNA DEKOMPOZYCJA PROGRAMU
Pliki nagłówkowe z deklaracjami klas, stałych i typów znajdują się w folderze include.
Pliki z implementacjami metod klas znajdują się w folderze src.


DECYZJE PROJEKTOWE
Ograniczony został maksymalny rozmiar grafu - do 10000 wierzchołków, z racji znacznej ilości zasobów
potrzebnych do przetwarzania dużych grafów gęstych.

Generowanie grafów przebiega na zasadzie losowania punktów na płaszczyźnie i obliczania odległości.
Wyliczone odległości są modyfikowane o współczynnik losowy, modyfikujący odległość w granicach +-30% pierwotnej wartości.
