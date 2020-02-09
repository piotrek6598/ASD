# Jablka

Laboratorium z ASD, Zadanie zaliczeniowe 1. Dostępna pamięć: 32 MB. 17.11.2019 23:59:59 <br/>
Na działce Bajtazara rośnie rozłożysta jabłoń. Jak w przypadku większości drzew w Bajtocji, każda gałąź
drzewa dokładnie metr powyżej miejsca rozpoczęcia kończy się lub rozwidla się na dwie mniejsze gałęzie.
Dodatkowo w punkcie każdego rozwidlenia oraz na końcach gałęzi rośnie dokładnie jedno jabłko. Bajtazar
zauważył, że pomimo tego, że jego drzewo jest bardzo duże, to posiada stosunkowo nieskomplikowaną strukturę:
występuje w nim co najwyżej n różnych typów gałęzi. Dzięki drabinie długości d metrów Bajtazar pozrywał
wszystkie jabłka do tej właśnie wysokości włącznie. Teraz zastanawia się, jak wiele jabłek wciąż pozostało na
drzewie. Napisz program, który wczyta reprezentację struktury drzewa i pomoże Bajtazarowi wyznaczyć liczbę
niezebranych jabłek.<br/>
<b>Wejście</b><br/>
Pierwszy wiersz zawiera dwie liczby całkowite n oraz d (1 ≤ n ≤ 10^6
, 1 ≤ d ≤ 100). Każdy z kolejnych n
wierszy zawiera dwie liczby całkowite ak oraz bk (0 ≤ ak, bk < k), oznaczające, że gałąź typu k rozdziela
się na dwie mniejsze, jedną typu ak i jedną typu bk. Liczba 0 oznacza gałąź, która nie ulega już podziałowi.
Z korzenia wychodzi gałąź typu n.<br/>
<b>Wyjście</b><br/>
Twój program powinien wypisać resztę z dzielenia przez 10^9
liczby węzłów drzewa oddalonych od korzenia
o więcej niż d metrów.<br/>
Przykład
Dla danych wejściowych:<br/>
4 3<br/>
0 0<br/>
1 0<br/>
2 1<br/>
3 2<br/>
poprawnym wynikiem jest:<br/>
8

Natomiast dla danych wejściowych: <br/>
4 4<br/>
0 0<br/>
1 0<br/>
2 1<br/>
3 2<br/>
poprawnym wynikiem jest:<br/>
2


# Cezar

ASD-lab, . Plik źródłowy cez.* Dostępna pamięć: 256 MB.
Jest ciężko. Wercyngetoryks, wódz galijskiej armii, ufortyfikował się w najbliższym mieście. Galijscy sojusznicy z północy obiecali nam dostawę zaopatrzenia, ale pewnie tylko sam Jupiter wie, kiedy i czy w ogóle
ona dotrze. Trzeba zebrać zapasy z okolicy. Cezar polecił Ci sformowanie patroli, które przeczeszą okolice w
poszukiwaniu jedzenia.
Ustawiłeś swoich żołnierzy jeden długi szereg o długości n. Każdy patrol stanowi pewien niepusty podciąg
żołnierzy - na rozkaz wskazani żołnierze występują z głównego szeregu i ustawiają się w nowy, zachowując
dotychczasową kolejność.
Cezar przechadza się wzdłuż szeregu i wydaje Ci polecenia:
• ? i j - polecenie typu ? - oblicz, na ile sposobów można wybrać godny zaufania patrol spośród żołnierzy
pomiędzy i-tym a j-tym włącznie. Jako że liczba sposobów może być bardzo duża, Cezarowi wystarczy
tylko wynik modulo 10^9 + 7.
Każdy rzymski legionista (’R’) jest godny zaufania. A przynajmniej tak musisz założyć. Jednak niestety, oprócz
Rzymian, Twój oddział zawiera także galijskich sojuszników z północy (’G’). O ile Galowie są podstępni, to w
otoczeniu legionistów są raczej niegroźni. Zatem warunkiem na to, by patrol był godny zaufania, jest to, by
dwóch Galów nie stało obok siebie. W ten sposób nie będą mogli ze sobą swobodnie spiskować. Divide et impera,
czyli dziel i rządź. Jako że rządzenie powinno polegać na łączeniu, to w wolnym tłumaczeniu: Split&Join.
Cezar wie, że nie może tasować Galów zupełnie bezkarnie. By korzystnie przebudować szereg i uniknąć
podejrzeń o dyskryminację (co mogłoby go narazić na bunt galijskich sojuszników, albo, co gorsza, wizytę
z rzymskiego HRu), Cezar postanowił, że będzie operował na szeregu używając następującego, etnicznieneutralnego rozkazu:
• O i j - polecenie typu O - odwróć kolejność żołnierzy między i-tym, a j-tym włącznie.
Dzięki temu poleceniu Cezar będzie mógł osiągnąć dowolną zaplanowaną przez siebie kolejność w szeregu.
Rzymskie szeregi są liczebne, a czasu jest niedużo. Wykonaj rozkazy Cezara! Do dzieła, legacie!
Wejście
W pierwszym wierszu wejścia podane są dwie liczby n i m (1 ≤ n, m ≤ 100 000) określające odpowiednio
liczebność szeregu i liczbę zapytań Cezara. Następny wiersz zawiera opis początkowego stanu szeregu, czyli
n znaków (’R’ lub ’G’) Kolejne m wierszy jest w formie t i j (t ∈ {?, O}, i ≤ j, 1 ≤ i, j ≤ n), każdy z nich
definiuje pojedyncze polecenie Cezara.
Wyjście
Na każde polecenie typu ? odpowiedz jedną liczbą w wierszu oznaczającą liczbę sposobów na wybranie godnego
zaufania patrolu z żołnierzy z zadanego przedziału. Jako że odpowiedź może być duża, wynik wypisz modulo
10^9 + 7.<br/>
Przykład<br/>
Dla danych wejściowych:<br/>
3 3<br/>
GRG<br/>
? 1 3<br/>
O 1 2<br/>
? 1 3<br/>

poprawnym wynikiem jest:<br/>
6<br/>
5<br/>
