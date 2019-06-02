#include "fenprincipale.h"
#include "fencodegenere.h"
#include "ui_fenprincipale.h"
#include <QMainWindow>
#include <QtWidgets>

FenPrincipale::FenPrincipale()
{

    setWindowIcon(QIcon("icone.png"));
    setWindowTitle("ClassGen C++");

    QGroupBox *groupBox1 = new QGroupBox(tr("Définition de la classe"), this);

    nom = new QLineEdit;
    lineNom = new QLineEdit;
    lineNom->setReadOnly(true);
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::gray);
    lineNom->setPalette(palette);

    classe_mere = new QLineEdit;
    classe_mere->setInputMask(QString("AAAAAAAAAAAAAAAAAA"));

    QFormLayout *form = new QFormLayout;
    form->addRow(tr("Nom :"), nom);
    form->addRow(tr("Classe mère :") ,classe_mere);

    QGridLayout * grid = new QGridLayout;

    grid->addLayout(form, 0, 0);
    grid->addWidget(lineNom, 1, 0);

    groupBox1->setLayout(grid);

    QGroupBox *groupBox2 = new QGroupBox(tr("Options"), this);
    option1 = new QCheckBox(tr("Protégér le header contre les inclusions multiples"));
    option2 = new QCheckBox(tr("Générer un contructeur par défaut"));
    option3 = new QCheckBox(tr("Générer un destructeur"));
    ajouterAttribut = new QPushButton(tr("Ajouter Attribut"));

    option1->setChecked(true);
    option2->setChecked(true);

    QVBoxLayout *vBox1 = new QVBoxLayout;
    vBox1->addWidget(option1);
    vBox1->addWidget(option2);
    vBox1->addWidget(option3);
    vBox1->addWidget(ajouterAttribut);

    groupBox2->setLayout(vBox1);

    groupe_commentaire = new QGroupBox(tr("Ajouter des commentaires") ,this);
    groupe_commentaire->setCheckable(true);
    groupe_commentaire->setChecked(false);


    auteur = new QLineEdit;
    date = new QDateEdit;
    gpl = new QCheckBox(tr("Ajouter La GPL"));
    date->setDisplayFormat(QString("dd/MM/yyyy"));
    date->setMaximumDate(QDate(2019, 12, 31));
    date->setDate(QDate(2010, 01, 01));
    date->setAccelerated(true);
    text = new QTextEdit;

    QFormLayout *form2 = new QFormLayout;
    form2->addRow(tr("Auteur :"), auteur);
    form2->addRow(tr("Date de création :"), date);
    form2->addRow(tr("Rôle de la classe :"), text);

    QVBoxLayout *vBox2 = new QVBoxLayout;
    vBox2->addLayout(form2);
    vBox2->addWidget(gpl);

    groupe_commentaire->setLayout(vBox2);


    m_quitter = new QPushButton(tr("Quitter"));
    m_generer = new QPushButton(tr("Générer"));

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

    QShortcut *shortcut = new QShortcut(QKeySequence("RETURN"), this); // Connecter la touche entrer au bouton
    // de generation du code

    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(genereCode()));
    connect(nom, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(modifLine()));
    QObject::connect(m_generer, SIGNAL(clicked()), this, SLOT(genereCode()));
    connect(ajouterAttribut, SIGNAL(clicked()), this, SLOT(popUp()));
    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

//No need for destructor apprently in QT

void FenPrincipale::genereCode()
{
    if(nom->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur Nom de classe Vide !"));
        return ;
    }

    QString codeHeader;

    /***************************Code du header*************************************/
    if(groupe_commentaire->isChecked()==true)
    {
        if(!auteur->text().isEmpty())
            codeHeader += tr("/*\nAuteur ") + auteur->text() + "\n";
        else
            codeHeader +="\n";

        codeHeader +=tr("\nDate de création : ") + date->date().toString() +"\n";

        if(gpl->isChecked() == true)
        {
            codeHeader += "\nThis program is free software: you can redistribute it and/or modify\n" ;
            codeHeader += "it under the terms of the GNU General Public License as published by\n";
            codeHeader += "the Free Software Foundation, either version 3 of the License, or\n";
            codeHeader += "(at your option) any later version.\n";

            codeHeader += "This program is distributed in the hope that it will be useful,\n";
            codeHeader += "but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
            codeHeader += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
            codeHeader += "GNU General Public License for more details.\n";

            codeHeader += "You should have received a copy of the GNU General Public License\n";
            codeHeader += "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";
        }

        codeHeader += text->toPlainText() + "\n*/\n";
    }

    if(option1->isChecked()==true)
    {
        codeHeader += "#ifndef " + nom->text().toUpper() +"_H\n";
        codeHeader += "#define " + nom->text().toUpper() +"_H\n";
    }

    codeHeader += "\nclass " + nom->text() + " : ";

    if(!classe_mere->text().isEmpty())
    {
        codeHeader += "public " + classe_mere->text() + "\n";
    }

    codeHeader +="{\n";
    codeHeader +="public :\n";

    if(option2->isChecked()==true)
        codeHeader +="\t"+ nom->text() + "();\n";

    if(option3->isChecked()==true)
        codeHeader += "\t~" + nom->text() + "();\n";
    else
        codeHeader += "\n";

    codeHeader +="private :\n\n";
    if(tabTypeAttribut.size()!=0)
    {
        for(int i=0; i<tabTypeAttribut.size(); i++)
        {
            codeHeader += "   " + tabTypeAttribut[i] + "   " + tabNomAttribut[i] +";\n";
        }
    }
    codeHeader +="\n};\n";

    if(option1->isChecked()==true)
        codeHeader += "\n#endif\n";

    /***************************Code du header*************************************/

    /***************************Code du cpp*************************************/

    QString codeCpp;
    codeCpp +="#include <" + nom->text() + ".h>\n";
    codeCpp += "#include <iostream.h>\n\n";

    if(option2->isChecked()==true)
    {
        codeCpp += nom->text() + "::" + nom->text() + "()\n";
        codeCpp +="{\n\n\n}\n";
    }

    if(option3->isChecked()==true)
    {
        codeCpp +=nom->text() +"::~" + nom->text() + "(){\n";

        if(tabNomAttribut.size()!=0)
        {
            for(int i=0; i<tabNomAttribut.size(); i++)
            {
                codeCpp +="    delete   " + tabNomAttribut[i] + ";\n";
            }
        }
        codeCpp += "}\n";
    }
    /***************************Code du cpp*************************************/

    FenCodeGenere *z = new FenCodeGenere(codeHeader, codeCpp, nom->text(),this);
    z->exec();
}

void FenPrincipale::modifLine()
{

    lineNom->setText(QString("HEADER_") + nom->text().toUpper());

    if(nom->text().isEmpty()==true)
        lineNom->clear();
}

void FenPrincipale::popUp()
{
    QDialog dialogBox;
    dialogBox.setWindowTitle(tr("Attribut"));
    dialogBox.setWindowIcon(QIcon("attribut.png"));

    QLineEdit *lineNom = new QLineEdit;
    QLineEdit *lineType = new QLineEdit;
    QPushButton *valider = new QPushButton(tr("Valider"));

    QFormLayout *form = new QFormLayout;
    form->addRow(tr("Nom Attribut"), lineNom);
    form->addRow(tr("Type Attribut"), lineType);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addLayout(form);
    layout->addWidget(valider);

    QShortcut *shortcut = new QShortcut(QKeySequence("RETURN"), this);
    connect(shortcut, SIGNAL(activated()), &dialogBox, SLOT(accept()));
    connect(valider, SIGNAL(clicked()), &dialogBox, SLOT(accept()));

    dialogBox.setLayout(layout);
    dialogBox.exec();

    tabNomAttribut.push_back(lineNom->text());
    tabTypeAttribut.push_back(lineType->text());
}




