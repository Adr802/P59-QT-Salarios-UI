#include "salario.h"
#include "ui_salario.h"

Salario::Salario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salario)
{
    ui->setupUi(this);
    m_control = new Controlador(); //Instanciar objeto


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
    Salario::on_cmdCalcular_clicked();
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
    ui->actionGuardar->setEnabled(false); //lock the  button guardar until the user presses "calcular" button
}


void Salario::on_cmdCalcular_clicked()
{
    ui->actionGuardar->setEnabled(true);
    //Obtener datos de la GUI
    QString nombre = ui->inName->text();
    int horas = ui->inHour->value();
    TipoJornada jornada;
    if(ui->inMatutino->isChecked()){
        jornada = TipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }
    //Agregar obrero al controlador
    m_control->agregarObrero(nombre,horas,jornada);

    //Calcular
    if(m_control->calcularSalario()){
        ui->outResult->appendPlainText(m_control->obrero()->toString());
    }
}

