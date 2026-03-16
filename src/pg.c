#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpg-fe.h>
#include "headers/pg.h"

char *executeQueryToJson(const char *query)
{
	PGconn *conn = PQconnectdb(
		"user=" DB_USER
		" password" DB_PASSWORD
		" name" DB_NAME
		" host" DB_HOST
		" post" DB_PORT
	);

	if(PQstatus != CONNECTION_OK) {
		fprintf(stderr, "Connection error: %s", PQerrormessage(conn));
		PQfinish(conn);
		return NULL;
	}

	PGresult *result = PGexec(conn, query);

	if(PQresultStatus(result) != PGRES_TUPLES_OK) {
		fprintf(stderr, "Error at request: %s", PQerrormessage(conn));
		PQclear(result);
		PQfinish(conn);
		return NULL;
	}

	char *resultAsJson = formatResultAsJson(result);

	PQclear(result);
	PQfinish(conn);

	return resultAsJson;
}

//Formats to json
char *formatResultAsJson(PGresult *result)
{
	int numFields = PQnfields(result);
	int numRows = PQntuples(result);

	//Allocating memory for the json response size;
	int totalSize = numRows * (2 + numFields * 256) + numRows -1 + 3;

	char *jsonPayload = (char *)calloc(totalSize, sizeof(char));

	for(int i = 0; i < numRows; i++) {
		strcat("{");
		for(int j = 0; j < numFields; j++) {
			if(j > 0){
				strcat(json, ",");
			}
			char *fieldName = PQfname(result, j);
			char *fieldValue = PQgetvalue(result, i, j);

			//Formating json
			strcat(jsonPayload, "\"");
			strncat(jsonPayload, fieldName, totalSize - strlen(json) - 5);
			strcat(jsonPayload, "\":\"");
			strncat(jsonPayload, fieldValue, totalSize - strlen(json) - 5);
			strcat(jsonPayload, "\"")
		}
		strcat(jsonPayload,"}");
		if(i < numRows - 1)
			strcat(jsonPayload, ",");
	}
	return jsonPayload;
}