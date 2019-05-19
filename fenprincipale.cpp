#include "fenprincipale.h"
#include "fencodegenere.h"
#include "ui_fenprincipale.h"
#include <QMainWindow>
#include <QtWidgets>

FenPrincipale::FenPrincipale()
{

    setWindowIcon(QIcon("icone.png"));
    setWindowTitle("ClassGen C++");

    QGroupBox *groupBox1 = new QGroupBox("Définition de la classe", this);

    nom = new QLineEdit;
    classe_mere = new QLineEdit;
    classe_mere->setInputMask(QString("AAAAAAAAAAAAAAAAAA"));

    QFormLayout *form = new QFormLayout;
    form->addRow("Nom :", nom);
    form->addRow("Classe mère :" ,classe_mere);

    groupBox1->setLayout(form);

    QGroupBox *groupBox2 = new QGroupBox("Options", this);
    option1 = new QCheckBox("Protégér le header contre les inclusions multiples");
    option2 = new QCheckBox("Générer un contructeur par défaut");
    option3 = new QCheckBox("Générer un destructeur");

    option1->setChecked(true);
    option2->setChecked(true);

    QVBoxLayout *vBox1 = new QVBoxLayout;
    vBox1->addWidget(option1);
    vBox1->addWidget(option2);
    vBox1->addWidget(option3);

    groupBox2->setLayout(vBox1);

    groupe_commentaire = new QGroupBox("Ajouter des commentaires" ,this);
    groupe_commentaire->setCheckable(true);
    groupe_commentaire->setChecked(false);


    auteur = new QLineEdit;
    date = new QDateEdit;
    date->setDisplayFormat(QString("dd/MM/yyyy"));
    date->setMaximumDate(QDate(2019, 12, 31));
    date->setDate(QDate(2010, 01, 01));
    date->setAccelerated(true);
    text = new QTextEdit;

    QFormLayout *form2 = new QFormLayout;
    form2->addRow("Auteur :", auteur);
    form2->addRow("Date de création :", date);
    form2->addRow("Rôle de la classe :", text);
    groupe_commentaire->setLayout(form2);


    m_quitter = new QPushButton("Quitter");
    m_generer = new QPushButton("Générer");

    QHBoxLayout *horizontal =new QHBoxLayout;
    horizontal->addWidget(m_generer);
    horizontal->addWidget(m_quitter);
    horizontal->setAlignment(Qt::AlignRight);

    QVBoxLayout *initiaLayout =new QVBoxLayout;

    initiaLayout->addWidget(groupBox1);
    initiaLayout->addWidget(groupBox2);
    initiaLayout->addWidget(groupe_commentaire);
    initiaLayout->addLayout(horizontal);

    this->setLayout(initiaLayout);

    QObject::connect(nom, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(genereCode2()));
    QObject::connect(m_generer, SIGNAL(clicked()), this, SLOT(genereCode()));
    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

FenPrincipale::~FenPrincipale()
{
    delete nom;
    delete classe_mere;
    QCheckBox option1;
    QCheckBox option2;
    QCheckBox option3;
    QGroupBox groupe_commentaire;
    QLineEdit auteur;
    QDateEdit date;
    QTextEdit text;
    delete m_quitter;
    delete m_generer;
}

void FenPrincipale::genereCode()
{
    if(nom->text().isEmpty())
    {
        QMessageBox::critical(this, "Warning", "Erreur Nom de classe Vide !");
        return ;
    }

    QString code;

    if(groupe_commentaire->isChecked()==true)
    {
        if(!auteur->text().isEmpty())
            code += "/*\nAuteur " + auteur->text() + "\n";
        else
            code +="\n";

        code +="\nDate de création : " + date->date().toString() +"\n\n";

        code += text->toPlainText() + "\n*/\n";
    }

    if(option1->isChecked()==true)
    {
        code += "#ifndef " + nom->text().toUpper() +"_H\n";
        code += "#define " + nom->text().toUpper() +"_H\n";
    }

    code += "\nclass " + nom->text() + " : ";

    if(!classe_mere->text().isEmpty())
    {
        code += "public " + classe_mere->text() + "\n";
    }

    code +="{\n";
    code +="public :\n";
    code +="\t"+ nom->text() + "();\n";

    if(option3->isChecked()==true)
        code += "\t~" + nom->text() + "();\n";
    else
        code += "\n";

    code +="private :\n\n";
    code +="};\n";

    code += "\n#endif\n";

    FenCodeGenere *z = new FenCodeGenere(this, code);
    z->exec();
}

void FenPrincipale::genereCode2()
{
    QString code;
    code+=nom->text();
    FenCodeGenere *z = new FenCodeGenere(this, code);
}
