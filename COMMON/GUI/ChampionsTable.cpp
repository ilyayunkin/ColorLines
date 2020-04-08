/** @file
  * @author Yunkin Ilya.
  */
#include "ChampionsTable.h"

#include <QCoreApplication>
#include <QSettings>
#include <QInputDialog>
#include <QMessageBox>

#include <algorithm>

ChampionsTable::ChampionsTable(QString company, QString application)
    : key("champions"),
      company(company),
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
                long long way = itemList[0].toLongLong();
                QString name = itemList[1];
                map.insert(way, name);
            }
        }
    }
}

void ChampionsTable::setCoins(long long coins)
{
    QList<int> sortedCoins = map.keys();
    std::sort(sortedCoins.begin(), sortedCoins.end(), std::greater<int>());
    if((sortedCoins.size() < COUNT) || (coins > sortedCoins.last())){
        QString name = QInputDialog::getText(0, "Enter your name", "Name");
        map.insert(coins, name);
        sortedCoins = map.keys();
        std::sort(sortedCoins.begin(), sortedCoins.end(), std::greater<int>());
        QString outputTable;
        QString text;
        int i = 1;
        for(int way: sortedCoins){
            if(i != 1){
                outputTable += ";";
            }
            QString name(map[way]);
            outputTable += QString("%1#%2").arg(way).arg(name);
            text += QString("%1 %2\n").arg(way).arg(name);
            if(i == COUNT){
                break;
            }
            i++;
        }
        text += QString("%1 (c) %2 2016").arg(application).arg(company);
        QMessageBox::information(0, "Champions", text);

        QSettings s;
        s.setValue(key, outputTable);
    }
}
