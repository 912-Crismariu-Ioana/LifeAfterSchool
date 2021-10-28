
#include <QtWidgets/QApplication>
#include <QObject>
#include "FileRepository.h"
#include "AdminGUI.h"
#include "userGUI.h"
#include "userGUITable.h"
#include "Configuration.h"
#include <QDebug>
#include "HTMLRepository.h"
#include "CSVRepository.h"
#include "GUITableView.h"
#include "OperationManager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepository frepo1{ "TextFile1.txt" };
    AbstractExternalRepository* arepo;
    CSVRepository csvrepo{ "TextFile2.txt", "events.csv" };
    HTMLRepository htmlrepo{ "TextFile2.txt", "events.html" };
    EventValidator ev;
    Config* c = new Config;
    std::string filename;
    c->exec();
    qDebug() << QString::fromStdString(c->getOption());
    if (c->getOption() == "CSV")
    {
        arepo = &csvrepo;
        arepo = dynamic_cast<CSVRepository*>(arepo);
        filename = "events.csv";
    }
    else if (c->getOption() == "HTML")
    {
        arepo = &htmlrepo;
        arepo = dynamic_cast<HTMLRepository*>(arepo);
        filename = "events.html";
    }
    OperationManager oper;
    Service serv{ frepo1, *arepo, ev, oper};
    adminGUI w{serv};
    GUITableView userv{ *arepo, "user" };
    GUITableView adminv{ frepo1, "admin" };
    userGUI u{ serv, filename};
    userGUITable ut{ serv, filename };
    QWidget mainwin;
    QFont f{ "Corbel Light", 16 };
    QLabel label("Choose one of the following: ");
    label.setFont(f);
    QPushButton user("&User Mode");
    user.setFont(f);
    QPushButton admin("&Admin mode");
    admin.setFont(f);
    QObject::connect(&user, &QPushButton::clicked, &ut, &QWidget::show);
    QObject::connect(&admin, &QPushButton::clicked, &w, &QWidget::show);
    QVBoxLayout layout{&mainwin};
    layout.addWidget(&label);
    layout.addWidget(&user);
    layout.addWidget(&admin);
    mainwin.show();
    return a.exec();
}
