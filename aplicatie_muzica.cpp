#include <iostream>
#include <string>
#include <vector>

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
    out << "Varsta: " << autor.age << std::endl;
    return out;
}

class Audio_Entity
{
private:
    int duration; ///in sec
    Autor autor;
    std::string name;
public:
    //Constructor
    Audio_Entity()
    {
        this->name = "Nume necunoscut";
        this->duration = 0;
    }

    void set_duration(int duration) { this->duration = duration; }
    void set_autor(const Autor& autor) { this->autor = autor; }
    void set_name(std::string name) { this->name = name; }

    int get_time() { return duration; }
    Autor get_autor() { return autor; }
    std::string get_name() { return name; }

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
    // Constructor
    Song (std::string name, int duration)
    { 
        set_name(name);
        set_duration(duration);
        album = "Single";
        casa_discuri = "-";
    }
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
        int mins = get_time();
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
    int episod;
    std::vector<std::string> invitati;
public:
    // Constructor
    Podcast (std::string name, int duration)
    { 
        set_name(name);
        set_duration(duration);
        episod = 1;
    }
    void set_episod(int episod) { this->episod = episod; }
    void add_invitat(std::string invitat)
    {
        invitati.push_back(invitat);
    }

    int get_episod() { return episod; }
    std::vector<std::string>& get_invitati() { return invitati; }

    void show_duration()
    {
        int dur = get_time();
        int mins = dur / 60 ;
        int secs = dur % 60;
        int hr = mins / 60;
        mins %= 60;
        std::cout << "Durata podcatului: " << hr << " hr " << mins << " min " << secs << " sec\n" ; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Podcast& podcast);
};

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
    bool album;
    int nr_melodii;
    std::string creator;
    std::string name;
    std::vector<Song> songs;
public:
    Playlist(std::string name)
    {
        this->name = name;
        album = 0;
        nr_melodii = 0;
        creator = "Autor necunoscut";
    }
    void add_song(const Song& song) { 
        songs.push_back(song);
        nr_melodii++;
    }
    void set_creator(std::string creator) { this->creator = creator; }
    void set_name(std::string name) { this->name = name; }
    void set_album(bool album) { this->album = album; }

    std::string get_creator() { return creator; }
    std::string get_name () const { return name; }
    bool is_album () { return album; }
    
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

};

std::ostream& operator<<(std::ostream& out, const Playlist& play)
{
    out << "Nume " << ((play.album) ? "album: " : "playlist: ") << play.name << '\n';
    out << "Autor: " << play.creator << '\n';
    out << "Songs:\n";
    for (int i = 0; i < play.songs.size(); ++i)
        out << i+1 << ":" << play.songs[i]; 
    return out;
}

int main()
{

    Autor A("Andrew Huberman", 45);
    Podcast Pod1("The Science & Practice of Perfecting Your Sleep", 7846);
    Pod1.set_autor(A);
    Pod1.set_episod(1);
    Pod1.add_invitat("Matthew Walker");
    Pod1.add_invitat("Michael Breus");
    std::cout << Pod1 ;
    Pod1.show_duration();

    Podcast Pod2("How to Enhance Focus and Improve Productivity", 10440);
    Pod2.set_autor(A);
    Pod2.add_invitat("Cal Newport");
    Pod2.set_episod(2);
    std::cout << Pod2 << std::endl;

    Autor PT("Pusha-T", 46, 6);
    Playlist Day("Daytona");
    Day.set_album(1);

    Song IfYou("If You Know You Know", 302);
    IfYou.set_autor(PT);
    IfYou.set_casadisc("Def Jam");
    IfYou.set_album("Daytona");
    Day.add_song(IfYou);

    Song The("The Games We Play", 166);
    The.set_autor(PT);
    The.set_casadisc("Def Jam");
    The.set_album("Daytona");
    Day.add_song(The);

    Song Hard("Hard Piano", 195);
    Hard.set_autor(PT);
    Hard.add_feature("Rick Ross");
    Hard.set_casadisc("Def Jam");
    Hard.set_album("Daytona");
    Day.add_song(Hard);

    Song Come("Come Back Baby", 206);
    Come.set_autor(PT);
    Come.set_casadisc("Def Jam");
    Come.set_album("Daytona");
    Day.add_song(Come);

    Song Santeria("Santeria", 176);
    Santeria.set_autor(PT);
    Santeria.set_casadisc("Def Jam");
    Santeria.set_album("Daytona");
    Day.add_song(Santeria);

    Song What("What Would Meek Do?", 153);
    What.set_autor(PT);
    What.add_feature("Kanye West");
    What.set_casadisc("Def Jam");
    What.set_album("Daytona");
    Day.add_song(What);

    Song Infrared("Infrared", 170);
    Infrared.set_autor(PT);
    Infrared.set_casadisc("Def Jam");
    Infrared.set_album("Daytona");
    Day.add_song(Infrared);

    std::cout << Day;
    Day.show_durataTotala();

    return 0;
}