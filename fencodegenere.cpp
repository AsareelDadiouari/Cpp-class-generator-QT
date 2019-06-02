#include "fencodegenere.h"
#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include <QMainWindow>

FenCodeGenere::FenCodeGenere(QString &codeH,QString &codeCpp, QString nomFichier ,QWidget *parent)
{
    setFixedSize(480, 480);
    tab = new QTabWidget(this);
    m_nom_fichier = nomFichier;

    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;

    setWindowTitle(tr("Classe"));
    setWindowIcon(QIcon("image.png"));

    codeGen_header = new QTextEdit;
    codeGen_header->setFont(QFont("Courier"));
    codeGen_header->setText(codeH);
    codeGen_header->setReadOnly(true);

    codeGen_cpp = new QTextEdit;
    codeGen_cpp->setFont(QFont("Courier"));
    codeGen_cpp->setText(codeCpp);
    codeGen_cpp->setReadOnly(true);

    m_fermer =new QPushButton(tr("Fermer"));
    m_enregistrer = new QPushButton(tr("Enregistrer"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(codeGen_header);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(codeGen_cpp);

    page1->setLayout(layout);
    page2->setLayout(layout2);

    tab->addTab(page1, nomFichier + ".h");
    tab->addTab(page2, nomFichier + ".cpp");

    QHBoxLayout *hBox = new QHBoxLayout;
    hBox->addWidget(m_enregistrer);
    hBox->addWidget(m_fermer);
    hBox->setAlignment(Qt::AlignRight);

    QVBoxLayout *pagesLayout = new QVBoxLayout;
    pagesLayout->addWidget(tab);
    pagesLayout->addLayout(hBox);

    setLayout(pagesLayout);

    connect(m_fermer, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_enregistrer, SIGNAL(clicked()), this, SLOT(enregistrer()));

    //enregistrer(codeH);
}

void FenCodeGenere::enregistrer()
{
    QString fichier = QFileDialog::getSaveFileName(this, tr("Enregistrer Header"), m_nom_fichier , "(*.hpp)");

    QFile file(fichier);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << codeGen_header->toPlainText() << endl;
    }

    file.close();

    QString fichier2 = QFileDialog::getSaveFileName(this, tr("Enregistrer Cpp"),  m_nom_fichier , "(*.cpp)");

    QFile file2(fichier2);
    if (file2.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file2);
        stream << codeGen_cpp->toPlainText() << endl;
    }

    file2.close();

    if(file.exists())
        QMessageBox::information(this, tr("Enregistrement"), tr("Fichiers Enregistrés"));
    else
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur d'enregistrement !"));
}

//No need for destructor apprently in Qt



