#include "leaderboard.h"
#include "qfontmetrics.h"

#include <algorithm>

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

Leaderboard::Leaderboard()
{

}

std::vector<Result> Leaderboard::parseJson(QString filename)
{
    results_vec.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
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
    for (const QJsonValue& json_value : json_array)
    {
        if (json_value.isObject())
        {
            QJsonObject json_object = json_value.toObject();
            Result result;
            result.name = json_object.value("name").toString();
            result.score = json_object.value("score").toInt();
            results_vec.push_back(result);
        }
    }

    sort();
    return results_vec;
}

void Leaderboard::saveToJsonFile(const QString& filename)
{
    QJsonArray jsonArray;

    for(int i = 0; i < results_vec.size(); i++)
    {
        QJsonObject object;
        object["name"] = results_vec.at(i).name;
        object["score"] = results_vec.at(i).score;
        jsonArray.append(object);
    }

    QJsonDocument json_document;
    json_document.setArray(jsonArray);

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(json_document.toJson());
        file.close();
        qDebug() << "JSON file saved.";
    }
    else
    {
        qDebug() << "Failed to save JSON file.";
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

// ---------------------------------- TODO ----------------------------------
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
                       results_vec.at(i).name + " " +//space +
                       QString::number(results_vec.at(i).score) + "\n";

        text.push_back(line);
    }

    return text;
}

void Leaderboard::sort()
{
    std::sort(results_vec.begin(), results_vec.end(), compareByLength);
}

bool Leaderboard::compareByLength(const Result &a, const Result &b)
{
    return a.score > b.score;
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





