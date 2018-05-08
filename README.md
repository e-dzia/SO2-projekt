# SO2-projekt

Piekarze pobierają składniki z magazynu (najkrótszy etap), urabiają ciasto na stole (średnio długi etap) i pieką chleb w piekarniku (najdłuższy etap), po czym kładą gotowy chleb na półki.

Przy magazynie, stole i piecu może przebywać tylko jeden kucharz na raz, przy czym kucharz jest przy piecu potrzebny tylko do włożenia i wyciągnięcia chleba.

W piecu i na półce może naraz znajdować się pewna liczba chlebów.

Klienci wchodzą do sklepu i kupują chleb z półki, jednocześnie płacąc za niego (zwiększając stan konta piekarni). Chlebów może być kilka rodzajów dla urozmaicenia (klient chce kupić konkretny rodzaj).

Może istnieć kolejka klientów.

Sprzedawca w tej wersji jest niepotrzebny.

Powinien za to być wątek piekarnika, który zwiększa okresowo upieczenie chlebów aktualnie znajdujących się w piekarniku.

Reasumując:

wątki: piekarze, piec, klienci.

zasoby: magazyn, stół, piec, półka, konto piekarni.
