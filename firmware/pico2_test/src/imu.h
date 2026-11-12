#define IMU_SPI spi0
#define IMU_SCK  2
#define IMU_MOSI 3
#define IMU_MISO 0
#define IMU_CS   1

int setup_imu();
void read_imu(float imu_data[6]);
float read_imu_temp();
void disable_imu();