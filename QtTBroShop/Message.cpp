#include "QtTBroShop.h"
QString messagelist[] = { 
        "Sender",
        "BoughtItem",
        "BoughtDino",
        "BoughtBeacon",
        "BoughtExp",
        "ReceivedPoints",
        "HavePoints",
        "NoPoints",
        "WrongId",
        "NoPermissionsKit",
        "CantBuyKit",
        "BoughtKit",
        "AvailableKits",
        "NoKits",
        "KitsLeft",
        "NoKitsLeft",
        "CantGivePoints",
        "RidingDino",
        "SentPoints",
        "GotPoints",
        "NoPlayer",
        "FoundMorePlayers",
        "BuyUsage",
        "ShopUsage",
        "KitUsage",
        "BuyKitUsage",
        "TradeUsage",
        "BadLevel",
        "OnlyOnSpawnKit",
        "KitsListPrice",
        "KitsListFormat",
        "StoreListDino",
        "StoreListItem",
        "StoreListFormat",
        "ShopMessage",
        "HelpMessage"
};
std::vector<std::string> spilt(std::string s, char ch)
{
    s.push_back(ch);
    int start = 0, end = 0, size = s.size();
    std::vector<std::string> vs;

    for (int i = 0; i < size; i++)
    {
        if (s[i] == ch)
        {
            end = i;
            std::string temp = s.substr(start, end - start);
            start = i + 1;
            vs.push_back(temp);
        }
    }
    return vs;
}

void QtTBroShop::Messagedef()
{
    for (int i = 0; i < ui.Messages->rowCount(); i++)
    {
        QTableWidgetItem* Messagesitem = new QTableWidgetItem();
        Messagesitem->setText(messagelist[i]);
        ui.Messages->setItem(i, 0, Messagesitem);

        QTableWidgetItem* Messagesitem1 = new QTableWidgetItem();
        Messagesitem1->setText(QString::fromStdString(loadjson["Messages"].value(messagelist[i].toStdString(), messagelist[i].toStdString())));
        ui.Messages->setItem(i, 1, Messagesitem1);
        //ui.Messages->item(i, 0)->setText(messagelist[i]);
        //std::string list = messagelist[i].toStdString();
        //ui.Messages->item(i, 1)->setText(QString::fromStdString(loadjson["Messages"].value(list,list)));
        std::string messageliststr = ui.Messages->item(i, 1)->text().toStdString();
        
        if (messageliststr.find("</>") != -1)
        {
            std::string colorstring;
            messageliststr = messageliststr.substr(messageliststr.find("<") + 1, messageliststr.find(">") - messageliststr.find("<") - 1);
            colorstring = messageliststr.substr(messageliststr.find("\"") + 1, messageliststr.rfind("\"") - messageliststr.find("\"") - 1);
            std::vector<std::string> parsed;
            parsed = spilt(colorstring, ','); 
            int a = std::stoi(parsed[0]);
            int b = std::stoi(parsed[1]);
            int c = std::stoi(parsed[2]);
            if (a <= 1)    a *= 255;
            if (b <= 1)    b *= 255;
            if (c <= 1)    c *= 255;
            ui.Messages->item(i, 0)->setBackgroundColor(QColor(a, b, c));
        }
    }
}
void QtTBroShop::loadMessageconfig()
{
    for (int i = 0; i < 36; i++)
    {
        std::string messageliststr = loadjson["Messages"].value(messagelist[i].toStdString().c_str(), ui.Messages->item(i, 1)->text().toStdString().c_str());
        while (messageliststr.find("\n")!=-1)
        {
            messageliststr = messageliststr.replace(messageliststr.find("\n"), 1, "\\n");
        }
        ui.Messages->item(i, 1)->setText(QString::fromStdString(messageliststr));
        ui.Messages->item(i, 0)->setBackgroundColor(QColor(255, 255, 255));
        if(messageliststr.find("</>") != -1)
        {
            std::vector<std::string> parsed;
            std::string colorstring;
            messageliststr = messageliststr.substr(messageliststr.find("<") + 1, messageliststr.find(">") - messageliststr.find("<") - 1);
            colorstring = messageliststr.substr(messageliststr.find("\"") + 1, messageliststr.rfind("\"") - messageliststr.find("\"") - 1);
            parsed = spilt(colorstring,',');
            int a = std::stoi(parsed[0]);
            int b = std::stoi(parsed[1]);
            int c = std::stoi(parsed[2]);
            if (a <= 1)    a *= 255;
            if (b <= 1)    b *= 255;
            if (c <= 1)    c *= 255;
            ui.Messages->item(i, 0)->setBackgroundColor(QColor(a, b, c));
        }
    }
}
void QtTBroShop::saveMessageconfig()
{

    if (ui.Messages->item(0, 1)->text() == "arkfgf")
        ui.Messages->item(0, 1)->setText("arkfgf.com");
    for (int i = 0; i < 36; i++)
    {
        std::string messageliststr = ui.Messages->item(i, 1)->text().toStdString();
        while (messageliststr.find("\\n") != -1)
        {
            messageliststr = messageliststr.replace(messageliststr.find("\\n"), 2, "\n");
        }
        savejson["Messages"][messagelist[i].toStdString().c_str()] = messageliststr;
    }

}