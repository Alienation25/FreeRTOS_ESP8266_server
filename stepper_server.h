#ifndef STEPPER_SERVER_HEADER_GUARD
#define STEPPER_SERVER_HEADER_GUARD

#include <esp_http_server.h>

static const char TAG[] = "APP";



//esp_err_t hello_get_handler(httpd_req_t *req);


httpd_handle_t start_webserver(httpd_uri_t test);
void stop_webserver(httpd_handle_t server);
void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id,void* event_data,httpd_uri_t test);
void disconnect_handler( void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);


#endif