#include "ui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{   
    Repo repo("produse.txt");
    Validator validator;
    Service service(repo, validator);

    QApplication app(argc, argv);
    AppGUI w(service);
    w.run();
    return app.exec();
}
