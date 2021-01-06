#include "client.h"

Client::Client()
{
    nomEntreprise="";
    description="";
    matriculeFiscale="";
    Email="nomEntreprise@gmail.com";
    adresse="";
    ville="";
    codePostal=0;
    numTel="";
    numFax="";

}

Client::Client(QString nom,QString desc,QString mf,QString mail,QString ad,QString ville,int cp,QString tel,QString fax)
{
    nomEntreprise=nom;
    description=desc;
    matriculeFiscale=mf;
    Email=mail;
    adresse=ad;
    this->ville=ville;
    codePostal=cp;
    numTel=tel;
    numFax=fax;

}




QSqlQueryModel * Client::afficher(){

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM CLIENT");

    return modal;

}



bool Client::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO CLIENT (NOM_ENTREPRISE,DESCRIPTION,MATRICULE_FISCALE,EMAIL,ADRESSE,VILLE,CODE_POSTAL,TEL,FAX) "
                        "VALUES (:nom_entreprise, :description, :matricule_fiscale,:email,:adresse,:ville,:code_postale,:tel,:fax)");
    query.bindValue(":nom_entreprise",nomEntreprise );
    query.bindValue(":description",description); //remplir la valeur d'une maniere securisée
    query.bindValue(":matricule_fiscale", matriculeFiscale);
    query.bindValue(":email", Email);
    query.bindValue(":adresse",adresse);
    query.bindValue(":ville",ville);
    query.bindValue(":code_postale",codePostal);
    query.bindValue(":tel",numTel);
    query.bindValue(":fax",numFax);


    return    query.exec();

}


bool Client::modifier(){

    QSqlQuery query;


    query.prepare("UPDATE CLIENT SET NOM_ENTREPRISE= :nom_entreprise , DESCRIPTION= :description, MATRICULE_FISCALE= :matricule_fiscale"
                  ",EMAIL= :email , ADRESSE= :adresse , VILLE= :ville , CODE_POSTAL= :code_postale ,TEL= :tel , FAX= :fax"
                  "where MATRICULE_FISCALE= :matricule_fiscale");
    query.bindValue(":nom_entreprise",nomEntreprise );
    query.bindValue(":description",description); //remplir la valeur d'une maniere securisée
    query.bindValue(":matricule_fiscale", matriculeFiscale);
    query.bindValue(":email", Email);
    query.bindValue(":adresse",adresse);
    query.bindValue(":ville",ville);
    query.bindValue(":code_postale",codePostal);
    query.bindValue(":tel",numTel);
    query.bindValue(":fax",numFax);

    return    query.exec();


}




bool Client::supprimer (QString mf_produitSelectionne)
{
    QSqlQuery query;
    query.prepare("Delete from Client where matricule_fiscale = :matriculeFiscale");
    query.bindValue(":matriculeFiscale",mf_produitSelectionne);
    return    query.exec();


}
