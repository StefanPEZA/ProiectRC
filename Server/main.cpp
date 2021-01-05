#include <QCoreApplication>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string>

#include "datahandler.h"
using namespace std;

extern int errno;

#define ADMIN_CODE    40678              /* cod conectare admin */
pthread_mutex_t mut;

#define PORT          2121                         /* protocolul default */
#define QLEN          6                            /* numarul maxim de clienti care asteapta in coada serverului*/

int            atempt_count = 0;                   /* numarul de clienti acceptati*/
list <string>* client_names = new list <string>(); /* retine numele de utilizator a fiecarui client autentificat*/

void* serverthread(void*
                   client_socket);           /* functia thread care se ocupa de un anumit client   */

//functie ce se ocupa de executarea cererii unui client
bool HandleRequest(int* usertype, int tnumber, const char* username,
                   char* request, char* response, DataHandler* DB_handler);

//functie prin care se incearca autentificarea unui utilizator
bool TryClientLogin(int* usertype, int thread_number, const char* username,
                    const char* password, char* response, DataHandler* database);

//functie prin care se incearca inregistrarea unui utilizator
bool TryClientRegister(int* usertype, int thread_number, const char* username,
                       const char* passsword, const char* first_name, const char* last_name,
                       int acount_type, char* response, DataHandler* database);

//functie ce returneaza in response topul cu melodii
bool GetSongTop(DataHandler* database, char* genre, char* response);

/* funtie care cauta utilizatorul in lista de utilizatori deja auentificati */
bool userAlreadyConnected(const char* username)
{
    for (list <string>::iterator it = client_names->begin(); it != client_names->end(); it++)
    {
        if (!strcmp((*it).c_str(), username))
        {
            return (true);
        }
    }
    return (false);
}

/* functie de convertire a adresei IP a clientului in sir de caractere */
char* ip_toStr(struct sockaddr_in address)
{
    static char str[25];

    /* adresa IP a clientului */
    sprintf(str, "%s", inet_ntoa(address.sin_addr));
    return (str);
}

int main(int argc, char* argv[])
{
    struct   sockaddr_in server_info; /* structura care salveaza adresa serverului */
    struct   sockaddr_in client_info; /* structura care salveaza adresa clientului */
    int       sv_sock, client_sock;   /* descriptori de socket */
    int       port;                   /* protocolul folosit */
    socklen_t addrlen;                /* lungimea structurii sockaddr_in - 'client_info' */
    pthread_t tid;                    /* salveaza id-ul thread-ului */

    pthread_mutex_init(&mut, NULL);

    /* pregatim structurile de date */
    memset((char*)&server_info, 0, sizeof(server_info));
    memset((char*)&client_info, 0, sizeof(client_info));
    server_info.sin_family      = AF_INET;    /* stabilirea familiei de socket-uri */
    server_info.sin_addr.s_addr = INADDR_ANY; /* acceptam orice adresa */

    if (argc > 1)
    {
        port = atoi(argv[1]);/* portul specificat ca argument*/
    }
    else
    {
        port = PORT;         /* portul default */
    }

    if (port > 0)
    {
        server_info.sin_port = htons((u_short)port); /*setam portul server-ului*/
    }
    else
    {
        fprintf(stderr, "[ERROR]>>Numarul portului este gresit: %s/n", argv[1]);
        exit(1);
    }

    /* Creem soket-ul*/
    sv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sv_sock < 0)
    {
        perror("[ERROR]>>Eroare la crearea socket-ului server!\n");
        close(sv_sock);
        exit(1);
    }

    int yes = 1; /*setam pentru socket optiunea SO_REUSEADDR */
    if (setsockopt(sv_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        perror("[ERROR]>>Nu s-a putut seta optiunea TCP : SO_REUSEADDR");
    }

    /* Leaga o adresa locala de soket */
    if (bind(sv_sock, (struct sockaddr*)&server_info, sizeof(server_info)) < 0)
    {
        perror("[ERROR]>>Eroare la realizarea legaturii! \n");
        close(sv_sock);
        exit(1);
    }

    /* Serverul asteapta conectiuni */
    if (listen(sv_sock, QLEN) < 0)
    {
        perror("[ERROR]>>Eroare la asculatere!\n");
        close(sv_sock);
        exit(1);
    }

    addrlen = sizeof(client_info);

    /* Bucla principala a serverului. Accepta clienti. Creaza un thread pentru fiecare client acceptat. */
    printf("[SERVER]>>Server-ul asculta cereri de conectare la portul : %d\n", port);
    fflush(stdout);
    while (true)
    {
        if ((client_sock = accept(sv_sock, (struct sockaddr*)&client_info, &addrlen)) < 0)
        {
            perror("[ERROR]>>Un client a fost respins.\n");
            continue;
        }
        printf("[SERVER]>>Cerere de conectare de la: %s\n", ip_toStr(client_info));
        fflush(stdout);
        if (pthread_create(&tid, NULL, serverthread, (void*)&client_sock) != 0)
        {
            fprintf(stderr, "[ERROR]>>Nu s-a putut crea thread-ul! : %s", strerror(errno));
            continue;
        }
        pthread_detach(tid);
    }

    close(sv_sock);
    return (0);
}

void* serverthread(void* client_socket)
{
    pthread_mutex_lock(&mut);
    int tnumber = ++atempt_count;
    pthread_mutex_unlock(&mut);
    DataHandler DB_handler;

    printf("[SERVER]>>S-a creat un thread pentru clientul #%d\n", tnumber);
    fflush(stdout);

    unsigned int msg_size = 0;          /* marimea mesajului primit/trimis */
    int          usertype = 0;          /* tipul de utilizator: obisnuit/admin */
    char         username[30];          /* numele utiliatorului conectat */
    bool         has_access = false;    /* daca clientul este autentificat sau nu*/
    int          tc_sock;               /* desriptorul de socket asociat clientului */
    char         request[4096]    = ""; /* buffer pentru datele primite la server de la client*/
    char         response[102400] = ""; /* buffer pentru datele trimise de server catre client */


    tc_sock = *(int*)client_socket;

    while (1)
    {
        if (read(tc_sock, &msg_size, 4) <= 0)
        {
            if (!has_access)
            {
                fprintf(stderr, "[SERVER]>>Clientul (%d) a pierdut conectiunea!\n", tnumber);
                close(tc_sock);
                pthread_exit(0);
            }
            break;
        }
        if (read(tc_sock, request, msg_size) <= 0)
        {
            if (!has_access)
            {
                fprintf(stderr, "[SERVER]>>Clientul (%d) a pierdut conectiunea!\n", tnumber);
                close(tc_sock);
                pthread_exit(0);
            }
            break;
        }
        request[msg_size] = '\0';

        char* saveptr;
        if (!has_access && strchr(request, '|'))
        {
            char* token = strtok_r(request, "|", &saveptr);
            if (!strcmp(token, "LOGIN") && !has_access)
            {
                sprintf(username, "%s", strtok_r(NULL, "|", &saveptr));
                char* password = strtok_r(NULL, "|", &saveptr);
                has_access = TryClientLogin(&usertype, tnumber, username, password, response, &DB_handler);
            }
            else if (!strcmp(token, "REGISTER") && !has_access)
            {
                bool ok = true;
                sprintf(username, "%s", strtok_r(NULL, "|", &saveptr));
                char* first_name = strtok_r(NULL, "|", &saveptr);
                char* last_name  = strtok_r(NULL, "|", &saveptr);
                char* password   = strtok_r(NULL, "|", &saveptr);
                int   acc_type   = atoi(strtok_r(NULL, "|", &saveptr));
                if (acc_type == 1)
                {
                    int check = atoi(strtok_r(NULL, "|", &saveptr));
                    if (check != ADMIN_CODE)
                    {
                        ok         = false;
                        has_access = false;
                    }
                }
                if (ok)
                {
                    has_access = TryClientRegister(&usertype, tnumber, username, password, first_name, last_name,
                                                   acc_type, response, &DB_handler);
                }
                else
                {
                    strcpy(response, "FAIL|Codul de admin introdus nu este un cod valid!");
                }
            }
            else
            {
                strcpy(response, "FAIL|Comanda necunoscuta!");
            }
        }
        else if (has_access && strchr(request, '|'))
        {
            HandleRequest(&usertype, tnumber, username, request, response, &DB_handler);
        }
        else
        {
            strcpy(response, "FAIL|Formatul comenzii nerecunoscut!");
        }

        msg_size = strlen(response);
        if (write(tc_sock, &msg_size, 4) <= 0)
        {
            if (!has_access)
            {
                fprintf(stderr, "[SERVER]>>Clientul (%d) a pierdut conectiunea!\n", tnumber);
                close(tc_sock);
                pthread_exit(0);
            }
            break;
        }
        if (write(tc_sock, response, msg_size) <= 0)
        {
            if (!has_access)
            {
                fprintf(stderr, "[SERVER]>>Clientul (%d) a pierdut conectiunea!\n", tnumber);
                close(tc_sock);
                pthread_exit(0);
            }
            break;
        }
    }

    fprintf(stderr, "[SERVER]>>Clientul %s (%d) s-a deconectat!\n", username, tnumber);

    pthread_mutex_lock(&mut);
    client_names->remove(*(new string(username)));
    pthread_mutex_unlock(&mut);

    close(tc_sock);
    pthread_exit(0);
}

bool HandleRequest(int* usertype, int tnumber, const char* username, char* request, char* response,
                   DataHandler* DB_handler)
{
    char* saveptr;
    char* token = strtok_r(request, "|", &saveptr);

    if (!strcmp(token, "GET_USERS"))
    {
        printf("[SERVER]>>Solicitare de la %s (%d): trimite lista cu utilizatori\n", username, tnumber);
        fflush(stdout);
        return ((*DB_handler).GetUsers(userAlreadyConnected, response));
    }
    else if (!strcmp(token, "GET_TOP"))
    {
        char* genre = strtok_r(NULL, "|", &saveptr);
        printf("[SERVER]>>Solicitare de la %s (%d): trimite topul cu melodii (genul : %s)\n", username,
               tnumber, genre);
        fflush(stdout);
        return (GetSongTop(DB_handler, genre, response));
    }
    else if (!strcmp(token, "GET_COMMS"))
    {
        char* song_id = strtok_r(NULL, "|", &saveptr);
        printf("[SERVER]>>Solicitare de la %s (%d): trimite comentariile melodiei cu id:%s!\n", username,
               tnumber, song_id);
        fflush(stdout);
        int id = atoi(song_id);
        return ((*DB_handler).GetComments(id, response));
    }
    else if (!strcmp(token, "ADD_COMM"))
    {
        int   song_id = atoi(strtok_r(NULL, "|", &saveptr));
        char* comment = strtok_r(NULL, "|", &saveptr);
        printf("[SERVER]>>Solicitare de la %s (%d): adauga un comentariu la melodia cu id:%d\n", username,
               tnumber, song_id);
        fflush(stdout);
        return ((*DB_handler).AddComment(song_id, username, comment, response));
    }
    else if (!strcmp(token, "VOTE_UP"))
    {
        int id = atoi(strtok_r(NULL, "|", &saveptr));
        printf("[SERVER]>>Solicitare de la %s (%d): voteaza melodia cu id:%d\n", username, tnumber, id);
        fflush(stdout);
        return ((*DB_handler).VoteSong(username, id, response, true));
    }
    else if (!strcmp(token, "VOTE_DOWN"))
    {
        char* id = strtok_r(NULL, "|", &saveptr);
        printf("[SERVER]>>Solicitare de la %s (%d): sterge votul dat melodiei cu id:%s\n", username,
               tnumber, id);
        fflush(stdout);
        int song_id = atoi(id);
        return ((*DB_handler).VoteSong(username, song_id, response, false));
    }
    else if (!strcmp(token, "ADD_SONG"))
    {
        char* name        = strtok_r(NULL, "|", &saveptr);
        char* author      = strtok_r(NULL, "|", &saveptr);
        char* description = strtok_r(NULL, "|", &saveptr);
        char* link        = strtok_r(NULL, "|", &saveptr);
        char* genres      = strtok_r(NULL, "|", &saveptr);
        printf("[SERVER]>>Solicitare de la %s (%d): adauga o melodie in baza de date.\n", username,
               tnumber);
        fflush(stdout);
        return ((*DB_handler).AddSong(name, author, description, link, genres, response));
    }
    else if (!strcmp(token, "DELETE_SONG"))
    {
        if (*usertype > 0)
        {
            int id = atoi(strtok_r(NULL, "|", &saveptr));
            printf("[SERVER]>>Solicitare de la %s (%d): sterge melodia cu id:%d din baza de date.\n", username,
                   tnumber, id);
            fflush(stdout);
            return ((*DB_handler).RemoveSong(id, response));
        }
    }
    else if (!strcmp(token, "CHANGE_RIGHT"))
    {
        if (*usertype > 0)
        {
            char* name      = strtok_r(NULL, "|", &saveptr);
            int   has_right = atoi(strtok_r(NULL, "|", &saveptr));
            printf("[SERVER]>>Solicitare de la %s (%d): schimba dreptul de vot al utilizatorului: %s!\n",
                   username, tnumber, name);
            fflush(stdout);
            return ((*DB_handler).RestrictVoteRight(name, has_right, response));
        }
    }
    else
    {
        strcpy(response, "FAIL|Comanda necunoscuta");
        return (true);
    }

    return (false);
}

bool TryClientLogin(int* usertype, int thread_number, const char* username, const char* password,
                    char* response, DataHandler* database)
{
    if (!userAlreadyConnected(username))
    {
        printf("[SERVER]>>Incercare de autentificare cu numele: %s! (%d)\n", username, thread_number);
        fflush(stdout);

        if ((*database).TryLogin(usertype, username, password, response))
        {
            //adaugarea clientului la lista clientilor deja autentificati pe server
            pthread_mutex_lock(&mut);
            client_names->insert(client_names->end(), *(new string(username)));
            pthread_mutex_unlock(&mut);
            fprintf(stderr, "[SERVER]>>%s s-a logat cu succes la server! (%d)\n", username, thread_number);
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        sprintf(response, "FAIL|Exista deja un client cu numele %s conectat pe server!", username);
        fflush(stdout);
        return (false);
    }
}

bool TryClientRegister(int* usertype, int thread_number, const char* username,
                       const char* passsword, const char* first_name,
                       const char* last_name, int acount_type, char* response, DataHandler* database)
{
    if (!userAlreadyConnected(username))
    {
        printf("[SERVER]>>Incercare de inregistrare cu numele: %s! (%d)\n", username, thread_number);
        fflush(stdout);
        if ((*database).TryRegister(usertype, username, passsword, first_name, last_name, acount_type,
                                    response))
        {
            //adaugarea clientului la lista clientilor deja autentificati pe server
            pthread_mutex_lock(&mut);
            client_names->insert(client_names->end(), *(new string(username)));
            pthread_mutex_unlock(&mut);
            printf("[SERVER]>>%s s-a inregistrat cu succes la server! (%d)\n", username, thread_number);
            fflush(stderr);
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        sprintf(response, "FAIL|Exista deja un client cu numele %s conectat pe server!", username);
        return (false);
    }
}

bool GetSongTop(DataHandler* database, char* genre, char* response)
{
    char* data = (*database).GetSongsTop(genre);

    if (!strcmp(data, "0|"))
    {
        strcpy(response, "FAIL|Nu s-a gasit nici o melodie in top care sa satisfaca genul ales!");
    }
    else
    {
        strcpy(response, data);
    }

    return (true);
}
