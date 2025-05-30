#include <iostream>
#include <string>
using namespace std;

struct Lagu
{
    char judul[50];
    char penyanyi[50];
    char album[50];
};

struct NodeStack
{
    Lagu data;
    NodeStack *next;
};
NodeStack *atas = nullptr;

struct NodeQueue
{
    Lagu data;
    NodeQueue *next;
};
struct Queue
{
    NodeQueue *depan;
    NodeQueue *belakang;
};
Queue daftarPutar = {nullptr, nullptr};

struct Simpul
{
    Lagu data;
    Simpul *kiri;
    Simpul *kanan;
};
Simpul *akar = nullptr;

struct NodeUndo
{
    Lagu data;
    NodeUndo *next;
};
NodeUndo *undoTop = nullptr;

void masukLagu()
{
    Lagu lagu;
    cin.ignore();
    cout << "Judul: ";
    cin.getline(lagu.judul, 50);
    cout << "Penyanyi: ";
    cin.getline(lagu.penyanyi, 50);
    cout << "Album: ";
    cin.getline(lagu.album, 50);

    NodeStack *baru = new NodeStack{lagu, atas};
    atas = baru;
    cout << "Lagu berhasil ditambahkan.\n";
}

void lihatLagu()
{
    if (!atas)
    {
        cout << "Daftar lagu kosong.\n";
        return;
    }
    cout << "\n--- Daftar Lagu ---\n";
    NodeStack *temp = atas;
    while (temp)
    {
        cout << "Judul: " << temp->data.judul << ", Penyanyi: " << temp->data.penyanyi << ", Album: " << temp->data.album << endl;
        temp = temp->next;
    }
}

void masukkanKePutar()
{
    if (!atas)
    {
        cout << "Tidak ada lagu untuk dimasukkan.\n";
        return;
    }
    Lagu lagu = atas->data;
    NodeQueue *baru = new NodeQueue{lagu, nullptr};
    if (!daftarPutar.depan)
        daftarPutar.depan = daftarPutar.belakang = baru;
    else
    {
        daftarPutar.belakang->next = baru;
        daftarPutar.belakang = baru;
    }
    cout << "Lagu dimasukkan ke daftar putar.\n";
}

void putarLagu()
{
    if (!daftarPutar.depan)
    {
        cout << "Daftar putar kosong.\n";
        return;
    }
    NodeQueue *temp = daftarPutar.depan;
    cout << "\nMemutar: Judul: " << temp->data.judul << ", Penyanyi: " << temp->data.penyanyi << ", Album: " << temp->data.album << endl;
    daftarPutar.depan = temp->next;
    if (!daftarPutar.depan)
        daftarPutar.belakang = nullptr;
    delete temp;
}

Simpul *buatSimpul(const Lagu &lagu)
{
    return new Simpul{lagu, nullptr, nullptr};
}

Simpul *susunLagu(Simpul *root, const Lagu &lagu)
{
    if (!root)
        return buatSimpul(lagu);
    string judulBaru = lagu.judul;
    string judulRoot = root->data.judul;
    if (judulBaru < judulRoot)
        root->kiri = susunLagu(root->kiri, lagu);
    else
        root->kanan = susunLagu(root->kanan, lagu);
    return root;
}

void mulaiSusun()
{
    akar = nullptr;
    NodeStack *temp = atas;
    while (temp)
    {
        akar = susunLagu(akar, temp->data);
        temp = temp->next;
    }
    cout << "Lagu sudah disusun berdasarkan judul.\n";
}

Simpul *cariJudul(Simpul *root, const string &judul)
{
    if (!root)
        return nullptr;
    string judulRoot = root->data.judul;
    if (judul == judulRoot)
        return root;
    else if (judul < judulRoot)
        return cariJudul(root->kiri, judul);
    else
        return cariJudul(root->kanan, judul);
}

void cariLagu()
{
    if (!akar)
    {
        cout << "Belum disusun, nggak bisa cari lagu.\n";
        return;
    }
    cin.ignore();
    char input[50];
    cout << "Masukkan judul lagu yang dicari: ";
    cin.getline(input, 50);
    string cari = input;

    Simpul *hasil = cariJudul(akar, cari);
    if (hasil)
    {
        cout << "\nKetemu: Judul: " << hasil->data.judul
             << ", Penyanyi: " << hasil->data.penyanyi
             << ", Album: " << hasil->data.album << endl;
    }
    else
    {
        cout << "Lagu nggak ketemu.\n";
    }
}

void hapusTeratas()
{
    if (!atas)
    {
        cout << "Daftar kosong, tidak bisa hapus.\n";
        return;
    }
    NodeUndo *undoBaru = new NodeUndo{atas->data, undoTop};
    undoTop = undoBaru;

    NodeStack *hapus = atas;
    atas = atas->next;
    delete hapus;
    cout << "Lagu teratas berhasil dihapus.\n";
}

void undoHapus()
{
    if (!undoTop)
    {
        cout << "Tidak ada yang bisa di-undo.\n";
        return;
    }
    NodeStack *baru = new NodeStack{undoTop->data, atas};
    atas = baru;

    NodeUndo *hapus = undoTop;
    undoTop = undoTop->next;
    delete hapus;
    cout << "Undo berhasil, lagu dikembalikan ke atas.\n";
}

int main()
{
    int pilih;
    do
    {
        cout << "\n===== SPOTIFY KW 100 =====\n";
        cout << "1. Masukkan Lagu Baru\n";
        cout << "2. Lihat Daftar Lagu\n";
        cout << "3. Masukkan ke Daftar Putar\n";
        cout << "4. Putar Lagu\n";
        cout << "5. Susun Lagu\n";
        cout << "6. Cari Lagu\n";
        cout << "7. Hapus Lagu Teratas\n";
        cout << "8. Batalkan Hapus Lagu\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;
        switch (pilih)
        {
        case 1:
            masukLagu();
            break;
        case 2:
            lihatLagu();
            break;
        case 3:
            masukkanKePutar();
            break;
        case 4:
            putarLagu();
            break;
        case 5:
            mulaiSusun();
            break;
        case 6:
            cariLagu();
            break;
        case 7:
            hapusTeratas();
            break;
        case 8:
            undoHapus();
            break;
        case 0:
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan nggak valid.\n";
        }
    } while (pilih != 0);
    return 0;
}