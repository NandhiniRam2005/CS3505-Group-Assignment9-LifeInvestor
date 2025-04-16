#ifndef SHOPITEM_H
#define SHOPITEM_H
/*
The header file for ShopItem.

This class represents a shop item. Shop items have a name and a cost.
The user can purchase Shop items for a certain amount.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
#include <QObject>

class ShopItem
{
public:
    /**
     * Creates a shop item with a given name and cost
     * @param name the name of the shop item
     * @param cost the cost to purchase this item
     */
    ShopItem(QString name, double cost);
    /**
     * Sets this item's purchased status
     * @param purchased true if you want to set the item to purchased, false to set the status to available for purchase.
     */
    void setPurchased(bool purchased);

    /**
     * @return The name of this item
     */
    QString getName() const;

    /**
     * @return The cost to purchase this item
     */
    double getCost() const;

    /**
     * @return true if this item has been purchased, otherwise false.
     */
    bool isPurchased() const;

private:
    QString name;
    double cost;
    bool purchased;
};

#endif // SHOPITEM_H
