#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>

int comboboxindex = 0;

QTextStream& qStdOut()
{
	static QTextStream ts(stdout);
	return ts;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	qStdOut() << "NOM?";
    // Directory view of top treeView, filters out files
    QString sPath = "C:\\";
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);
    ui->treeView->setModel(dirModel);

	// File view of bottom treeView, filters out directories
    dirListModel = new QFileSystemModel(this);
    dirListModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirListModel->setRootPath(sPath);

    ui->comboBox->addItem("C:/");
	//ui->progressBar->hide();
	ui->progressBar->setMinimum(0);
	ui->progressBar->setMaximum(99);
	ui->progressBar->setValue(0);
	ui->progressBar->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
	// Bottom treeview show files

	// Precondition: Bottom treeview in unspecified directory
	assert(true);
	// Postcondition: Bottom treeview shows files from top treeview directory 

    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->treeView_2->setModel(dirListModel);
    ui->treeView_2->setRootIndex(dirListModel->setRootPath(sPath));
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
	// Top treeview on doubleclick

	// Precondition: Top treeview in unspecified directory
	assert(true);
	// Postcondition: Set top treeview root directory to doubleclicked folder


    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    int comboBoxSize = ui->comboBox->count();
    ui->comboBox->addItem(sPath);
    ui->treeView->setRootIndex(dirModel->setRootPath(sPath));
    ui->treeView_2->setRootIndex(dirListModel->setRootPath(sPath));
    ui->comboBox->setCurrentIndex(comboBoxSize);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
	// Combobox File Path dropdown

	// Precondition: Combobox filled with one or more possible filepaths
	assert(true);
	// Postcondition: Set treeviews to selected filepath

    ui->treeView->setRootIndex(dirModel->setRootPath(arg1));
    ui->treeView_2->setRootIndex(dirListModel->setRootPath(arg1));
}

bool MainWindow::fileExists(QString path) {
	// Check if file exists and if yes: Is it really a file and no directory?

	// Precondition: filepath to conversion output file (*.mzXML)
	assert(!path.isEmpty());
	// Postcondition: 
	// IF	Single *.SMS file is correctly converted to *.mzXML file format
	//		OUTPUT: Statusbar succes
	// ELSE	OUTPUT: Statusbar error

	// Checks if .mzXML file exists
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        QString FP = "Succes: mzXML file is created at " + path;
        ui->statusBar->showMessage(FP);
        return true;
    } else {
        QString FP = "Error: mzXML file is not created";
        ui->statusBar->showMessage(FP);
        return false;
    }
}

void MainWindow::notifyStart()
{
}

void MainWindow::handleError(QProcess::ProcessError error)
{
}

void MainWindow::notifyStop(int exitCode, QProcess::ExitStatus ex)
{
}

void MainWindow::on_pushButton_2_clicked()
{
	// Single File conversion - On pushbutton click

	// Precondition: PushButton 2 not clicked 
		assert(true);
	// Postcondition: Single *.SMS file is converted to *.mzXML file format

	// Open File dialog and get filepath
	QProcess *Myprocess = new QProcess(this);
	QStringList arguments;

    QString TV_SingleConversion_FilePath = QFileDialog::getOpenFileName(this,tr("Open .SMS file"),"C:\\","Varian SMS files (*.SMS)");
    QFileInfo TV_SingleConversion_FileInfo(TV_SingleConversion_FilePath);
    QString TV_SingleConversion_FileParentDirectory = TV_SingleConversion_FileInfo.filePath();

	// Launch SMS file converter EXE and point it to the *.SMS file
	QString file = QDir::currentPath() + "\\xms2mzXML\\xms2mzxml.exe";

	// Make string usable for windows XP
	file.replace(QString("/"), QString("\\"));
	ui->statusBar->showMessage(file);
	arguments << TV_SingleConversion_FileParentDirectory;
    Myprocess->start(file,arguments);

	// Wait for file conversion and check if conversion was succesful
	Sleep(1000);
    QString TV_SingleConversion_outFile = TV_SingleConversion_FileInfo.absolutePath() + "\\" + TV_SingleConversion_FileInfo.completeBaseName() + ".mzXML";
	TV_SingleConversion_outFile.replace(QString("/"), QString("\\"));
    fileExists(TV_SingleConversion_outFile);
}

void MainWindow::on_pushButton_clicked()
{
    // Single File conversion - On pushbutton click

    // Precondition: PushButton not clicked
        assert(true);
    // Postcondition: *.SMS files converted to *.mzXML file format

	QModelIndex TV_BatchConversion_currentindex = ui->treeView->currentIndex();
    // Root filepath
    
	int TV_BatchConversion_CurrentSMS = 0;
	int TV_BatchConversion_Currentpercentage = 0;
	int TV_BatchConversion_TotalDirs = 0;
	double TV_BatchConversion_Currentpercentage_db = 0;

    QString sPath = dirModel->fileInfo(TV_BatchConversion_currentindex).absoluteFilePath();

	// Check if path is not empty
	if (sPath.isEmpty()) {
		ui->statusBar->showMessage(QString("No root directory selected"));
		return;
	}

	// 
	QDirIterator it(sPath, QDir::AllDirs, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		TV_BatchConversion_TotalDirs = TV_BatchConversion_TotalDirs + 1;
		if (TV_BatchConversion_TotalDirs > 3000) {
			ui->statusBar->showMessage(QString("Selected root directory has over 3000 subfolders, this can't be right :("));
			return;
		}
		it.next();
	}



	ui->progressBar->show();
	
	if (!ui->radioButton_2->isChecked()) {
		if (ui->radioButton->isChecked()) {
			// Find all SMS files and loop over directories
			QDirIterator it(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::Subdirectories);
			while (it.hasNext()) {
				int TV_BatchConversion_TotalSMS = 0;

				// Get total number of SMS files
				QDirIterator it2(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::Subdirectories);
				while (it2.hasNext()) {
					TV_BatchConversion_TotalSMS = TV_BatchConversion_TotalSMS + 1;
					it2.next();
				}

				// Get path to SMS file converter
				QProcess *Myprocess = new QProcess(this);
				QString file;
				QStringList arguments;
				file = QDir::currentPath() + "\\xms2mzXML\\xms2mzxml.exe";

				// Get path to SMS file
				QString TV_BatchConversion_FileParentDirectory = it.next();
				file.replace(QString("/"), QString("\\"));

				// Set progressbar
				TV_BatchConversion_FileParentDirectory.replace(QString("/"), QString("\\"));
				TV_BatchConversion_Currentpercentage_db = 100 * (static_cast<double>(TV_BatchConversion_CurrentSMS) / static_cast<double>(TV_BatchConversion_TotalSMS));
				TV_BatchConversion_Currentpercentage = static_cast<int>(TV_BatchConversion_Currentpercentage_db);
				ui->progressBar->setValue(TV_BatchConversion_Currentpercentage);
				ui->progressBar->valueChanged(TV_BatchConversion_Currentpercentage);
				ui->progressBar->show();

				// Convert SMS file
				arguments << TV_BatchConversion_FileParentDirectory;
				Myprocess->start(file, arguments);
				Sleep(1000);
				TV_BatchConversion_CurrentSMS = TV_BatchConversion_CurrentSMS + 1;
			}
		}
		else if (!ui->radioButton->isChecked()) {
			QDirIterator it(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::NoIteratorFlags);
			while (it.hasNext()) {
				int TV_BatchConversion_TotalSMS = 0;

				// Get total number of SMS files
				QDirIterator it2(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::Subdirectories);
				while (it2.hasNext()) {
					TV_BatchConversion_TotalSMS = TV_BatchConversion_TotalSMS + 1;
					it2.next();
				}
				// Get path to SMS file converter
				QProcess *Myprocess = new QProcess(this);
				QString file;
				QStringList arguments;
				file = QDir::currentPath() + "\\xms2mzXML\\xms2mzxml.exe";

				// Get path to SMS file
				QString TV_BatchConversion_FileParentDirectory = it.next();
				file.replace(QString("/"), QString("\\"));

				// Set progressbar
				TV_BatchConversion_FileParentDirectory.replace(QString("/"), QString("\\"));
				TV_BatchConversion_Currentpercentage_db = 100 * (static_cast<double>(TV_BatchConversion_CurrentSMS) / static_cast<double>(TV_BatchConversion_TotalSMS));
				TV_BatchConversion_Currentpercentage = static_cast<int>(TV_BatchConversion_Currentpercentage_db);
				ui->progressBar->setValue(TV_BatchConversion_Currentpercentage);
				ui->progressBar->valueChanged(TV_BatchConversion_Currentpercentage);
				ui->progressBar->show();

				// Convert SMS file
				arguments << TV_BatchConversion_FileParentDirectory;
				Myprocess->start(file, arguments);
				Sleep(1000);
				TV_BatchConversion_CurrentSMS = TV_BatchConversion_CurrentSMS + 1;
			}
		}
	}
	else {
		// Respecting folder integrity
		// Get output directory
		QString TV_BatchConversion_FilePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "C:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (TV_BatchConversion_FilePath.isEmpty()) {
			ui->statusBar->showMessage(QString("No folder selected"));
			return;
		}
		if (ui->radioButton->isChecked()) {
			// Find all SMS files and loop over directories
			QDirIterator it(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::Subdirectories);
			while (it.hasNext()) {
				int TV_BatchConversion_TotalSMS = 0;

				// Get total number of SMS files
				QDirIterator it2(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::Subdirectories);
				while (it2.hasNext()) {
					TV_BatchConversion_TotalSMS = TV_BatchConversion_TotalSMS + 1;
					it2.next();
				}

				// Get path to SMS file converter
				QProcess *Myprocess = new QProcess(this);
				QString file;
				QStringList arguments;
				file = QDir::currentPath() + "\\xms2mzXML\\xms2mzxml.exe";

				// Get path to SMS file
				QString TV_BatchConversion_FileParentDirectory = it.next();
				file.replace(QString("/"), QString("\\"));

				// Set progressbar
				TV_BatchConversion_FileParentDirectory.replace(QString("/"), QString("\\"));
				TV_BatchConversion_Currentpercentage_db = 100 * (static_cast<double>(TV_BatchConversion_CurrentSMS) / static_cast<double>(TV_BatchConversion_TotalSMS));
				TV_BatchConversion_Currentpercentage = static_cast<int>(TV_BatchConversion_Currentpercentage_db);
				ui->progressBar->setValue(TV_BatchConversion_Currentpercentage);
				ui->progressBar->valueChanged(TV_BatchConversion_Currentpercentage);
				ui->progressBar->show();

				// Converted file name + directory
				QFileInfo TV_BatchConversion_FileInfo(TV_BatchConversion_FileParentDirectory);
				//TV_BatchConversion_FileParentDirectory.replace(QString(".SMS"), QString(".mzXML"));

				// Target path  = .SMS file
				QString targetpath = TV_BatchConversion_FileParentDirectory;
				sPath.replace(QString("/"), QString("\\"));
				targetpath.replace(sPath, QString(""));
				targetpath = TV_BatchConversion_FilePath + targetpath;
				targetpath.replace(QString("/"), QString("\\"));
				targetpath.replace(QString(".SMS"), QString(".mzXML"));

				// Original .mzXML path
				QString TV_SingleConversion_outFile = TV_BatchConversion_FileInfo.absolutePath() + "\\" + TV_BatchConversion_FileInfo.completeBaseName() + ".mzXML";
				TV_SingleConversion_outFile.replace(QString("/"), QString("\\"));

				// Target path parent directory
				QString parentdir = TV_BatchConversion_FileInfo.path();
				parentdir.replace(QString("/"), QString("\\"));
				parentdir.replace(sPath, QString(""));
				parentdir = TV_BatchConversion_FilePath + parentdir;
				parentdir.replace(QString("/"), QString("\\"));

				// Convert SMS file
				arguments << TV_BatchConversion_FileParentDirectory;
				Myprocess->start(file, arguments);
				Sleep(1000);

				ui->statusBar->showMessage(parentdir);

				int skip = 0;
				if (!QDir(parentdir).exists()) {
					QDir().mkdir(parentdir);
				}
				else if (QFile::exists(targetpath)) {
					ui->statusBar->showMessage(QString("File already exists. Skipping"));
					skip = 1;
				}
				if (skip == 0) {
					if (!QFile::rename(TV_SingleConversion_outFile, targetpath)) {
						ui->statusBar->showMessage(QString("Move failed"));
						return;
					}
				}
				TV_BatchConversion_CurrentSMS = TV_BatchConversion_CurrentSMS + 1;
			}
		}
		else if (!ui->radioButton->isChecked()) {
			QDirIterator it(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::NoIteratorFlags);
			while (it.hasNext()) {
				int TV_BatchConversion_TotalSMS = 0;

				// Get total number of SMS files
				QDirIterator it2(sPath, QStringList() << "*.SMS", QDir::Files, QDirIterator::NoIteratorFlags);

				while (it2.hasNext()) {
					TV_BatchConversion_TotalSMS = TV_BatchConversion_TotalSMS + 1;
					it2.next();
				}

				// Get path to SMS file converter
				QProcess *Myprocess = new QProcess(this);
				QString file;
				QStringList arguments;
				file = QDir::currentPath() + "\\xms2mzXML\\xms2mzxml.exe";

				// Get path to SMS file
				QString TV_BatchConversion_FileParentDirectory = it.next();
				file.replace(QString("/"), QString("\\"));

				// Set progressbar
				TV_BatchConversion_FileParentDirectory.replace(QString("/"), QString("\\"));
				TV_BatchConversion_Currentpercentage_db = 100 * (static_cast<double>(TV_BatchConversion_CurrentSMS) / static_cast<double>(TV_BatchConversion_TotalSMS));
				TV_BatchConversion_Currentpercentage = static_cast<int>(TV_BatchConversion_Currentpercentage_db);
				ui->progressBar->setValue(TV_BatchConversion_Currentpercentage);
				ui->progressBar->valueChanged(TV_BatchConversion_Currentpercentage);
				ui->progressBar->show();

				// Converted file name + directory
				QFileInfo TV_BatchConversion_FileInfo(TV_BatchConversion_FileParentDirectory);
				//TV_BatchConversion_FileParentDirectory.replace(QString(".SMS"), QString(".mzXML"));

				// Target path to copy file to
				QString targetpath = TV_BatchConversion_FileParentDirectory;
				sPath.replace(QString("/"), QString("\\"));
				targetpath.replace(sPath, QString(""));
				targetpath = TV_BatchConversion_FilePath + targetpath;
				targetpath.replace(QString("/"), QString("\\"));
				targetpath.replace(QString(".SMS"), QString(".mzXML"));

				// Target path parent directory
				QString parentdir = TV_BatchConversion_FileInfo.path();
				parentdir.replace(QString("/"), QString("\\"));
				parentdir.replace(sPath, QString(""));
				parentdir = TV_BatchConversion_FilePath + parentdir;
				parentdir.replace(QString("/"), QString("\\"));
				parentdir.replace(QString("."), QString(""));

				// Original .mzXML path
				QString TV_SingleConversion_outFile = TV_BatchConversion_FileInfo.absolutePath() + "\\" + TV_BatchConversion_FileInfo.completeBaseName() + ".mzXML";
				TV_SingleConversion_outFile.replace(QString("/"), QString("\\"));

				// Convert SMS file
				arguments << TV_BatchConversion_FileParentDirectory;
				Myprocess->start(file, arguments);
				Sleep(1000);
				int skip = 0;
				if (!QDir(parentdir).exists()) {
					QDir().mkdir(parentdir);
				}
				else if (QFile::exists(targetpath)) {
					ui->statusBar->showMessage(QString("File already exists. Skipping"));
					skip = 1;
				}
				if (skip == 0) {
					if (!QFile::rename(TV_SingleConversion_outFile, targetpath)) {
						ui->statusBar->showMessage(QString("Move failed"));
						return;
					}
				}
				TV_BatchConversion_CurrentSMS = TV_BatchConversion_CurrentSMS + 1;
			}
		}
	}
	QString TV_BatchConversion_outputMessage = QString("Succesfully converted: ") + QString::number(TV_BatchConversion_CurrentSMS) + QString(" *.SMS files.");
	ui->statusBar->showMessage(TV_BatchConversion_outputMessage);
	ui->progressBar->setValue(99);
	ui->progressBar->valueChanged(99);
	ui->progressBar->show();
}
