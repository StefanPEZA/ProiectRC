#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#define DATABASE_NAME    "MainDB.db"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>

class DataHandler
{
public:
   static int connections_count;
   DataHandler();
   bool TryLogin(int *usertype, const char *username, const char *password, char *data); //autentificare
   bool TryRegister(int *usertype, const char *username, const char *password,           //inregistrare
                    const char *first_name, const char *last_name, int acc_type, char *data);
   char *GetSongsTop(char *genre);                                                       //returneaza topul de melodii
   bool GetComments(int song_id, char *data);                                            //returneaza comentariile unei melodii
   bool AddComment(int song_id, const char *username, const char *comment, char *data);  //adauga un comentariu
   bool VoteSong(const char *username, int song_id, char *data, bool is_upvote = true);  //adauga/retrage un vot
   bool AddSong(const char *name, const char *author, const char *description,           //adauga o melodie la top
                const char *link, const char *genres, char *data);
   bool RemoveSong(int song_id, char *data);                                             //sterge o melodie din top
   bool RestrictVoteRight(const char *username, int has_right, char *data);              //restrictioneaza/ofera dreptul la vot

   ~DataHandler();
private:
   QString connection_name;
   QSqlDatabase DB;
   int GetLastSongId();
};

#endif // DATAHANDLER_H
