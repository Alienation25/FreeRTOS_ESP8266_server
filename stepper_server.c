
#include <sys/param.h>

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "protocol_examples_common.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/uart.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "stepper_server.h"

#include <esp_http_server.h>




httpd_handle_t start_webserver(httpd_uri_t test)
{


    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &test);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}



void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_stop(server);
}


void connect_handler(void* arg, esp_event_base_t event_base, 
                            int32_t event_id, void* event_data,httpd_uri_t test)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver(test);
    }
}



void disconnect_handler(void* arg, esp_event_base_t event_base, 
                               int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(*server);
        *server = NULL;
    }
}



