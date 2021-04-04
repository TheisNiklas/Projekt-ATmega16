enum CO2_Error_t
{
	CO2_NOERROR = 0,
	CO2_ERROR = 1
};
typedef enum CO2_Error_t CO2_Error_t;

enum CO2_AutocalibMode_t
{
	CO2_AUTOCAL_INACTIVE = 0,
	CO2_AUTOCAL_ACTIVE = 1
};
typedef enum CO2_AutocalibMode_t CO2_AutocalibMode_t;

enum CO2_MeasurementState_t
{
	CO2_MEAS_STOPPED = 0,
	CO2_MEAS_RUNNING = 1
};
typedef enum CO2_MeasurementState_t CO2_MeasurementState_t;

struct SensorData_t
{
	//uint8_t new_data_available_u8;
	float co2_value_f;
	float humidity_value_f;
	float temperature_value_f;
	CO2_AutocalibMode_t AutocalibMode_en;
	CO2_MeasurementState_t MeasState_en;
	uint16_t firmware_version_u16;
};
typedef struct SensorData_t SensorData_t;

struct SensorConfigData_t
{
	uint16_t meas_interval_in_sec_u16;
	uint16_t ambient_pressure_in_mbar_u16;
	uint16_t altitude_in_m_u16;
	uint16_t temp_offset_u16;
};
typedef struct SensorConfigData_t SensorConfigData_t;

CO2_Error_t CO2_InitSensor(SensorData_t *SensorData_st);
CO2_Error_t CO2_ConfigSensor(SensorConfigData_t *SensorConfigData_st);
CO2_Error_t CO2_StartMeasurement(void);
CO2_Error_t CO2_StopMeasurement(void);
CO2_Error_t CO2_UpdateMeasData(void);
CO2_Error_t CO2_UpdateSensorParameterData(void);
CO2_Error_t CO2_StartAutoCalibrationMode(void);
CO2_Error_t CO2_StopAutoCalibrationMode(void);
CO2_Error_t CO2_SetCO2CalibrationValue(uint16_t Co2_concentration_in_ppm);


