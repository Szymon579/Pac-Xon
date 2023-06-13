#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QString>
#include <QJsonObject>

struct Result
{
    QString name;
    int score;
};

class Leaderboard
{
public:
    Leaderboard();

    void addObject(QString name, int score);
    void addJsonObjectToFile(const QString &filename, const QJsonObject &newJsonObject);

    std::vector<Result> parseJson(QString filename);
    void debug();
    void addResult(QString name, int score);

public:
    std::vector<Result> results_vec;
    QString formatForDisplay();
    static bool compareByLength(const Result &a, const Result &b);
    void sort();
};

#endif // LEADERBOARD_H
