#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "galaxy.hh"
#include "igamerunner.hh"
#include "eventhandler.hh"
#include "statistics.hh"
#include "grafiikka_ikkuna.h"
#include "alus_grafiikka.h"
#include "pelaajanalus.h"
#include "cargoship.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui{
class MainWindow;
}

/**
 * @brief jarjestelmaInfo strukti kuvaa pelkistettyä systeemiä.
 */
struct jarjestelmaInfo{
    jarjestelmaInfo(Common::Point p, std::string n) : sijainti(p), nimi(n)
    {
    }

    //! systeemin sijainti.
    Common::Point sijainti;
    //! systeemin nimi.
    std::string nimi;
};

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(std::shared_ptr<Student::Galaxy> galaxy,
                        std::shared_ptr<Common::IGameRunner> gameRunner,
                        std::shared_ptr<Student::EventHandler> handler,
                        QWidget *parent = 0);
    ~MainWindow();

public slots:

    /**
     * @brief avaaAlustusdialogi avaa pelin alustavan dialogin.
     */
    void avaaAlustusdialogi();

    /**
     * @brief alustaPeli alustaa pelin tilan valmiiksi peliä varten.
     * @param nimi pelaajan nimi.
     * @param alustenLMK galaxin alusten lukumäärä.
     */
    void alustaPeli(const std::string& nimi, int alustenLMK);
    /**
     * @brief lopetaPeli huolehtii pelin lopettamisesta ja siivoamisesta.
     */
    void lopetaPeli();

    /**
     * @brief liikutaAluksia suorittaa alusten grafiikan animaation päivitykset.
     */
    void liikutaAluksia();
    /**
     * @brief uusiVuoro arpoo ei pelattaville alukille toimintoja ja alkaa suorittaa niitä.
     */
    void uusiVuoro();

    /**
     * @brief asetaKohde asettaa pelaajan aluksen grafiikan kohteeksi sen hetkisen valitun systeemin.
     */
    void asetaKohde();
    /**
     * @brief korjaa korjaa pelaajan systeemin alukset.
     */
    void korjaa();
    /**
     * @brief vastaanotaHiirenVasenPainallus etsii painallusta lähimmän systeemn
     * ja asettaa sen painalluksenPaikka_ muuttujaan.
     * @param piste
     */
    void vastaanotaHiirenVasenPainallus(QPointF piste);

    /**
     * @brief vastaanotaAlusSpawnattu luo grafiikan spawnatulle alukselle.
     * @param ship spawnattu alus.
     */
    void vastaanotaAlusSpawnattu(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief vastaanotaAlusPoistettu poistaa aluksen pelistä.
     * @param ship poistettava alus.
     */
    void vastaanotaAlusPoistettu(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief vastaanotaEiPelattavanLiike liikuttaa ei pelattavan aluksen grafiikkaa.
     * @param ship liikuteltava alus.
     * @param origin lähtöpiste.
     * @param target kohdepiste.
     */
    void vastaanotaEiPelattavanLiike(std::shared_ptr<Common::Ship> ship,
                                     Common::Point origin, Common::Point target);

    /**
     * @brief vastaanotaPoikkeus tulostaa virheen aluksen toiminnon suorittamisesta.
     * @param ship virheen tuottanut alus.
     * @param msg virheen viesti.
     */
    void vastaanotaPoikkeus(std::shared_ptr<Common::Ship> ship, const std::__cxx11::string &msg);

    /**
     * @brief vastaanotaDistressOn muuttaa aluksen pelastettavaksi.
     * @param ship pelastettava alus.
     */
    void vastaanotaDistressOn(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief vastaanotaDistressOff poistaa aluksen pelastettavista ja samalla pelistä.
     * @param ship pelastamatta jäänyt alus.
     */
    void vastaanotaDistressOff(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief vastaanotaAlusHylatty poistaa aluksenpelistä.
     * @param ship poistettava alus.
     */
    void vastaanotaAlusHylatty(std::shared_ptr<Common::Ship> ship);

private:
    //! pääikkuna.
    Ui::MainWindow *ui;
    //! scene.
    QGraphicsScene *scene;
    //! grafiikka ikkuna.
    GrafiikkaIkkuna *grafiikka_ikkuna;

    //! ajastin ei pelattavien alusten vuoroille.
    QTimer *vuoroTimer_;
    //! ajasin grafiikoiden päivittämiselle.
    QTimer *animaatioTimer_;

    //! hiiren painalluksen grafiikka.
    QGraphicsEllipseItem *hiirenPainallus_;
    //! hiiren painalluksen systeemi.
    std::shared_ptr<Common::StarSystem> painalluksenPaikka_;
    //! pelattava alus.
    std::shared_ptr<PelaajanAlus> pelaajanAlus_;

    //! pelin galaxi.
    std::shared_ptr<Student::Galaxy> galaxy_;
    //! pelin toimintoja suorittava gamerunner.
    std::shared_ptr<Common::IGameRunner> gameRunner_;
    //! pelin toimintoja välittävä handleri.
    std::shared_ptr<Student::EventHandler> handler_;
    //! kirjanpidosta huolehtiva statistiikat.
    std::shared_ptr<Student::Statistics> statistics_;

    //! ei pelattavien alusten grafiikat.
    std::map<std::shared_ptr<Common::Ship>, AlusGrafiikka*> eiPelattavatAlukset_;
    //! pelastettavissa olevat alukset.
    std::vector<std::shared_ptr<Common::Ship>> pelastettavat_;

    //! pelkistettyjen systeemien säiliö.
    std::vector<jarjestelmaInfo> tahtijarjestelmat_;

};

#endif // MAINWINDOW_H
