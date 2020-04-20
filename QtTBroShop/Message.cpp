#include "QtTBroShop.h"
QString messagelist[] = { 
        "Sender",
        "BoughtItem",
        "BoughtDino",
        "BoughtBeacon",
        "BoughtExp",
        "ReceivedPoints",
        "ReceivedwekendPoints",
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
QString vipmessagelist[] = {
        "Sender",
        "BoughtItem",
        "BoughtDino",
        "BoughtBeacon",
        "BoughtExp",
        "ReceivedPoints",
        "HavePoints",
        "NoPoints",
        "RidingDino",
        "BuyUsage",
        "ShopUsage",
        "StoreListDino",
        "StoreListItem",
        "StoreListFormat",
        "ShopMessage",
        "ShopUsage",
        "exchangeUsage",
        "exchangeSuccess",
        "updatevip",
        "NoVip"
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
    for (int i = 0; i < 37; i++)
    {
        std::string messageliststr = ui.Messages->item(i, 1)->text().toStdString();
        if (messageliststr.find("</>") != -1)
        {
            std::string colorstring;
            messageliststr = messageliststr.substr(messageliststr.find("<") + 1, messageliststr.find(">") - messageliststr.find("<") - 1);
            colorstring = messageliststr.substr(messageliststr.find("\"") + 1, messageliststr.rfind("\"") - messageliststr.find("\"") - 1);
            std::vector<std::string> parsed;
            parsed = spilt(colorstring, ','); 
            ui.Messages->item(i, 0)->setBackgroundColor(QColor(std::stoi(parsed[0]), std::stoi(parsed[1]), std::stoi(parsed[2])));
        }
    }
    for (int i = 0; i < 20; i++)
    {
        std::string vipmessageliststr = ui.vipMessages->item(i, 1)->text().toStdString();
        if (vipmessageliststr.find("</>") != -1)
        {
            std::vector<std::string> parsed;
            std::string colorstring;
            vipmessageliststr = vipmessageliststr.substr(vipmessageliststr.find("<") + 1, vipmessageliststr.find(">") - vipmessageliststr.find("<") - 1);
            colorstring = vipmessageliststr.substr(vipmessageliststr.find("\"") + 1, vipmessageliststr.rfind("\"") - vipmessageliststr.find("\"") - 1);
            parsed = spilt(colorstring, ',');
            ui.vipMessages->item(i, 0)->setBackgroundColor(QColor(std::stoi(parsed[0]), std::stoi(parsed[1]), std::stoi(parsed[2])));
        }
    }
}
void QtTBroShop::loadMessageconfig()
{
    for (int i = 0; i < 37; i++)
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
            ui.Messages->item(i, 0)->setBackgroundColor(QColor(std::stoi(parsed[0]), std::stoi(parsed[1]), std::stoi(parsed[2])));
        }
    }

    if (loadjson["vipMessages"].empty())
        return;
    for (int i = 0; i < 20; i++)
    {
        std::string vipmessageliststr = loadjson["vipMessages"].value(vipmessagelist[i].toStdString().c_str(), ui.vipMessages->item(i, 1)->text().toStdString().c_str());
        while (vipmessageliststr.find("\n") != -1)
        {
            vipmessageliststr = vipmessageliststr.replace(vipmessageliststr.find("\n"), 1, "\\n");
        }
        ui.vipMessages->item(i, 1)->setText(QString::fromStdString(vipmessageliststr)); 
        ui.vipMessages->item(i, 0)->setBackgroundColor(QColor(255, 255, 255));
        if (vipmessageliststr.find("</>") != -1)
        {
            std::vector<std::string> parsed;
            std::string colorstring;
            vipmessageliststr = vipmessageliststr.substr(vipmessageliststr.find("<") + 1, vipmessageliststr.find(">") - vipmessageliststr.find("<") - 1);
            colorstring = vipmessageliststr.substr(vipmessageliststr.find("\"") + 1, vipmessageliststr.rfind("\"") - vipmessageliststr.find("\"") - 1);
            parsed = spilt(colorstring, ',');
            ui.vipMessages->item(i, 0)->setBackgroundColor(QColor(std::stoi(parsed[0]), std::stoi(parsed[1]), std::stoi(parsed[2])));
        }
    }

}
void QtTBroShop::saveMessageconfig()
{
    for (int i = 0; i < 37; i++)
    {
        std::string messageliststr = ui.Messages->item(i, 1)->text().toStdString();
        while (messageliststr.find("\\n") != -1)
        {
            messageliststr = messageliststr.replace(messageliststr.find("\\n"), 2, "\n");
        }
        savejson["Messages"][messagelist[i].toStdString().c_str()] = messageliststr;
    }

    for (int i = 0; i < 20; i++)
    {
        std::string vipmessageliststr = ui.vipMessages->item(i, 1)->text().toStdString();
        while (vipmessageliststr.find("\\n") != -1)
        {
            vipmessageliststr = vipmessageliststr.replace(vipmessageliststr.find("\\n"), 2, "\n");
        }
        savejson["vipMessages"][vipmessagelist[i].toStdString().c_str()] = vipmessageliststr;
    }

}