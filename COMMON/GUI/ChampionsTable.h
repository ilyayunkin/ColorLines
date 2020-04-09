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
    QString company;
    QString application;
    const unsigned count;
    const bool greater;
public:
    ChampionsTable(QString company, QString application, unsigned count=10, bool greater = true);
    void setResult(long long coins);
};

#endif // CHAMPIONSTABLE_H
