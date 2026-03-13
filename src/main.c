#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include "headers/handler.h"

#define PORT 3000

int main()
{
	printf("Server listening on port %d\n", PORT);

	struct MHD_Daemon *daemon;

	//Starts API with MHD_daemon
	daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL, &default_handler, NULL, MHD_OPTION_END);

	if(!daemon){
		return 1;
	}

	//Keeps server active
	while(1){
		sleep(1);
	}

	//Stops Daemon
	MHD_stop_daemon(daemon);

	return 0;
}
