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
    ~FenPrincipale();
public slots:
    void genereCode();
    void genereCode2();

private:
    QLineEdit *nom;
    QLineEdit *classe_mere;

    QCheckBox *option1;
    QCheckBox *option2;
    QCheckBox *option3;

    QGroupBox *groupe_commentaire;

    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *text;

    QPushButton *m_generer;
    QPushButton *m_quitter;
};

#endif // FENPRINCIPALE_H
