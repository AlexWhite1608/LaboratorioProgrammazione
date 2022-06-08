#include "readFile.h"

QStringList readFile(const QString path)
{
    QStringList result;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Errore apertura file" << file.errorString();
    }

    QTextStream fileStream(&file);

    while(!fileStream.atEnd()) {
        QString line = fileStream.readLine();
        result.append(line);
    }

    file.close();

    return result;
}
