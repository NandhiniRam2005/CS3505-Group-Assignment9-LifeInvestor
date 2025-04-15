#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QObject>

class ShopItem
{
public:
    ShopItem(QString name, double cost);
    void setPurchased(bool purchased);

    QString getName() const;
    double getCost() const;
    bool isPurchased() const;

private:
    QString name;
    double cost;
    bool purchased;
};

#endif // SHOPITEM_H
