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
    refreshTask();
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
    unsigned int row = 0;
    unsigned int column = 0;

    // Remise à 0 du GridLayout
    QLayoutItem* item;
    while ( ( item = view->getActiveNotes()->getGridLayout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    QSignalMapper* signalMapper = new QSignalMapper(view);
    view->connect(signalMapper, SIGNAL(mapped(QString)),view, SLOT(refreshCentralNote(QString)));

    for(unsigned int i = 0; i < notes->size(); i++) {
        Note* note = notes->at(i);

        V_Littlenote* ln;

        if( typeid(*note) == typeid(Article) ) {
            Article* a = new Article( dynamic_cast<Article&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),article);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row,column);

            if( column != 0 && column % 2 == 0 )
            {
                row++;
                column=0;
            } else column++;

            signalMapper->setMapping(ln, note->getId());
            view->connect(ln, SIGNAL(clicked()), signalMapper, SLOT(map()));
        }

        if( typeid(*note) == typeid(Multimedia) ) {
            Multimedia* a = new Multimedia( dynamic_cast<Multimedia&>(*note) );
            ln = new V_Littlenote(this->getView()->getActiveNotes()->getContainer(),a->getId(),multimedia);
            view->getActiveNotes()->getGridLayout()->addWidget(ln,row,column);

            if( column != 0 && column % 2 == 0 )
            {
                row++;
                column=0;
            } else column++;
        }

            signalMapper->setMapping(ln, note->getId());
            view->connect(ln, SIGNAL(clicked()), signalMapper, SLOT(map()));
        }
    }

void C_Mainwindow::refreshTask()
{
    std::vector<Note*> *notes = app->getActiveNotesManager()->getTab();
    unsigned int row = 0;
    unsigned int column = 0;

    QSignalMapper* signalMapper = new QSignalMapper(view);
    view->connect(signalMapper, SIGNAL(mapped(QString)),view, SLOT(refreshCentralNote(QString)));

    std::vector<Note*> *tasks = new std::vector<Note*>;;

    //Recupération de toutes les taches
    for (unsigned int i = 0; i < notes->size(); i++)
    {
        Note* note = notes->at(i);

        if(typeid(*note) == typeid(Task))
        {
            tasks->push_back(note);
        }
    }

    //tri des taches

    for (unsigned int i = 0; i < tasks->size(); i++)
    {
        Note* task = tasks->at(i);
        Task* a = new Task( dynamic_cast<Task&>(*task) );

        unsigned int max, indice = 0;

        Note* tmp;

        //initialisation
        max = a->getPriority();
        indice = i;

        for(unsigned j = i; j < tasks->size(); j++)
        {
            Note* task2 = tasks->at(j);
            Task* b = new Task( dynamic_cast<Task&>(*task2) );

            //recupération du maximum
            if( max < b->getPriority())
            {
                max = b->getPriority();
                indice = j;
            }
         }
        if(i!= indice)
        {
            tmp = tasks->at(i);
            tasks->at(i) = tasks->at(indice);
            tasks->at(indice) = tmp;
        }
    }

    for(unsigned int i = 0; i < tasks->size(); i++) {
        Note* task = tasks->at(i);
        V_Littletask* la;
        Task* a = new Task( dynamic_cast<Task&>(*task) );

        la = new V_Littletask(this->getView()->getTasks()->getContainer(),a->getTitle(),a->getDeadline().toString(),a->getPriority());
        view->getTasks()->getGridLayout()->addWidget(la,row,column);

        if( column != 0 && column % 2 == 0 )
        {
                row++;
                column=0;
        } else column++;

            signalMapper->setMapping(la, task->getId());
            view->connect(la, SIGNAL(clicked()), signalMapper, SLOT(map()));
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

    // Déplacer le fichier dans le dossier ressources
    QFile *file = new QFile(m->getFileName());
    QFileInfo fileInfo(file->fileName());
    QDir dirToRessources(QDir::currentPath());
    dirToRessources.cd("../plurinotes/ressources/");

    QString from(m->getFileName());
    QString to(dirToRessources.absolutePath()+ QDir::separator() + m->getId() + "." + fileInfo.completeSuffix());
    QFile::copy(from,to);

    m->setFileName(m->getId() + "." + fileInfo.completeSuffix());

    app->getActiveNotesManager()->getTab()->push_back(m);
    app->getXMLManager()->insertIntoMultimedia(m);
    refreshActiveNotes();
}

void C_Mainwindow::saveNewTask(Task *t) {

    app->getActiveNotesManager()->getTab()->push_back(t);
    app->getXMLManager()->insertIntoTask(t);
    refreshTask();
}

void C_Mainwindow::deleteByID(QString id) {
    // WIP Suppression en base
    Note* note = app->getNoteByID(id);

    if( typeid(*note) == typeid(Article) ) {
        Article* article = new Article(dynamic_cast<Article&>(*note));
        app->getXMLManager()->deleteFromArticle(article);
    }

    if( typeid(*note) == typeid(Multimedia) ) {
        Multimedia* multimedia = new Multimedia(dynamic_cast<Multimedia&>(*note));
        app->getXMLManager()->deleteFromMultimedia(multimedia);
        // TODO Suppression du fichier pour les multimédias

        QFile file(multimedia->getFileName());
        QFileInfo fileInfo(file.fileName());
        QDir dirToRessources(QDir::currentPath());
        dirToRessources.cd("../plurinotes/ressources/");
        QString filePath = dirToRessources.absolutePath()+ QDir::separator() + multimedia->getId() + "." + fileInfo.completeSuffix();
        QFile completeFile(filePath);
        completeFile.remove();
    }

    if( typeid(*note) == typeid(Task) ) {
        Task* task = new Task(dynamic_cast<Task&>(*note));
        app->getXMLManager()->deleteFromTask(task);
    }

    //Suppression dans les notes actives
    for(unsigned int i = 0; i < app->getActiveNotesManager()->getTab()->size() ; i++ )
    {
        note = app->getActiveNotesManager()->getTab()->at(i);
        if( note->getId() == id ) app->getActiveNotesManager()->getTab()->erase(app->getActiveNotesManager()->getTab()->begin() + i);
    }
    refreshActiveNotes();
    refreshTask();
    view->setEmptyCentralNote();
}
