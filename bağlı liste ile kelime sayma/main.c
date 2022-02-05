#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n {          //linked list tanýmý
    int adet;
    char *kelime;
    struct n *next;
};

typedef struct n node;      //n tipinde deðiþkeni oluþturma

int enKucuk = 0;      //yeni eklenen kelimenin sona eklenip eklenmeyeceðini kontrol etmeyi saðlayan deðiþken

void bastir(node *r) {   //linked listi bastýrma fonksiyonu, parametre olarak linked listin baþ elemanýný alýyor
    int b = 1;
    while (r != NULL) {     //NULL olana kadar elemanlarý yazdýrma döngüsü
        printf("%2d. %s: %d\n", b, r->kelime, r->adet);
        r = r->next;
        b++;
    }
}

int ara(node *r, char *kelimee) {    //arama fonksiyonu, parametre olarak linked listin baþ elemanýný ve aranacak kelimeyi alýyor
    int a = 0;
    while (r != NULL) {     //linked list en sona gidene kadar ara, eðer o kelime daha önceden linked liste eklenmiþse
        if (strcmp(r->kelime, kelimee) == 0) {   //a deðerini 1 yap
            a = 1;
        }
        r = r->next;
    }
    return a;  //aranacak kelime linked listte varsa 1, yoksa 0 döndür
}

int kacTane(char *kelime) {     //o an okunan kelimeden txt dosyasýnda kaç tane olduðunu bulan döngü
    char *str = malloc(sizeof(char) * 100);
    int count = 0;      //kaç tane olduðunu sayan deðiþken

    FILE *dosya;
    dosya = fopen("C:\\Users\\JAN\\Desktop\\metin.txt", "r");   //dosyayý okuma modunda aç

    if (dosya == 0) {					//dosya açýlmadýysa programý sonlandýr
        printf("Dosya acilamadi.");
        return 0;
    }

    fscanf(dosya, "%s", str);       //boþluk görene kadar oku ve okuduðun string i str deðiþkenine ata

    while (!feof(dosya)) {      //txt nin sonuna gidene kadar devam eden döngü
        if (strcmp(str, kelime) == 0)   //aranacak kelimeden txt de varsa
            count++;                    //count deðiþkenini 1 arttýr
        fscanf(dosya, "%s", str);       //sýradaki kelimeyi oku ve str deðiþkenine ata
    }

    fclose(dosya);      //dosyayý kapa
    return count;       //o kelimeden kaç tane olduðunu gösteren deðiþkenin deðerini döndür
}

node *basaEkle(node *r, int adet, char *kelime) {   //yeni okunan kelimenin adet deðeri linked listin ilk elemanýnýn
    node *temp = (node *) malloc(sizeof(node));     //deðerinden daha yüksekse
    temp->adet = adet;          //temp adýnda kutu oluþturduk, adet ve kelime bilgisini atadýk
    temp->kelime = kelime;
    temp->next = r;             //temp in next i r yi gösterdi, yani ilk elemanýmýz temp oldu
    return temp;                //temp i döndürdü
}

node *arayaEkle(node *r, int adet, char *kelime) {  //yeni okunan kelimenin adet deðeri linked listin ilk elemanýnýn
    //deðerinden küçük, son elemanýn deðerinden büyükse
    node *iter = r;              //node tipinde iter adýnda deðiþken oluþturdu ve r deðerini ona atadý

    while (iter->next != NULL && iter->next->adet > adet) {     //eklenen kelimenin adedi linked listteki elemanlarýn
        iter = iter->next;                  //adedinden küçük olana kadar ilerledi
    }
    while (iter->next != NULL && iter->next->adet == adet) {    //kaldýðý yerden eþit olduðu sürece ilerlemeye
        iter = iter->next;          //devam etti, bu sayede ayný adet sayýsýna eþit olanlar arasýnda sonuncu sýraya ilerledi
    }

    node *temp = (node *) malloc(sizeof(node));     //temp adýnda yeni kutu oluþturuldu
    temp->next = iter->next;        //araya girmek için baðlantýlar kuruldu
    iter->next = temp;
    temp->adet = adet;              //bilgileri atandý
    temp->kelime = kelime;
    return r;                       //r deðeri döndürüldü
}

node *sonaEkle(node *r, int adet, char *kelime) {   //en küçük deðerden küçük veya eþitse
    node *iter = r;                 //node tipinde iter adýnda deðiþken oluþturdu ve r deðerini ona atadý

    while (iter->next != NULL) {    //iter in next i NULL olana kadar iter i ilerletti
        iter = iter->next;
    }

    iter->next = (node *) malloc(sizeof(node));     //iter in next ine yeni kutu ekledi
    iter->next->adet = adet;            //deðerleri atandý
    iter->next->kelime = kelime;
    enKucuk = adet;                 //en küçük deðer deðiþti ya da ayný kaldý, bu sayede bu fonksiyonu girildi
    iter->next->next = NULL;        //NULL deðeri elle atandý
    return r;                       //r deðeri döndürüldü
}

node *ekle(node *r, int adet, char *kelime) {       //linked liste eleman ekleyen fonksiyon
    if (r == NULL) {                            //linked list boþsa
        r = (node *) malloc(sizeof(node));      //kutu ekle
        r->next = NULL;                 //NULL deðeri elle atandý
        r->adet = adet;                 //deðerleri atandý
        r->kelime = kelime;
        return r;                       //r deðeri döndürüldü
    }

    if (r->adet < adet) {       //ilk elemandan büyük bir eleman olma durumu
        return basaEkle(r, adet, kelime);
    }

    else if (adet <= enKucuk) {         //en küçük deðerden eþit veya küçükse sona ekleme durumu
        return sonaEkle(r, adet, kelime);
    }

    return arayaEkle(r, adet, kelime);          //hiçbir koþul saðlanmadýysa araya ekleme durumu
}

int main() {
    node *root;         //node dan root adýnda deðiþken üretti

    root = (node *) malloc(sizeof(node));       //root deðiþkeni için bellekten yer ayrýldý

    char *kontrol;
    char *str = malloc(sizeof(char) * 1000);
    FILE *dosya;
    dosya = fopen("C:\\Users\\JAN\\Desktop\\metin.txt", "r");       //dosya okuma modunda açýldý

    if (dosya == 0) {						//dosya açýlmadýysa programý sonlandýr
        printf("Dosya acilamadi.");
        return 0;
    }

    fscanf(dosya, "%[^NULL]", str);     //dosya okundu ve str deðiþkenine atandý
    kontrol = strtok(str, " ");         //txt den ilk kelime alýndý
    root->kelime = kontrol;             //ilk kutuya deðerler atandý
    root->adet = kacTane(kontrol);
    root->next = NULL;                  //NULL deðeri elle atandý
    enKucuk = kacTane(kontrol);
    kontrol = strtok(NULL, " ");        //txt den bir sonraki kelime alýndý

    while (kontrol != NULL) {
        if (!ara(root, kontrol)) {       //eðer linked listte þuan aranan kelime yoksa
            root = ekle(root, kacTane(kontrol), kontrol);   //ekle fonksiyonunu kullanarak linked liste ekle
        }
        kontrol = strtok(NULL, " ");        //txt den bir sonraki kelime alýndý
    }

    fclose(dosya);          //dosyayý kapa
    bastir(root);           //linked listi konsola bastýr
    return 0;
}
