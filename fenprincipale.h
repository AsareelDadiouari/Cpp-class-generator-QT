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
    virtual ~FenPrincipale();
public slots:
    void genereCode();
    void modifLine();

private:
    QLineEdit *nom;
    QLineEdit *lineNom;
    QLineEdit *classe_mere;

    QCheckBox *option1;
    QCheckBox *option2;
    QCheckBox *option3;

    QGroupBox *groupe_commentaire;


    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *text;
    QCheckBox *gpl;
    QListWidget *list;

    QPushButton *m_generer;
    QPushButton *m_quitter;
};

#endif // FENPRINCIPALE_H
