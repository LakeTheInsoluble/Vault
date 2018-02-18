// Copied from: https://wiki.qt.io/Download_Data_from_URL

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>

/**
 * @brief Lataa tiedoston verkosta
 */
class FileDownloader : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Rakentaja
     * @param url Osoite, josta tiedosto ladataan
     * @param parent Edeltäjä
     */
    explicit FileDownloader(QUrl url, QObject *parent);

    /**
     * @brief Palauttaa ladatun datan
     * Palauttaa tyhjän, jos tiedostoa ei vielä ole ladattu
     * @return Ladattu data
     */
    QByteArray downloadedData() const;

signals:
    /**
     * @brief Tiedosto on ladattu ja data on valmis luettavaksi
     */
    void downloaded();

private:
    /**
     * @brief Lukee ladatun datan ja emittoi oikeat signaalit.
     * Asettaa myös ladatun tiedoston poistettavaksi ohjelman lopussa.
     * @param pReply
     */
    void fileDownloaded(QNetworkReply* pReply);

    QNetworkAccessManager netAccessManager_;  ///< Verkkoyhteyden käsittelijä
    QByteArray downloadedData_;   ///< Ladattu data
};

#endif // FILEDOWNLOADER_H
