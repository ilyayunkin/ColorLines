/** @file
  * @author Yunkin Ilya.
  */
#ifndef CHAMPIONSTABLE_H
#define CHAMPIONSTABLE_H

#include <QString>
#include <vector>

class ChampionsTable
{
    struct Entry
    {
        long long coins;
        QString name;
    };

    std::vector<Entry> map;
    enum{
        COUNT = 10
    };
    QString company;
    QString application;
public:
    ChampionsTable(QString company, QString application);
    void setCoins(long long coins);
};

#endif // CHAMPIONSTABLE_H
