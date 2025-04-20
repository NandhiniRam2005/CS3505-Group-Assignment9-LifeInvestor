/*
The source file for ShopItem.

This class represents a shop item. Shop items have a name and a cost.
The user can purchase Shop items for a certain amount.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

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

