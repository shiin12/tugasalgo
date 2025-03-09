#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Film
{
    string judul;
    string kode;
    double rating;
};

void tampilkanFilm(Film films[], int n)
{
    cout << setfill('=') << setw(40) << "=" << endl;
    cout << "Judul            Kode    Rating\n";
    cout << setfill('=') << setw(40) << "=" << endl;
    for (Film *ptr = films; ptr < films + n; ptr++)
    {
        cout << ptr->judul << "\t\t" << ptr->kode << "\t" << ptr->rating << endl;
    }
    cout << setfill('=') << setw(40) << "=" << endl;
}

int cariFilmByKode(Film films[], int n, string kode)
{
    for (int i = 0; i < n; i++)
    {
        if (films[i].kode == kode)
        {
            return i;
        }
    }
    return -1;
}

int binarySearchByJudul(Film films[], int left, int right, string judul)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (films[mid].judul == judul)
            return mid;
        if (films[mid].judul < judul)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void quickSort(Film films[], int low, int high)
{
    if (low < high)
    {
        double pivot = films[high].rating;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (films[j].rating < pivot)
            {
                i++;
                swap(films[i], films[j]);
            }
        }
        swap(films[i + 1], films[high]);
        int pi = i + 1;

        quickSort(films, low, pi - 1);
        quickSort(films, pi + 1, high);
    }
}

void bubbleSort(Film films[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (films[j].rating < films[j + 1].rating)
            {
                swap(films[j], films[j + 1]);
            }
        }
    }
}

void sortByJudul(Film films[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (films[j].judul > films[j + 1].judul)
            {
                swap(films[j], films[j + 1]);
            }
        }
    }
}

int main()
{
    system("cls");
    Film films[5] = {
        {"Avengers", "F001", 8.50},
        {"Titanic", "F002", 9.00},
        {"Inception", "F003", 8.80},
        {"Interstellar", "F004", 9.20},
        {"Joker", "F005", 8.70}};

    int pilihan;
    do
    {
        cout << setfill('=') << setw(40) << "=" << endl;
        cout << setfill(' ') << setw(25) << "Bioskop Double A" << " " << endl;
        cout << setfill('=') << setw(40) << "=" << endl;
        cout << "1. Tampilkan Film\n";
        cout << "2. Cari film berdasarkan Kode\n";
        cout << "3. Cari film berdasarkan Judul\n";
        cout << "4. Urutkan film berdasarkan Rating (Asc)\n";
        cout << "5. Urutkan film berdasarkan Rating (Desc)\n";
        cout << "6. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        system("cls");

        if (pilihan == 1)
        {
            tampilkanFilm(films, 5);
        }
        else if (pilihan == 2)
        {
            string kode;
            cout << "Masukkan Kode Film: ";
            cin >> kode;
            int idx = cariFilmByKode(films, 5, kode);
            if (idx != -1)
                cout << "Film ditemukan: " << films[idx].judul << " dengan Rating: " << films[idx].rating << endl;
            else
                cout << "Film tidak ditemukan.\n";
        }
        else if (pilihan == 3)
        {
            sortByJudul(films, 5);
            string judul;
            cout << "Masukkan Judul Film: ";
            cin.ignore();
            getline(cin, judul);
            int index = binarySearchByJudul(films, 0, 4, judul);
            if (index != -1)
                cout << "Film ditemukan: " << films[index].judul << " dengan Rating: " << films[index].rating << endl;
            else
                cout << "Film tidak ditemukan.\n";
        }
        else if (pilihan == 4)
        {
            quickSort(films, 0, 4);
            cout << "Film telah diurutkan berdasarkan Rating (Asc).\n";
            tampilkanFilm(films, 5);
        }
        else if (pilihan == 5)
        {
            bubbleSort(films, 5);
            cout << "Film telah diurutkan berdasarkan Rating (Desc).\n";
            tampilkanFilm(films, 5);
        }
        else if (pilihan == 6)
        {
            system("cls");
            cout << "Keluar dari program.\n";
        }
        else
        {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}