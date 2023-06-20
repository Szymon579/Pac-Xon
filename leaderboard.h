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

    std::vector<Result> parseJson(QString filename);
    void saveToJsonFile(const QString& filename);
    void addResult(QString name, int score);
    QString formatForDisplay();
    void sort();

public: //!!!!!!!!!!!!!!!!
    static bool compareByLength(const Result &a, const Result &b);
    std::vector<Result> results_vec;
    void debug();

};

#endif // LEADERBOARD_H
