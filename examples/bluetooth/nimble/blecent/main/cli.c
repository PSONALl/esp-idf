#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "console/console.h"
#include "services/gap/ble_svc_gap.h"
#include <stdio.h>
#include <ctype.h>
#include "esp_log.h"
#include <string.h>
#include <esp_log.h>
#include <esp_console.h>
#include <driver/uart.h>
#include <assert.h>
#include "host/ble_hs.h"
#include "modlog/modlog.h"

#include "blecent.h"
#include "app_ble.h"

static int blecent_read(int argc, char *argv[]);
static int blecent_write(int argc, char *argv[]);
static int blecent_connect(int argc, char *argv[]);

static esp_console_cmd_t cmds[] = {
    {
        .command = "ble-chr-read",
        .help = "read characteristics data",
        .func = blecent_read,
    },
    {
        .command = "ble-chr-write",
        .help = "write characteristics data",
        .func = blecent_write,
    },
    {
        .command = "ble-connect",
        .help = "list all  characteristics data",
        .func = blecent_connect,
    },
};
static int ble_register_cli(void)
{
    int cmds_num = sizeof(cmds) / sizeof(esp_console_cmd_t);
    int i;
    for (i = 0; i < cmds_num; i++) {
        esp_console_cmd_register(&cmds[i]);
    }
    return 0;
}
int scli_init(void)
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    // init console REPL environment
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ble_register_cli();
    ESP_ERROR_CHECK(esp_console_start_repl(repl));

    return ESP_OK;
}

static int blecent_read(int argc, char *argv[])
{
    int rc;
    uint8_t data[50];
    uint16_t len = 50;
    uint16_t uuid = 0x1811;
    rc = ble_read_chr(uuid, data, &len);

    if (rc != 0) {
        MODLOG_DFLT(ERROR, "Error: Failed to read characteristic; rc=%d\n",
                    rc);
        goto err;
    }
    printf("Read Complete status= %d ", rc);
    int i;
    printf("Data length= %d ", len);
    printf("Data =");
    for ( i = 0; i < len; i++ ) {
        printf("0x%02x ", data[i]);
    }


err:

    return 0;
}

static int blecent_write(int argc, char *argv[])
{
    int rc;
    uint8_t data[2] = {0x03, 0x04};
    uint16_t len = 2;
    uint16_t uuid = 0x1811;
    rc = ble_write_chr(uuid, data, len);

    if (rc != 0) {
        MODLOG_DFLT(ERROR, "Error: Failed to write characteristic; rc=%d\n",
                    rc);
        goto err;
    }
    printf("Write Complete status= %d ", rc);

err:

    return 0;
}
static int blecent_connect(int argc, char *argv[])
{
    int timeout = 10000;
    char dev_name[] = "ble-light";
                      int rc;
    rc = ble_connect( dev_name, timeout );
    if (rc != 0) {
        MODLOG_DFLT(ERROR, "Error: Failed to read characteristic; rc=%d\n",
                    rc);
        goto err;
    }

err:

    return 0;
}
