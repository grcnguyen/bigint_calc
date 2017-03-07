#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    std::cout <<  dbigint() << std::endl;
    std::cout << -dbigint() << std::endl;
    std::cout <<  dbigint(1) << std::endl;
    std::cout << -dbigint(1) << std::endl;
    std::cout <<  dbigint("1234567890") << std::endl;
    std::cout <<  dbigint("-1234567890") << std::endl;

    for (int e1 = -1; e1 <= 1; ++e1)
        for (int e2 = -1; e2 <= 1; ++e2)
        {
            std::cout << e1 << ", " << e2 << ": ";
            std::cout << (dbigint(e1) < dbigint(e2)) << " ";
            std::cout << (dbigint(e1) <= dbigint(e2)) << " ";
            std::cout << (dbigint(e1) == dbigint(e2)) << " ";
            std::cout << (dbigint(e1) != dbigint(e2)) << " ";
            std::cout << (dbigint(e1) >= dbigint(e2)) << " ";
            std::cout << (dbigint(e1) >  dbigint(e2)) << " ";
            std::cout << dbigint(e1) + dbigint(e2) << " ";
            std::cout << dbigint(e1) - dbigint(e2) << " ";
            std::cout << dbigint(e2) - dbigint(e1) << " ";
            std::cout << dbigint(e1) * dbigint(e2) << " ";
            std::cout << std::endl;
        }

    dbigint x("1234567890"), y("9876543210");
    std::cout << x + y << " ";
    std::cout << x - y << " ";
    std::cout << y - x << " ";
    std::cout << x * y << std::endl;

    dbigint product(1);
    for (int i = 1; i <= 100; ++i)
        product *= dbigint(i);

    std::cout << product << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
