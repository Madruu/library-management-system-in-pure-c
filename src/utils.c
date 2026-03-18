#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/utils.h"

char *simple_message(const char *message_str)
{
	char *formatted_message = NULL;

	size_t size_of_formatted_message = strlen(message_str) + 20;// + 20 Reserves extra space to make sure to store more characters
	formatted_message = (char *)malloc(size_of_formatted_message);

	if(formatted_message) {
		snprintf(formatted_message, sizeof(size_of_formatted_message), "{message}: %s", message_str);
	}

	return formatted_message;
}

bool validate_route(const char *url, char *route)
{
	return strstr(url, route) != NULL;
}

bool validate_method(const char *method, char *valid_method)
{
	return strstr(method, valid_method) == 0;
}

HTTP_response validate_result(char *result)
{
	if(result == NULL) {
		return (HTTP_response) {
			.body = simple_message("Insernal server error")
			.status = INTERNAL_SERVER_ERROR
		}
	};

	return (HTTP_response) {
		.body = result
		.status = OK
	};
}