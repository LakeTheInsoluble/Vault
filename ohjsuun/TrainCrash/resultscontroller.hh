#ifndef RESULTSCONTROLLER_HH
#define RESULTSCONTROLLER_HH

#include <QObject>

/**
 * @brief Toiminnot, joita voi suorittaa tulosnäytössä.
 */
class ResultsController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Antaa tulosnäyttöohjaaja olion
     * @return Singleton tulosnäyttöohjaajaolion
     */
    static ResultsController *instance();

signals:
    /**
     * @brief Lopeta peli
     */
    void quit();

    /**
     * @brief Aloita peli alusta
     */
    void toStart();

private:
    static ResultsController *instance_;  ///< Singleton-olio

    /**
     * @brief Rakentaja
     */
    ResultsController();
};

#endif // RESULTSCONTROLLER_HH
