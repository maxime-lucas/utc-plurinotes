/********************************************************************************
** Form generated from reading UI file 'v_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V_MAINWINDOW_H
#define UI_V_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_V_Mainwindow
{
public:
    QAction *actionQuit;
    QAction *actionArticle;
    QAction *actionMultimedia;
    QAction *actionTask;
    QAction *actionRelation;
    QAction *actionDefault_view;
    QAction *actionRelations_view;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuNew;

    void setupUi(QMainWindow *V_Mainwindow)
    {
        if (V_Mainwindow->objectName().isEmpty())
            V_Mainwindow->setObjectName(QStringLiteral("V_Mainwindow"));
        V_Mainwindow->resize(800, 600);
        V_Mainwindow->setStyleSheet(QStringLiteral(""));
        actionQuit = new QAction(V_Mainwindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionArticle = new QAction(V_Mainwindow);
        actionArticle->setObjectName(QStringLiteral("actionArticle"));
        actionMultimedia = new QAction(V_Mainwindow);
        actionMultimedia->setObjectName(QStringLiteral("actionMultimedia"));
        actionTask = new QAction(V_Mainwindow);
        actionTask->setObjectName(QStringLiteral("actionTask"));
        actionRelation = new QAction(V_Mainwindow);
        actionRelation->setObjectName(QStringLiteral("actionRelation"));
        actionDefault_view = new QAction(V_Mainwindow);
        actionDefault_view->setObjectName(QStringLiteral("actionDefault_view"));
        actionRelations_view = new QAction(V_Mainwindow);
        actionRelations_view->setObjectName(QStringLiteral("actionRelations_view"));
        centralwidget = new QWidget(V_Mainwindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setEnabled(true);
        centralwidget->setStyleSheet(QStringLiteral(""));
        V_Mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(V_Mainwindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuNew = new QMenu(menu_File);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        V_Mainwindow->setMenuBar(menubar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(menuNew->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionQuit);
        menuNew->addAction(actionArticle);
        menuNew->addAction(actionMultimedia);
        menuNew->addAction(actionTask);
        menuNew->addSeparator();

        retranslateUi(V_Mainwindow);

        QMetaObject::connectSlotsByName(V_Mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *V_Mainwindow)
    {
        V_Mainwindow->setWindowTitle(QApplication::translate("V_Mainwindow", "PluriNotes - FAYAX", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("V_Mainwindow", "Quit", Q_NULLPTR));
        actionArticle->setText(QApplication::translate("V_Mainwindow", "Article", Q_NULLPTR));
        actionMultimedia->setText(QApplication::translate("V_Mainwindow", "Multimedia", Q_NULLPTR));
        actionTask->setText(QApplication::translate("V_Mainwindow", "Task", Q_NULLPTR));
        actionRelation->setText(QApplication::translate("V_Mainwindow", "Relation", Q_NULLPTR));
        actionDefault_view->setText(QApplication::translate("V_Mainwindow", "Default view", Q_NULLPTR));
        actionRelations_view->setText(QApplication::translate("V_Mainwindow", "Relations view", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("V_Mainwindow", "&File", Q_NULLPTR));
        menuNew->setTitle(QApplication::translate("V_Mainwindow", "New...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class V_Mainwindow: public Ui_V_Mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V_MAINWINDOW_H