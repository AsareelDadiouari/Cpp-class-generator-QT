#include "fencodegenere.h"
#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include <QMainWindow>

FenCodeGenere::FenCodeGenere(const QWidget *parent, QString &code)
{

    setWindowTitle("Class");
    setWindowIcon(QIcon("image.png"));
    codeGen = new QTextEdit;
    codeGen->setFont(QFont("Courier"));
    codeGen->setText(code);
    codeGen->setReadOnly(true);

    m_fermer =new QPushButton("Fermer");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(codeGen);
    layout->addWidget(m_fermer);

    setLayout(layout);
    QObject::connect(m_fermer, SIGNAL(clicked()), this, SLOT(accept()));
}

FenCodeGenere::~FenCodeGenere()
{
    delete codeGen;
    delete m_fermer;
}



