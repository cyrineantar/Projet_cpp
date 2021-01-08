QT       += core sql gui texttospeech widgets multimedia serialport multimediawidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achat.cpp \
    arduino.cpp \
    cartefidelite.cpp \
    chat_employe.cpp \
    chat_server.cpp \
    client.cpp \
    conge.cpp \
    connexion.cpp \
    employe.cpp \
    espace_client.cpp \
    espace_fournisseur.cpp \
    espace_livraison.cpp \
    espace_machine.cpp \
    espaceemploye.cpp \
    exportexcelobject.cpp \
    fournisseur.cpp \
    livraison.cpp \
    machine.cpp \
    main.cpp \
    mainwindow.cpp \
    matierepremiere.cpp \
    produit.cpp \
    reclamation.cpp \
    stock.cpp \
    vente.cpp

HEADERS += \
    achat.h \
    arduino.h \
    cartefidelite.h \
    chat_employe.h \
    chat_server.h \
    client.h \
    conge.h \
    connexion.h \
    employe.h \
    espace_client.h \
    espace_fournisseur.h \
    espace_livraison.h \
    espace_machine.h \
    espaceemploye.h \
    exportexcelobject.h \
    fournisseur.h \
    livraison.h \
    machine.h \
    mainwindow.h \
    matierepremiere.h \
    produit.h \
    reclamation.h \
    stock.h \
    vente.h

FORMS += \
    chat_employe.ui \
    chat_server.ui \
    espaceEmploye.ui \
    espace_client.ui \
    espace_fournisseur.ui \
    espace_livraison.ui \
    espace_machine.ui \
    mainwindow.ui \
    stock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    res.qrc \
    ressource.qrc \
    ressource.qrc

DISTFILES += \
    stylesheet/Combinear.qss
