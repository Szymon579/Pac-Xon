#include "leaderboard.h"

#include <algorithm>

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

Leaderboard::Leaderboard()
{
    parseJson("test.json");
}

std::vector<Result> Leaderboard::parseJson(QString filename)
{
    results_vec.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return results_vec;
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!json_doc.isArray())
    {
        qDebug() << "invalid JSON";
        return results_vec;
    }

    QJsonArray json_array = json_doc.array();
    for (const QJsonValue& jsonValue : json_array) {
        if (jsonValue.isObject()) {
            QJsonObject json_object = jsonValue.toObject();
            Result result;
            result.name = json_object.value("name").toString();
            result.score = json_object.value("score").toInt();
            results_vec.push_back(result);
        }
    }

    sort();
    return results_vec;
}

void Leaderboard::debug()
{
    for (const Result& result : results_vec)
    {
        qDebug() << "----------------------";
        qDebug() << "Name:" << result.name;
        qDebug() << "Score:" << result.score;
    }
}

void Leaderboard::addResult(QString name, int score)
{
    Result result;
    result.name = name;
    result.score = score;

    results_vec.push_back(result);

    sort();
}

QString Leaderboard::formatForDisplay()
{
    QString text;

    int span = 20;

    for(int i = 0; i < results_vec.size(); i++)
    {
        QString space;
        int spacing = span - results_vec.at(i).name.size() - QString::number(results_vec.at(i).score).size();
        for(int j = 0; j < spacing; j++)
        {
            space.push_back("  ");
        }

        QString line = QString::number(i+1) + ". " +
                       results_vec.at(i).name + space +
                       QString::number(results_vec.at(i).score) + "\n";

        text.push_back(line);
    }

    qDebug() << text;

    return text;
}

bool Leaderboard::compareByLength(const Result &a, const Result &b)
{
    return a.score > b.score;
}

void Leaderboard::sort()
{
    std::sort(results_vec.begin(), results_vec.end(), compareByLength);
}





