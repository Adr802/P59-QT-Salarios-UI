#ifndef SALARIO_H
#define SALARIO_H

#include <QMainWindow>
#include <QDebug>

#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Salario; }
QT_END_NAMESPACE

class Salario : public QMainWindow
{
    Q_OBJECT

public:
    Salario(QWidget *parent = nullptr);
    ~Salario();

private slots:



    void on_actionSalir_triggered();
    void on_actionCalcular_triggered();
    void on_actionGuardar_triggered();
    void on_actionNuevo_triggered();



    void on_cmdCalcular_clicked();

private:
    Ui::Salario *ui;

    Controlador *m_control;
};
#endif // SALARIO_H
