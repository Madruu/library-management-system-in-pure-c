#ifndef USER_CONTOLLER
#define USER_CONTOLLER
#include "utils.h"

HTTP_response get_all_users(const char *url);

HTTP_response get_user_by_id(const char *user_id);

HTTP_response create_user(const char *body);

HTTP_response update_user(const char *user_id, const char *body);

HTTP_response delete_user(const char *user_id)

HTTP_response user_router(const char *url, const char *method, const char *body);

#endif