#include "tietokantadll.h"

//testi




TietokantaDLL::TietokantaDLL()
{
    //kortinnumero = new QString;




    tietokanta = new QSqlTableModel;
}


void TietokantaDLL::connectToDatabase()
{




    QString name;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t6kuve00");

    db.setUserName("t6kuve00");

    db.setPassword("gbakk6UmbWBaBKZf");

    if (!db.open()) {
        qDebug() << "Database error occurred";

    }
    else
    {
        qDebug() << "Database OK";

    }
    //    tietokanta->setTable("tili");

    //    tietokanta->select();

    //    QString tili_id = tietokanta->data(tietokanta->index(0,0)).toString();
    //    QString saldo = tietokanta->data(tietokanta->index(0,1)).toString();
    //    QString kortti_id = tietokanta->data(tietokanta->index(0,2)).toString();
    //    QString asiakas_id = tietokanta->data(tietokanta->index(0,3)).toString();

    //    qDebug() <<tili_id;
    //    qDebug() <<saldo;
    //    qDebug() <<kortti_id;
    //    qDebug() <<asiakas_id;

}

void TietokantaDLL::tietokantaLogin(QString parametriKortti,QString parametriTunnusluku)
{
    kortinnumero = parametriKortti;
    kayttajanSalasana = parametriTunnusluku;
    qDebug()<<kortinnumero;
    qDebug()<<kayttajanSalasana;

    tietokanta = new QSqlTableModel;
    tietokanta->setTable("kortti");
    tietokanta->setFilter(QString("kortti_id = '%1'").arg(kortinnumero));
    //tietokanta->setFilter("tunnusluku = '1234'");

    tietokanta->select();

    //    QString tili_id = tietokanta->data(tietokanta->index(0,0)).toString();
    //    QString saldo = tietokanta->data(tietokanta->index(0,1)).toString();
    //    QString kortti_id = tietokanta->data(tietokanta->index(0,2)).toString();
    //    QString asiakas_id = tietokanta->data(tietokanta->index(0,3)).toString();


    //        qDebug() <<tili_id;
    //        qDebug() <<saldo;
    //        qDebug() <<kortti_id;
    //        qDebug() <<asiakas_id;

    kortti_id = tietokanta->data(tietokanta->index(0,0)).toString();
    tunnusluku = tietokanta->data(tietokanta->index(0,1)).toString();

    qDebug() <<kortti_id;
    qDebug() <<tunnusluku;

    this->vertaaNumeroita();

}

void TietokantaDLL::printLog()
{
    // QString filterTili = "10005";
    QString filterTili = QString::number(tili_id);
    tietokanta->setTable("tapahtumat");
    tietokanta->setFilter(QString("tili_id = '%1'").arg(filterTili));


    tietokanta->select();
  //qDebug()<<  tietokanta->rowCount();
QString tulostaTili;
QString summa;
QString paivamaara;
int i;
    for (i=0;i < tietokanta->rowCount(); ++i)

    {
     tulostaTili= tietokanta->data(tietokanta->index(i,0)).toString();
    summa = tietokanta->data(tietokanta->index(i,1)).toString();
   paivamaara  = tietokanta->data(tietokanta->index(i,2)).toString();

    list <<tulostaTili <<summa <<paivamaara;
    }





//    qDebug() <<tulostaTili;
//    qDebug() <<summa;
//    qDebug() <<paivamaara;
   //qDebug()<< list;

//    for (int i = 0; i < tietokanta->rowCount(); ++i) {
//         qDebug() << tietokanta->record(i);
//    }

    //      tietokanta->setHeaderData(0, Qt::Horizontal, QObject::tr("tili_id"));
    //      tietokanta->setHeaderData(1, Qt::Horizontal, QObject::tr("summa"));
    //      tietokanta->setHeaderData(2, Qt::Horizontal, QObject::tr("paivamaara"));

    //malli->setQuery(QString("SELECT * FROM tapahtumat WHERE tili_id = '%1' ORDER BY paivamaara DESC").arg(filterTili));





}

QStringList TietokantaDLL::returnList()
{
   // qDebug()<< list;
    return list;
}




//QTableView *createView(QSqlTableModel *model, const QString &title = "")
//{
//    QTableView *view = new QTableView;
//    view->setModel(model);
//    view->setWindowTitle(title);
//    return view;
//}
////-----------------------------------
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    if (!createConnection())
//        return 1;

//    QSqlTableModel model;

//    getValuesFromModel(&model);
////TEHTÄVÄ osa 3-------------------------------
//    QTableView *view1 = createView(&model, QObject::tr("Table Model (View 1)"));
//    QTableView *view2 = createView(&model, QObject::tr("Table Model (View 2)"));

//    view1->show();
//    view2->move(view1->x() + view1->width() + 20, view1->y());
//    view2->show();

bool TietokantaDLL::vertaaNumeroita()
{
    if (kortinnumero == kortti_id && kayttajanSalasana == tunnusluku)
    {
        qDebug()<<"totta";
        return true;

    }

    else
    {
        qDebug()<<"ei";
        return false;
    }

}

void TietokantaDLL::nosto(float parametriNostettavaSumma)
{
    qDebug()<<kortinnumero;
    QSqlQuery tietokanta_nosto;

    tietokanta_nosto.prepare("SELECT saldo FROM tili WHERE kortti_id = :kortinnumero");
    tietokanta_nosto.bindValue(":kortinnumero", kortinnumero);
    tietokanta_nosto.exec();

    while (tietokanta_nosto.next()) {
        saldo = tietokanta_nosto.value(0).toFloat();
        qDebug() << saldo;
    }

    nostettavaSumma = parametriNostettavaSumma;
    qDebug()<<nostettavaSumma;
    this->nostoSuoritus();



    //    tietokanta_nosto.exec("UPDATE tili SET saldo = 20 WHERE kortti_id = :kortinnumero");
    //    qDebug() <<"perse";


}

bool TietokantaDLL::nostonTarkistus()
{

    if (nostettavaSumma>saldo)
    {
        qDebug()<<"ei toimi";
        return false;

    }
    else
    {
        qDebug()<<"toimii";

        return true;

    }


}


void TietokantaDLL::nostoSuoritus()
{
    qDebug()<<"täällä";
    QSqlQuery tietokanta_nosto;

    if (nostonTarkistus() == true)
    {
        muutettavaSumma = saldo - nostettavaSumma;
        qDebug()<<muutettavaSumma;
        tietokanta_nosto.prepare("UPDATE tili SET saldo = :muutettavaSumma WHERE kortti_id = :kortinnumero");
        tietokanta_nosto.bindValue(":muutettavaSumma",muutettavaSumma);
        tietokanta_nosto.bindValue(":kortinnumero",kortinnumero);
        tietokanta_nosto.exec();

    }
    else emit failedsignal();



}

void TietokantaDLL::getTili()
{
    QSqlQuery tietokanta_nosto;

    tietokanta_nosto.prepare("SELECT tili_id FROM tili WHERE kortti_id = :kortinnumero");
    tietokanta_nosto.bindValue(":kortinnumero", kortinnumero);
    tietokanta_nosto.exec();

    while (tietokanta_nosto.next()) {
        tili_id = tietokanta_nosto.value(0).toInt();
        qDebug() << tili_id;
    }


}
void  TietokantaDLL::currentDateTime()
{

    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    as = a.toString(time_format);

    qDebug() << as; // print "2014-07-16  17:47:04"

    QDateTime b = QDateTime::fromString(as,time_format);
    qDebug() << b;



    // fails
    /* QDateTime aika = QDateTime::currentDateTime();
    qDebug()<< aika;
    return aika*/;
}



void TietokantaDLL::updateLog()
{
    qDebug() << "hohoo";

    QSqlQuery tietokanta_nosto;
    nostettavaSumma = 20;
    qDebug() << tili_id;
    qDebug() <<nostettavaSumma;
    qDebug() << as;
    // qDebug() << b;

    tietokanta_nosto.prepare("INSERT INTO tapahtumat (tili_id, summa, paivamaara)"
                             "VALUES (:tili_id, :summa, :paivamaara)");
    tietokanta_nosto.bindValue(":tili_id",tili_id);
    tietokanta_nosto.bindValue(":summa",nostettavaSumma);
    tietokanta_nosto.bindValue(":paivamaara",as);

    tietokanta_nosto.exec();

    qDebug() << "hahaaa";
}

QString TietokantaDLL::nostoEpaonnistui()
{
    QString failed = "Nosto epäonnistui";
    return failed;
}

void TietokantaDLL::naytaSaldo()
{
    QSqlQuery tietokanta_nosto;


    tietokanta_nosto.prepare("SELECT saldo FROM tili WHERE kortti_id = :kortinnumero");
    tietokanta_nosto.bindValue(":kortinnumero", kortinnumero);
    tietokanta_nosto.exec();

    while (tietokanta_nosto.next()) {
        saldo = tietokanta_nosto.value(0).toFloat();
        qDebug() << saldo;
    }

}

float TietokantaDLL::returnSaldo()
{
    return saldo;
}





