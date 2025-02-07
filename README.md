# Epoch Hesaplama Programı

Bu proje, kullanıcı tarafından girilen iki farklı tarih ve saat bilgisi arasındaki zaman farkını epoch üzerinden hesaplayan bir C programını içermektedir.

## Epoch Nedir?

Epoch, bilgisayar sistemlerinde zamanın başlangıç noktası olarak kabul edilir ve çoğunlukla 1 Ocak 1970, UTC'yi referans alır. Bu tarihten itibaren geçen saniyeler epoch zamanı olarak kabul edilir ve birçok işletim sistemi ve programlama dili zaman hesaplamaları için bu zamanı kullanır.

## Program Açıklaması

Bu program, kullanıcıdan iki farklı tarih ve saat bilgisi alır, bu bilgileri epoch zamanına dönüştürür ve iki tarih arasındaki zaman farkını saniye cinsinden hesaplar ve ekrana yazdırır. Program, `struct` ve `union` kullanarak işlem yapmaktadır.

## Kullanım

1. Programı çalıştırın.
2. İlk tarih ve saat bilgilerini girin (örneğin: 2023, 4, 5, 12, 30, 45).
3. İkinci tarih ve saat bilgilerini girin (örneğin: 2023, 4, 6, 15, 45, 30).
4. Program, girilen tarih ve saat bilgilerini epoch zamanına dönüştürecek ve iki tarih arasındaki zaman farkını saniye cinsinden ekrana yazdıracaktır.

## Kod

```c
#include <stdio.h>
#include <time.h>

// Tarih bilgilerini saklamak için struct tanımlama
struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

// Tarih ve saati epoch'a dönüştürme fonksiyonu
time_t epochZamaninaDonustur(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    zamanBilgisi.tm_year = ts.yil - 1900;
    zamanBilgisi.tm_mon = ts.ay - 1;
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    zamanBilgisi.tm_isdst = -1;
    return mktime(&zamanBilgisi);
}

// Tarih ve saat bilgilerini kullanıcıdan alma fonksiyonu
void kullaniciGirdisi(struct TarihSaat *ts) {
    printf("Yıl: ");
    scanf("%d", &ts->yil);
    printf("Ay: ");
    scanf("%d", &ts->ay);
    printf("Gün: ");
    scanf("%d", &ts->gun);
    printf("Saat: ");
    scanf("%d", &ts->saat);
    printf("Dakika: ");
    scanf("%d", &ts->dakika);
    printf("Saniye: ");
    scanf("%d", &ts->saniye);
}

int main() {
    struct TarihSaat ts1, ts2;
    time_t epochZamani1, epochZamani2;

    // Kullanıcıdan ilk tarihi al
    printf("Birinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts1);

    // Kullanıcıdan ikinci tarihi al
    printf("İkinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts2);

    // Epoch zamanına dönüştür
    epochZamani1 = epochZamaninaDonustur(ts1);
    epochZamani2 = epochZamaninaDonustur(ts2);

    // Zaman farkını hesapla
    double fark = difftime(epochZamani2, epochZamani1);

    // Sonuçları yazdır
    printf("Birinci tarih epoch zamanı: %ld\n", (long)epochZamani1);
    printf("İkinci tarih epoch zamanı: %ld\n", (long)epochZamani2);
    printf("İki tarih arasındaki fark: %.0f saniye\n", fark);

    return 0;
}
