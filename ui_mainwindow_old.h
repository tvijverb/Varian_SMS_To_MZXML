/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTreeView *treeView_2;
    QTreeView *treeView;
    QLabel *label;
    QComboBox *comboBox;
    QRadioButton *radioButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QRadioButton *radioButton_2;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuSMS_to_mzXML_converter;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(733, 546);
        MainWindow->setWindowOpacity(1);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::GroupedDragging|QMainWindow::VerticalTabs);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeView_2 = new QTreeView(centralWidget);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        treeView_2->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(treeView_2, 3, 0, 1, 5);

        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->header()->setCascadingSectionResizes(true);
        treeView->header()->setHighlightSections(true);
        treeView->header()->setProperty("showSortIndicator", QVariant(true));

        gridLayout->addWidget(treeView, 2, 0, 1, 5);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(300, 30));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(500, 20));
        comboBox->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(comboBox, 0, 1, 1, 2);

        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setMaximumSize(QSize(180, 16777215));
        radioButton->setChecked(true);
        radioButton->setAutoExclusive(false);

        gridLayout->addWidget(radioButton, 5, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 6, 0, 1, 2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(350, 0));
        pushButton_2->setMaximumSize(QSize(350, 16777215));

        gridLayout->addWidget(pushButton_2, 6, 2, 1, 1);

        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setChecked(true);
        radioButton_2->setAutoExclusive(false);

        gridLayout->addWidget(radioButton_2, 5, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 733, 21));
        menuSMS_to_mzXML_converter = new QMenu(menuBar);
        menuSMS_to_mzXML_converter->setObjectName(QStringLiteral("menuSMS_to_mzXML_converter"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSMS_to_mzXML_converter->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SMS to mzXML Converter - Thomas Vijverberg - Radboud University Nijmegen - v_1.0", 0));
        label->setText(QApplication::translate("MainWindow", "Current Working Directory:", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Search Subdirectories", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Batch File Conversion", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Single File Conversion", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Respect File Structure", 0));
        menuSMS_to_mzXML_converter->setTitle(QApplication::translate("MainWindow", "SMS to mzXML converter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
