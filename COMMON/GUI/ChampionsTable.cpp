/** @file
  * @author Yunkin Ilya.
  */
#include "ChampionsTable.h"

#include <QCoreApplication>
#include <QSettings>
#include <QInputDialog>
#include <QMessageBox>

#include <algorithm>

namespace
{
const QString key("champions");
}

ChampionsTable::ChampionsTable(QString company, QString application, unsigned count, bool greater)
    : company(company),
      application(application),
      count(count),
      greater(greater)
{
    QCoreApplication::setOrganizationName(company);
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName(application);

    QSettings s;
    QString defaultValue("NULLVALUE");
    QString key = "champions";
    QVariant champions = s.value(key, defaultValue);
    QString championsString(champions.toString());
    if(champions != defaultValue){
        QStringList list = championsString.split(";");
        for (QString item: list) {
            QStringList itemList = item.split("#");
            if(itemList.size() == 2){
                long long coins = itemList[0].toLongLong();
                QString name = itemList[1];
                map.push_back(Entry{coins, name});
            }
        }
    }
}

void ChampionsTable::setResult(long long coins)
{
    auto greaterCoinsFunctor= [&](const Entry &e1, const Entry &e2)
    {
        return e1.coins > e2.coins;
    };
    auto lessCoinsFunctor= [&](const Entry &e1, const Entry &e2)
    {
        return e1.coins < e2.coins;
    };

    if(greater)
        std::sort(map.begin(), map.end(), greaterCoinsFunctor);
    else
        std::sort(map.begin(), map.end(), lessCoinsFunctor);

    if((map.size() < count) || (coins > map.rbegin()->coins)){
        QString name = QInputDialog::getText(0, "Enter your name", "Name");
        map.push_back({coins, name});

        if(greater)
            std::sort(map.begin(), map.end(), greaterCoinsFunctor);
        else
            std::sort(map.begin(), map.end(), lessCoinsFunctor);

        QString outputTable;
        QString text;
        for(unsigned i = 0; i < count && i < map.size(); ++i){
            const Entry &e = map[i];
            if(i != 0){
                outputTable += ";";
            }
            outputTable += QString("%1#%2").arg(e.coins).arg(e.name);
            text += QString("%1. %2 %3\n").arg(i + 1).arg(e.name).arg(e.coins);

        }
        text += QString("%1 (c) %2 2016").arg(application).arg(company);
        QMessageBox::information(0, "Champions", text);

        QSettings s;
        s.setValue(key, outputTable);
    }
}
