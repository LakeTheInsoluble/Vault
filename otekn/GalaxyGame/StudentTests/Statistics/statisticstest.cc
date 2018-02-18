#include <QString>
#include <QtTest>
#include <memory>

#include "statistics.hh"
#include "stateexception.hh"

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();

private Q_SLOTS:
    void init();

    void testSavedShips();
    void testLostShips();

    void testPoints();

    void testCredits();

private:
    std::shared_ptr<Student::Statistics> statistics_;
};

StatisticsTest::StatisticsTest()
{
}

//resetoidaan olio ennen uutta testitapausta
void StatisticsTest::init()
{
    statistics_.reset();
    statistics_ = std::make_shared<Student::Statistics>();
}

void StatisticsTest::testSavedShips()
{
    //haetaan alkuarvo
    unsigned ships = statistics_->getSavedShips();

    //lisataan yksi alus
    statistics_->addSavedShip();
    QVERIFY(statistics_->getSavedShips() == ships+1);

    //lisataan toinen alus
    statistics_->addSavedShip();
    QVERIFY(statistics_->getSavedShips() == ships+2);
}

void StatisticsTest::testLostShips()
{
    //haetaan alkuarvo
    unsigned ships = statistics_->getLostShips();

    //lisataan yksi alus
    statistics_->addLostShip();
    QVERIFY(statistics_->getLostShips() == ships+1);

    //lisataan toinen alus
    statistics_->addLostShip();
    QVERIFY(statistics_->getLostShips() == ships+2);
}

void StatisticsTest::testPoints()
{
    //haetaan alkuarvo
    unsigned points = statistics_->getPoints();

    //lisataan pisteita
    statistics_->addPoints(3);
    QVERIFY(statistics_->getPoints() == points+3);

    //vahennetaan pisteita (pisteita jaa jaljelle)
    statistics_->addPoints(10);
    points = statistics_->getPoints();
    statistics_->reducePoints(3);
    QVERIFY(statistics_->getPoints() == points-3);

    //vahennetaan pisteita (nollille)
    statistics_->addPoints(10);
    points = statistics_->getPoints();
    statistics_->reducePoints(points);
    QVERIFY(statistics_->getPoints() == 0);

    //vahennetaan pisteita (menisi miinukselle -> poikkeus)
    statistics_->addPoints(10);
    points = statistics_->getPoints();
    QVERIFY_EXCEPTION_THROWN(statistics_->reducePoints(points+1), Common::StateException);
}

void StatisticsTest::testCredits()
{
    //haetaan alkuarvo
    int credits = statistics_->getCreditBalance();

    //lisataan creditteja
    statistics_->addCredits(3);
    QVERIFY(statistics_->getCreditBalance() == credits+3);

    //vahennetaan creditteja (jaa jaljelle)
    statistics_->addCredits(10);
    credits = statistics_->getCreditBalance();
    statistics_->reduceCredits(3);
    QVERIFY(statistics_->getCreditBalance() == credits-3);

    //vahennetaan creditteja (pysyy rajan MAX_LOAN_ALLOWANCE sisalla)
    statistics_->addCredits(10);
    credits = statistics_->getCreditBalance();
    statistics_->reduceCredits(credits+Student::MAX_LOAN_ALLOWANCE);
    QVERIFY(statistics_->getCreditBalance() == -Student::MAX_LOAN_ALLOWANCE);


    //pahemmin miinuksella kuin MAX_LOAN_ALLOWANCE -> StateException
    statistics_->addCredits(10);
    credits = statistics_->getCreditBalance();
    QVERIFY_EXCEPTION_THROWN(statistics_->reduceCredits(credits+
              Student::MAX_LOAN_ALLOWANCE+1), Common::StateException);
}






QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"
