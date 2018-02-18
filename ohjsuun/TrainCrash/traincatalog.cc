#include "traincatalog.hh"
#include "servicetrain.hh"

TrainCatalog::TrainType::TrainType(QString model, uint price, uint maxHealth, uint speed) :
    model(model),
    price(price),
    maxHealth(maxHealth),
    speed(speed)
{}

TrainCatalog::TrainCatalog(QObject *parent) :
    QAbstractListModel(parent),
    trainTypes_()
{
    createDefaultTypes();
}

TrainCatalog::~TrainCatalog()
{
    for (TrainType *type : trainTypes_)
    {
        delete type;
    }
}

int TrainCatalog::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : trainTypes_.size();
}

QVariant TrainCatalog::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= trainTypes_.size())
    {
        return QVariant();
    }
    else
    {
        switch (role)
        {
        case Qt::DisplayRole: return QVariant(trainTypes_.at(index.row())->model);
        case ModelRole: return QVariant(trainTypes_.at(index.row())->model);
        case MaxHealtRole: return QVariant(trainTypes_.at(index.row())->maxHealth);
        case PriceRole: return QVariant(trainTypes_.at(index.row())->price);
        case SpeedRole: return QVariant(trainTypes_.at(index.row())->speed);
        case TrainRole: return QVariant::fromValue(makeTrain(trainTypes_.at(index.row())));
        default: return QVariant();
        }
    }
}

QHash<int, QByteArray> TrainCatalog::roleNames() const
{
    return {{ModelRole, "model"},
            {MaxHealtRole, "maxHealth"},
            {PriceRole, "price"},
            {SpeedRole, "speed"},
            {TrainRole, "train"}};
}

ServiceTrain* TrainCatalog::makeTrain(TrainType* type) const
{
    return new ServiceTrain(type->model, type->maxHealth, type->price, type->speed);
}

void TrainCatalog::createDefaultTypes()
{
    trainTypes_.push_back(new TrainType("Resiina", 35, 20, 2500));
    trainTypes_.push_back(new TrainType("Standard", 75, 40, 5000));
    trainTypes_.push_back(new TrainType("Superjuna", 150, 350, 10000));
}
