//
// Created by markj on 6/11/2024.
//

#ifndef BIKE_LIGHT_MPU6050_H
#define BIKE_LIGHT_MPU6050_H

#define MPU6050_SENSOR_ADDR                 0x68        /*!< Slave address of the MPU6050 sensor */
#define MPU6050_WHO_AM_I_REG_ADDR           0x75        /*!< Register addresses of the "who am I" register */
#define MPU6050_PWR_MGMT_1_REG_ADDR         0x6B        /*!< Register addresses of the power management register */
#define MPU6050_RESET_BIT                   7


extern void mpu6050_configure(void);

extern void mpu6050_diagnostic(void);


#endif //BIKE_LIGHT_MPU6050_H
