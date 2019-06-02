#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QDialog>
#include <QPushButton>
#include <QtWidgets>
#include <QCheckBox>

class FenPrincipale : public QWidget
{
    Q_OBJECT

public:
    FenPrincipale();
    QString getNom(){return nom->text();}


public slots:
    void genereCode();
    void popUp();
    void modifLine();

private:
    QLineEdit *nom;
    QLineEdit *lineNom;
    QLineEdit *classe_mere;

    QCheckBox *option1; // inclusion header
    QCheckBox *option2; // contrcuteur
    QCheckBox *option3; //Destructeur
    QPushButton *ajouterAttribut;
    QVector<QString> tabNomAttribut;
    QVector<QString> tabTypeAttribut;


    QGroupBox *groupe_commentaire;

    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *text;
    QCheckBox *gpl;

    QPushButton *m_generer;
    QPushButton *m_quitter;
};

#endif // FENPRINCIPALE_H
