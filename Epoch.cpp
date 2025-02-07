#include <stdio.h>
#include <time.h>

// Tarih bilgilerini saklamak için struct tanýmlama
struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

// Tarih ve saati epoch'a dönüþtürme fonksiyonu
time_t epochZamaninaDonustur(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    zamanBilgisi.tm_year = ts.yil - 1900; // yýl 1900'den baþlar
    zamanBilgisi.tm_mon = ts.ay - 1; // ay 0'dan baþlar
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    zamanBilgisi.tm_isdst = -1; // yaz saati uygulamasý bilgisi yok
    return mktime(&zamanBilgisi);
}

// Tarih ve saat bilgilerini kullanýcýdan alma fonksiyonu
void kullaniciGirdisi(struct TarihSaat *ts) {
    printf("Yýl: ");
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
    
    // Kullanýcýdan ilk tarihi al
    printf("Birinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts1);
    
    // Kullanýcýdan ikinci tarihi al
    printf("Ýkinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts2);
    
    // Epoch zamanýna dönüþtür
    epochZamani1 = epochZamaninaDonustur(ts1);
    epochZamani2 = epochZamaninaDonustur(ts2);
    
    // Zaman farkýný hesapla
    double fark = difftime(epochZamani2, epochZamani1);
    
    // Sonuçlarý yazdýr
    printf("Birinci tarih epoch zamaný: %ld\n", (long)epochZamani1);
    printf("Ýkinci tarih epoch zamaný: %ld\n", (long)epochZamani2);
    printf("Ýki tarih arasýndaki fark: %.0f saniye\n", fark);
    
    return 0;
}

