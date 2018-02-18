#ifndef ALUSTUSDIALOGI_H
#define ALUSTUSDIALOGI_H

#include <QDialog>


namespace Ui {
class AlustusDialogi;
}

/**
 * @brief AlustusDialogi luokka dialogille, jonka
 * avulla pelaajalta kysytään alkutietoa pelin alustukseen liittyen
 */

class AlustusDialogi : public QDialog
{
    Q_OBJECT

public:
    explicit AlustusDialogi(QWidget *parent = 0);
    ~AlustusDialogi();

    /**
     * @brief funktio, joka odottaa käyttäjän valintaa dialogissa
     * @return palauttaa tiedon funktion suorituksesta
     */

    virtual int exec();

signals:
    /**
     * @brief signaali alustusdialogin tietojen lähettämiseen
     * @param nimi Pelaajan nimi
     * @param alustenLKM ei-pelattavien alusten maara pelissä
     */
    void laheta(const std::string& nimi, int alustenLKM);

private:
    //! dialogi
    Ui::AlustusDialogi *ui;
};

#endif // ALUSTUSDIALOGI_H
