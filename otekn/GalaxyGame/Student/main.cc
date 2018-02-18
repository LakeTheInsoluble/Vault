#include "mainwindow.h"
#include "alustusdialogi.h"

#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"
#include "ioexception.hh"
#include "formatexception.hh"

#include <QApplication>
#include <memory>
#include <time.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<Student::EventHandler> handler =
            std::make_shared<Student::EventHandler>();
    std::shared_ptr<Student::Galaxy> galaxy = std::make_shared<Student::Galaxy>();
    try{
        std::shared_ptr<Common::IGameRunner> gameRunner =
                Common::getGameRunner(galaxy, handler);

        Common::utilityInit(time(NULL));

        MainWindow w(galaxy, gameRunner, handler);
        w.show();

        return a.exec();

    }
    catch(const Common::IoException &msg) {
        std::cout << msg.msg() << std::endl;
        return 0;
    }
    catch(const Common::FormatException &msg) {
        std::cout << msg.msg() << std::endl;
        return 0;
    }
    //siivotaan loputkin poikkeukset, vaikka niita ei edes pitaisi tulla
    catch(...) {
        std::cout << "Tuntematon poikkeus! Suljetaan ohjelma" << std::endl;
        return 0;
    }
}
