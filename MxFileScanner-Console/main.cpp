#include <QtCore/QCoreApplication>
#include <QDebug>
#include <clocale>
#include <QList>
#include <QDir>
#include <QQueue>

int filesCount = 0;
qint64 filesSize = 0;
int foldersCount = 0;

//QString pathSource = "D:/YandexDisk/Temp";
QString pathSource = "D:/YandexDisk/Work";
QString pathDestination = "C:/Temp";

QQueue<QString> filesQueue;
QList<QString> dirs;


void fileList(QDir& root)
{
    foreach(QFileInfo fi, root.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name))
    {
        if (fi.isFile())
        {
            filesCount++;
            filesSize += fi.size();

            qInfo() << "[" << filesCount << "]" << "File: " << fi.filePath();
            filesQueue.enqueue(fi.filePath());
        }

        if (fi.isDir())
        {
            foldersCount++;
            dirs.append(fi.filePath());
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

    //QString path = QCoreApplication::applicationDirPath();

    // Header information
    qInfo() << "Start folder: " + pathSource;
    qInfo() << "----------------";

    // Add files to queue
    QDir dir(pathSource);
    fileList(dir);

    qInfo() << "Queue: " + QString::number(filesQueue.count());

    // Create destination folders
    qInfo() << "Create destination folders";
    for (qsizetype i = 0; i < dirs.size(); ++i)
    {
        QDir dir(dirs.at(i));
        QString newDir = dir.absolutePath();
        newDir.replace(pathSource, pathDestination);

        dir.mkpath(newDir);
        // dir.mkdir(newDir);
        qInfo() << "Create folder: " << newDir;
    }

    // Copy selected files
    while (!filesQueue.isEmpty())
    {
        QString fileSource = filesQueue.head();
        QString fileDestination = fileSource;
        fileDestination.replace(pathSource, pathDestination);
        qInfo() << "New path: " << fileDestination;

        QFile::copy(fileSource, fileDestination);

        filesQueue.dequeue();
    }


    // Footer information
    qInfo() << "----------------";
    qInfo() << "Files: " + QString::number(filesCount);
    qInfo() << "Files size: " + QString::number(filesSize);
    qInfo() << "Folders: " + QString::number(foldersCount);   


    return a.exec();
}
