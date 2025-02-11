#include <stdio.h>
#include <time.h>
#include <string.h>

// Tarih ve saat bilgilerini saklamak icin yapi tanimlama
struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

// Toplanti bilgilerini saklamak icin yapi tanimlama
struct Toplanti {
    char ad[100];
    struct TarihSaat baslangic;
    struct TarihSaat bitis;
    time_t baslangic_epoch;
    time_t bitis_epoch;
};

// Tarih ve saati epoch zamanina donusturme fonksiyonu
time_t epochZamaninaDonustur(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    zamanBilgisi.tm_year = ts.yil - 1900;
    zamanBilgisi.tm_mon = ts.ay - 1;
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    zamanBilgisi.tm_isdst = -1; // Yaz saati uygulamasi otomatik
    return mktime(&zamanBilgisi);
}

// Tarih ve saat bilgilerini kullanicidan alma fonksiyonu
void kullaniciGirdisi(struct TarihSaat *ts) {
    printf("Yil (or: 2023): ");
    scanf("%d", &ts->yil);
    printf("Ay (1-12): ");
    scanf("%d", &ts->ay);
    printf("Gun (1-31): ");
    scanf("%d", &ts->gun);
    printf("Saat (0-23): ");
    scanf("%d", &ts->saat);
    printf("Dakika (0-59): ");
    scanf("%d", &ts->dakika);
    printf("Saniye (0-59): ");
    scanf("%d", &ts->saniye);
}

// Toplanti bilgilerini ekrana yazdirma fonksiyonu
void toplantiBilgisiYazdir(struct Toplanti t) {
    printf("\nToplanti Adi: %s\n", t.ad);
    printf("Baslangic Zamani: %04d-%02d-%02d %02d:%02d:%02d\n",
           t.baslangic.yil, t.baslangic.ay, t.baslangic.gun,
           t.baslangic.saat, t.baslangic.dakika, t.baslangic.saniye);
    printf("Bitis Zamani: %04d-%02d-%02d %02d:%02d:%02d\n",
           t.bitis.yil, t.bitis.ay, t.bitis.gun,
           t.bitis.saat, t.bitis.dakika, t.bitis.saniye);
}

int main() {
    struct Toplanti toplanti1;
    time_t simdi = time(NULL);
    double kalanSure;

    // Toplanti bilgilerini al
    printf("Toplantinin adini giriniz: ");
    getchar(); // Onceki girdiden kalan newline karakterini temizle
    fgets(toplanti1.ad, sizeof(toplanti1.ad), stdin);
    toplanti1.ad[strcspn(toplanti1.ad, "\n")] = '\0'; // Yeni satir karakterini kaldir

    printf("Toplantinin baslangic zamanini giriniz:\n");
    kullaniciGirdisi(&toplanti1.baslangic);

    printf("Toplantinin bitis zamanini giriniz:\n");
    kullaniciGirdisi(&toplanti1.bitis);

    // Epoch zamanina donustur
    toplanti1.baslangic_epoch = epochZamaninaDonustur(toplanti1.baslangic);
    toplanti1.bitis_epoch = epochZamaninaDonustur(toplanti1.bitis);

    // Toplanti bilgilerini yazdir
    printf("\n--- Toplanti Bilgileri ---\n");
    toplantiBilgisiYazdir(toplanti1);

    // Toplantiya kalan sureyi hesapla
    kalanSure = difftime(toplanti1.baslangic_epoch, simdi);
    if (kalanSure > 0) {
        int kalanGun = (int)(kalanSure / (24 * 3600));
        kalanSure -= kalanGun * 24 * 3600;

        int kalanSaat = (int)(kalanSure / 3600);
        kalanSure -= kalanSaat * 3600;

        int kalanDakika = (int)(kalanSure / 60);
        int kalanSaniye = (int)(kalanSure - kalanDakika * 60);

        printf("\nToplantiya kalan sure: %d gun %d saat %d dakika %d saniye\n",
               kalanGun, kalanSaat, kalanDakika, kalanSaniye);
    } else if (difftime(toplanti1.bitis_epoch, simdi) > 0) {
        printf("\nToplanti su anda devam ediyor.\n");
    } else {
        printf("\nToplanti basladi veya gecti.\n");
    }

    return 0;
}

