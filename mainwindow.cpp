#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///mises en place du widget central:

    view = new MyGraphicsView(this);
    setCentralWidget(view);

    ///mises en place de la barre d'outils:

    CBafficherCoef = new QCheckBox("afficher coef IA");
    AcbAfficherCoef = ui->toolBar->addWidget(CBafficherCoef);
    AcbAfficherCoef->setVisible(false);

    ui->toolBar->addSeparator();

    buttonJouerIA = new QPushButton("faire jouer l'IA");
    AButtonJouerIA = ui->toolBar->addWidget(buttonJouerIA);
    AButtonJouerIA->setVisible(false);

    ui->toolBar->hide();

    //setNiveauIA(IA_NORMALE);

    QObject::connect(CBafficherCoef, SIGNAL(toggled(bool)), view, SLOT(setAfficherCoefIA(bool)) );
    QObject::connect(buttonJouerIA, SIGNAL(clicked()), view, SLOT(faireJouerIA()) );

    QObject::connect(view, SIGNAL(aChanger()), this, SLOT(afficherScore()) );
    QObject::connect(view, SIGNAL(finDuJeux()), this, SLOT(close()) );
    //gestion changement de niveau IA:
    QObject::connect(ui->actionIA_Debutant, SIGNAL(triggered()), this, SLOT(setNiveauIADebutant()));
    QObject::connect(ui->actionIA_Facile, SIGNAL(triggered()), this, SLOT(setNiveauIAFacile()));
    QObject::connect(ui->actionIA_Normal, SIGNAL(triggered()), this, SLOT(setNiveauIANormale()));
    //gestion changement de mode UI
    QObject::connect(ui->actionModeDebug, SIGNAL(triggered()), this, SLOT(setDebugMode()));
    QObject::connect(ui->actionModeNormale, SIGNAL(triggered()), this, SLOT(setNormaleMode()));
    //gestion menu Jeux
    QObject::connect(ui->actionNouvelle_Partie,SIGNAL(triggered()), view, SLOT(nouvellePartie()));
}

MainWindow::~MainWindow()
{
    delete view;
    delete ui;
}

void MainWindow::setModeToolBox(int mode)
{
    if(mode == UI_MODE_NORMALE)
    {
        //CBafficherCoef->setChecked(false);
        AcbAfficherCoef->setVisible(false);
        //AcbJeuxAutoIA->setVisible(false);
        AButtonJouerIA->setVisible(false);
        ui->actionModeDebug->setChecked(false);
        ui->actionModeNormale->setChecked(true);
        ui->toolBar->hide();
    }
    else
    {
        AcbAfficherCoef->setVisible(true);
        AButtonJouerIA->setVisible(true);
        //AcbJeuxAutoIA->setVisible(true);
        //AcbJeuxAutoIA->setChecked(true);
        ui->actionModeDebug->setChecked(true);
        ui->actionModeNormale->setChecked(false);
        ui->toolBar->show();
    }
}

void MainWindow::afficherScore()
{
    ui->statusBar->showMessage("vert: "+QString::number(view->nbrJetons(1))+" rouge: "+QString::number( view->nbrJetons(2)),0);
}

//void MainWindow::setNiveauIA(int nivIA)
//{
//    view->setNiveauIA(nivIA);
//    ui->actionIA_Debutant->setChecked(false);
//    ui->actionIA_Facile->setChecked(false);
//    ui->actionIA_Normal->setChecked(false);

//    switch (nivIA) {
//    case IA_DEBUTANT:
//        ui->actionIA_Debutant->setChecked(true);
//        break;
//    case IA_FACILE:
//        ui->actionIA_Facile->setChecked(true);
//        break;
//    case IA_NORMALE:
//        ui->actionIA_Normal->setChecked(true);
//        break;
//    default:
//        ui->actionIA_Normal->setChecked(true);
//        view->setNiveauIA(IA_NORMALE);
//        break;
//    }
//}

//void MainWindow::setNiveauIADebutant(){
//    setNiveauIA(IA_DEBUTANT);
//}
//void MainWindow::setNiveauIAFacile(){
//    setNiveauIA(IA_FACILE);
//}

//void MainWindow::setNiveauIANormale(){
//    setNiveauIA(IA_NORMALE);
//}

//void MainWindow::setDebugMode(){
//    setModeToolBox(UI_MODE_DEBUG);
//    view->setModeJeuxIA(UI_MODE_DEBUG);
//}
void MainWindow::setNormaleMode(){
    setModeToolBox(UI_MODE_NORMALE);
    //view->setModeJeuxIA(UI_MODE_NORMALE);
}

