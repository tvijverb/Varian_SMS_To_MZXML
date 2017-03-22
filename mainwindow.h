#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <assert.h>

//Qt Includes
#include <QMainWindow>
#include <Qdialog>
#include <QtGui>
#include <QFileSystemModel>
#include <QAbstractItemModel>
#include <QWidget>
#include <QDir>
#include <QtCore>
#include <QFileDialog>
#include <QFileInfo>
#include <QObject>
#include <QProgressBar>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

	void on_pushButton_clicked();

    bool fileExists(QString path);

	void notifyStart();

	void handleError(QProcess::ProcessError error);

	void notifyStop(int exitCode, QProcess::ExitStatus ex);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *dirListModel;
    QStatusBar *status;
	QProgressBar *progressBar;
};

#endif // MAINWINDOW_H
