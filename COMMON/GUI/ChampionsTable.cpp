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

ChampionsTable::ChampionsTable(QString company, QString application)
    : company(company),
      application(application)
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

void ChampionsTable::setCoins(long long coins)
{
    auto greaterCoinsFunctor= [&](const Entry &e1, const Entry &e2)
    {
        return e1.coins > e2.coins;
    };

    std::sort(map.begin(), map.end(), greaterCoinsFunctor);
    if((map.size() < COUNT) || (coins > map.rbegin()->coins)){
        QString name = QInputDialog::getText(0, "Enter your name", "Name");
        map.push_back({coins, name});
        std::sort(map.begin(), map.end(), greaterCoinsFunctor);
        QString outputTable;
        QString text;
        for(unsigned i = 0; i < COUNT && i < map.size(); ++i){
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
