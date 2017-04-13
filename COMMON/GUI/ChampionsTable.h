/** @file
  * @author Yunkin Ilya.
  */
#ifndef CHAMPIONSTABLE_H
#define CHAMPIONSTABLE_H

#include <QString>
#include <QMap>

class ChampionsTable
{
    QString key;
    QMap<int, QString> map;
    enum{
        COUNT = 15
    };
    QString company;
    QString application;
public:
    ChampionsTable(QString company, QString application);
    void setCoins(long long coins);
};

#endif // CHAMPIONSTABLE_H
