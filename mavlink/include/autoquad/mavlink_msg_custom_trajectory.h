// MESSAGE CUSTOM_TRAJECTORY PACKING

#define MAVLINK_MSG_ID_CUSTOM_TRAJECTORY 153

typedef struct __mavlink_custom_trajectory_t
{
 float param1; ///< PARAM1, see MAV_CMD enum
 float param2; ///< PARAM2, see MAV_CMD enum
 float param3; ///< PARAM3, see MAV_CMD enum
 float param4; ///< PARAM4, see MAV_CMD enum
 float x; ///< PARAM5 / local: x position, global: latitude
 float y; ///< PARAM6 / y position: global: longitude
 float z; ///< PARAM7 / z position: global: altitude (relative or absolute, depending on frame.
 float sStart; ///< value1
 float sEnd; ///< value2
 float dsdt; ///< value3
 float N; ///< value4
 float E; ///< value5
 float D; ///< value6
 float y2N; ///< value7
 float y2E; ///< value8
 float y2D; ///< value9
 uint16_t seq; ///< Sequence
 uint16_t command; ///< The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint8_t frame; ///< The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 uint8_t current; ///< false:0, true:1
 uint8_t autocontinue; ///< autocontinue to next wp
} mavlink_custom_trajectory_t;

#define MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN 73
#define MAVLINK_MSG_ID_153_LEN 73

#define MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC 48
#define MAVLINK_MSG_ID_153_CRC 48



#define MAVLINK_MESSAGE_INFO_CUSTOM_TRAJECTORY { \
	"CUSTOM_TRAJECTORY", \
	23, \
	{  { "param1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_custom_trajectory_t, param1) }, \
         { "param2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_custom_trajectory_t, param2) }, \
         { "param3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_custom_trajectory_t, param3) }, \
         { "param4", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_custom_trajectory_t, param4) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_custom_trajectory_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_custom_trajectory_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_custom_trajectory_t, z) }, \
         { "sStart", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_custom_trajectory_t, sStart) }, \
         { "sEnd", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_custom_trajectory_t, sEnd) }, \
         { "dsdt", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_custom_trajectory_t, dsdt) }, \
         { "N", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_custom_trajectory_t, N) }, \
         { "E", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_custom_trajectory_t, E) }, \
         { "D", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_custom_trajectory_t, D) }, \
         { "y2N", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_custom_trajectory_t, y2N) }, \
         { "y2E", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_custom_trajectory_t, y2E) }, \
         { "y2D", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_custom_trajectory_t, y2D) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT16_T, 0, 64, offsetof(mavlink_custom_trajectory_t, seq) }, \
         { "command", NULL, MAVLINK_TYPE_UINT16_T, 0, 66, offsetof(mavlink_custom_trajectory_t, command) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 68, offsetof(mavlink_custom_trajectory_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 69, offsetof(mavlink_custom_trajectory_t, target_component) }, \
         { "frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 70, offsetof(mavlink_custom_trajectory_t, frame) }, \
         { "current", NULL, MAVLINK_TYPE_UINT8_T, 0, 71, offsetof(mavlink_custom_trajectory_t, current) }, \
         { "autocontinue", NULL, MAVLINK_TYPE_UINT8_T, 0, 72, offsetof(mavlink_custom_trajectory_t, autocontinue) }, \
         } \
}


/**
 * @brief Pack a custom_trajectory message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 * @param frame The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 * @param command The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
 * @param current false:0, true:1
 * @param autocontinue autocontinue to next wp
 * @param param1 PARAM1, see MAV_CMD enum
 * @param param2 PARAM2, see MAV_CMD enum
 * @param param3 PARAM3, see MAV_CMD enum
 * @param param4 PARAM4, see MAV_CMD enum
 * @param x PARAM5 / local: x position, global: latitude
 * @param y PARAM6 / y position: global: longitude
 * @param z PARAM7 / z position: global: altitude (relative or absolute, depending on frame.
 * @param sStart value1
 * @param sEnd value2
 * @param dsdt value3
 * @param N value4
 * @param E value5
 * @param D value6
 * @param y2N value7
 * @param y2E value8
 * @param y2D value9
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custom_trajectory_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint16_t seq, uint8_t frame, uint16_t command, uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, float x, float y, float z, float sStart, float sEnd, float dsdt, float N, float E, float D, float y2N, float y2E, float y2D)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN];
	_mav_put_float(buf, 0, param1);
	_mav_put_float(buf, 4, param2);
	_mav_put_float(buf, 8, param3);
	_mav_put_float(buf, 12, param4);
	_mav_put_float(buf, 16, x);
	_mav_put_float(buf, 20, y);
	_mav_put_float(buf, 24, z);
	_mav_put_float(buf, 28, sStart);
	_mav_put_float(buf, 32, sEnd);
	_mav_put_float(buf, 36, dsdt);
	_mav_put_float(buf, 40, N);
	_mav_put_float(buf, 44, E);
	_mav_put_float(buf, 48, D);
	_mav_put_float(buf, 52, y2N);
	_mav_put_float(buf, 56, y2E);
	_mav_put_float(buf, 60, y2D);
	_mav_put_uint16_t(buf, 64, seq);
	_mav_put_uint16_t(buf, 66, command);
	_mav_put_uint8_t(buf, 68, target_system);
	_mav_put_uint8_t(buf, 69, target_component);
	_mav_put_uint8_t(buf, 70, frame);
	_mav_put_uint8_t(buf, 71, current);
	_mav_put_uint8_t(buf, 72, autocontinue);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#else
	mavlink_custom_trajectory_t packet;
	packet.param1 = param1;
	packet.param2 = param2;
	packet.param3 = param3;
	packet.param4 = param4;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.sStart = sStart;
	packet.sEnd = sEnd;
	packet.dsdt = dsdt;
	packet.N = N;
	packet.E = E;
	packet.D = D;
	packet.y2N = y2N;
	packet.y2E = y2E;
	packet.y2D = y2D;
	packet.seq = seq;
	packet.command = command;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.frame = frame;
	packet.current = current;
	packet.autocontinue = autocontinue;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CUSTOM_TRAJECTORY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
}

/**
 * @brief Pack a custom_trajectory message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 * @param frame The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 * @param command The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
 * @param current false:0, true:1
 * @param autocontinue autocontinue to next wp
 * @param param1 PARAM1, see MAV_CMD enum
 * @param param2 PARAM2, see MAV_CMD enum
 * @param param3 PARAM3, see MAV_CMD enum
 * @param param4 PARAM4, see MAV_CMD enum
 * @param x PARAM5 / local: x position, global: latitude
 * @param y PARAM6 / y position: global: longitude
 * @param z PARAM7 / z position: global: altitude (relative or absolute, depending on frame.
 * @param sStart value1
 * @param sEnd value2
 * @param dsdt value3
 * @param N value4
 * @param E value5
 * @param D value6
 * @param y2N value7
 * @param y2E value8
 * @param y2D value9
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custom_trajectory_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint16_t seq,uint8_t frame,uint16_t command,uint8_t current,uint8_t autocontinue,float param1,float param2,float param3,float param4,float x,float y,float z,float sStart,float sEnd,float dsdt,float N,float E,float D,float y2N,float y2E,float y2D)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN];
	_mav_put_float(buf, 0, param1);
	_mav_put_float(buf, 4, param2);
	_mav_put_float(buf, 8, param3);
	_mav_put_float(buf, 12, param4);
	_mav_put_float(buf, 16, x);
	_mav_put_float(buf, 20, y);
	_mav_put_float(buf, 24, z);
	_mav_put_float(buf, 28, sStart);
	_mav_put_float(buf, 32, sEnd);
	_mav_put_float(buf, 36, dsdt);
	_mav_put_float(buf, 40, N);
	_mav_put_float(buf, 44, E);
	_mav_put_float(buf, 48, D);
	_mav_put_float(buf, 52, y2N);
	_mav_put_float(buf, 56, y2E);
	_mav_put_float(buf, 60, y2D);
	_mav_put_uint16_t(buf, 64, seq);
	_mav_put_uint16_t(buf, 66, command);
	_mav_put_uint8_t(buf, 68, target_system);
	_mav_put_uint8_t(buf, 69, target_component);
	_mav_put_uint8_t(buf, 70, frame);
	_mav_put_uint8_t(buf, 71, current);
	_mav_put_uint8_t(buf, 72, autocontinue);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#else
	mavlink_custom_trajectory_t packet;
	packet.param1 = param1;
	packet.param2 = param2;
	packet.param3 = param3;
	packet.param4 = param4;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.sStart = sStart;
	packet.sEnd = sEnd;
	packet.dsdt = dsdt;
	packet.N = N;
	packet.E = E;
	packet.D = D;
	packet.y2N = y2N;
	packet.y2E = y2E;
	packet.y2D = y2D;
	packet.seq = seq;
	packet.command = command;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.frame = frame;
	packet.current = current;
	packet.autocontinue = autocontinue;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CUSTOM_TRAJECTORY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
}

/**
 * @brief Encode a custom_trajectory struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param custom_trajectory C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custom_trajectory_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_custom_trajectory_t* custom_trajectory)
{
	return mavlink_msg_custom_trajectory_pack(system_id, component_id, msg, custom_trajectory->target_system, custom_trajectory->target_component, custom_trajectory->seq, custom_trajectory->frame, custom_trajectory->command, custom_trajectory->current, custom_trajectory->autocontinue, custom_trajectory->param1, custom_trajectory->param2, custom_trajectory->param3, custom_trajectory->param4, custom_trajectory->x, custom_trajectory->y, custom_trajectory->z, custom_trajectory->sStart, custom_trajectory->sEnd, custom_trajectory->dsdt, custom_trajectory->N, custom_trajectory->E, custom_trajectory->D, custom_trajectory->y2N, custom_trajectory->y2E, custom_trajectory->y2D);
}

/**
 * @brief Encode a custom_trajectory struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param custom_trajectory C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custom_trajectory_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_custom_trajectory_t* custom_trajectory)
{
	return mavlink_msg_custom_trajectory_pack_chan(system_id, component_id, chan, msg, custom_trajectory->target_system, custom_trajectory->target_component, custom_trajectory->seq, custom_trajectory->frame, custom_trajectory->command, custom_trajectory->current, custom_trajectory->autocontinue, custom_trajectory->param1, custom_trajectory->param2, custom_trajectory->param3, custom_trajectory->param4, custom_trajectory->x, custom_trajectory->y, custom_trajectory->z, custom_trajectory->sStart, custom_trajectory->sEnd, custom_trajectory->dsdt, custom_trajectory->N, custom_trajectory->E, custom_trajectory->D, custom_trajectory->y2N, custom_trajectory->y2E, custom_trajectory->y2D);
}

/**
 * @brief Send a custom_trajectory message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 * @param frame The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 * @param command The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
 * @param current false:0, true:1
 * @param autocontinue autocontinue to next wp
 * @param param1 PARAM1, see MAV_CMD enum
 * @param param2 PARAM2, see MAV_CMD enum
 * @param param3 PARAM3, see MAV_CMD enum
 * @param param4 PARAM4, see MAV_CMD enum
 * @param x PARAM5 / local: x position, global: latitude
 * @param y PARAM6 / y position: global: longitude
 * @param z PARAM7 / z position: global: altitude (relative or absolute, depending on frame.
 * @param sStart value1
 * @param sEnd value2
 * @param dsdt value3
 * @param N value4
 * @param E value5
 * @param D value6
 * @param y2N value7
 * @param y2E value8
 * @param y2D value9
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_custom_trajectory_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t seq, uint8_t frame, uint16_t command, uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, float x, float y, float z, float sStart, float sEnd, float dsdt, float N, float E, float D, float y2N, float y2E, float y2D)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN];
	_mav_put_float(buf, 0, param1);
	_mav_put_float(buf, 4, param2);
	_mav_put_float(buf, 8, param3);
	_mav_put_float(buf, 12, param4);
	_mav_put_float(buf, 16, x);
	_mav_put_float(buf, 20, y);
	_mav_put_float(buf, 24, z);
	_mav_put_float(buf, 28, sStart);
	_mav_put_float(buf, 32, sEnd);
	_mav_put_float(buf, 36, dsdt);
	_mav_put_float(buf, 40, N);
	_mav_put_float(buf, 44, E);
	_mav_put_float(buf, 48, D);
	_mav_put_float(buf, 52, y2N);
	_mav_put_float(buf, 56, y2E);
	_mav_put_float(buf, 60, y2D);
	_mav_put_uint16_t(buf, 64, seq);
	_mav_put_uint16_t(buf, 66, command);
	_mav_put_uint8_t(buf, 68, target_system);
	_mav_put_uint8_t(buf, 69, target_component);
	_mav_put_uint8_t(buf, 70, frame);
	_mav_put_uint8_t(buf, 71, current);
	_mav_put_uint8_t(buf, 72, autocontinue);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
#else
	mavlink_custom_trajectory_t packet;
	packet.param1 = param1;
	packet.param2 = param2;
	packet.param3 = param3;
	packet.param4 = param4;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.sStart = sStart;
	packet.sEnd = sEnd;
	packet.dsdt = dsdt;
	packet.N = N;
	packet.E = E;
	packet.D = D;
	packet.y2N = y2N;
	packet.y2E = y2E;
	packet.y2D = y2D;
	packet.seq = seq;
	packet.command = command;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.frame = frame;
	packet.current = current;
	packet.autocontinue = autocontinue;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, (const char *)&packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, (const char *)&packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_custom_trajectory_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint16_t seq, uint8_t frame, uint16_t command, uint8_t current, uint8_t autocontinue, float param1, float param2, float param3, float param4, float x, float y, float z, float sStart, float sEnd, float dsdt, float N, float E, float D, float y2N, float y2E, float y2D)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, param1);
	_mav_put_float(buf, 4, param2);
	_mav_put_float(buf, 8, param3);
	_mav_put_float(buf, 12, param4);
	_mav_put_float(buf, 16, x);
	_mav_put_float(buf, 20, y);
	_mav_put_float(buf, 24, z);
	_mav_put_float(buf, 28, sStart);
	_mav_put_float(buf, 32, sEnd);
	_mav_put_float(buf, 36, dsdt);
	_mav_put_float(buf, 40, N);
	_mav_put_float(buf, 44, E);
	_mav_put_float(buf, 48, D);
	_mav_put_float(buf, 52, y2N);
	_mav_put_float(buf, 56, y2E);
	_mav_put_float(buf, 60, y2D);
	_mav_put_uint16_t(buf, 64, seq);
	_mav_put_uint16_t(buf, 66, command);
	_mav_put_uint8_t(buf, 68, target_system);
	_mav_put_uint8_t(buf, 69, target_component);
	_mav_put_uint8_t(buf, 70, frame);
	_mav_put_uint8_t(buf, 71, current);
	_mav_put_uint8_t(buf, 72, autocontinue);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, buf, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
#else
	mavlink_custom_trajectory_t *packet = (mavlink_custom_trajectory_t *)msgbuf;
	packet->param1 = param1;
	packet->param2 = param2;
	packet->param3 = param3;
	packet->param4 = param4;
	packet->x = x;
	packet->y = y;
	packet->z = z;
	packet->sStart = sStart;
	packet->sEnd = sEnd;
	packet->dsdt = dsdt;
	packet->N = N;
	packet->E = E;
	packet->D = D;
	packet->y2N = y2N;
	packet->y2E = y2E;
	packet->y2D = y2D;
	packet->seq = seq;
	packet->command = command;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->frame = frame;
	packet->current = current;
	packet->autocontinue = autocontinue;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, (const char *)packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY, (const char *)packet, MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE CUSTOM_TRAJECTORY UNPACKING


/**
 * @brief Get field target_system from custom_trajectory message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_custom_trajectory_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  68);
}

/**
 * @brief Get field target_component from custom_trajectory message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_custom_trajectory_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  69);
}

/**
 * @brief Get field seq from custom_trajectory message
 *
 * @return Sequence
 */
static inline uint16_t mavlink_msg_custom_trajectory_get_seq(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  64);
}

/**
 * @brief Get field frame from custom_trajectory message
 *
 * @return The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 */
static inline uint8_t mavlink_msg_custom_trajectory_get_frame(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  70);
}

/**
 * @brief Get field command from custom_trajectory message
 *
 * @return The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
 */
static inline uint16_t mavlink_msg_custom_trajectory_get_command(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  66);
}

/**
 * @brief Get field current from custom_trajectory message
 *
 * @return false:0, true:1
 */
static inline uint8_t mavlink_msg_custom_trajectory_get_current(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  71);
}

/**
 * @brief Get field autocontinue from custom_trajectory message
 *
 * @return autocontinue to next wp
 */
static inline uint8_t mavlink_msg_custom_trajectory_get_autocontinue(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  72);
}

/**
 * @brief Get field param1 from custom_trajectory message
 *
 * @return PARAM1, see MAV_CMD enum
 */
static inline float mavlink_msg_custom_trajectory_get_param1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field param2 from custom_trajectory message
 *
 * @return PARAM2, see MAV_CMD enum
 */
static inline float mavlink_msg_custom_trajectory_get_param2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field param3 from custom_trajectory message
 *
 * @return PARAM3, see MAV_CMD enum
 */
static inline float mavlink_msg_custom_trajectory_get_param3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field param4 from custom_trajectory message
 *
 * @return PARAM4, see MAV_CMD enum
 */
static inline float mavlink_msg_custom_trajectory_get_param4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field x from custom_trajectory message
 *
 * @return PARAM5 / local: x position, global: latitude
 */
static inline float mavlink_msg_custom_trajectory_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field y from custom_trajectory message
 *
 * @return PARAM6 / y position: global: longitude
 */
static inline float mavlink_msg_custom_trajectory_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field z from custom_trajectory message
 *
 * @return PARAM7 / z position: global: altitude (relative or absolute, depending on frame.
 */
static inline float mavlink_msg_custom_trajectory_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field sStart from custom_trajectory message
 *
 * @return value1
 */
static inline float mavlink_msg_custom_trajectory_get_sStart(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field sEnd from custom_trajectory message
 *
 * @return value2
 */
static inline float mavlink_msg_custom_trajectory_get_sEnd(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field dsdt from custom_trajectory message
 *
 * @return value3
 */
static inline float mavlink_msg_custom_trajectory_get_dsdt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field N from custom_trajectory message
 *
 * @return value4
 */
static inline float mavlink_msg_custom_trajectory_get_N(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field E from custom_trajectory message
 *
 * @return value5
 */
static inline float mavlink_msg_custom_trajectory_get_E(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field D from custom_trajectory message
 *
 * @return value6
 */
static inline float mavlink_msg_custom_trajectory_get_D(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field y2N from custom_trajectory message
 *
 * @return value7
 */
static inline float mavlink_msg_custom_trajectory_get_y2N(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field y2E from custom_trajectory message
 *
 * @return value8
 */
static inline float mavlink_msg_custom_trajectory_get_y2E(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field y2D from custom_trajectory message
 *
 * @return value9
 */
static inline float mavlink_msg_custom_trajectory_get_y2D(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Decode a custom_trajectory message into a struct
 *
 * @param msg The message to decode
 * @param custom_trajectory C-struct to decode the message contents into
 */
static inline void mavlink_msg_custom_trajectory_decode(const mavlink_message_t* msg, mavlink_custom_trajectory_t* custom_trajectory)
{
#if MAVLINK_NEED_BYTE_SWAP
	custom_trajectory->param1 = mavlink_msg_custom_trajectory_get_param1(msg);
	custom_trajectory->param2 = mavlink_msg_custom_trajectory_get_param2(msg);
	custom_trajectory->param3 = mavlink_msg_custom_trajectory_get_param3(msg);
	custom_trajectory->param4 = mavlink_msg_custom_trajectory_get_param4(msg);
	custom_trajectory->x = mavlink_msg_custom_trajectory_get_x(msg);
	custom_trajectory->y = mavlink_msg_custom_trajectory_get_y(msg);
	custom_trajectory->z = mavlink_msg_custom_trajectory_get_z(msg);
	custom_trajectory->sStart = mavlink_msg_custom_trajectory_get_sStart(msg);
	custom_trajectory->sEnd = mavlink_msg_custom_trajectory_get_sEnd(msg);
	custom_trajectory->dsdt = mavlink_msg_custom_trajectory_get_dsdt(msg);
	custom_trajectory->N = mavlink_msg_custom_trajectory_get_N(msg);
	custom_trajectory->E = mavlink_msg_custom_trajectory_get_E(msg);
	custom_trajectory->D = mavlink_msg_custom_trajectory_get_D(msg);
	custom_trajectory->y2N = mavlink_msg_custom_trajectory_get_y2N(msg);
	custom_trajectory->y2E = mavlink_msg_custom_trajectory_get_y2E(msg);
	custom_trajectory->y2D = mavlink_msg_custom_trajectory_get_y2D(msg);
	custom_trajectory->seq = mavlink_msg_custom_trajectory_get_seq(msg);
	custom_trajectory->command = mavlink_msg_custom_trajectory_get_command(msg);
	custom_trajectory->target_system = mavlink_msg_custom_trajectory_get_target_system(msg);
	custom_trajectory->target_component = mavlink_msg_custom_trajectory_get_target_component(msg);
	custom_trajectory->frame = mavlink_msg_custom_trajectory_get_frame(msg);
	custom_trajectory->current = mavlink_msg_custom_trajectory_get_current(msg);
	custom_trajectory->autocontinue = mavlink_msg_custom_trajectory_get_autocontinue(msg);
#else
	memcpy(custom_trajectory, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CUSTOM_TRAJECTORY_LEN);
#endif
}
