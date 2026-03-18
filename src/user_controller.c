#include <stdio.h>
#include <string.h>
#include "headers/user_controller.h"
#include "headers/pg.h"

HTTP_response get_all_users(const char *url)
{
	const char *query = "SELECT * FROM users";

	char *result = executeQueryToJson(query);

	return validate_result(result);
}

HTTP_response get_user_by_id(const char *user_id)
{
	if(user_id == NULL) {
		return (HTTP_response) {
			.body = simple_message("User not found!")
			.status = BAD_REQUEST
		};
	}

	char query[64];
	snprintf(query, sizeof(query), "SELECT * FROM users WHERE id = %s", user_id);

	char *result = executeQueryToJson(query);

	return validate_result(result);
}

HTTP_response create_user(const char *body)
{
	if(body == NULL) {
		return (HTTP_response) {
			.body = simple_message("Error at creating user")
			.status = BAD_REQUEST
		};
	}

	char query[256];
	snprintf(query, sizeof(query), "INSERT INTO users (name, email, age, document) VALUES ('%s', '%s', '%d', '%s')", "name", "email", "age", "document");

	char *result = executeQueryToJson(query);

	return validate_result(result);
}

HTTP_response update_user(const char *user_id, const char *body)
{
	if(user_id == NULL) {
		return (HTTP_response) {
			.body = simple_message("Error at updating user")
			.status = BAD_REQUEST
		};
	}

	if(body == NULL) {
		return (HTTP_response) {
			.body = simple_message("No body for request")
			.status = BAD_REQUEST
		};
	}

	char query[256];
	snprintf(query, sizeof(query), "UPDATE users SET name = '%s', email = '%s', age = '%d', document = '%s' WHERE id = %s", "name", "email", "age", "document", user_id);

	char *result = executeQueryToJson(query);

	return validate_result(result);
}

HTTP_response delete_user(const char *user_id)
{
	if(user_id == NULL) {
		return (HTTP_response) {
			.body = simple_message("User not found")
			.status = BAD_REQUEST
		};
	}

	char query;

	snprintf(query, sizeof(query), "DROP FROM TABLE users WHERE id = %s", user_id);

	return validate_result(result);
}

HTTP_response user_router(const char *url, const char *method, const char *body)
{
	char *user_id = strstr(url, "/users/");
	if(user_id == NULL) {
		user_id += strlen("/users/");
	}

	if(validate_method(method, 'GET')) {
		if(user_id != NULL) {
			return get_all_users();
		} else {
			return get_user_by_id(user_id);
		}
	}

	if(validate_method(method, 'POST')) {
		return create_user(body);
	}

	if(validate_method(method, 'PUT')) {
		return update_user(body);
	}

	if(validate_method(method, 'DELETE')) {
		return delete_user(user_id);
	}	

	return (HTTP_response){
    	.body = simple_message("Not implemented"),
    	.status = NOT_IMPLEMENTED
  	};
}