#ifndef MEDAL_HH
#define MEDAL_HH

#include <QObject>

/// @brief Mitaleita saa tietyistä suorituksista (ensimmäinen roska poistettu jne.).
class Medal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    Medal(QObject *parent = nullptr);

    Medal(QString name, QObject *parent = nullptr);

    QString name() const;
    void setName(QString newName);

signals:
    void nameChanged(QString newName);

private:
    QString name_;
};

#endif // MEDAL_HH
