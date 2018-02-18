#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alustusdialogi.h"

#include <iostream>
#include <QGraphicsTextItem>
#include <math.h>
#include <QtWidgets>

static const unsigned MAX_MENETYT_ALUKSET = 20;

MainWindow::MainWindow(std::shared_ptr<Student::Galaxy> galaxy,
                       std::shared_ptr<Common::IGameRunner> gameRunner,
                       std::shared_ptr<Student::EventHandler> handler,
                       QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    grafiikka_ikkuna = new GrafiikkaIkkuna(this);
    grafiikka_ikkuna->setGeometry(180,10, 581,500);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-30,-30, 60, 60);

    grafiikka_ikkuna->setScene(scene);
    grafiikka_ikkuna->scale(20,20);

    hiirenPainallus_ = new QGraphicsEllipseItem;

    handler_ = handler;
    gameRunner_ = gameRunner;
    galaxy_ = galaxy;



    //uusien alusten spawnaus, pitaa connectoida ennen pelin alustusta
    QObject::connect(handler_.get(), SIGNAL(lahetaAlusSpawnattu(std::shared_ptr<Common::Ship>)),
                     this, SLOT(vastaanotaAlusSpawnattu(std::shared_ptr<Common::Ship>)));


    AlustusDialogi d(this);
    connect(&d, SIGNAL(laheta(const std::string&, int)), this ,
            SLOT(alustaPeli(const std::string&,int)));
    connect(&d, SIGNAL(peliaEiAlustettu()), this ,
            SLOT());

    connect(ui->aloita_Button, SIGNAL(clicked()),this, SLOT(avaaAlustusdialogi()));
    connect(ui->keskeyta_Button, SIGNAL(clicked()),this, SLOT(lopetaPeli()));
    connect(ui->liiku_Button, SIGNAL(clicked()),this, SLOT(asetaKohde()));
    connect(ui->korjaa_Button, SIGNAL(clicked()),this, SLOT(korjaa()));

    connect(grafiikka_ikkuna, SIGNAL(lahetaHiirenVasenPiste(QPointF)), this,
            SLOT(vastaanotaHiirenVasenPainallus(QPointF)));


    //ei pelattavien alusten signaalit
    QObject::connect(handler_.get(), SIGNAL(lahetaLiike(std::shared_ptr<Common::Ship>,
                         Common::Point, Common::Point)), this,
                        SLOT(vastaanotaEiPelattavanLiike(std::shared_ptr<Common::Ship>,
                        Common::Point, Common::Point)));

    QObject::connect(handler_.get(), SIGNAL(lahetaAlusPoistettu(std::shared_ptr<Common::Ship>)),
                     this, SLOT(vastaanotaAlusPoistettu(std::shared_ptr<Common::Ship>)));

    QObject::connect(handler_.get(), SIGNAL(lahetaPoikkeus(std::shared_ptr<Common::Ship>,
                                                           std::__cxx11::string)), this,
                     SLOT(vastaanotaPoikkeus(std::shared_ptr<Common::Ship>, std::__cxx11::string)));

    QObject::connect(handler_.get(), SIGNAL(lahetaDistressOn(std::shared_ptr<Common::Ship>)),
                     this, SLOT(vastaanotaDistressOn(std::shared_ptr<Common::Ship>)));

    QObject::connect(handler_.get(), SIGNAL(lahetaDistressOff(std::shared_ptr<Common::Ship>)),
                     this, SLOT(vastaanotaDistressOff(std::shared_ptr<Common::Ship>)));

    QObject::connect(handler_.get(), SIGNAL(lahetaAlusHylatty(std::shared_ptr<Common::Ship>)),
                     this, SLOT(vastaanotaAlusHylatty(std::shared_ptr<Common::Ship>)));

    //lisaa ajastin alusten liikkeeseen
    vuoroTimer_ = new QTimer(this);
    animaatioTimer_ = new QTimer(this);
    QObject::connect(this->vuoroTimer_, SIGNAL(timeout()), this, SLOT(uusiVuoro()));
    QObject::connect(this->animaatioTimer_, SIGNAL(timeout()), this, SLOT(liikutaAluksia()));

    //avataan aloitusdialogi
    d.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::avaaAlustusdialogi()
{
    AlustusDialogi d(this);
    connect(&d, SIGNAL(laheta(const std::string&, int)), this ,
            SLOT(alustaPeli(const std::string&, int)));
    d.exec();
}


void MainWindow::alustaPeli(const std::string& nimi, int alustenLKM)
{
    this->lopetaPeli();

    statistics_.reset();
    statistics_ = std::make_shared<Student::Statistics>();

    //asetetaan pelaajan nimi, pisteet yms.
    ui->nimi_label->setText(QString::fromStdString(nimi));
    ui->pisteet_lcd->display((int)statistics_->getPoints());
    ui->raha_lcd->display(statistics_->getCreditBalance());
    ui->menetetyt_lcd->display((int)statistics_->getLostShips());
    ui->pelastetut_lcd->display((int)statistics_->getSavedShips());
    ui->pelinTila_label->setText("Peli käynnissä!");


    //lisataan tahtijarjestelmat
    std::vector<std::string> nimet = galaxy_->getSystemNames();
    for( std::string nimi : nimet )
    {
        std::shared_ptr<Common::StarSystem>  jarjestelma =
                galaxy_->getStarSystemByName(nimi);

        Common::Point piste = jarjestelma->getCoordinates();
        scene->addEllipse(piste.x, piste.y, 0.1, 0.1);

        jarjestelmaInfo info = jarjestelmaInfo(piste, nimi);
        tahtijarjestelmat_.push_back(info);

        QGraphicsTextItem *nimii = new QGraphicsTextItem;
        nimii->setPlainText(QString::fromStdString(nimi));
        nimii->setPos(piste.x+0.5, piste.y-1);
        nimii->setScale(0.05);
        scene->addItem(nimii);
    }

    //asetetaan pelaajan alus
    pelaajanAlus_ = std::make_shared<PelaajanAlus>
            ( std::make_shared<Common::WarpDrive>(galaxy_),
            galaxy_->getStarSystemByName("Sol"), handler_);

    AlusGrafiikka *graf = new AlusGrafiikka(Qt::blue,1);
    Common::Point s = pelaajanAlus_->getLocation()->getCoordinates();
    graf->asetaSijainti((double)s.x,(double)s.y);
    pelaajanAlus_->lisaaGrafiikka(graf);
    scene->addItem(graf);
    grafiikka_ikkuna->centerOn(graf->scenePos());


    //ei pelattavat alukset
    pelastettavat_.clear();
    try {
        gameRunner_->spawnShips(alustenLKM);
    }
    catch(const Common::StateException &msg)
    {
        std::cout << "Alusten luonti epaonnistui: " << msg.msg() << std::endl;
    }


    //ajastimet
    vuoroTimer_->start(500);
    animaatioTimer_->start(35);
}

void MainWindow::lopetaPeli()
{
    if( vuoroTimer_->isActive()) {
        vuoroTimer_->stop();
        animaatioTimer_->stop();
    }

    if( pelaajanAlus_) {
        scene->removeItem(pelaajanAlus_->haeGrafiikka());
        pelaajanAlus_.reset();
    }
    for( auto const& eiPelattava : eiPelattavatAlukset_ ) {
        scene->removeItem(eiPelattava.second);
        try {
            galaxy_->removeShip(eiPelattava.first);
        }
        catch(const Common::ObjectNotFoundException &msg)
        {
            std::cout << "Aluksen poisto epaonnistui: " << msg.msg() << std::endl;
        }
    }
    eiPelattavatAlukset_.clear();
    pelastettavat_.clear();

    ui->raha_lcd->display(0);
    ui->pelinTila_label->setText("Peli päättyi!");
}

void MainWindow::asetaKohde()
{
    if(vuoroTimer_->isActive())
        pelaajanAlus_->asetaKohdeJarjestelma(painalluksenPaikka_);
}

void MainWindow::korjaa()
{
    if(!pelaajanAlus_->haeGrafiikka()->matkalla())
    {
        auto b = painalluksenPaikka_;
        auto c = pelastettavat_;
        for(auto ship : c)
        {
            if(ship->getLocation() == b)
            {
                statistics_->addSavedShip();
                statistics_->addPoints(100);
                handler_->shipRemoved(ship);
                statistics_->addCredits(100);
                try {
                    gameRunner_->spawnShips(1);
                }
                catch(const Common::StateException &msg)
                {
                    std::cout << "Uuden aluksen luonti epaonnistui: " << msg.msg() << std::endl;
                }
            }
        }
    }
}

void MainWindow::liikutaAluksia()
{
    bool rahatLoppu = false;
    //liikuta pelaajan alusta ja vahenna rahaa liikutun matkan mukaan
    try{
        double edetty = pelaajanAlus_->haeGrafiikka()->etene()*10;
        bool matkalla = pelaajanAlus_->haeGrafiikka()->matkalla();

        statistics_->reduceCredits((unsigned)round(edetty));
        statistics_->addPoints((unsigned)round(edetty));

        //tutki saavuttiinko systeemiin
        if(edetty > 0 && !matkalla)
        {
            auto b = painalluksenPaikka_;
            auto c = pelastettavat_;
            for(auto ship : c)
            {
                if(ship->getLocation() == b)
                {
                    statistics_->addSavedShip();
                    statistics_->addPoints(100);
                    handler_->shipRemoved(ship);
                    statistics_->addCredits(100);
                    try {
                        gameRunner_->spawnShips(1);
                    }
                    catch(const Common::StateException &msg)
                    {
                        std::cout << "Uuden aluksen luonti epaonnistui: " << msg.msg() << std::endl;
                    }
                }
            }
        }
    }
    catch(const Common::StateException &msg) {
        std::cout << "Rahat loppuivat: " << msg.msg() << std::endl;
        rahatLoppu = true;
    }

    grafiikka_ikkuna->centerOn((pelaajanAlus_->haeGrafiikka())->scenePos());
    pelaajanAlus_->haeGrafiikka()->etene();

    //liikuta ei pelattavia aluksia
    for( auto const& alus : eiPelattavatAlukset_ ) {
       alus.second->etene();
    }

    //paivitetaan tilastot naytolle
    ui->pisteet_lcd->display((int)statistics_->getPoints());
    ui->raha_lcd->display(statistics_->getCreditBalance());
    ui->menetetyt_lcd->display((int)statistics_->getLostShips());
    ui->pelastetut_lcd->display((int)statistics_->getSavedShips());

    //lopetetaan peli, jos liian monta menetettya alusta
    if( statistics_->getLostShips() > MAX_MENETYT_ALUKSET  ||
        statistics_->getLostShips() >= eiPelattavatAlukset_.size() ||
            rahatLoppu)
    {
        this->lopetaPeli();
    }
}

void MainWindow::uusiVuoro()
{
    gameRunner_->createActions();
    try {
        gameRunner_->doActions();    }
    catch(const Common::GameException &msg)
    {
        std::cout << "Alusten toimintojen teko epaonnistui: " << msg.msg() << std::endl;
    }
}

void MainWindow::vastaanotaHiirenVasenPainallus(QPointF piste)
{
    double etaisyys = 100.0;
    double dist;
    int x,y;
    std::string n;

    //etsitaan lahin tahtijarjestelma
    std::vector<jarjestelmaInfo>::iterator it;
    for(it = tahtijarjestelmat_.begin(); it != tahtijarjestelmat_.end(); ++it)
    {
        dist = sqrt(pow(piste.x()-(it->sijainti.x),2)+pow(piste.y()-(it->sijainti.y),2));
        if(  dist < etaisyys && dist < 1) {
            etaisyys = dist;
            x = it->sijainti.x;
            y = it->sijainti.y;
            n = it->nimi;
            try {
                painalluksenPaikka_ = galaxy_->getStarSystemByName(n);
            }
            catch(const Common::ObjectNotFoundException &msg)
            {
                std::cout << "Tahtijarjestelmaa ei loytynyt: " << msg.msg() << std::endl;
            }
        }
    }

    //poistetaan edellisella hiiren painalluksella tehty merkinta ja tehdaan uusi
    scene->removeItem(this->hiirenPainallus_);
    this->hiirenPainallus_ = scene->addEllipse(x, y, 0.1, 0.1, QPen(Qt::red));

    //jos loydettiin tahtijarjestelma, esitetaan sen tiedot ikkunassa
    if ( n != "" ) {
        std::shared_ptr<Common::StarSystem> jarj = galaxy_->getStarSystemByName(n);
        ui->populaatio_label->setText(QString::number(jarj->getPopulation()));
        ui->tahtijarjestelma_label->setText(QString::fromStdString(n));

        std::string talous;
        switch(jarj->getEconomy()) {
            case Common::StarSystem::ECONOMY_TYPE::Refinery:
                talous = "Refinery"; break;
            case Common::StarSystem::ECONOMY_TYPE::Extraction:
                talous = "Extraction"; break;
            case Common::StarSystem::ECONOMY_TYPE::HiTech:
                talous = "Hi Tech"; break;
            case Common::StarSystem::ECONOMY_TYPE::Industrial:
                talous = "Industrial"; break;
            case Common::StarSystem::ECONOMY_TYPE::Tourism:
                talous = "Tourism"; break;
            case Common::StarSystem::ECONOMY_TYPE::Agriculture:
                talous = "Agriculture"; break;
            case Common::StarSystem::ECONOMY_TYPE::Service:
                talous = "Service"; break;
            case Common::StarSystem::ECONOMY_TYPE::Military:
                talous = "Military"; break;
            case Common::StarSystem::ECONOMY_TYPE::Terraforming:
                talous = "Terraforming"; break;
            case Common::StarSystem::ECONOMY_TYPE::Colony:
                talous = "Colony"; break;
            default:
                talous = "None";
            break;

        }
        ui->elinkeino_label->setText(QString::fromStdString(talous));
    }
}


void MainWindow::vastaanotaAlusSpawnattu(std::shared_ptr<Common::Ship> ship)
{
    AlusGrafiikka *graf;
    graf = new AlusGrafiikka(Qt::red,0.5);
    Common::Point p = ship->getLocation()->getCoordinates();
    graf->asetaSijainti((double)p.x, (double)p.y);
    scene->addItem(graf);
    eiPelattavatAlukset_.insert( std::pair<std::shared_ptr<Common::Ship>, AlusGrafiikka*>
                                           (ship, graf));
}

void MainWindow::vastaanotaAlusPoistettu(std::shared_ptr<Common::Ship> ship)
{
    auto it = eiPelattavatAlukset_.find(ship);
    if( it != eiPelattavatAlukset_.end() ) {
        scene->removeItem(it->second);
        eiPelattavatAlukset_.erase(it);

        //poista alus pelastettavien listasta
        auto s = std::find(pelastettavat_.begin(), pelastettavat_.end(), ship);
        if( s != pelastettavat_.end() ) pelastettavat_.erase(s);
    }
    try {
        galaxy_->removeShip(ship);
    }
    catch(const Common::ObjectNotFoundException &msg)
    {
        std::cout << "Aluksen poisto epaonnistui: " << msg.msg() << std::endl;
    }
}


void MainWindow::vastaanotaEiPelattavanLiike(std::shared_ptr<Common::Ship> ship,
                                             Common::Point origin, Common::Point target)
{
    double nopeus = origin.distanceTo(target);
    nopeus = nopeus/10;
    auto it = eiPelattavatAlukset_.find(ship);
    if( it != eiPelattavatAlukset_.end() ) {
        it->second->asetaKohde(QPointF(target.x,target.y));
        it->second->asetaNopeus(nopeus);
    }
}


void MainWindow::vastaanotaPoikkeus(std::shared_ptr<Common::Ship> ship, const std::__cxx11::string &msg)
{
    std::cout << "Alus " << ship->getName() << " tapahtui virhe tehtavan suorituksesta ";
    std::cout << msg << std::endl;
}

void MainWindow::vastaanotaDistressOn(std::shared_ptr<Common::Ship> ship)
{
    auto it = eiPelattavatAlukset_.find(ship);
    if( it != eiPelattavatAlukset_.end() ) {
        scene->removeItem(it->second);
        delete it->second;

        AlusGrafiikka *graf;
        graf = new AlusGrafiikka(Qt::yellow,0.5);
        Common::Point p = ship->getLocation()->getCoordinates();
        graf->asetaSijainti((double)p.x, (double)p.y);
        scene->addItem(graf);
        it->second = graf;

        pelastettavat_.push_back(ship);
    }
}

void MainWindow::vastaanotaDistressOff(std::shared_ptr<Common::Ship> ship)
{
    auto it = eiPelattavatAlukset_.find(ship);
    if( it != eiPelattavatAlukset_.end() ) {
        scene->removeItem(it->second);
        delete it->second;

        AlusGrafiikka *graf;
        graf = new AlusGrafiikka(Qt::red,0.5);
        Common::Point p = ship->getLocation()->getCoordinates();
        graf->asetaSijainti((double)p.x, (double)p.y);
        scene->addItem(graf);
        it->second = graf;
    }
    pelastettavat_.erase(std::find(pelastettavat_.begin(), pelastettavat_.end(), ship));
    galaxy_->removeShip(ship);
}

void MainWindow::vastaanotaAlusHylatty(std::shared_ptr<Common::Ship> ship)
{
    statistics_->addLostShip();
    try {
        statistics_->reducePoints(50);
    }
    catch(const Common::StateException &msg) {
        std::cout << msg.msg() << "vahennettaessa pisteita!" << std::endl;
        statistics_->reducePoints(statistics_->getPoints());
    }

    //lisataan uusi alus
    try {
        gameRunner_->spawnShips(1);
    }
    catch(const Common::StateException &msg)
    {
        std::cout << "Uuden aluksen luonti epaonnistui: " << msg.msg() << std::endl;
    }

    handler_->shipRemoved(ship);
}


