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
    lineNom = new QLineEdit;
    lineNom->setReadOnly(true);
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::gray);
    lineNom->setPalette(palette);

    classe_mere = new QLineEdit;
    classe_mere->setInputMask(QString("AAAAAAAAAAAAAAAAAA"));

    QFormLayout *form = new QFormLayout;
    form->addRow("Nom :", nom);
    form->addRow("Classe mère :" ,classe_mere);

    QGridLayout * grid = new QGridLayout;

    grid->addLayout(form, 0, 0);
    grid->addWidget(lineNom, 1, 0);

    groupBox1->setLayout(grid);

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
    gpl = new QCheckBox("Ajouter La GPL");
    list = new QListWidget;
    QListWidgetItem *item1 = new QListWidgetItem;
    date->setDisplayFormat(QString("dd/MM/yyyy"));
    date->setMaximumDate(QDate(2019, 12, 31));
    date->setDate(QDate(2010, 01, 01));
    date->setAccelerated(true);
    text = new QTextEdit;

    QFormLayout *form2 = new QFormLayout;
    form2->addRow("Auteur :", auteur);
    form2->addRow("Date de création :", date);
    form2->addRow("Rôle de la classe :", text);

    QVBoxLayout *vBox2 = new QVBoxLayout;
    vBox2->addLayout(form2);
    vBox2->addWidget(gpl);
    vBox2->addWidget(list);

    groupe_commentaire->setLayout(vBox2);


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

    connect(nom, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(modifLine()));
    QObject::connect(m_generer, SIGNAL(clicked()), this, SLOT(genereCode()));
    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

FenPrincipale::~FenPrincipale()
{
    delete nom;
    delete lineNom;
    delete classe_mere;
    delete option1;
    delete option2;
    delete option3;
    delete groupe_commentaire;
    delete gpl;
    delete auteur;
    delete date;
    delete text;
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

        code +="\nDate de création : " + date->date().toString() +"\n";

        if(gpl->isChecked() == true)
        {
            code += "\nThis program is free software: you can redistribute it and/or modify\n" ;
            code += "it under the terms of the GNU General Public License as published by\n";
            code += "the Free Software Foundation, either version 3 of the License, or\n";
            code += "(at your option) any later version.\n";

            code += "This program is distributed in the hope that it will be useful,\n";
            code += "but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
            code += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
            code += "GNU General Public License for more details.\n";

            code += "You should have received a copy of the GNU General Public License\n";
            code += "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";
        }

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

    if(option2->isChecked()==true)
        code +="\t"+ nom->text() + "();\n";

    if(option3->isChecked()==true)
        code += "\t~" + nom->text() + "();\n";
    else
        code += "\n";

    code +="private :\n\n";
    code +="};\n";

    if(option1->isChecked()==true)
        code += "\n#endif\n";

    FenCodeGenere *z = new FenCodeGenere(this, code);
    z->exec();
}

void FenPrincipale::modifLine()
{

    lineNom->setText(QString("HEADER_") + nom->text().toUpper());

    if(nom->text().isEmpty()==true)
        lineNom->clear();
}


