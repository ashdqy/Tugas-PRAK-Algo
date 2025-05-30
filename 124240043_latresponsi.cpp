#include <iostream>
#include <string>
using namespace std;

struct Video
{
    string judul;
    int durasi;
    string status;
    Video *prev;
    Video *next;
};

struct Riwayat
{
    string judul;
    Riwayat *next;
};

struct StackNode
{
    string aksi;
    Video *data;
    StackNode *next;
};

Video *head = NULL;
Video *tail = NULL;
Video *playlistHead = NULL;
Video *playlistTail = NULL;
Riwayat *riwayatHead = NULL;

StackNode *undoTop = NULL;

// Stack untuk Undo
void pushUndo(string aksi, Video *data)
{
    StackNode *baru = new StackNode{aksi, data, undoTop};
    undoTop = baru;
}

void popUndo()
{
    if (undoTop)
    {
        StackNode *hapus = undoTop;
        undoTop = undoTop->next;
        delete hapus;
    }
}

// Fungsi Tambah Video
void tambahVideo(string judul, int durasi)
{

    Video *cek = head;
    while (cek)
    {
        if (cek->judul == judul)
        {
            cout << "Judul sudah ada!" << endl;
            return;
        }
        cek = cek->next;
    }
    Video *baru = new Video{judul, durasi, "tersedia", NULL, NULL};
    if (!head)
        head = tail = baru;
    else
    {
        Video *bantu = head;
        while (bantu && bantu->judul < judul)
            bantu = bantu->next;
        if (!bantu)
        {
            baru->prev = tail;
            tail->next = baru;
            tail = baru;
        }
        else if (bantu == head)
        {
            baru->next = head;
            head->prev = baru;
            head = baru;
        }
        else
        {
            baru->next = bantu;
            baru->prev = bantu->prev;
            bantu->prev->next = baru;
            bantu->prev = baru;
        }
    }
    cout << "Video " << endl << judul << " ditambahkan." << endl;
    pushUndo("tambah", baru);
}

void tampilkanVideo()
{
    cout << "Daftar Video: " << endl;
    Video *bantu = head;
    while (bantu)
    {
        cout << "- " << bantu->judul << " (" << bantu->durasi << " menit) [" << bantu->status << "]\n";
        bantu = bantu->next;
    }
}

void tambahKePlaylist(string judul)
{
    Video *cari = head;
    while (cari && cari->judul != judul)
        cari = cari->next;
    if (!cari)
    {
        cout << "Video tidak ditemukan." << endl;
        return;
    }
    if (cari->status != "tersedia")
    {
        cout << "Video tidak dapat ditambahkan ke playlist." << endl;
        return;
    }
    cari->status = playlistHead ? "dalam antrean" : "sedang diputar";
    if (!playlistHead)
        playlistHead = playlistTail = cari;
    else
    {
        playlistTail->next = cari;
        cari->prev = playlistTail;
        playlistTail = cari;
    }
    cout << "Video " << judul << " ditambahkan ke playlist." << endl;
    pushUndo("playlist", cari);
}

void tontonVideo()
{
    if (!playlistHead)
    {
        cout << "Tidak ada video di playlist." << endl;
        return;
    }
    Video *tonton = playlistHead;
    tonton->status = "tersedia";
    playlistHead = playlistHead->next;
    if (playlistHead)
        playlistHead->prev = NULL;
    else
        playlistTail = NULL;

    Riwayat *baru = new Riwayat{tonton->judul, riwayatHead};
    riwayatHead = baru;

    cout << "Menonton: " << tonton->judul << endl;
    pushUndo("tonton", tonton);
}

void tampilkanRiwayat()
{
    cout << "Riwayat Tontonan:\n";
    Riwayat *bantu = riwayatHead;
    while (bantu)
    {
        cout << "- " << bantu->judul << endl;
        bantu = bantu->next;
    }
}

void hapusVideo(string judul)
{
    Video *hapus = head;
    while (hapus && hapus->judul != judul)
        hapus = hapus->next;
    if (!hapus)
    {
        cout << "Video tidak ditemukan." << endl;
        return;
    }
    if (hapus->status != "tersedia")
    {
        char pilih;
        cout << "Video sedang " << hapus->status << ". Yakin nih hapus? (y/t) ";
        cin >> pilih;
        if (pilih != 'y')
            return;
    }
    if (hapus == head)
        head = hapus->next;
    if (hapus == tail)
        tail = hapus->prev;
    if (hapus->prev)
        hapus->prev->next = hapus->next;
    if (hapus->next)
        hapus->next->prev = hapus->prev;
    hapus->next = hapus->prev = NULL;
    cout << "Video " << judul << " dihapus." << endl;
    pushUndo("hapus", hapus);
}

void undo()
{
    if (!undoTop)
    {
        cout << "Tidak ada aksi yang bisa di-undo. " << endl;
        return;
    }
    string aksi = undoTop->aksi;
    Video *data = undoTop->data;
    popUndo();

    if (aksi == "tambah")
    {
        hapusVideo(data->judul);
        cout << "Undo Tambah Video: " << data->judul << endl;
    }
    else if (aksi == "hapus")
    {
        tambahVideo(data->judul, data->durasi);
        cout << "Undo Hapus Video: " << data->judul << endl;
    }
    else if (aksi == "playlist")
    {
        data->status = "tersedia";
        cout << "Undo Tambah ke Playlist: " << data->judul << endl;
    }
    else if (aksi == "tonton")
    {
        data->status = "sedang diputar";
        playlistHead = data;
        cout << "Undo Tonton Video: " << data->judul << endl;
    }
}

int main()
{
    int pilihan;
    string judul;
    int durasi;
    do
    {
        cout << "=== Menu IDLIX Tube ===" << endl;
        cout << "1. Tambah Video" << endl;
        cout << "2. Tampilkan Daftar Video"<< endl;
        cout << "3. Tambah ke Playlist" << endl;
        cout << "4. Tonton Video" << endl;
        cout << "5. Tampilkan Riwayat" << endl;
        cout << "6. Hapus Video" << endl;
        cout << "7. Undo" << endl;
        cout << " 8. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 1:
            int jumlah;
            cout << "Berapa banyak video yang ingin ditambahkan? ";
            cin >> jumlah;
            cin.ignore();
            for (int i = 0; i < jumlah; ++i)
            {
                cout << "Video ke-" << i + 1 << ": " << endl;
                cout << "Judul: ";
                getline(cin, judul);
                cout << "Durasi (menit): ";
                cin >> durasi;
                cin.ignore();
                tambahVideo(judul, durasi);
            }
            break;
        case 2:
            tampilkanVideo();
            break;
        case 3:
            cout << "Judul yang akan ditambahkan: ";
            getline(cin, judul);
            tambahKePlaylist(judul);
            break;
        case 4:
            tontonVideo();
            break;
        case 5:
            tampilkanRiwayat();
            break;
        case 6:
            cout << "Judul yang akan dihapus: ";
            getline(cin, judul);
            hapusVideo(judul);
            break;
        case 7:
            undo();
            break;
        }
    } while (pilihan != 0);
    return 0;
}
