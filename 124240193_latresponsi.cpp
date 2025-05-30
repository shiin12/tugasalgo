#include <iostream>
using namespace std;

struct Lagu
{
    char judul[50];
    char penyanyi[50];
    char album[50];
    Lagu *next;
    Lagu *prev;
};

Lagu *head = nullptr; 
Lagu *tail = nullptr;

struct StackNode
{
    Lagu data;
    StackNode *next;
};

StackNode *undoTop = nullptr; // stack undo 

struct QueueNode
{
    Lagu data;
    QueueNode *next;
};

QueueNode *frontQ = nullptr; 
QueueNode *rearQ = nullptr;

struct TreeNode
{
    Lagu data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *root = nullptr;

void simpanKeFile(const Lagu *l)
{
    FILE *file = fopen("riwayat_lagu.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file.\n";
        return;
    }
    fwrite(l, sizeof(Lagu) - 2 * sizeof(Lagu *), 1, file);
    fclose(file);
}

void tambahLagu()
{
    Lagu *baru = new Lagu;
    cin.ignore();
    cout << "Judul lagu: ";
    cin.getline(baru->judul, 50);
    cout << "Penyanyi: ";
    cin.getline(baru->penyanyi, 50);
    cout << "Album: ";
    cin.getline(baru->album, 50);

    baru->next = nullptr;
    baru->prev = tail;
    if (!head)
        head = tail = baru;
    else
    {
        tail->next = baru;
        tail = baru;
    }

    cout << "Lagu berhasil ditambahkan.\n";
}

void tampilkanLagu()
{
    if (!head)
    {
        cout << "Daftar lagu kosong.\n";
        return;
    }
    cout << "\n=== Daftar Lagu ===\n";
    Lagu *temp = head;
    while (temp)
    {
        cout << "Judul: " << temp->judul << ", Penyanyi: " << temp->penyanyi << ", Album: " << temp->album << endl;
        temp = temp->next;
    }
}

// Push lagu ke stack undo
void pushUndo(Lagu *l)
{
    StackNode *baru = new StackNode;
    baru->data = *l;
    baru->next = undoTop;
    undoTop = baru;
}

// Pop lagu dari stack undo dan masukkan kembali ke linked list
void undoHapus()
{
    if (!undoTop)
    {
        cout << "Tidak ada lagu untuk undo.\n";
        return;
    }
    StackNode *temp = undoTop;
    Lagu *baru = new Lagu(temp->data);

    baru->next = nullptr;
    baru->prev = tail;
    if (!head)
        head = tail = baru;
    else
    {
        tail->next = baru;
        tail = baru;
    }

    undoTop = undoTop->next;
    delete temp;
    cout << "Undo hapus lagu berhasil.\n";
}

void hapusLagu()
{
    if (!head)
    {
        cout << "Daftar lagu kosong.\n";
        return;
    }
    char judulHapus[50];
    cin.ignore();
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.getline(judulHapus, 50);

    Lagu *temp = head;
    while (temp)
    {
        bool cocok = true;
        for (int i = 0; i < 50; i++)
        {
            if (judulHapus[i] != temp->judul[i])
            {
                cocok = false;
                break;
            }
            if (judulHapus[i] == '\0' && temp->judul[i] == '\0')
                break;
        }
        if (cocok)
        {
            // Push lagu ke undo stack sebelum dihapus
            pushUndo(temp);

            if (temp->prev)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next)
                temp->next->prev = temp->prev;
            else
                tail = temp->prev;

            delete temp;
            cout << "Lagu berhasil dihapus dan bisa diundo.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Lagu tidak ditemukan.\n";
}

void tukarNode(Lagu *a, Lagu *b)
{
    if (a == b)
        return;

    if (a->next == b)
    {
        Lagu *prevA = a->prev;
        Lagu *nextB = b->next;

        if (prevA)
            prevA->next = b;
        b->prev = prevA;

        b->next = a;
        a->prev = b;

        a->next = nextB;
        if (nextB)
            nextB->prev = a;
    }
    else if (b->next == a)
    {
        tukarNode(b, a);
    }
    else
    {
        Lagu *prevA = a->prev;
        Lagu *nextA = a->next;
        Lagu *prevB = b->prev;
        Lagu *nextB = b->next;

        if (prevA)
            prevA->next = b;
        if (nextA)
            nextA->prev = b;
        b->prev = prevA;
        b->next = nextA;

        if (prevB)
            prevB->next = a;
        if (nextB)
            nextB->prev = a;
        a->prev = prevB;
        a->next = nextB;
    }

    if (head == a)
        head = b;
    else if (head == b)
        head = a;

    if (tail == a)
        tail = b;
    else if (tail == b)
        tail = a;
}

void urutkanJudul()
{
    if (!head || !head->next)
        return;

    bool swapped;
    do
    {
        swapped = false;
        Lagu *curr = head;
        while (curr && curr->next)
        {
            int cmp = 0;
            for (int i = 0; i < 50; i++)
            {
                if (curr->judul[i] != curr->next->judul[i])
                {
                    cmp = (curr->judul[i] < curr->next->judul[i]) ? -1 : 1;
                    break;
                }
                if (curr->judul[i] == '\0')
                    break;
            }

            if (cmp > 0)
            {
                tukarNode(curr, curr->next);
                swapped = true;
            }
            else
            {
                curr = curr->next;
            }
        }
    } while (swapped);

    cout << "Lagu berhasil diurutkan berdasarkan judul.\n";
}

void tambahQueue()
{
    Lagu lagu;
    cin.ignore();
    cout << "Judul lagu antrian: ";
    cin.getline(lagu.judul, 50);
    cout << "Penyanyi: ";
    cin.getline(lagu.penyanyi, 50);
    cout << "Album: ";
    cin.getline(lagu.album, 50);

    QueueNode *baru = new QueueNode;
    baru->data = lagu;
    baru->next = nullptr;

    if (!frontQ)
        frontQ = rearQ = baru;
    else
    {
        rearQ->next = baru;
        rearQ = baru;
    }

    cout << "Lagu berhasil ditambahkan ke antrian putar.\n";
}

void putarLagu()
{
    if (!frontQ)
    {
        cout << "Antrian putar kosong.\n";
        return;
    }
    QueueNode *temp = frontQ;
    cout << "\nMemutar lagu:\n";
    cout << "Judul: " << temp->data.judul << ", Penyanyi: " << temp->data.penyanyi << ", Album: " << temp->data.album << endl;

    simpanKeFile(&temp->data);

    frontQ = frontQ->next;
    if (!frontQ)
        rearQ = nullptr;

    delete temp;
}

TreeNode *buatNodeTree(const Lagu &lagu)
{
    TreeNode *node = new TreeNode;
    node->data = lagu;
    node->left = node->right = nullptr;
    return node;
}

TreeNode *sisipTree(TreeNode *root, const Lagu &lagu)
{
    if (!root)
        return buatNodeTree(lagu);

    int cmp = 0;
    for (int i = 0; i < 50; i++)
    {
        if (lagu.judul[i] != root->data.judul[i])
        {
            cmp = (lagu.judul[i] < root->data.judul[i]) ? -1 : 1;
            break;
        }
        if (lagu.judul[i] == '\0')
            break;
    }

    if (cmp < 0)
        root->left = sisipTree(root->left, lagu);
    else if (cmp > 0)
        root->right = sisipTree(root->right, lagu);

    return root;
}

TreeNode *cariTree(TreeNode *root, const char *judul)
{
    if (!root)
        return nullptr;

    int cmp = 0;
    for (int i = 0; i < 50; i++)
    {
        if (judul[i] != root->data.judul[i])
        {
            cmp = (judul[i] < root->data.judul[i]) ? -1 : 1;
            break;
        }
        if (judul[i] == '\0')
            break;
    }

    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return cariTree(root->left, judul);
    else
        return cariTree(root->right, judul);
}

void tambahTree()
{
    if (!head)
    {
        cout << "Daftar lagu kosong.\n";
        return;
    }
    root = nullptr;
    Lagu *temp = head;
    while (temp)
    {
        root = sisipTree(root, *temp);
        temp = temp->next;
    }
    cout << "Pencarian Cepat sudah dibuat.\n";
}

void cariLaguTree()
{
    if (!root)
    {
        cout << "Pencarian Cepat Kosong.\n";
        return;
    }
    char judulCari[50];
    cin.ignore();
    cout << "Masukkan judul lagu yang dicari: ";
    cin.getline(judulCari, 50);

    TreeNode *hasil = cariTree(root, judulCari);
    if (hasil)
    {
        cout << "Lagu ditemukan:\n";
        cout << "Judul: " << hasil->data.judul << ", Penyanyi: " << hasil->data.penyanyi << ", Album: " << hasil->data.album << endl;
    }
    else
    {
        cout << "Lagu tidak ditemukan di pohon.\n";
    }
}

int main()
{
    int pilihan;
    do
    {
        cout << "\n=== Spotify KW 100 ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Semua Lagu\n";
        cout << "3. Hapus Lagu\n";
        cout << "4. Undo Hapus Lagu\n";
        cout << "5. Urutkan Lagu berdasarkan Judul\n";
        cout << "6. Tambah Lagu ke Antrian Putar\n";
        cout << "7. Putar Lagu Berikutnya\n";
        cout << "8. Simpan Lagu ke Pencarian Cepat\n";
        cout << "9. Cari Lagu di Pencarian Cepat\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahLagu();
            break;
        case 2:
            tampilkanLagu();
            break;
        case 3:
            hapusLagu();
            break;
        case 4:
            undoHapus();
            break;
        case 5:
            urutkanJudul();
            break;
        case 6:
            tambahQueue();
            break;
        case 7:
            putarLagu();
            break;
        case 8:
            tambahTree();
            break;
        case 9:
            cariLaguTree();
            break;
        case 0:
            cout << "Terima kasih sudah menggunakan program ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}