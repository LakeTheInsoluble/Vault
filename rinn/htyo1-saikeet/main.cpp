// TIE-02500 rinnakkaisuus harjoitustyö-01
// Henri Laakso 240062
// Antti Tolonen 247589
// Niko Lappalainen 253002

#include "rinn2017.h"
#include <iostream>
#include <stdint.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

// montako näytettä käsitellään ennen pysähtymistä
const int NAYTTEITA = 1000;

// luodaan nollaksi alustetut laskurit
// kolmelle laskettavalle säteilytyypille
typedef uint64_t Laskuri_t;
struct {
	std::atomic<Laskuri_t> alpha;
    std::atomic<Laskuri_t> beta;
    std::atomic<Laskuri_t> gamma;
} laskurit = { {0}, {0}, {0} };

// luodaan lukko detect-funktion kutsumiseen ja konsolille kirjoittamiseen
std::mutex detect_mutex, cout_mutex;

// rinn2017 detectorin näytteen mukaisesti
// lisätään kyseisen säteilyn laskuria
void kirjaa_nayte( rinn2017::DetectorData_t nayte )
{
    auto nimi = rinn2017::itemName( nayte );
    if( nimi == "alpha" ) {
        laskurit.alpha++;
    } else if( nimi == "beta") {
        laskurit.beta++;
    } else if( nimi == "gamma" ) {
        laskurit.gamma++;
    } else {} // jos ei tunneta, niin ei tehdä mitään
}

// kerää annetun määrän näytteitä laskurit-tietokantaan
void keraa_nayteet ( const int naytteita ) 
{
	for( auto i = 0; i < naytteita; i++ ) {
		// otetaan näyte
		rinn2017::DetectorData_t nayte;
		{
			std::lock_guard<std::mutex> lukko ( detect_mutex );
			nayte = rinn2017::detect();
		}
        auto nimi = rinn2017::itemName( nayte );
		
		// tulostetaan nimi
		{
			std::lock_guard<std::mutex> lukko ( cout_mutex );
			std::cout << "Luettiin " << nimi << std::endl;
		}
        kirjaa_nayte( nayte );
    }
}

int main()
{
	// säikeiden määrä
	const int saikeita = 5;
	std::vector<std::thread> saikeet;

    // aloitetaan säikeet
	// jos NAYTTEITA ei mene tasan, laitetaan ensimmäinen säie laskemaan enemmän
	const int naytteita_per_saie = NAYTTEITA/saikeita;
	saikeet.push_back(std::thread(keraa_nayteet, 
				(naytteita_per_saie + NAYTTEITA%saikeita)));
    for( auto i = 0; i < saikeita -1; i++ ) {
       saikeet.push_back(std::thread(keraa_nayteet, naytteita_per_saie));
    }
	
	// odotetaan säikeiden loppumista
	for ( auto i = 0; i < saikeita; i++ ) {
		saikeet[i].join();
	}

    // tulostetaan montako kappaletta kutakin näytettä saatiin
    std::cout << "Laskurit:" << std::endl;
    std::cout << "alpha: " << laskurit.alpha << std::endl;
    std::cout << "beta : " << laskurit.beta << std::endl;
    std::cout << "gamma: " << laskurit.gamma << std::endl;
    return EXIT_SUCCESS;
}
