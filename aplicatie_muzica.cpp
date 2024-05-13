#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class ExceptieCustom : public std::exception
{
private:
    std::string mesaj_custom;
public:
    //Constructor
    ExceptieCustom(const std::string& mesaj) : mesaj_custom(mesaj) {}

    const char* what() const noexcept override
    {
        return mesaj_custom.c_str();
    }

};


class Autor
{
private:
    std::string name; 
    int age;
    int nr_albume; 

public:
    //Constructori
    Autor()
    {
        name = "Artist necunoscut";
        age = -1;
        nr_albume = 0;
    }
    Autor(std::string name) { this->name = name; age = -1; nr_albume = 0; }
    Autor(std::string name, int age) { this->name = name; this->age = age; nr_albume = 0;}
    Autor(std::string name, int age, int nr_albume) 
    { 
        this->name = name; 
        this->nr_albume = nr_albume; 
        this->age = age;
    }
    // Constructor de copiere
    Autor(const Autor& altul)
    {
        name = altul.name;
        age = altul.age;
        nr_albume = altul.nr_albume;
    }

    void set_name(std::string name) { this->name = name; }
    void set_age(int age) { this->age = age; }
    void set_nralbume(int nr_albume) { this->nr_albume = nr_albume; }

    std::string get_name() { return name; }
    int get_age() { return age; } 
    int get_nralbume() { return nr_albume; }

    // Overloading atribuire
    Autor& operator= (const Autor& autor)
    {
        this->name = autor.name;
        this->age = autor.age;
        this->nr_albume = autor.nr_albume;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Autor& autor);

    // Destructor
    ~Autor() { }

};

// Operator afisare
std::ostream& operator<<(std::ostream& out, const Autor& autor)
{
    out << "Nume: " << autor.name << std::endl ;
    out << "Numar albume: " << autor.nr_albume << std::endl;
    out << "Varsta: "; 
    
    try
    {
        if (autor.age == -1)
        {
            throw ExceptieCustom("Neprecizat");
        }
        else
        {
            out << autor.age << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        out << e.what() << std::endl;
    }
    
    return out;
}

class Audio_Entity
{
private:
    Autor autor;
    std::string name;
protected:
    int duration; ///in sec
public:
    //Constructor
    Audio_Entity () {}
    Audio_Entity(std::string name, int duration)
    {
        this->name = name;
        this->duration = duration;
    }

    // functie virtuala, clasa e abstracta
    virtual void show_duration() = 0;
    virtual void add_feature(std::string feature) = 0;

    void set_duration(int duration) { this->duration = duration; }
    void set_autor(const Autor& autor) { this->autor = autor; }
    void set_name(std::string name) { this->name = name; }

    int get_time() const { return duration; }
    Autor get_autor() { return autor; }
    std::string get_name() { return name; }

protected:
    friend std::ostream& operator<<(std::ostream& out, const Audio_Entity& audio);

};


std::ostream& operator<<(std::ostream& out, const Audio_Entity& audio)
{
    out << "\nNume: " << audio.name;
    out << "\nDespre autor:\n" << audio.autor;
    return out;
}

class Song : public Audio_Entity
{
private:
    std::string album;
    std::string casa_discuri;
    std::vector<std::string> features;
public:
    // lista de initializare cu constructor clasa de baza
    Song (std::string name, int duration, std::string album) : Audio_Entity(name, duration) , album(album) {}

    void set_album(std::string album) { this->album = album; }
    void set_casadisc(std::string casa) { casa_discuri = casa; }

    std::string get_album() { return album; }
    std::string get_casadisc() { return casa_discuri; }

    void add_feature(std::string feature)
    {
        features.push_back(feature);
    }

    void show_duration()
    {
        
        if (duration < 0)
        {
            throw std::invalid_argument("Durata nu poate fi negativa.");
        }

        int mins = duration;
        int secs = mins % 60;
        mins /= 60; 
        std::cout << "Durata: " << mins << " minute " << secs << " secunde\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const Song& song);

};

std::ostream& operator<<(std::ostream& out, const Song& song)
{
    const Audio_Entity& entity = song;
    out << entity;
    if (!song.album.empty())
        out << "Album: " << song.album << std::endl;
    if (!song.casa_discuri.empty())
        out << "Casa de discuri: " << song.casa_discuri << std::endl;
    if (!song.features.empty()) {
        out << "Features: ";
        int i = 0;
        for (i = 0; i < song.features.size() - 1; ++i) {
            out << song.features[i] << ", ";
        }
        out << song.features[i] << "\n";
    }
    return out;
}

class Podcast : public Audio_Entity
{
private:
    static int pod_totale;
    int episod;
    std::vector<std::string> invitati;
public:
    // Constructor
    Podcast () 
    {
        pod_totale++;
    }
    Podcast (std::string name, int duration) : Audio_Entity(name, duration) 
    {
        pod_totale++;
    }
    
    void set_episod(int episod) { this->episod = episod; }
    void add_feature(std::string invitat)
    {
        invitati.push_back(invitat);
    }

    int get_episod() { return episod; }
    std::vector<std::string>& get_invitati() { return invitati; }
    static int get_count() 
    {
        return pod_totale;
    }

    void show_duration()
    {
        
        if (duration < 0)
        {
            throw std::invalid_argument("Duration cannot be negative.");
        }
        

        int mins = duration / 60 ;
        int secs = duration % 60;
        int hr = mins / 60;
        mins %= 60;
        std::cout << "Durata podcatului: " << hr << " hr " << mins << " min " << secs << " sec\n" ; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Podcast& podcast);

    ~Podcast()
    {
        pod_totale--;
    }
};

int Podcast::pod_totale = 0;

std::ostream& operator<<(std::ostream& out, const Podcast& podcast)
{
    const Audio_Entity& entity = podcast;
    out << entity;
    if (!podcast.invitati.empty())
    {
        out << "Invitati: ";
        int i = 0; 
        for (i = 0; i < podcast.invitati.size() - 1; ++i)
            out << podcast.invitati[i] << ", ";
        out << podcast.invitati[i] << "\n";
    }
    return out;
}

class Playlist
{
private:
    static int nr_total;
    static int durata_totala;
    bool is_album;
    int nr_melodii;
    Autor creator;
    std::string name;
    std::vector<Song> songs;
public:
    Playlist(std::string name)
    {
        this->name = name;
        is_album = 0;
        nr_melodii = 0;
        creator = Autor();
        nr_total++;
    }
    void add_song(const Song& song) {
        songs.push_back(song);
        nr_melodii++;
        durata_totala += song.get_time();
    }
    void set_creator(const Autor& creator) { this->creator = creator; }
    void set_name(std::string name) { this->name = name; }
    void set_album(bool is_album) { this->is_album = is_album; }

    const Autor& get_creator() { return creator; }
    std::string get_name () const { return name; }
    bool get_is_album () { return is_album; }

    static int get_durata_medie()
    {
        return (durata_totala / nr_total / 60) ;
    }
    
    void show_durataTotala()
    {
        int durataTotala = 0;
        for (int i = 0; i < songs.size(); ++i)
            durataTotala += songs[i].get_time();
        int mins = durataTotala / 60 ;
        int secs = durataTotala % 60;
        int hr = mins / 60;
        mins %= 60;
        std::cout << "Durata totala: ";
        if (hr > 0)
            std::cout << hr << " hr "; 
        std::cout << mins << " min " << secs << " sec\n" ;
    }

    void show_songlist()
    {
        std::cout << "Songs:\n";
        for (int i = 0; i < songs.size(); ++i)
            std::cout << songs[i].get_name() << '\n';          
    }

    friend std::ostream& operator<<(std::ostream& out, const Playlist& play);

    ~Playlist()
    {
        nr_total--;
    }

};

int Playlist::nr_total = 0;
int Playlist::durata_totala = 0;

std::ostream& operator<<(std::ostream& out, const Playlist& play)
{
    out << "Nume " << ((play.is_album) ? "album: " : "playlist: ") << play.name << '\n';
    out << "Autor:\n" << play.creator << '\n';
    out << "Songs:\n";
    for (int i = 0; i < play.songs.size(); ++i)
        out << i+1 << ":" << play.songs[i]; 
    return out;
}

class Album : public Playlist
{
private:
    int an_lansare;
    std::string publisher;

public:
    Album(std::string name) : Playlist(name) , an_lansare(0), publisher("Unknown") {}

    void set_lansare(int an_lansare) { this->an_lansare = an_lansare; }
    void set_publisher(std::string publisher) { this->publisher = publisher; }

    int get_lansare() { return an_lansare; }
    std::string get_publisher() { return publisher; }

    friend std::ostream& operator<<(std::ostream& out, const Album& album);
    
};

std::ostream& operator<<(std::ostream& out, const Album& album)
{
    const Playlist& play = album;
    out << play;
    out << "Anul lansarii: ";
    if (album.an_lansare)
    {
        out << album.an_lansare << "\n";
    }
    else
    {
        out << "Unknown\n";
    }  
    out << "Publisher: " << album.publisher << "\n";
    return out;
}

class PlaylistSpotify : public Playlist
{
private:
    std::string genre;
    std::string descriere;

public:
    PlaylistSpotify(std::string name) : Playlist(name) , genre("Unknown") {}

    void set_genre (std::string genre) { this->genre = genre; }
    void set_descriere (std::string descriere) { this->descriere = descriere; }

    std::string get_genre() { return genre; }
    std::string get_descriere() { return descriere; }

    friend std::ostream& operator<<(std::ostream& out, const PlaylistSpotify& spotify);

};

std::ostream& operator<<(std::ostream& out, const PlaylistSpotify& spotify)
{
    const Playlist& play = spotify;
    out << play;
    out << "Gen muzical: " << spotify.genre << "\n";
    if (!spotify.descriere.empty())
    {
        out << "Descriere: " << spotify.descriere << "\n";
    }  
    return out;
}

int main()
{

    Autor A("Andrew Huberman", 45);
    Podcast Pod1("The Science & Practice of Perfecting Your Sleep", 7846);
    Pod1.set_autor(A);
    Pod1.set_episod(1);
    Pod1.add_feature("Matthew Walker");
    Pod1.add_feature("Michael Breus");
    std::cout << Pod1 ;
    Pod1.show_duration();

    Podcast Pod2;
    Pod2.set_name("How to Enhance Focus and Improve Productivity");
    Pod2.set_autor(A);
    Pod2.add_feature("Cal Newport");
    Pod2.set_episod(2);
    std::cout << Pod2 << std::endl;

    Autor PT("Pusha-T", 46, 6);
    Album Day("Daytona");
    Day.set_album(1);
    Day.set_creator(PT);
    Day.set_lansare(2018);
    Day.set_publisher("Def Jam Music");

    Song IfYou("If You Know You Know", 302, "Daytona");
    IfYou.set_autor(PT);
    IfYou.set_casadisc("Def Jam");
    Day.add_song(IfYou);

    Song The("The Games We Play", 166, "Daytona");
    The.set_autor(PT);
    The.set_casadisc("Def Jam");
    Day.add_song(The);

    Song Hard("Hard Piano", 195, "Daytona");
    Hard.set_autor(PT);
    Hard.add_feature("Rick Ross");
    Hard.set_casadisc("Def Jam");
    Day.add_song(Hard);

    Song Come("Come Back Baby", 206, "Daytona");
    Come.set_autor(PT);
    Come.set_casadisc("Def Jam");
    Day.add_song(Come);

    Song Santeria("Santeria", 176, "Daytona");
    Santeria.set_autor(PT);
    Santeria.set_casadisc("Def Jam");
    Day.add_song(Santeria);

    Song What("What Would Meek Do?", 153, "Daytona");
    What.set_autor(PT);
    What.add_feature("Kanye West");
    What.set_casadisc("Def Jam");
    Day.add_song(What);

    Song Infrared("Infrared", 170, "Daytona");
    Infrared.set_autor(PT);
    Infrared.set_casadisc("Def Jam");
    Day.add_song(Infrared);

    std::cout << Day;
    Day.show_durataTotala();

    //runtime polymorphism

    Audio_Entity* base1 = &Infrared;

    base1->show_duration();
    base1->add_feature("Pharell Williams");

    Audio_Entity* base2 = &Pod2;

    base2->add_feature("Matthew Walker");
    base2->set_duration(10456);

    //
    Autor Ion("Ion Paladi", 50, 3);

    Song Test("Bine sade-i mesei mele", -13, "Muzica populara");
    Test.set_autor(Ion);
    Test.set_casadisc("EtnoMusic");

    try
    {
        Test.show_duration();
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    // testam exceptia din afisarea varstei autorului
    Autor Brent("Brent Fayaz");
    std::cout << Brent;

    //variabila si functie statica
    std::cout << Podcast::get_count() << "\n";


    //variabile si functie statica 2
    std::cout << "Durata medie a tuturor playlisturilor este de " << Playlist::get_durata_medie() << " minute\n";

    return 0;
}