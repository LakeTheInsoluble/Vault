#ifndef PELAAJANALUS_H
#define PELAAJANALUS_H

#include "ship.hh"
#include "eventhandler.hh"
#include "alus_grafiikka.h"
#include "warpdrive.hh"

/**
 * @brief PelaajanAlus liikkuu galaksissa ja pelastaa toisia aluksia.
 *
 * Sisältää myös pelaajan grafiikan hallinnan.
 */
class PelaajanAlus : public Common::Ship
{
public:
    PelaajanAlus(std::shared_ptr<Common::WarpDrive> engine,
                 std::shared_ptr<Common::StarSystem> initialLocation,
                 std::shared_ptr<Student::EventHandler> events);

    ~PelaajanAlus();

    /**
     * @brief lisaaGrafiikka lisää pelaajalle grafiikan.
     * @param graf lisättävä grafiikka.
     */
    void lisaaGrafiikka(AlusGrafiikka *graf);
    /**
     * @brief haeGrafiikka palauttaa pelaajan grafiikan.
     * @return pelaajan grafiikka.
     */
    AlusGrafiikka* haeGrafiikka();

    /**
     * @brief asetaKohdeJarjestelma asetta pelaajalle kohdejärjestelmän.
     * @param systeemi kohdejärjestelmä.
     */
    void asetaKohdeJarjestelma(std::shared_ptr<Common::StarSystem> systeemi);

    /**
     * @brief decideAction ei tee mitään.
     * @return true.
     */
    virtual bool decideAction();


private:
    //! pelaajan liikkeen kohde.
    std::shared_ptr<Common::StarSystem> kohde_;
    //! pelaajan grafiikka.
    AlusGrafiikka *grafiikka;
    //! pelaajan aluksen moottori.
    std::shared_ptr<Common::WarpDrive> moottori_;

};

#endif // PELAAJANALUS_H
