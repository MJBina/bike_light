/* ----------------------------------------------------------------------------
 * bike_light_hw.h
 *
 * This file encapsulates all definitions that are specific to the hardware
 * platform for the Bike Light project.
 *
 =========================================================================== */

#ifndef BIKE_LIGHT_HW_H
#define BIKE_LIGHT_HW_H

//  GPIO 19 is SCL
//  GPIO 18 is SDA

// #define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
// #define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_SCL_IO           19      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           18      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#endif  //  BIKE_LIGHT_HW_H

// eof
