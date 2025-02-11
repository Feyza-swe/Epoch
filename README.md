# Epoch Zaman Farkı Hesaplama Programı

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

// Tarih bilgilerini saklamak icin struct tanimlama
struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

// Tarih ve saati epoch'a donusturme fonksiyonu
time_t epochZamaninaDonustur(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    zamanBilgisi.tm_year = ts.yil - 1900;  // Yil 1900'dan baslar
    zamanBilgisi.tm_mon = ts.ay - 1;       // Ay 0'dan baslar
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    zamanBilgisi.tm_isdst = -1;            // Yaz saati bilgisi yok
    return mktime(&zamanBilgisi);
}

// Tarih ve saat bilgilerini kullanicidan alma fonksiyonu
void kullaniciGirdisi(struct TarihSaat *ts) {
    printf("Yil: ");
    scanf("%d", &ts->yil);
    printf("Ay: ");
    scanf("%d", &ts->ay);
    printf("Gun: ");
    scanf("%d", &ts->gun);
    printf("Saat: ");
    scanf("%d", &ts->saat);
    printf("Dakika: ");
    scanf("%d", &ts->dakika);
    printf("Saniye: ");
    scanf("%d", &ts->saniye);
}

// Iki tarih arasindaki farki hesaplama fonksiyonu
void farkiHesapla(struct TarihSaat ts1, struct TarihSaat ts2) {
    // Zaman yapilarina donustur
    struct tm t1;
    t1.tm_year = ts1.yil - 1900;
    t1.tm_mon = ts1.ay - 1;
    t1.tm_mday = ts1.gun;
    t1.tm_hour = ts1.saat;
    t1.tm_min = ts1.dakika;
    t1.tm_sec = ts1.saniye;
    t1.tm_isdst = -1;

    struct tm t2;
    t2.tm_year = ts2.yil - 1900;
    t2.tm_mon = ts2.ay - 1;
    t2.tm_mday = ts2.gun;
    t2.tm_hour = ts2.saat;
    t2.tm_min = ts2.dakika;
    t2.tm_sec = ts2.saniye;
    t2.tm_isdst = -1;

    // Epoch zamanlarina donustur
    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    if (time1 == (time_t)(-1) || time2 == (time_t)(-1)) {
        printf("Zaman donusturmede hata olustu.\n");
        return;
    }

    // Epoch zamanlarini yazdir
    printf("\nBirinci tarih epoch zamani: %ld\n", (long)time1);
    printf("Ikinci tarih epoch zamani: %ld\n", (long)time2);

    // Epoch zamanlari arasindaki farki hesapla
    double farkSaniye = difftime(time2, time1);

    if (farkSaniye < 0) {
        printf("\nIkinci tarih, birinci tarihten once olamaz.\n");
        return;
    }

    // Iki tarih arasindaki farki hesapla
    int yil, ay, gun, saat, dakika, saniye;
    saniye = t2.tm_sec - t1.tm_sec;
    dakika = t2.tm_min - t1.tm_min;
    saat = t2.tm_hour - t1.tm_hour;
    gun = t2.tm_mday - t1.tm_mday;
    ay = t2.tm_mon - t1.tm_mon;
    yil = t2.tm_year - t1.tm_year;

    // Negatif degerleri duzelt
    if (saniye < 0) {
        saniye += 60;
        dakika--;
    }
    if (dakika < 0) {
        dakika += 60;
        saat--;
    }
    if (saat < 0) {
        saat += 24;
        gun--;
    }
    if (gun < 0) {
        // Onceki ayin gun sayisini bul
        t2.tm_mon--;
        if (t2.tm_mon < 0) {
            t2.tm_mon += 12;
            t2.tm_year--;
        }

        int aylar[] = {31, (t2.tm_year % 4 == 0 && (t2.tm_year % 100 != 0 || t2.tm_year % 400 == 0)) ? 29 : 28,
                       31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        gun += aylar[t2.tm_mon];
        ay--;
    }
    if (ay < 0) {
        ay += 12;
        yil--;
    }

    // Sonuclari yazdir
    printf("Iki epoch zamani arasindaki fark: %.0f saniye\n", farkSaniye);
    printf("Iki tarih arasindaki fark:\n");
    printf("%d yil, %d ay, %d gun, %d saat, %d dakika, %d saniye\n", yil, ay, gun, saat, dakika, saniye);
}

int main() {
    struct TarihSaat ts1, ts2;

    // Kullanicidan ilk tarihi al
    printf("Birinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts1);

    // Kullanicidan ikinci tarihi al
    printf("Ikinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts2);

    // Zaman farkini hesapla ve epoch zamanlarini yazdir
    farkiHesapla(ts1, ts2);

    return 0;
}

