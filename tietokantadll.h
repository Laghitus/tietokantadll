#ifndef TIETOKANTADLL_H
#define TIETOKANTADLL_H

#include "tietokantadll_global.h"
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QObject>
#include <QDateTime>
#include <QtWidgets>



class TIETOKANTADLLSHARED_EXPORT TietokantaDLL:public QObject
{
    Q_OBJECT

public:
    TietokantaDLL();

    static bool TIETOKANTADLLSHARED_EXPORT createConnection();

    void TIETOKANTADLLSHARED_EXPORT connectToDatabase();

    QSqlTableModel *tietokanta;

    QTableView *createView;

    void TIETOKANTADLLSHARED_EXPORT tietokantaLogin(QString parametriKortti,QString parametriTunnusluku);

    void TIETOKANTADLLSHARED_EXPORT nosto(float parametriNostettavaSumma);

    bool TIETOKANTADLLSHARED_EXPORT vertaaNumeroita();

    void TIETOKANTADLLSHARED_EXPORT naytaSaldo();

    float TIETOKANTADLLSHARED_EXPORT returnSaldo();

    void TIETOKANTADLLSHARED_EXPORT printLog();

    // void createView();

    void updateLog();

    void getTili();

    QString kortinnumero;
    bool nostonTarkistus();
    void nostoSuoritus();

    QString nostoEpaonnistui();

    QStringList returnList();



    void currentDateTime();

    QString as;
    QString b;
    QStringList list;





private:
    // QString kortinnumero;
    QSqlQuery tietokanta_nosto;
    // QString *kortinnumero;
    QString kayttajanSalasana;
    QString kortti_id;
    QString tunnusluku;
    float saldo;
    float nostettavaSumma;
    float muutettavaSumma;
    int tili_id;



public slots:

signals:
    void failedsignal();








};






#endif // TIETOKANTADLL_H
