#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class FenCodeGenere : public QDialog
{
    Q_OBJECT

public:
    FenCodeGenere(const QWidget *parent, QString &code);
    virtual ~FenCodeGenere();

private:
    QTextEdit *codeGen;
    QPushButton *m_fermer;
};

#endif // FENCODEGENERE_H
