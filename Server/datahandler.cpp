/* https://doc.qt.io/qt-5/sql-sqlstatements.html */
/* https://www.tutorialspoint.com/sqlite/ */
/* https://katecpp.github.io/sqlite-with-qt/ */

/*https://topic.alibabacloud.com/a/
 * the-solution-of-multithreading-problem-in-qt-database-qsqldatabase-can-only-be-used-in-the-thread-that-created-it_8_8_30063098.html*/

#include "datahandler.h"

int DataHandler::connections_count = 0;

DataHandler::DataHandler()
{
    /*se creaza o conectiune unica cu baza de date*/
    connections_count++;
    connection_name = "DB" + QString::number(connections_count);
    DB = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    DB.setDatabaseName(DATABASE_NAME);
    DB.open();
    QSqlQuery query(DB);
    query.exec("PRAGMA foreign_keys = ON;");
}

bool DataHandler::TryLogin(int* usertype, const char* username, const char* password, char* data)
{
    bool    ok = false;
    QString name_search(username);
    QString password_check(password);

    strcpy(data, "");
    QSqlQuery q(DB);
    q.prepare("SELECT username, password, type FROM users WHERE username = :username");
    q.bindValue(":username", name_search);
    q.exec();
    if (q.first())
    {
        if (q.value("PASSWORD").toString() == password_check)
        {
            *usertype = q.value("TYPE").toInt();
            sprintf(data, "PASS|V-ati autentificat cu succes. Bine ati revenit %s!|%d",
                    username, *usertype);
            ok = true;
        }
        else
        {
            strcpy(data, "FAIL|Parola introdusa este incorecta. Incercati din nou!");
            ok = false;
        }
    }
    else
    {
        strcpy(data, "FAIL|Numele de utilizator nu exista in baza de date. Incercati sa va inregistrati!");
        ok = false;
    }
    return (ok);
}

bool DataHandler::TryRegister(int* usertype, const char* username,
                              const char* password, const char* first_name,
                              const char* last_name, int acc_type, char* data)
{
    strcpy(data, "");
    bool ok = false;

    QSqlQuery q(DB);
    q.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    q.bindValue(":username", username);
    q.exec();
    q.first();
    if (q.value(0).toInt() > 0)
    {
        sprintf(data, "FAIL|Deja exista un utilator cu numele %s in baza de date",
                username);
    }
    else
    {
        q.prepare("INSERT INTO users VALUES(?, ?, ?, ?, ?, ?);");
        q.addBindValue(username);
        q.addBindValue(password);
        q.addBindValue(first_name);
        q.addBindValue(last_name);
        q.addBindValue(acc_type);
        q.addBindValue(1);
        if (q.exec())
        {
            sprintf(data, "PASS|V-ati inregistrat cu succes cu numele %s!", username);
            *usertype = acc_type;
            ok        = true;
        }
    }
    return (ok);
}

char* DataHandler::GetSongsTop(char* genre)
{
    int  nr_songs        = 0;
    bool search_by_genre = false;

    std::string* lines = new std::string();

    *lines = "";

    if (genre != NULL)
    {
        search_by_genre = true;
    }

    QSqlQuery q(DB);
    if (search_by_genre)
    {
        q.prepare("SELECT s.song_id, s.name, s.author, s.description, s.link, s.genres, "
                  "(SELECT COUNT(*) FROM votes v WHERE v.song_id = s.song_id) as vote "
                  "FROM songs s WHERE s.genres LIKE '%" + QString(genre) + "%' ORDER BY vote DESC");
        q.exec();
        while (q.next())
        {
            std::string id     = q.value(0).toString().toStdString();
            std::string name   = q.value(1).toString().toStdString();
            std::string author = q.value(2).toString().toStdString();
            std::string desc   = q.value(3).toString().toStdString();
            std::string link   = q.value(4).toString().toStdString();
            std::string gens   = q.value(5).toString().toStdString();
            std::string votes  = q.value(6).toString().toStdString();
            lines->append(id + "|" + name + "|" + author + "|" + desc + "|" + link + "|" +
                          gens + "|" + votes + "||");
            nr_songs++;
        }
    }
    else
    {
        q.prepare("SELECT s.song_id, s.name, s.author, s.description, s.link, s.genres, "
                  "(SELECT COUNT(*) FROM votes v WHERE v.song_id = s.song_id) as vote "
                  "FROM songs s ORDER BY vote DESC");
        q.exec();
        while (q.next())
        {
            std::string id     = q.value(0).toString().toStdString();
            std::string name   = q.value(1).toString().toStdString();
            std::string author = q.value(2).toString().toStdString();
            std::string desc   = q.value(3).toString().toStdString();
            std::string link   = q.value(4).toString().toStdString();
            std::string gens   = q.value(5).toString().toStdString();
            std::string votes  = q.value(6).toString().toStdString();
            lines->append(id + "|" + name + "|" + author + "|" + desc + "|" + link + "|" +
                          gens + "|" + votes + "||");
            nr_songs++;
        }
    }

    char songs_count[10];
    sprintf(songs_count, "%d|", nr_songs);
    lines->insert(0, std::string(songs_count));

    q.finish();
    return ((char*)lines->c_str());
}

bool DataHandler::GetComments(int song_id, char* data)
{
    strcpy(data, "");
    int       ok       = false;
    int       nr_comms = 0;
    QSqlQuery q(DB);

    q.prepare("SELECT writed_by, comment FROM comments WHERE song_id = :song_id");
    q.bindValue(":song_id", song_id);
    q.exec();
    while (q.next())
    {
        std::string name    = q.value(0).toString().toStdString();
        std::string comment = q.value(1).toString().toStdString();
        nr_comms++;
        char com[1000];
        sprintf(com, "%s|%s||", name.c_str(), comment.c_str());
        strncat(data, com, strlen(com));
    }

    if (nr_comms > 0)
    {
        sprintf(data, "%d|%s", nr_comms, std::string(data).c_str());
    }
    else
    {
        strcpy(data, "FAIL|Aceasta melodie nu are nici un comentariu!");
    }

    return (ok);
}

bool DataHandler::AddComment(int song_id, const char* username,
                             const char* comment, char* data)
{
    bool ok = false;

    QSqlQuery q(DB);

    q.prepare("INSERT INTO comments VALUES (?, ?, ?)");
    q.addBindValue(song_id);
    q.addBindValue(username);
    q.addBindValue(comment);
    if (q.exec())
    {
        strcpy(data, "PASS|Comentariul a fost adaugat cu succes!");
        ok = true;
    }
    else
    {
        strcpy(data, "FAIL|Ceva nu a mers bine, nu s-a putut adauga comentariul");
        ok = false;
    }

    return (ok);
}

int DataHandler::GetLastSongId()
{
    QSqlQuery q(DB);

    q.prepare("SELECT MAX(song_id) FROM songs");
    q.exec();
    q.first();
    int id = q.value(0).toInt() + 1;
    q.finish();

    return (id);
}

bool DataHandler::RemoveSong(int song_id, char* data)
{
    bool      ok = false;
    QSqlQuery q(DB);

    q.prepare("DELETE FROM songs WHERE song_id = ?");
    q.addBindValue(song_id);
    if (q.exec())
    {
        strcpy(data, "PASS|Melodia a fost stearsa cu succes!");
        ok = true;
    }
    else
    {
        strcpy(data, "FAIL|Ceva nu a mers bine la stergerea melodiei!");
        ok = false;
    }
    return (ok);
}

bool DataHandler::VoteSong(const char* username, int song_id, char* data,
                           bool is_upvote)
{
    DB.transaction();
    QSqlQuery q(DB);

    q.prepare("SELECT COUNT(*) FROM songs WHERE song_id = :song_id");
    q.bindValue(":song_id", song_id);
    q.exec();
    q.first();
    if (q.value(0).toInt() == 0)
    {
        strcpy(data, "FAIL|Melodia ceruta nu exista in baza de date");
        DB.rollback();
        return (false);
    }

    q.prepare("SELECT can_vote FROM users WHERE username = :username");
    q.bindValue(":username", username);
    q.exec();
    q.first();
    if (q.value(0).toInt() == 0)
    {
        strcpy(data, "FAIL|Nu aveti permisiunea de a vota!");
        DB.rollback();
        return (false);
    }

    q.prepare("SELECT COUNT(*) FROM votes WHERE username = :username AND song_id = :songid");
    q.bindValue(":username", username);
    q.bindValue(":songid", song_id);
    q.exec();
    q.first();
    if (q.value(0).toInt() > 0 && is_upvote)
    {
        strcpy(data, "FAIL|Aveti deja un vot la aceasta melodie!");
        DB.rollback();
        return (false);
    }
    else if (q.value(0).toInt() == 0 && !is_upvote)
    {
        strcpy(data, "FAIL|Nu aveti inca vot la aceasta melodie!");
        DB.rollback();
        return (false);
    }


    if (is_upvote)
    {
        q.prepare("INSERT INTO votes VALUES (:song_id, :name)");
        q.bindValue(":song_id", song_id);
        q.bindValue(":name", username);
        q.exec();
        strcpy(data, "PASS|Multumim, ati votat cu succes!");
    }
    else
    {
        q.prepare("DELETE FROM votes WHERE song_id = :song_id AND username = :name");
        q.bindValue(":song_id", song_id);
        q.bindValue(":name", username);
        q.exec();
        strcpy(data, "PASS|V-ati retras cu succes votul dat melodiei!");
    }
    DB.commit();

    return (true);
}

bool DataHandler::AddSong(const char* name, const char* author,
                          const char* description,
                          const char* link, const char* genres, char* data)
{
    int  new_id = GetLastSongId();
    bool ok     = false;

    DB.transaction();
    QSqlQuery q(DB);

    q.prepare("INSERT INTO songs VALUES (?, ?, ?, ?, ?, ?)");
    q.addBindValue(new_id);
    q.addBindValue(name);
    q.addBindValue(author);
    q.addBindValue(description);
    q.addBindValue(link);
    q.addBindValue(genres);
    if (q.exec())
    {
        strcpy(data, "PASS|Melodia a fost adaugata cu succes!");
        DB.commit();
        ok = true;
    }
    else
    {
        strcpy(data, "FAIL|Ceva nu a mers bine la adaugarea melodiei!");
        DB.rollback();
        ok = false;
    }

    return (ok);
}

bool DataHandler::RestrictVoteRight(const char* username, int has_right,
                                    char* data)
{
    DB.transaction();
    QSqlQuery q(DB);

    q.prepare("SELECT type FROM users WHERE username = ?");
    q.addBindValue(username);
    q.exec();
    q.first();
    if (q.value(0).toInt() == 1)
    {
        strcpy(data, "FAIL|Ceva nu a mers bine, nu puteti bloca accesul la vot unui alt admin!");
        DB.rollback();
        return (false);
    }

    q.prepare("UPDATE users SET can_vote = ? WHERE username = ?");
    q.addBindValue(has_right);
    q.addBindValue(username);
    if (q.exec())
    {
        if (has_right == 0)
        {
            sprintf(data, "PASS|Succes, ati restrictionat accesul la vot utilizatorului %s", username);
        }
        else
        {
            sprintf(data, "PASS|Succes, ati permis accesul la vot utilizatorului %s", username);
        }
        DB.commit();
    }
    else
    {
        strcpy(data, "FAIL|Nu s-a putut actualiza baza de date!");
        DB.rollback();
        return (false);
    }

    return (true);
}

bool DataHandler::GetUsers(bool (*isConnected)(const char*), char* data)
{
    strcpy(data, "");
    int       ok       = false;
    int       nr_users = 0;
    QSqlQuery q(DB);

    q.prepare("SELECT t.username, t.type, t.can_vote, t.vote_cnt, count(c.comment) comm_cnt "
              "FROM (SELECT u.username, u.type, u.can_vote, count(v.song_id) vote_cnt "
              "FROM users u LEFT JOIN votes v ON u.username = v.username GROUP BY u.username) t "
              "LEFT JOIN comments c ON t.username = c.writed_by GROUP BY t.username ORDER BY LOWER(t.username) ASC;");

    q.exec();
    while (q.next())
    {
        std::string name    = q.value(0).toString().toStdString();
        int type = q.value(1).toInt();
        int can_vote = q.value(2).toInt();
        int vote_cnt = q.value(3).toInt();
        int comm_cnt = q.value(4).toInt();
        int online = (int)(*isConnected)(name.c_str());
        nr_users++;
        char user[500];
        sprintf(user, "%s|%d|%d|%d|%d|%d||", name.c_str(), type, can_vote, vote_cnt, comm_cnt, online);
        strncat(data, user, strlen(user));
    }

    if (nr_users > 0)
    {
        sprintf(data, "%d|%s", nr_users, std::string(data).c_str());
    }
    else
    {
        strcpy(data, "FAIL|Nici un utilizator gasit!");
    }

    return (ok);
}

DataHandler::~DataHandler()
{
    DB.close();
}
