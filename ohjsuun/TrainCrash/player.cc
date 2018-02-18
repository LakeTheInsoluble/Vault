#include "player.hh"

Player::Player() : QObject(), name_(), coupons_(0), medals_() { }

Player::Player(QString name, QObject *parent) :
    QObject(parent),
    name_(name),
    coupons_(50),
    medals_()
{}

QString Player::name() const { return name_; }

void Player::setName(QString newName)
{
    name_ = newName;
    emit nameChanged(newName);
}

uint Player::coupons() const { return coupons_; }

void Player::setCoupons(uint newCoupons)
{
    coupons_ = newCoupons;
    emit couponsChanged(newCoupons);
}

void Player::addCoupons(uint amount) { setCoupons(coupons_ + amount); }

void Player::chargeCoupons(uint amount) { setCoupons(coupons() - amount); }

QQmlListProperty<Medal> Player::medals()
{
    return QQmlListProperty<Medal>(this, nullptr,
                                   Player::appendMedal,
                                   Player::medalCount,
                                   Player::medalAt,
                                   Player::clearMedals);
}

QVector<Medal *> Player::medalList() const
{
    return medals_;
}

void Player::addMedal(Medal *medal)
{
    if (medal != nullptr)
    {
        medal->setParent(this);
        medals_.push_back(medal);
    }
}

void Player::appendMedal(QQmlListProperty<Medal> *medals, Medal *newMedal)
{
    Player *player = qobject_cast<Player *>(medals->object);
    player->medals_.append(newMedal);
    emit player->medalsChanged(player->medals());
}

int Player::medalCount(QQmlListProperty<Medal> *medals)
{
    return qobject_cast<Player *>(medals->object)->medals_.length();
}

Medal *Player::medalAt(QQmlListProperty<Medal> *medals, int index)
{
    return qobject_cast<Player *>(medals->object)->medals_.at(index);
}

void Player::clearMedals(QQmlListProperty<Medal> *medals)
{
    Player *player = qobject_cast<Player *>(medals->object);
    player->medals_.clear();
    emit player->medalsChanged(player->medals());
}
