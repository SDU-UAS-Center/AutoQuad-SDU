// MESSAGE DETECHTOR PACKING

#define MAVLINK_MSG_ID_DETECHTOR 232

typedef struct __mavlink_detechtor_t
{
 float no2; ///< NO2 ppm
 float no2_voltage; ///< NO2 mV
 float no2_aux_voltage; ///< NO2-AUX mV
 float so2; ///< SO2 ppm
 float so2_voltage; ///< SO2 mV
 float so2_aux_voltage; ///< SO2-AUX mV
 float no; ///< NO ppm
 float no_voltage; ///< NO mV
 float no_aux_voltage; ///< NO-AUX mV
 float co2; ///< CO2 ppm
 float temperature; ///< Temperature C
 float humidity; ///< Humidity RH
 float grab; ///< Sample
 uint32_t timestamp; ///< Timestamp
} mavlink_detechtor_t;

#define MAVLINK_MSG_ID_DETECHTOR_LEN 56
#define MAVLINK_MSG_ID_232_LEN 56

#define MAVLINK_MSG_ID_DETECHTOR_CRC 137
#define MAVLINK_MSG_ID_232_CRC 137



#define MAVLINK_MESSAGE_INFO_DETECHTOR { \
	"DETECHTOR", \
	14, \
	{  { "no2", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_detechtor_t, no2) }, \
         { "no2_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_detechtor_t, no2_voltage) }, \
         { "no2_aux_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_detechtor_t, no2_aux_voltage) }, \
         { "so2", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_detechtor_t, so2) }, \
         { "so2_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_detechtor_t, so2_voltage) }, \
         { "so2_aux_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_detechtor_t, so2_aux_voltage) }, \
         { "no", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_detechtor_t, no) }, \
         { "no_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_detechtor_t, no_voltage) }, \
         { "no_aux_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_detechtor_t, no_aux_voltage) }, \
         { "co2", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_detechtor_t, co2) }, \
         { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_detechtor_t, temperature) }, \
         { "humidity", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_detechtor_t, humidity) }, \
         { "grab", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_detechtor_t, grab) }, \
         { "timestamp", NULL, MAVLINK_TYPE_UINT32_T, 0, 52, offsetof(mavlink_detechtor_t, timestamp) }, \
         } \
}


/**
 * @brief Pack a detechtor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param no2 NO2 ppm
 * @param no2_voltage NO2 mV
 * @param no2_aux_voltage NO2-AUX mV
 * @param so2 SO2 ppm
 * @param so2_voltage SO2 mV
 * @param so2_aux_voltage SO2-AUX mV
 * @param no NO ppm
 * @param no_voltage NO mV
 * @param no_aux_voltage NO-AUX mV
 * @param co2 CO2 ppm
 * @param temperature Temperature C
 * @param humidity Humidity RH
 * @param grab Sample
 * @param timestamp Timestamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_detechtor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float no2, float no2_voltage, float no2_aux_voltage, float so2, float so2_voltage, float so2_aux_voltage, float no, float no_voltage, float no_aux_voltage, float co2, float temperature, float humidity, float grab, uint32_t timestamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_DETECHTOR_LEN];
	_mav_put_float(buf, 0, no2);
	_mav_put_float(buf, 4, no2_voltage);
	_mav_put_float(buf, 8, no2_aux_voltage);
	_mav_put_float(buf, 12, so2);
	_mav_put_float(buf, 16, so2_voltage);
	_mav_put_float(buf, 20, so2_aux_voltage);
	_mav_put_float(buf, 24, no);
	_mav_put_float(buf, 28, no_voltage);
	_mav_put_float(buf, 32, no_aux_voltage);
	_mav_put_float(buf, 36, co2);
	_mav_put_float(buf, 40, temperature);
	_mav_put_float(buf, 44, humidity);
	_mav_put_float(buf, 48, grab);
	_mav_put_uint32_t(buf, 52, timestamp);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DETECHTOR_LEN);
#else
	mavlink_detechtor_t packet;
	packet.no2 = no2;
	packet.no2_voltage = no2_voltage;
	packet.no2_aux_voltage = no2_aux_voltage;
	packet.so2 = so2;
	packet.so2_voltage = so2_voltage;
	packet.so2_aux_voltage = so2_aux_voltage;
	packet.no = no;
	packet.no_voltage = no_voltage;
	packet.no_aux_voltage = no_aux_voltage;
	packet.co2 = co2;
	packet.temperature = temperature;
	packet.humidity = humidity;
	packet.grab = grab;
	packet.timestamp = timestamp;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_DETECHTOR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
}

/**
 * @brief Pack a detechtor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param no2 NO2 ppm
 * @param no2_voltage NO2 mV
 * @param no2_aux_voltage NO2-AUX mV
 * @param so2 SO2 ppm
 * @param so2_voltage SO2 mV
 * @param so2_aux_voltage SO2-AUX mV
 * @param no NO ppm
 * @param no_voltage NO mV
 * @param no_aux_voltage NO-AUX mV
 * @param co2 CO2 ppm
 * @param temperature Temperature C
 * @param humidity Humidity RH
 * @param grab Sample
 * @param timestamp Timestamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_detechtor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float no2,float no2_voltage,float no2_aux_voltage,float so2,float so2_voltage,float so2_aux_voltage,float no,float no_voltage,float no_aux_voltage,float co2,float temperature,float humidity,float grab,uint32_t timestamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_DETECHTOR_LEN];
	_mav_put_float(buf, 0, no2);
	_mav_put_float(buf, 4, no2_voltage);
	_mav_put_float(buf, 8, no2_aux_voltage);
	_mav_put_float(buf, 12, so2);
	_mav_put_float(buf, 16, so2_voltage);
	_mav_put_float(buf, 20, so2_aux_voltage);
	_mav_put_float(buf, 24, no);
	_mav_put_float(buf, 28, no_voltage);
	_mav_put_float(buf, 32, no_aux_voltage);
	_mav_put_float(buf, 36, co2);
	_mav_put_float(buf, 40, temperature);
	_mav_put_float(buf, 44, humidity);
	_mav_put_float(buf, 48, grab);
	_mav_put_uint32_t(buf, 52, timestamp);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DETECHTOR_LEN);
#else
	mavlink_detechtor_t packet;
	packet.no2 = no2;
	packet.no2_voltage = no2_voltage;
	packet.no2_aux_voltage = no2_aux_voltage;
	packet.so2 = so2;
	packet.so2_voltage = so2_voltage;
	packet.so2_aux_voltage = so2_aux_voltage;
	packet.no = no;
	packet.no_voltage = no_voltage;
	packet.no_aux_voltage = no_aux_voltage;
	packet.co2 = co2;
	packet.temperature = temperature;
	packet.humidity = humidity;
	packet.grab = grab;
	packet.timestamp = timestamp;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_DETECHTOR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
}

/**
 * @brief Encode a detechtor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param detechtor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_detechtor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_detechtor_t* detechtor)
{
	return mavlink_msg_detechtor_pack(system_id, component_id, msg, detechtor->no2, detechtor->no2_voltage, detechtor->no2_aux_voltage, detechtor->so2, detechtor->so2_voltage, detechtor->so2_aux_voltage, detechtor->no, detechtor->no_voltage, detechtor->no_aux_voltage, detechtor->co2, detechtor->temperature, detechtor->humidity, detechtor->grab, detechtor->timestamp);
}

/**
 * @brief Encode a detechtor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param detechtor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_detechtor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_detechtor_t* detechtor)
{
	return mavlink_msg_detechtor_pack_chan(system_id, component_id, chan, msg, detechtor->no2, detechtor->no2_voltage, detechtor->no2_aux_voltage, detechtor->so2, detechtor->so2_voltage, detechtor->so2_aux_voltage, detechtor->no, detechtor->no_voltage, detechtor->no_aux_voltage, detechtor->co2, detechtor->temperature, detechtor->humidity, detechtor->grab, detechtor->timestamp);
}

/**
 * @brief Send a detechtor message
 * @param chan MAVLink channel to send the message
 *
 * @param no2 NO2 ppm
 * @param no2_voltage NO2 mV
 * @param no2_aux_voltage NO2-AUX mV
 * @param so2 SO2 ppm
 * @param so2_voltage SO2 mV
 * @param so2_aux_voltage SO2-AUX mV
 * @param no NO ppm
 * @param no_voltage NO mV
 * @param no_aux_voltage NO-AUX mV
 * @param co2 CO2 ppm
 * @param temperature Temperature C
 * @param humidity Humidity RH
 * @param grab Sample
 * @param timestamp Timestamp
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_detechtor_send(mavlink_channel_t chan, float no2, float no2_voltage, float no2_aux_voltage, float so2, float so2_voltage, float so2_aux_voltage, float no, float no_voltage, float no_aux_voltage, float co2, float temperature, float humidity, float grab, uint32_t timestamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_DETECHTOR_LEN];
	_mav_put_float(buf, 0, no2);
	_mav_put_float(buf, 4, no2_voltage);
	_mav_put_float(buf, 8, no2_aux_voltage);
	_mav_put_float(buf, 12, so2);
	_mav_put_float(buf, 16, so2_voltage);
	_mav_put_float(buf, 20, so2_aux_voltage);
	_mav_put_float(buf, 24, no);
	_mav_put_float(buf, 28, no_voltage);
	_mav_put_float(buf, 32, no_aux_voltage);
	_mav_put_float(buf, 36, co2);
	_mav_put_float(buf, 40, temperature);
	_mav_put_float(buf, 44, humidity);
	_mav_put_float(buf, 48, grab);
	_mav_put_uint32_t(buf, 52, timestamp);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, buf, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, buf, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
#else
	mavlink_detechtor_t packet;
	packet.no2 = no2;
	packet.no2_voltage = no2_voltage;
	packet.no2_aux_voltage = no2_aux_voltage;
	packet.so2 = so2;
	packet.so2_voltage = so2_voltage;
	packet.so2_aux_voltage = so2_aux_voltage;
	packet.no = no;
	packet.no_voltage = no_voltage;
	packet.no_aux_voltage = no_aux_voltage;
	packet.co2 = co2;
	packet.temperature = temperature;
	packet.humidity = humidity;
	packet.grab = grab;
	packet.timestamp = timestamp;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, (const char *)&packet, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, (const char *)&packet, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_DETECHTOR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_detechtor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float no2, float no2_voltage, float no2_aux_voltage, float so2, float so2_voltage, float so2_aux_voltage, float no, float no_voltage, float no_aux_voltage, float co2, float temperature, float humidity, float grab, uint32_t timestamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, no2);
	_mav_put_float(buf, 4, no2_voltage);
	_mav_put_float(buf, 8, no2_aux_voltage);
	_mav_put_float(buf, 12, so2);
	_mav_put_float(buf, 16, so2_voltage);
	_mav_put_float(buf, 20, so2_aux_voltage);
	_mav_put_float(buf, 24, no);
	_mav_put_float(buf, 28, no_voltage);
	_mav_put_float(buf, 32, no_aux_voltage);
	_mav_put_float(buf, 36, co2);
	_mav_put_float(buf, 40, temperature);
	_mav_put_float(buf, 44, humidity);
	_mav_put_float(buf, 48, grab);
	_mav_put_uint32_t(buf, 52, timestamp);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, buf, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, buf, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
#else
	mavlink_detechtor_t *packet = (mavlink_detechtor_t *)msgbuf;
	packet->no2 = no2;
	packet->no2_voltage = no2_voltage;
	packet->no2_aux_voltage = no2_aux_voltage;
	packet->so2 = so2;
	packet->so2_voltage = so2_voltage;
	packet->so2_aux_voltage = so2_aux_voltage;
	packet->no = no;
	packet->no_voltage = no_voltage;
	packet->no_aux_voltage = no_aux_voltage;
	packet->co2 = co2;
	packet->temperature = temperature;
	packet->humidity = humidity;
	packet->grab = grab;
	packet->timestamp = timestamp;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, (const char *)packet, MAVLINK_MSG_ID_DETECHTOR_LEN, MAVLINK_MSG_ID_DETECHTOR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DETECHTOR, (const char *)packet, MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE DETECHTOR UNPACKING


/**
 * @brief Get field no2 from detechtor message
 *
 * @return NO2 ppm
 */
static inline float mavlink_msg_detechtor_get_no2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field no2_voltage from detechtor message
 *
 * @return NO2 mV
 */
static inline float mavlink_msg_detechtor_get_no2_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field no2_aux_voltage from detechtor message
 *
 * @return NO2-AUX mV
 */
static inline float mavlink_msg_detechtor_get_no2_aux_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field so2 from detechtor message
 *
 * @return SO2 ppm
 */
static inline float mavlink_msg_detechtor_get_so2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field so2_voltage from detechtor message
 *
 * @return SO2 mV
 */
static inline float mavlink_msg_detechtor_get_so2_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field so2_aux_voltage from detechtor message
 *
 * @return SO2-AUX mV
 */
static inline float mavlink_msg_detechtor_get_so2_aux_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field no from detechtor message
 *
 * @return NO ppm
 */
static inline float mavlink_msg_detechtor_get_no(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field no_voltage from detechtor message
 *
 * @return NO mV
 */
static inline float mavlink_msg_detechtor_get_no_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field no_aux_voltage from detechtor message
 *
 * @return NO-AUX mV
 */
static inline float mavlink_msg_detechtor_get_no_aux_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field co2 from detechtor message
 *
 * @return CO2 ppm
 */
static inline float mavlink_msg_detechtor_get_co2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field temperature from detechtor message
 *
 * @return Temperature C
 */
static inline float mavlink_msg_detechtor_get_temperature(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field humidity from detechtor message
 *
 * @return Humidity RH
 */
static inline float mavlink_msg_detechtor_get_humidity(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field grab from detechtor message
 *
 * @return Sample
 */
static inline float mavlink_msg_detechtor_get_grab(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field timestamp from detechtor message
 *
 * @return Timestamp
 */
static inline uint32_t mavlink_msg_detechtor_get_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  52);
}

/**
 * @brief Decode a detechtor message into a struct
 *
 * @param msg The message to decode
 * @param detechtor C-struct to decode the message contents into
 */
static inline void mavlink_msg_detechtor_decode(const mavlink_message_t* msg, mavlink_detechtor_t* detechtor)
{
#if MAVLINK_NEED_BYTE_SWAP
	detechtor->no2 = mavlink_msg_detechtor_get_no2(msg);
	detechtor->no2_voltage = mavlink_msg_detechtor_get_no2_voltage(msg);
	detechtor->no2_aux_voltage = mavlink_msg_detechtor_get_no2_aux_voltage(msg);
	detechtor->so2 = mavlink_msg_detechtor_get_so2(msg);
	detechtor->so2_voltage = mavlink_msg_detechtor_get_so2_voltage(msg);
	detechtor->so2_aux_voltage = mavlink_msg_detechtor_get_so2_aux_voltage(msg);
	detechtor->no = mavlink_msg_detechtor_get_no(msg);
	detechtor->no_voltage = mavlink_msg_detechtor_get_no_voltage(msg);
	detechtor->no_aux_voltage = mavlink_msg_detechtor_get_no_aux_voltage(msg);
	detechtor->co2 = mavlink_msg_detechtor_get_co2(msg);
	detechtor->temperature = mavlink_msg_detechtor_get_temperature(msg);
	detechtor->humidity = mavlink_msg_detechtor_get_humidity(msg);
	detechtor->grab = mavlink_msg_detechtor_get_grab(msg);
	detechtor->timestamp = mavlink_msg_detechtor_get_timestamp(msg);
#else
	memcpy(detechtor, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_DETECHTOR_LEN);
#endif
}
