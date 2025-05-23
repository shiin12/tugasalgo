#include <iostream>

using namespace std;

struct Pegawai
{
    int id;
    char nama[50];
    int gaji;
};

void tambahPegawai()
{
    FILE *file = fopen("pegawai.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    int jumlah;
    cout << "Masukkan jumlah data: ";
    cin >> jumlah;
    cin.ignore();

    Pegawai p;
    for (int i = 0; i < jumlah; i++)
    {
        cout << "Masukkan ID: ";
        cin >> p.id;
        cin.ignore();
        cout << "Masukkan Nama: ";
        cin.getline(p.nama, 50);
        cout << "Masukkan Gaji: ";
        cin >> p.gaji;
        cin.ignore();

        fwrite(&p, sizeof(Pegawai), 1, file);
    }

    fclose(file);
    cout << jumlah << " data berhasil ditambahkan.\n";
}

void lihatPegawai()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Tidak ada data pegawai." << endl;
        return;
    }

    Pegawai p;
    cout << "=== Daftar Pegawai ===" << endl;
    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        cout << "------------------------------\n";
        cout << "ID: " << p.id << "\nNama: " << p.nama << "\nGaji: Rp. " << p.gaji << endl;
    }

    fclose(file);
}

void cariPegawai()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Tidak ada data pegawai." << endl;
        return;
    }

    int cariID;
    bool ditemukan = false;
    cout << "Masukkan ID untuk dicari: ";
    cin >> cariID;

    Pegawai p;
    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        if (p.id == cariID)
        {
            cout << "Pegawai ditemukan!\n";
            cout << "------------------------------\n";
            cout << "ID: " << p.id << "\nNama: " << p.nama << "\nGaji: Rp. " << p.gaji << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << cariID << " tidak ditemukan!" << endl;
    }

    fclose(file);
}

void perbaruiGaji()
{
    FILE *file = fopen("pegawai.dat", "rb+");
    if (!file)
    {
        cout << "Tidak ada data pegawai." << endl;
        return;
    }

    int cariID;
    cout << "Masukkan ID pegawai untuk diperbarui: ";
    cin >> cariID;

    Pegawai p;
    bool ditemukan = false;
    long pos;

    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        if (p.id == cariID)
        {
            cout << "Pegawai ditemukan!\n";
            cout << "------------------------------\n";
            cout << "ID: " << p.id << "\nNama: " << p.nama << "\nGaji Lama: Rp. " << p.gaji << endl;

            cout << "Masukkan gaji baru: ";
            cin >> p.gaji;

            fseek(file, sizeof(Pegawai), SEEK_CUR);
            fwrite(&p, sizeof(Pegawai), 1, file);
            cout << "Gaji berhasil diperbarui.\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << cariID << " tidak ditemukan!" << endl;
    }

    fclose(file);
}

int main()
{
    int pilihan;
    do
    {
        cout << "\n=== Sistem Informasi Kepegawaian ===\n";
        cout << "1. Tambah Data Pegawai\n";
        cout << "2. Lihat Daftar Pegawai\n";
        cout << "3. Cari Pegawai berdasarkan ID\n";
        cout << "4. Perbarui Gaji Pegawai\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambahPegawai();
            break;
        case 2:
            lihatPegawai();
            break;
        case 3:
            cariPegawai();
            break;
        case 4:
            perbaruiGaji();
            break;
        case 0:
            cout << "Keluar dari program...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}