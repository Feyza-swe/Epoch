#include <stdio.h>
#include <time.h>

// Tarih bilgilerini saklamak i�in struct tan�mlama
struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

// Tarih ve saati epoch'a d�n��t�rme fonksiyonu
time_t epochZamaninaDonustur(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    zamanBilgisi.tm_year = ts.yil - 1900; // y�l 1900'den ba�lar
    zamanBilgisi.tm_mon = ts.ay - 1; // ay 0'dan ba�lar
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    zamanBilgisi.tm_isdst = -1; // yaz saati uygulamas� bilgisi yok
    return mktime(&zamanBilgisi);
}

// Tarih ve saat bilgilerini kullan�c�dan alma fonksiyonu
void kullaniciGirdisi(struct TarihSaat *ts) {
    printf("Y�l: ");
    scanf("%d", &ts->yil);
    printf("Ay: ");
    scanf("%d", &ts->ay);
    printf("G�n: ");
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
    
    // Kullan�c�dan ilk tarihi al
    printf("Birinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts1);
    
    // Kullan�c�dan ikinci tarihi al
    printf("�kinci tarih ve saati giriniz:\n");
    kullaniciGirdisi(&ts2);
    
    // Epoch zaman�na d�n��t�r
    epochZamani1 = epochZamaninaDonustur(ts1);
    epochZamani2 = epochZamaninaDonustur(ts2);
    
    // Zaman fark�n� hesapla
    double fark = difftime(epochZamani2, epochZamani1);
    
    // Sonu�lar� yazd�r
    printf("Birinci tarih epoch zaman�: %ld\n", (long)epochZamani1);
    printf("�kinci tarih epoch zaman�: %ld\n", (long)epochZamani2);
    printf("�ki tarih aras�ndaki fark: %.0f saniye\n", fark);
    
    return 0;
}

