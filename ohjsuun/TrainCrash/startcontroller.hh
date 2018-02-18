#ifndef STARTCONTROLLER_HH
#define STARTCONTROLLER_HH

#include <QObject>

/**
 * @brief Toiminnot, joita voi suorittaa aloitusnäytössä
 */
class StartController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Antaa aloitusnäyttöohjaaja olion
     * @return Singleton taloitusnäyttöohjaajaolion
     */
    static StartController *instance();

signals:
    /**
     * @brief Aloita peli
     */
    void startGame();

private:
    static StartController* instance_;  ///< Singleton-olio

    /**
     * @brief Rakentaja
     */
    StartController();
};

#endif // STARTCONTROLLER_HH
