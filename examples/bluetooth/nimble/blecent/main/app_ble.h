#ifndef APP_BLE_H
#define APP_BLE_H


/**
 * @brief     This function will read and get the data of characteristic with given UUID
 *
 * @param[in]    uuid  UUID of the characteristic
 * @param[inout] data  The buffer to store data
 * @param[inout]  len   The buffer length
 *
 * @return
 *     - Status code
 */

int ble_read_chr(uint16_t uuid, uint8_t *data, uint16_t *len);

/**
 * @brief     This function will write the given data to the
              data of characteristic with given UUID
 *
 * @param[in]    uuid  UUID of the characteristic
 * @param[in]    data  The buffer containing data to be written
 * @param[in]    len   The length of data
 * 
 * @return
 *     - Status code
 */
int ble_write_chr(uint16_t uuid, uint8_t *data, uint16_t len);
 /**
 * @brief     This function will waits for given timeout to discover and connect to the device
 *             Then it will connect to the device with given device name
 * @param[in]    dev_name  The name of the device to connect
 * @param[in]    timeout_in_msec  The timeout in miliseconds
 * 
 * @return
 *     - Status code
 */
int ble_connect(const char *dev_name, int timeout_in_msec);

#endif
