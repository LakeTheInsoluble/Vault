#ifndef RINN2017API
#define RINN2017API
#include <cstdint>
#include <string>

namespace rinn2017 {
    // tietotyyppi binääridatalle (säteilyn binääritunniste)
    typedef uint_least64_t DetectorData_t;

    // Pyydetään tunnistimelta yksi tieto (binääridatana)
    // SÄIE: ei turvallinen, vain yksi säie kerrallaan saa kutsua
    DetectorData_t detect();

    // muutetaan binäärinen tunniste merkkijonoksi
    // paluuarvo on jokin merkkijonoista:
    // "alpha", "beta", "gamma", "unknown"
    // ESIEHTO: parametrin 'item' tulee olla detect()-rutiinin palauttama
    // SÄIE: säieturvallinen (useampi säie saa kutsua yhtäaikaa)
    std::string itemName( DetectorData_t item );

} // namespace rinn2017

#endif // RINN2017API
