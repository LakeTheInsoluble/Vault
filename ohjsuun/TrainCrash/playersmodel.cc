#include "playersmodel.hh"

#include <QGuiApplication>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>

PlayersModel* PlayersModel::instance_ = nullptr;

PlayersModel *PlayersModel::instance()
{
    if (instance_ == nullptr) {
        instance_ = new PlayersModel();
    }
    return instance_;
}

void PlayersModel::addPlayer(const QString &name) { addPlayer(new Player(name, this)); }

void PlayersModel::addPlayer(Player *player)
{
    beginInsertRows(QModelIndex(), players_.size(), players_.size());
    players_.append(player);
    connect(player, SIGNAL(nameChanged(QString)), this, SLOT(savePlayers()));
    connect(player, SIGNAL(medalsChanged(QQmlListProperty<Medal>)), this, SLOT(savePlayers()));
    endInsertRows();
    savePlayers();
}

int PlayersModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : players_.size();
}


QVariant PlayersModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() < players_.size())
    {
        switch (role)
        {
        case Qt::DisplayRole: return QVariant(players_.at(index.row())->name());
        case NameRole: return QVariant(players_.at(index.row())->name());
        case PlayerRole: return QVariant::fromValue(players_.at(index.row()));
        }
    }
    return QVariant();
}

QHash<int, QByteArray> PlayersModel::roleNames() const {
    return {{NameRole, "name"}, {PlayerRole, "player"}};
}

void PlayersModel::savePlayers()
{
    QJsonDocument doc = createPlayerJson();
    QFile file(playerFile());
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << doc.toJson();
        file.close();
    }
    else
    {
        std::cerr << "Virhe: Pelaajia ei voitu tallentaa." << std::endl;
    }
}

PlayersModel::PlayersModel(QObject *parent) :
    QAbstractListModel(parent),
    players_(),
    activePlayer_(nullptr)
{
    readPlayerJson();
}

QJsonDocument PlayersModel::createPlayerJson()
{
    QJsonArray playerList;
    for ( Player *player : players_)
    {
        QJsonObject playerJson;
        playerJson["name"] =  player->name();
        QJsonArray medalJson;
        for ( Medal *medal : player->medalList())
        {
            medalJson.append(medal->name());
        }
        playerJson["medals"] = medalJson;
        playerList.append(playerJson);
    }
    QJsonDocument doc(playerList);

    return doc;
}

void PlayersModel::readPlayerJson()
{
    QFile file(playerFile());
    if (!file.open(QIODevice::ReadOnly))
    {
        // avaus epäonnistui
        std::cerr << "Virhe: Pelaajia ei voitu ladata." << std::endl;
    }
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
    file.close();

    QJsonArray playerArray = doc.array();
    for (auto playerRef: playerArray)
    {
        if (playerRef.isObject()){
            QJsonObject playerObject = playerRef.toObject();
            QString name = playerObject.value("name").toString();
            QJsonArray medalArray = playerObject.value("medals").toArray();
            Player *player = new Player(name, this);
            for (auto medalRef : medalArray)
            {
                QString medalName = medalRef.toString();
                player->addMedal(new Medal(medalName));
            }
            addPlayer(player);
        }
    }
}

QString PlayersModel::playerFile()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    directory = directory.append("/TrainCrash");
    if (QDir(directory).mkpath("."))
    {
        return directory + "/players.json";
    }
    return "";
}

