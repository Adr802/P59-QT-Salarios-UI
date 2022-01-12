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
    calcular();
}


void Salario::on_actionGuardar_triggered()
{
    guardar();
}


void Salario::on_actionNuevo_triggered()  //Function to clear all program and do new
{
    limpiar();                            //Llama a la funcion para volver a valores por default
    ui->outResult->clear();               //Clear text field(campo de texto)
    ui->actionGuardar->setEnabled(false); //lock the  button guardar until the user presses "calcular" button
}


void Salario::on_cmdCalcular_clicked()
{
    calcular();
}

void Salario::limpiar()
{
    //Volver a valores por default
    ui->inHour->setValue(0);
    ui->inName->clear();
    ui->inName->setFocus();
    ui->inMatutino->setChecked(true);
}

void Salario::calcular()
{
    if(ui->inName->text() == "" || ui->inHour->value() == 0){ //Ver si el campo de texto ha sido modificado (El usuario escribio)

        QMessageBox::warning(this,"Advertencia","Campos vacios u horas 0 \nIntente de nuevo");  //Ventana emergente
        limpiar();

    }else{
        ui->actionGuardar->setEnabled(true);    //Activar la accion guardar en el menu
        //Obtener datos de la GUI
        QString nombre = ui->inName->text();
        int horas = ui->inHour->value();
        TipoJornada jornada;
        if(ui->inMatutino->isChecked()){   //Settear la jornada
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
            //Muestra los calculos del obrero
            ui->outResult->appendPlainText(m_control->obrero()->toString());
            //Mensaje si todo va bien
            ui->statusbar->showMessage("Calculos procesados correctamente para " + nombre, 5000);
            limpiar(); //Limpiar interfaz
        }
    }
}

void Salario::guardar()
{
    //Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos slr (*.slr");

    //Crear un objeto QFile
    QFile archivo(nombreArchivo);

    //Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear un stream de texto
        QTextStream salida(&archivo);
        //Enviar los datos del resultado
        salida << ui->outResult->toPlainText();
        //Mostar que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 5000);
    }else{
        //Mensaje si no se pudo guardar
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
    }

    //Cerrar archivo
    archivo.close();
}

void Salario::abrir()
{
    //Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         "Abrir archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos slr (*.slr");

    //Crear un objeto QFile
    QFile archivo(nombreArchivo);

    //Abrirlo para lectura
    if(archivo.open(QFile::ReadOnly)){
        //Crear un stream de texto
        QTextStream entrada(&archivo);
        //Leer los datos del resultado
        QString datos = entrada.readAll();

        //Asignar datos al out
        ui->outResult->clear();
        ui->outResult->setPlainText(datos);

        //Mostar que todo fue bien
        ui->statusbar->showMessage("Datos leidos desde " + nombreArchivo, 5000);
    }else{
        //Mensaje si no se pudo abrir
        QMessageBox::warning(this,
                             "Abrir datos",
                             "No se pudo abrir el archivo");
    }

    //Cerrar archivo
    archivo.close();
}

void Salario::on_actionAbrir_triggered()
{
    abrir();
}

void Salario::on_actionAcerca_de_salarios_triggered()
{
    //Crear objeto de la ventana a crear
    Acerca *cuadro = new Acerca(this);

    //Enviar parametro a la ventana
    cuadro->setVersion(VERSION);

    //ejecuta el cuadro en modo modal (mientras no se cierre la ventana no continua el codigo)
    cuadro->exec();
}

