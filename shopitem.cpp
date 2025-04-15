#include "shopitem.h"

ShopItem::ShopItem(QString name, double cost)
    : name(name), cost(cost)
{
    purchased = false;
}

QString ShopItem::getName() const {
    return name;
}

double ShopItem::getCost() const {
    return cost;
}

bool ShopItem::isPurchased() const {
    return purchased;
}

void ShopItem::setPurchased(bool isPurchased)
{
    purchased = isPurchased;
}

