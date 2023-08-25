struct estructura {
	String type[4][10];         
	String command[4][10];
	uint8_t max[4][10];
	uint8_t timeout[4][10];
	
	String mac;
	String firmware_version;
	float voltage_coefficient;
	uint32_t unix_time;
	uint32_t wakeup_number;
	bool modo12;
	bool manual_measure;
	bool offline;
};