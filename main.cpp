#include "salario.h"
#include "obrero.h"
#include "controlador.h"

#include <QApplication>
#include <QDebug>

float Salario::sBruto = 0;
float Salario::sIESS = 0;
float Salario::sNeto = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salario w;
    w.show();
    return a.exec();
}
