#include "main.h"
#include "../models/p_core.h"
#include "c_mainwindow.h"
#include "../views/v_mainwindow.h"
#include "../views/v_littlenote.h"
#include "ui_v_mainwindow.h"
#include "ui_v_articleform.h"
#include "ui_v_multimediaform.h"
#include "ui_v_taskform.h"
#include "ui_v_multiplenotes.h"

C_Mainwindow::C_Mainwindow(QApplication *q) {

    // Initialisation des models et de la view
    qapp = q;
    view = new V_Mainwindow(0,this);
    app = new PluriNotes;

    refreshActiveNotes();
    createActions();
}

void C_Mainwindow::createActions()
{
    view->connect(view->getUi()->actionQuit, SIGNAL(triggered()), qapp, SLOT(quit()) );
    view->connect(view->getUi()->actionArticle, SIGNAL(triggered()), view, SLOT(openNewArticle()));
    view->connect(view->getUi()->actionMultimedia,SIGNAL(triggered()),view,SLOT(openNewMultimedia()));
    view->connect(view->getUi()->actionTask,SIGNAL(triggered()),view,SLOT(openNewTask()));
}

void C_Mainwindow::refreshActiveNotes() {
    std::vector<Note*> *notes = app->getActiveNotesManager()->getTab();
    unsigned int row1 = 0;
    unsigned int column1 = 0;
    unsigned int row2 = 0;
    unsigned int column2 = 0;

    QSignalMapper* signalMapper = new QSignalMapper(view);
    view->connect(signalMapper, SIGNAL(mapped(QString)),view, SLOT(refreshCentralNote(QString)));

    for(unsigned int i = 0; i < notes->size(); i++) {
        Note* note = notes->at(i);
        V_Littlenote* ln;
        V_Littletask* la;

        if( typeid(*note) == typeid(Article) ) {
            Article* a = new Article( dynamic_cast<Article&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),article);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row1,column1);

            if( column1 != 0 && column1 % 2 == 0 )
            {
                row1++;
                column1=0;
            } else column1++;
        }

        if( typeid(*note) == typeid(Multimedia) ) {
            Multimedia* a = new Multimedia( dynamic_cast<Multimedia&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),multimedia);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row1,column1);

            if( column1 != 0 && column1 % 2 == 0 )
            {
                row1++;
                column1=0;
            } else column1++;
        }

        if( typeid(*note) == typeid(Task) ) {
            Task* a = new Task( dynamic_cast<Task&>(*note) );
            la = new V_Littletask(this->getView()->getTasks()->getContainer(),a->getId());
            view->getTasks()->getGridLayout()->addWidget(la,row2,column2);

            if( column2 != 0 && column2 % 2 == 0 )
            {
                row2++;
                column2=0;
            } else column2++;

        }

        signalMapper->setMapping(ln, note->getId());
        view->connect(ln, SIGNAL(clicked()), signalMapper, SLOT(map()));

        //view->connect(ln,SIGNAL(clicked()),view,SLOT(refreshCentralNote()));

    }
}



void C_Mainwindow::saveNewArticle(Article *a) {
    // TODO:Vérifier s'il n'y a pas de références dans le texte de l'article vers d'autres notes

    app->getActiveNotesManager()->getTab()->push_back(a);
    app->getXMLManager()->insertIntoArticle(a);
    refreshActiveNotes();
}

void C_Mainwindow::saveNewMultimedia(Multimedia *m) {

    app->getActiveNotesManager()->getTab()->push_back(m);
    //app->getXMLManager()->insertIntoMultiMedia(m);
    refreshActiveNotes();
}

void C_Mainwindow::saveNewTask(Task *t) {

    app->getActiveNotesManager()->getTab()->push_back(t);
    //app->getXMLManager()->insertIntoTask(t);
    refreshActiveNotes();
}
