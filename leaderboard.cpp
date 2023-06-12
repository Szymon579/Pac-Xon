#include "leaderboard.h"

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
