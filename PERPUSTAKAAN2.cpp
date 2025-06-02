#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct Book
{
    string Judul;
    string namaPenulis;
    string Genre;
    string tahunTerbit;
    string Penerbit;
    string Ketersediaan;
};

Book dataBuku[100];
int jumlahBuku = 0;

struct TanggalPinjam
{
    int hariP, bulanP, tahunP;
};

struct TanggalKembali
{
    int hariK, bulanK, tahunK;
};

struct DataPeminjam
{
    string nama;
    string pinjamBuku;
    TanggalPinjam tPinjam;
    TanggalKembali tKembali;
};

DataPeminjam dataPeminjam[100];

void loadDataBuku();
void saveDataBuku();
void loadDataPeminjam(int &jumlahPeminjam);
void saveDataPeminjam(int jumlahPeminjam);
void menuDataBuku();
void menuDataPeminjam(int *jumlahPeminjam);
void menuEditData();
int hitungBuku(int i, int jumlahBuku);
int cariBuku(string namaBuku, int &indeks);
bool cekSedia(int indeks);

int main()
{
    loadDataBuku();
    int jumlahPeminjam = 0;
    loadDataPeminjam(jumlahPeminjam);
    bool program = false;
    int pil;
    while (!program)
    {
        system("cls");
        cout << "Perpustakaan\n";
        cout << "1. Daftar Buku\n";
        cout << "2. Menu Pinjam Buku\n";
        cout << "3. Edit Data \n";
        cout << "4. Keluar\n";
        cout << "Pilih      : ";
        cin >> pil;

        switch (pil)
        {
        case 1:
            menuDataBuku();
            break;
        case 2:
            menuDataPeminjam(&jumlahPeminjam);
            break;
        case 3:
            menuEditData();
            break;
        case 4:
            saveDataBuku();
            saveDataPeminjam(jumlahPeminjam);
            program = true;
            break;
        default:
            cout << "Mohon masukkan pilihan yang valid!\n";
            system("pause");
            break;
        }
    }
    return 0;
}

int hitungBuku(int i, int jumlahBuku)
{
    if (i >= jumlahBuku)
    {
        return 0;
    }
    else
    {
        return 1 + hitungBuku(i + 1, jumlahBuku);
    }
}

int cariBuku(string namaBuku, int &indeks)
{
    if (indeks >= jumlahBuku)
    {
        indeks = -1;
        return indeks;
    }
    if (namaBuku == dataBuku[indeks].Judul)
    {
        return indeks;
    }
    else
    {
        indeks++;
        return cariBuku(namaBuku, indeks);
    }
}

bool cekSedia(int indeks)
{
    bool tersedia = true;
    if (indeks < 0)
        return false;
    string judulPinjam = dataPeminjam[indeks].pinjamBuku;
    for (int i = 0; i < jumlahBuku; i++)
    {
        if (dataBuku[i].Judul == judulPinjam)
        {
            if (dataBuku[i].Ketersediaan == "Tidak Tersedia")
            {
                tersedia = false;
                break;
            }
        }
    }
    return tersedia;
}

void SortingAsc(int size)
{
    if (size > 1)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (dataBuku[j].Judul > dataBuku[j + 1].Judul)
                {
                    swap(dataBuku[j], dataBuku[j + 1]);
                }
            }
        }
    }
}


void loadDataBuku()
{
    ifstream file("dataBuku.txt");
    jumlahBuku = 0;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find("Judul: ") == 0)
            dataBuku[jumlahBuku].Judul = line.substr(7);
            getline(file, line);
            dataBuku[jumlahBuku].namaPenulis = line.substr(9);
            getline(file, line);
            dataBuku[jumlahBuku].Genre = line.substr(7);
            getline(file, line);
            dataBuku[jumlahBuku].tahunTerbit = line.substr(14);
            getline(file, line);
            dataBuku[jumlahBuku].Penerbit = line.substr(10);
            getline(file, line);
            dataBuku[jumlahBuku].Ketersediaan = line.substr(14);
            getline(file, line);
            jumlahBuku++;
            if (jumlahBuku >= 100)
                break;
        }
        file.close();
    }
    else
    {
        cout << "TIDAK DAPAT MEMBUKA FILE DATA BUKU\n";
    }
}

void saveDataBuku()
{
    ofstream file("dataBuku.txt");
    if (file.is_open())
    {
        for (int i = 0; i < jumlahBuku; i++)
        {
            file << "Judul: " << dataBuku[i].Judul << endl;
            file << "Penulis: " << dataBuku[i].namaPenulis << endl;
            file << "Genre: " << dataBuku[i].Genre << endl;
            file << "Tahun Terbit: " << dataBuku[i].tahunTerbit << endl;
            file << "Penerbit: " << dataBuku[i].Penerbit << endl;
            file << "Ketersediaan: " << dataBuku[i].Ketersediaan << endl;
            file << "--------------------------------" << endl;
        }
        file.close();
    }
    else
    {
        cout << "TIDAK DAPAT MEMUKA FILE DATA BUKU\n";
    }
}


void loadDataPeminjam(int &jumlahPeminjam)
{
    ifstream file("dataPeminjam.txt");
    jumlahPeminjam = 0;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find("Nama: ") == 0)
                dataPeminjam[jumlahPeminjam].nama = line.substr(6);
            getline(file, line);

            dataPeminjam[jumlahPeminjam].pinjamBuku = line.substr(12);
            getline(file, line);

            sscanf(line.c_str(), "Tanggal Pinjam: %d-%d-%d",
                   &dataPeminjam[jumlahPeminjam].tPinjam.hariP,
                   &dataPeminjam[jumlahPeminjam].tPinjam.bulanP,
                   &dataPeminjam[jumlahPeminjam].tPinjam.tahunP);

            getline(file, line);
           
            jumlahPeminjam++;
            if (jumlahPeminjam >= 100)
                break;
        }
        file.close();
    }
    else
    {
        cout << "TIDAK DAPAT MEMBUKA FILE DATA PEMINJAM\n";
    }
}

void saveDataPeminjam(int jumlahPeminjam)
{
    ofstream file("dataPeminjam.txt");
    if (file.is_open())
    {
        for (int i = 0; i < jumlahPeminjam; i++)
        {
            file << "Nama: " << dataPeminjam[i].nama << endl;
            file << "Judul Buku: " << dataPeminjam[i].pinjamBuku << endl;
            file << "Tanggal Pinjam: "
                 << dataPeminjam[i].tPinjam.hariP << "-"
                 << dataPeminjam[i].tPinjam.bulanP << "-"
                 << dataPeminjam[i].tPinjam.tahunP << endl;
            file << "--------------------------------" << endl;
        }
        file.close();
    }
    else
    {
        cout << "TIDAK DAPAT MEMBUKA FILE DATA PEMINJAM\n";
    }
}

void menuDataBuku()
{
    int pil;
    bool keluar = false;
    int indeks = 0;
    string namaBuku;
    while (!keluar)
    {
        system("cls");
        cout << "Jumlah buku yang ada  : " << hitungBuku(0, jumlahBuku) << endl;
        cout << "1. Tampilkan semua\n";
        cout << "2. Cari buku tertentu\n";
        cout << "3. Kembali\n";
        cout << "Pilih      : ";
        cin >> pil;
        switch (pil)
        {
        case 1:
            system("cls");
            SortingAsc(jumlahBuku);
            cout << setw(60) << setfill('-') << " Perpustakaan " << setw(55) << setfill('-') << "\n";
            for (int i = 0; i < jumlahBuku; i++)
            {
                cout << setw(2) << setfill(' ') << i + 1 << ". " << dataBuku[i].Judul << setw(108 - int(dataBuku[i].Judul.length())) << dataBuku[i].Ketersediaan << endl;
            }
            cout << setw(116) << setfill('-') << "\n\n";
            system("pause");
            break;
        case 2:
            system("cls");
            cin.ignore();
            cout << "Masukkan nama buku yang ingin ditampilkan  : ";
            getline(cin, namaBuku); 
            indeks = 0;
            indeks = cariBuku(namaBuku, indeks);
            if (indeks != -1)
            {
                cout << "Buku berhasil ditemukan!\n";
                cout << "Judul Buku         : " << dataBuku[indeks].Judul << endl;
                cout << "Nama Penulis       : " << dataBuku[indeks].namaPenulis << endl;
                cout << "Genre Buku         : " << dataBuku[indeks].Genre << endl;
                cout << "Tahun Terbit       : " << dataBuku[indeks].tahunTerbit << endl;
                cout << "Penerbit           : " << dataBuku[indeks].Penerbit << endl;
                cout << "Keterangan         : " << dataBuku[indeks].Ketersediaan;
                if (dataBuku[indeks].Ketersediaan == "Tersedia")
                    cout << " untuk dipinjam" << endl;
                cout << endl;
            }
            else
            {
                cout << "Buku dengan judul " << namaBuku << " tidak ditemukan.\n\n";
            }
            system("pause");
            break;
        case 3:
            keluar = true;
            break;
        default:
            cout << "Mohon masukkan pilihan yang valid!\n";
            system("pause");
            break;
        }
    }
}

void menuDataPeminjam(int *jumlahPeminjam)
{
    int pil;
    bool keluar = false;
    while (!keluar)
    {
        system("cls");
        cout << "Jumlah buku yang ada  : " << hitungBuku(0, jumlahBuku) << endl;
        cout << "1. Tambahkan Data Peminjam\n";
        cout << "2. Pengembalian Buku\n";
        cout << "3. Tampilkan Data Peminjam\n";
        cout << "4. Kembali\n";
        cout << "Pilih      : ";
        cin >> pil;

        switch (pil)
        {
        case 1:
        {
            system("cls");
            cin.ignore();
            cout << setw(60) << setfill('-') << " Perpustakaan " << setw(55) << setfill('-') << "\n";
            cout << "Masukkan Nama Peminjam                : ";
            getline(cin, dataPeminjam[*jumlahPeminjam].nama);
            bool ketemu = false;
            bool sama = false;
            int x = -1;
            while (!ketemu)
            {
                cout << "Masukkan Judul buku yang dipinjam     : ";
                getline(cin, dataPeminjam[*jumlahPeminjam].pinjamBuku);

                for (int i = 0; i < jumlahBuku; i++)
                {
                    if (dataBuku[i].Judul == dataPeminjam[*jumlahPeminjam].pinjamBuku)
                    {
                        sama = true;
                        x = i;
                        break;
                    }
                }

                if (sama && cekSedia(*jumlahPeminjam))
                {
                    cout << "Tanggal Meminjam (DD/MM/YYYY)\n";
                    cout << "DD = ";
                    cin >> dataPeminjam[*jumlahPeminjam].tPinjam.hariP;
                    cout << "MM = ";
                    cin >> dataPeminjam[*jumlahPeminjam].tPinjam.bulanP;
                    cout << "YYYY = ";
                    cin >> dataPeminjam[*jumlahPeminjam].tPinjam.tahunP;
                    cout << "Data berhasil ditambahkan!\n";
                    ketemu = true;
                    dataBuku[x].Ketersediaan = "Tidak Tersedia";
                    (*jumlahPeminjam)++;
                    saveDataPeminjam(*jumlahPeminjam);
                    saveDataBuku();
                }
                else if (sama && !cekSedia(*jumlahPeminjam))
                {
                    cout << "Buku Berjudul " << dataPeminjam[*jumlahPeminjam].pinjamBuku << " Sudah Dipinjam!\nHarap meminjam buku lain...\n";
                }
                else
                {
                    cout << "Mohon masukkan judul buku yang valid!\n";
                }
            }
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            cin.ignore();
            cout << "Pengembalian Buku\n";
            cout << "Masukkan nama peminjam: ";
            string namaPeminjam;
            getline(cin, namaPeminjam);
            bool bukuDikembalikan = false;
            bool validasiNama = false;
            int x = -1;
            char konfirm;
            for (int i = 0; i < *jumlahPeminjam; i++)
            {
                if (dataPeminjam[i].nama == namaPeminjam)
                {
                    validasiNama = true;
                    cout << "Apakah anda ingin mengembalikan buku " << dataPeminjam[i].pinjamBuku << " (y/n) ? : ";
                    cin >> konfirm;
                    konfirm = tolower(konfirm);
                    if (konfirm == 'y')
                    {
                        cout << "Tanggal Meminjam (" << dataPeminjam[i].tPinjam.hariP << "/"
                             << dataPeminjam[i].tPinjam.bulanP << "/" << dataPeminjam[i].tPinjam.tahunP << ")\n";
                        cout << "Tanggal Kembali Buku (DD/MM/YYYY)\n";
                        cout << "DD = ";
                        cin >> dataPeminjam[i].tKembali.hariK;
                        cout << "MM = ";
                        cin >> dataPeminjam[i].tKembali.bulanK;
                        cout << "YYYY = ";
                        cin >> dataPeminjam[i].tKembali.tahunK;
                        bool tanggalValid =
                            (dataPeminjam[i].tKembali.tahunK > dataPeminjam[i].tPinjam.tahunP) ||
                            (dataPeminjam[i].tKembali.tahunK == dataPeminjam[i].tPinjam.tahunP && dataPeminjam[i].tKembali.bulanK > dataPeminjam[i].tPinjam.bulanP) ||
                            (dataPeminjam[i].tKembali.tahunK == dataPeminjam[i].tPinjam.tahunP && dataPeminjam[i].tKembali.bulanK == dataPeminjam[i].tPinjam.bulanP && dataPeminjam[i].tKembali.hariK >= dataPeminjam[i].tPinjam.hariP);
                        if (tanggalValid)
                        {
                            int tglPinjam = dataPeminjam[i].tPinjam.tahunP * 365 + dataPeminjam[i].tPinjam.bulanP * 30 + dataPeminjam[i].tPinjam.hariP;
                            int tglKembali = dataPeminjam[i].tKembali.tahunK * 365 + dataPeminjam[i].tKembali.bulanK * 30 + dataPeminjam[i].tKembali.hariK;
                            int Selisih = tglKembali - tglPinjam;

                            if (Selisih > 7)
                            {
                                cout << "Anda dikenakan denda karena telat " << Selisih - 7 << " hari\n";
                                cout << "Denda sebesar (hari * 1000)  = Rp." << (Selisih - 7) * 1000 << endl;
                            }
                            for (int j = 0; j < jumlahBuku; j++)
                            {
                                if (dataBuku[j].Judul == dataPeminjam[i].pinjamBuku)
                                {
                                    dataBuku[j].Ketersediaan = "Tersedia";
                                    bukuDikembalikan = true;
                                    x = i;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            cout << "Maaf mungkin ada kesalahan dalam memasukkan tanggal\n";
                        }
                        break;
                    }
                    else if (konfirm == 'n')
                    {
                        cout << "Pengembalian buku dibatalkan...\n";
                        break;
                    }
                }
            }
            if (!validasiNama)
            {
                cout << "Nama peminjam tidak ditemukan.\n";
            }
            if (bukuDikembalikan)
            {
                cout << "Buku '" << dataPeminjam[x].pinjamBuku << "' telah dikembalikan.\n";
                dataPeminjam[x] = dataPeminjam[*jumlahPeminjam - 1];
                (*jumlahPeminjam)--;
                saveDataPeminjam(*jumlahPeminjam);
                saveDataBuku();
            }
            system("pause");
            break;
        }
        case 3:
        {
            system("cls");
            cin.ignore();
            cout << setw(58) << setfill('-') << " Data Peminjam " << setw(53) << setfill('-') << "\n";
            for (int i = 0; i < *jumlahPeminjam; i++)
            {
                cout << endl;
                cout << setw(57) << setfill(' ') << "Nama Peminjam     :  " << dataPeminjam[i].nama << endl;
                cout << setw(57) << setfill(' ') << "Judul Buku        :  " << dataPeminjam[i].pinjamBuku << endl;
                cout << setw(57) << setfill(' ') << "Tanggal Meminjam  :  " << dataPeminjam[i].tPinjam.hariP << "/" << dataPeminjam[i].tPinjam.bulanP << "/" << dataPeminjam[i].tPinjam.tahunP << endl;
            }
            cout << endl;
            cout << setw(112) << setfill('-') << "\n\n";
            system("pause");
            break;
        }
        case 4:
            keluar = true;
            break;
        default:
            cout << "Mohon masukkan pilihan yang valid!\n";
            system("pause");
            break;
        }
    }
}

void menuEditData()
{
    int pil, pil2, bagian;
    bool keluar = false, program = true;
    while (program)
    {
        pil = 0;
        system("cls");
        cout << "Jumlah buku yang ada  : " << hitungBuku(0, jumlahBuku) << endl;
        cout << "1. Mengubah data buku\n";
        cout << "2. Menambah data buku\n";
        cout << "3. Menghapus data buku\n";
        cout << "4. Kembali\n";
        cout << "Pilih      : ";
        cin >> pil2;

        switch (pil2)
        {
        case 1:
        {
            system("cls");
            SortingAsc(jumlahBuku);
            cout << setw(60) << setfill('-') << " Perpustakaan " << setw(55) << setfill('-') << "\n";
            for (int i = 0; i < jumlahBuku; i++)
            {
                cout << setw(2) << setfill(' ') << i + 1 << ". " << dataBuku[i].Judul << setw(108 - int(dataBuku[i].Judul.length())) << dataBuku[i].Ketersediaan << endl;
            }
            cout << setw(116) << setfill('-') << "\n\n";
            cout << "Pilih Buku    (No) : ";
            cin >> pil;
            if (pil > 0 && pil <= jumlahBuku)
            {
                keluar = false;
                while (!keluar)
                {
                    system("cls");
                    int idx = pil - 1;
                    cout << "Judul Buku         : " << dataBuku[idx].Judul << endl;
                    cout << "Nama Penulis       : " << dataBuku[idx].namaPenulis << endl;
                    cout << "Genre Buku         : " << dataBuku[idx].Genre << endl;
                    cout << "Tahun Terbit       : " << dataBuku[idx].tahunTerbit << endl;
                    cout << "Penerbit           : " << dataBuku[idx].Penerbit << endl;
                    cout << "Keterangan         : " << dataBuku[idx].Ketersediaan << endl
                         << endl;
                    cout << "Bagian mana yang ingin anda edit? \n";
                    cout << "1. Judul   2. Nama Penulis     3. Genre    4. Tahun Terbit     5. Penerbit     6. Keterangan   7. Kembali\n";
                    cout << "Pilih  : ";
                    cin >> bagian;
                    cin.ignore();
                    switch (bagian)
                    {
                    case 1:
                        cout << "\nJudul buku yang baru : ";
                        getline(cin, dataBuku[idx].Judul);
                        cout << "Judul buku berhasil diganti menjadi " << dataBuku[idx].Judul << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 2:
                        cout << "\nNama penulis yang baru : ";
                        getline(cin, dataBuku[idx].namaPenulis);
                        cout << "Nama penulis berhasil diganti menjadi " << dataBuku[idx].namaPenulis << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 3:
                        cout << "\nGenre buku yang baru : ";
                        getline(cin, dataBuku[idx].Genre);
                        cout << "Genre buku berhasil diganti menjadi " << dataBuku[idx].Genre << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 4:
                        cout << "\nTahun terbit yang baru : ";
                        getline(cin, dataBuku[idx].tahunTerbit);
                        cout << "Tahun terbit berhasil diganti menjadi " << dataBuku[idx].tahunTerbit << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 5:
                        cout << "\nPenerbit buku yang baru : ";
                        getline(cin, dataBuku[idx].Penerbit);
                        cout << "Penerbit buku berhasil diganti menjadi " << dataBuku[idx].Penerbit << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 6:
                        cout << "\nUbah ketersediaan : ";
                        getline(cin, dataBuku[idx].Ketersediaan);
                        cout << "Ketersediaan buku berhasil diganti menjadi " << dataBuku[idx].Ketersediaan << endl;
                        saveDataBuku();
                        system("pause");
                        break;
                    case 7:
                        keluar = true;
                        break;
                    default:
                        cout << "Pilihan tidak valid!\n";
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                cout << "mohon pilih nomor yang valid!\n";
                system("pause");
            }
            break;
        }
        case 2:
        {
            system("cls");
            int n;
            cout << "Berapa banyak buku yang ingin anda tambahkan? : ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++)
            {
                cout << "Masukkan judul buku    : ";
                getline(cin, dataBuku[jumlahBuku].Judul);
                cout << "Masukkan Nama Penulis  : ";
                getline(cin, dataBuku[jumlahBuku].namaPenulis);
                cout << "Masukkan Genre Buku    : ";
                getline(cin, dataBuku[jumlahBuku].Genre);
                cout << "Masukkan Tahun terbit  : ";
                getline(cin, dataBuku[jumlahBuku].tahunTerbit);
                cout << "Masukkan Penerbit buku : ";
                getline(cin, dataBuku[jumlahBuku].Penerbit);
                dataBuku[jumlahBuku].Ketersediaan = "Tersedia";
                jumlahBuku++;
                cout << endl;
            }
            saveDataBuku();
            break;
        }
        case 3:
        {
            system("cls");
            SortingAsc(jumlahBuku);
            cout << setw(60) << setfill('-') << " Perpustakaan " << setw(55) << setfill('-') << "\n";
            for (int i = 0; i < jumlahBuku; i++)
            {
                cout << setw(2) << setfill(' ') << i + 1 << ". " << dataBuku[i].Judul << setw(108 - int(dataBuku[i].Judul.length())) << dataBuku[i].Ketersediaan << endl;
            }
            cout << setw(116) << setfill('-') << "\n\n";
            cout << "Pilih Buku untuk dihapus    (No) : ";
            cin >> pil;
            if (pil < 1 || pil > jumlahBuku)
                cout << "Pilihan tidak valid!\n";
            else
            {
                for (int i = pil - 1; i < jumlahBuku - 1; i++)
                {
                    dataBuku[i] = dataBuku[i + 1];
                }
                jumlahBuku--;
                cout << "Data berhasil dihapus\n";
                saveDataBuku();
            }
            system("pause");
            break;
        }
        case 4:
            program = false;
            break;
        default:
            cout << "Input tidak valid!\n";
            system("pause");
            break;
        }
    }
}


