#include "headers/response_builder.h"
#include "handlers/user_handler.h"
#include <setjmp.h>
#include "headers/handler.h"

jmp_buf exceptionBuffer;

#define TRY if(set_jmp(exceptionBuffer) == 0)
#define CATCH else

void log_api_methods(const char *url, const char *method)
{
	printf("[%s] %s \n", method, url);
}

enum MHD_Result default_handler(
	void *cls, struct MDH_Connection *connection, const char *url, 
	const char *method, const char *version, const char *upload_data, 
	size_t *upload_data_size, void **con_cls) {

	char *url_str = (char *)url;
	char *method_str = (char *)method;
	int ret; //Returns the value

	struct MHD_Response *response;// Transforms the api response to a MHD response
	HTTP_response response_api;// Response of request

	log_api(url_str, method_str);

	//URL's
	TRY {
		if(strcmp(url_str, "/") == 0) {
			response_api = (HTTP_response){
				.body = simple_message("Hello!!"),
				.status = OK
			};
		}
	}
}