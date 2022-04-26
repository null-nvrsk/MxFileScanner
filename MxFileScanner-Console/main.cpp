#include <QtCore/QCoreApplication>
#include <QDir>
#include <clocale>

int filesCount = 0;
int filesSize = 0;
int foldersCount = 0;

void fileList(QDir& root)
{
    foreach(QFileInfo fi, root.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name))
    {
        if (fi.isFile())
        {
            filesCount++;
            filesSize += fi.size();

            qInfo() << "[" << filesCount << "]" << "File: " << fi.filePath() << "\t" << fi.size();
        }

        if (fi.isDir())
        {
            foldersCount++;
            // qInfo() << "Dir: " << fi.filePath();
            QDir childDir(fi.filePath());

            fileList(childDir);
        }
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "Russian");

    QString path = "D:/YandexDisk/Temp";
    //QString path = QCoreApplication::applicationDirPath();

    // Header information
    qInfo() << "Start folder: " + path;
    qInfo() << "----------------";

    QDir dir(path);
    fileList(dir);

    // Footer information
    qInfo() << "----------------";
    qInfo() << "Files: " + QString::number(filesCount);
    qInfo() << "Files size: " + QString::number(filesSize);
    qInfo() << "Folders: " + QString::number(foldersCount);

    return a.exec();
}
