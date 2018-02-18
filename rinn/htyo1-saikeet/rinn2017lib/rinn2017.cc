/*
 * TIE-02500 kurssin ensimmäisen harjoitustyön kirjasto, kevät 2017
 *
 * Tähän koodiin EI SAA TEHDÄ MUUTOKSIA
 * Koodin tarkastelu on tiedysti sallittua ja suotavaa
 *
 * Version: 2017-02-12 - ensimmäinen julkinen versio
 *
 */

#include "rinn2017.h"
#include <array>
#include <map>
#include <tuple>
#include <utility>
#include <random>
#include <atomic>
#include <cassert>
#include <thread>
#include <chrono>
#include <iostream>

namespace rinn2017 {

    namespace { // nimeämätön nimiavaruus (moduulin paikalliset)

        // sisäiset tunnisteluvut eri säteilyille
        const unsigned int ITEMS = 4;
        std::array< std::pair< std::string, rinn2017::DetectorData_t >, ITEMS > BLOBs = {
            std::make_pair( "alpha", 0xfa94f710d61de002 ),
            std::make_pair( "beta", 0xa2e87e2870033f42),
            std::make_pair( "gamma", 0x12984b9c48ecdb4b),
            std::make_pair( "unknown", 0x9de355f3575a5322 )
        };

        // tunnisteluku -> säteilyn nimi "mäppäystä" varten
        std::map< DetectorData_t,  std::string > mapping;
        int initMapping()
        {
            // käydään läpi BLOBs taulukko ja talletataan sen jokaisesta parista
            // haluttu mäppäys mapping-muuttujaan
            for( auto item : BLOBs )
                mapping[ item.second ] = item.first;
            return 42;
        }
        // tämän muuttujan alustus pakottaa alustusrutiinin kutsun ennen kuin
        // ohjelman main()-funktio suoritetaan
        int __attribute__((unused)) justtriggerinit = initMapping();

        // c++11 satunnaislukukirjasto
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, ITEMS-1);

        // sisäinen tarkistus säieturvallisuuden noudattamisesta
        std::atomic<int> DetectorCounter( 0 );

        void my_assert( bool ehto, const char* WHAT, const char* FILE, int LINE ) {
            if( ehto ) {
                return;
            } else {
                std::cerr << FILE << ":" << LINE << ":" << WHAT << ":Assertion failed" << std::endl;
                exit(1);
            }
        }
#define MY_ASSERT( ehto ) my_assert(ehto, #ehto, __FILE__, __LINE__)

    } // namespace

    // palautetaan "löydetty" säteilytyyppi (oikeasti arvottu arvo)
    // paikallinen i ja readonly-tietorakenteen luku -> oikeasti säieturvallinen
    // RAJAPINTA speksaa että ei ole säieturvallinen, kurssin sisäinen tarkistus
    // että käyttö on myös sellaista
    DetectorData_t detect() {
        // rinn tarkistus
        DetectorCounter++;
        std::this_thread::sleep_for( std::chrono::microseconds( dis(gen)*100 ) );
        MY_ASSERT( DetectorCounter.load() == 1);

        // arvotaan "löydetty" säteily:
        auto i = dis(gen);
        auto retval = BLOBs.at(i).second;

        // rinn tarkistus
        DetectorCounter--;
        std::this_thread::sleep_for( std::chrono::microseconds( dis(gen)*20 ) );
        MY_ASSERT( DetectorCounter.load() == 0 );

        return retval;
    }

    // palautetaan lukua vastaava nimi
    // mapping-rakennetta vain luetaan alustuksen jälkeen -> säieturvallinen ilman lukkoja
    std::string itemName( DetectorData_t item ) {
        return mapping.at( item );
    }
} // namespace rinn2017

