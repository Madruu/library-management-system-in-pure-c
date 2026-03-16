#ifndef PG_H
#define PG_H

#include <libpq-fe.h>

#define DB_USER "USER_FOR_DB"
#define DB_NAME "NAME_FOR_DB"
#define DB_PASSWORD "PASSWORD_FOR_DB"
#define DB_HOST "HOST_FOR_DB"
#define DB_PORT 5432

char *executeQueryToJson(const char *query);
char *formatResultAsJson(PGresult *result);

#endif