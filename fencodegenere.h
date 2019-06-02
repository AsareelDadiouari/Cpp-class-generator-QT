#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QTabWidget>

class FenCodeGenere : public QDialog
{
    Q_OBJECT

public:
    FenCodeGenere(QString &codeH, QString &codeCpp , QString nomFichier,QWidget *parent);
public slots:
    void enregistrer();

private:
    QTabWidget *tab;
    QTextEdit *codeGen_header;
    QTextEdit *codeGen_cpp;
    QString m_nom_fichier;
    QPushButton *m_fermer;
    QPushButton *m_enregistrer;
};

#endif // FENCODEGENERE_H
