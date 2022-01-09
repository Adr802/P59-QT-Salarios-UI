#include "salario.h"
#include "ui_salario.h"

Salario::Salario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salario)
{
    ui->setupUi(this);

    //
    ui->inMatutino->setStatusTip("Jornada de la mañana"); //Set text on statusbar   boton elegir
    ui->inVespertina->setStatusTip("Jornada de la tarde"); //Set text on statusbar  boton elegir
    ui->inNocturna->setStatusTip("Jornada de la noche"); //Set text on statusbar    boton elegir
    ui->actionCalcular->setStatusTip("Calcular salario pana"); //Set tex on status bar actionCalcular


}

Salario::~Salario()
{
    delete ui;
}



void Salario::on_actionSalir_triggered() //Function to exit
{
    Salario::close();
}


void Salario::on_actionCalcular_triggered()
{
    ui->actionGuardar->setEnabled(true);
}


void Salario::on_actionGuardar_triggered()
{
    qDebug()<<"Active guardar"<<endl;
}


void Salario::on_actionNuevo_triggered()  //Function to clear all program and do new
{
    ui->inHour->clear();                  //Clear number hour
    ui->inName->clear();                  //Clear name text
    ui->outResult->clear();               //Clear text field(campo de texto)
    ui->inMatutino->setChecked(true);     //Set focus on matunino again
}


void Salario::on_inMatutino_clicked()
{
}


void Salario::on_inVespertina_clicked()
{
}


void Salario::on_inNocturna_clicked()
{

}

