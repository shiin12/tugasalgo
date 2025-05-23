#include <iostream>
using namespace std;

struct Pesanan
{
    char nama[50];
    char jenisRoti[50];
    int totalHarga;
    Pesanan *next;
    Pesanan *prev;
};

Pesanan *head = nullptr;
Pesanan *tail = nullptr;

void simpanRiwayat(Pesanan *p)
{
    FILE *file = fopen("riwayat.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file riwayat!\n";
        return;
    }
    fwrite(p, sizeof(Pesanan) - 2 * sizeof(Pesanan *), 1, file);
    fclose(file);
}

void simpanPesanan(Pesanan *p)
{
    FILE *file = fopen("pesanan.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file pesanan!\n";
        return;
    }
    fwrite(p, sizeof(Pesanan) - 2 * sizeof(Pesanan *), 1, file);
    fclose(file);
}

void ambilAntrean()
{
    Pesanan *baru = new Pesanan;
    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
    cin.getline(baru->nama, 50);
    cout << "Jenis roti: ";
    cin.getline(baru->jenisRoti, 50);
    cout << "Total harga: ";
    cin >> baru->totalHarga;

    baru->next = nullptr;
    baru->prev = tail;

    if (!head)
    {
        head = tail = baru;
    }
    else
    {
        tail->next = baru;
        tail = baru;
    }

    simpanPesanan(baru);
    cout << "Pesanan ditambahkan ke antrean dan disimpan ke file.\n";
}

void layaniPembeli()
{
    if (!head)
    {
        cout << "Antrean kosong.\n";
        return;
    }

    Pesanan *dilayani = head;
    cout << "Melayani: " << dilayani->nama << ", Roti: " << dilayani->jenisRoti << ", Harga: " << dilayani->totalHarga << "\n";

    simpanRiwayat(dilayani);

    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;

    delete dilayani;
    cout << "Pesanan telah dilayani dan disimpan ke riwayat.\n";
}

void tampilkanAntrean()
{
    if (!head)
    {
        cout << "Antrean kosong.\n";
        return;
    }

    Pesanan *temp = head;
    cout << "\n--- Daftar Pesanan dalam Antrean ---\n";
    while (temp)
    {
        cout << "Nama: " << temp->nama << ", Roti: " << temp->jenisRoti << ", Harga: " << temp->totalHarga << "\n";
        temp = temp->next;
    }
}

void batalkanPesanan()
{
    if (!tail)
    {
        cout << "Tidak ada pesanan untuk dibatalkan.\n";
        return;
    }

    Pesanan *dibatalkan = tail;
    cout << "Pesanan oleh " << dibatalkan->nama << " dibatalkan.\n";

    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;

    delete dibatalkan;
}

void tampilkanRiwayat()
{
    FILE *file = fopen("riwayat.dat", "rb");
    if (!file)
    {
        cout << "Belum ada riwayat tersimpan.\n";
        return;
    }

    Pesanan temp;
    cout << "\n--- Riwayat Pesanan ---\n";
    while (fread(&temp, sizeof(Pesanan) - 2 * sizeof(Pesanan *), 1, file))
    {
        cout << "Nama: " << temp.nama << ", Roti: " << temp.jenisRoti << ", Harga: " << temp.totalHarga << "\n";
    }
    fclose(file);
}

int main()
{
    int pilihan;
    do
    {
        cout << "\n=== Sistem Antrian Toko Roti 'Manis Lezat' ===\n";
        cout << "1. Ambil Antrean\n";
        cout << "2. Layani Pembeli\n";
        cout << "3. Tampilkan Antrean\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Tampilkan Riwayat Pesanan\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            ambilAntrean();
            break;
        case 2:
            layaniPembeli();
            break;
        case 3:
            tampilkanAntrean();
            break;
        case 4:
            batalkanPesanan();
            break;
        case 5:
            tampilkanRiwayat();
            break;
        case 0:
            cout << "Terima kasih!\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}