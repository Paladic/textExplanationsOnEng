#include <QCoreApplication>
#include <windows.h>
#include <conio.h>
void printHelpMessage(QTextStream& cout, const QString& filename);

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);
    cout.setEncoding(QStringConverter::Utf8);

    QString fileName = QCoreApplication::applicationFilePath();
    QFileInfo fileInfo(fileName);
    fileName = fileInfo.fileName();

    qDebug() << "hello world";
    a.exit(0);
    return 0;
}
}

void printHelpMessage(QTextStream& cout, const QString& filename)
{
    cout << ".\\" + filename + " [-help | -test] [input-file] [output-file]\n";
    cout << "-help      - Выводит сообщение-помощник. При вводе этой команды путь к файлам указывать не нужно.\n";
    cout << "-test      - Запускает тесты. При вводе этой команды путь к файлам указывать не нужно.\n";
    cout << "input-file - путь к входному файлу. В случае, если в пути файла присутствуют пробелы, необходимо указать путь в кавычках. Например:\n";
    cout << "               \"C:\\\\input files\\input.txt\"\n";
    cout << "output-file - путь к выходному файлу. Если файла не существует - он будет создан. В случае, если в пути файла присутствуют пробелы, необходимо указать путь в кавычках. Например:\n";
    cout << "               \"C:\\\\output files\\output.txt\"\n";
    cout << "Пример запуска: \n";
    cout << "   .\\" + filename + " input.txt \"C:\\\\files\\New folder\\output.txt\"\n";
}
