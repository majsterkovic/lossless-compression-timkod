### Jaka jest najkrótsza możliwa długość takiego kodu dla korpusu z dzisiejszych zajęć?

Najkrótsza możliwa długość takiego kodu dla korpusu z dzisiejszych zajęć wyniesie 6 bitów na symbol, ponieważ liczba możliwych symboli jest mniejsza od 2^6 i większa od 2^5.

###  Ile wyniesie stopień kompresji?

Stopień kompresji wyniesie około 75% (potencjalna niewielka różnica wynika z zapisu pełnych bajtów w zakodowanym pliku, im większy plik, tym narzut ten ma mniejsze znaczenie).

### Jaki jest rozmiar oryginalnego pliku, a jaki pliku (lub plików) z kodem i zakodowaną reprezentacją?

* oryginalny plik: 10 788 941 bajtów

* zakodowany plik: 8 091 706 bajtów (około 75% oryginalnego pliku, co jest zgodne, bo kodujemy na 6 bitach, a nie na 8)
* plik z kodem: 370 bajtów

### Co można zrobić, żeby bardziej skompresować tekst?

Aby bardziej skompresować tekst, można zastosować bardziej zaawansowane techniki kompresji danych, np. zmienną długość kodów.

### Co z nieużytymi kodami?

Nieużyte kody (jeśli istnieją) zajmują niepotrzebnie miejsce w pliku z kodami. Poza tym, jeśli nie są potrzebne kody dla wszystkich znaków, to można użyć mniejszej liczby bitów na kod.

### Jak odkodowywać kody o zmiennej długości (ang. variable-length code)?

Aby odkodowywać kody o zmiennej długości, można zastosować kod prefiksowy, czyli żaden kod nie jest prefiksem innego kodu.

### Jaka jest granica wydajności takich kodów (ang. symbol-by-symbol)?

Granica wydajności kodów symbol-po-symbolu jest osiągana w przypadku, gdy długość kodu każdego symbolu jest równa logarytmowi o podstawie 2 z liczby możliwych symboli. Oznacza to, że długość kodu rośnie proporcjonalnie do logarytmu liczby symboli. Przykładowo, jeśli mamy alfabet o rozmiarze 256 (jak w przypadku kodowania bajtowego), granica wydajności to 8 bitów na symbol (log2(256) = 8).