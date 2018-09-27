//==============================================================================
//
//  RtmpProvider
//
//  Created by Jaejong Bong
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once
#include <string.h>
#include <vector>
#include <map>
#include <memory>


#ifdef WIN32
#include <winsock2.h>
#else 
#include <arpa/inet.h>
#endif 

#pragma pack(1) 
#define RTMP_AVC_NAL_HEADER_SIZE			(4) // 00 00 00 01  or 00 00 01
#define RTMP_ADTS_HEADER_SIZE				(7)
#define RTMP_MAX_PACKET_SIZE				(20*1024*1024) // 20M

//Avc Nal Header 
const char g_rtmp_avc_nal_header[RTMP_AVC_NAL_HEADER_SIZE] = {0,0,0,1};

//Rtmp - 44100(4) 22050(7) 11025(10) 사용 
const int g_rtmp_sample_rate_table[] = {96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 0, 0, 0, 0};
#define RTMP_SAMPLERATE_TABLE_SIZE (16)

#define RTMP_SESSION_KEY_MAX_SIZE				(1024)
#define RTMP_TIME_SCALE							(1000)

// HANDSHAKE
#define RTMP_HANDSHAKE_VERSION					(0x03)
#define RTMP_HANDSHAKE_PACKET_SIZE				(1536)

// CHUNK
#define RTMP_CHUNK_BASIC_HEADER_SIZE_MAX		(3)
#define RTMP_CHUNK_MSG_HEADER_SIZE_MAX			(11 + 4)	// header + extended timestamp
#define RTMP_PACKET_HEADER_SIZE_MAX				(RTMP_CHUNK_BASIC_HEADER_SIZE_MAX + RTMP_CHUNK_MSG_HEADER_SIZE_MAX)

#define RTMP_CHUNK_BASIC_FORMAT_TYPE_MASK		(0xc0)
#define RTMP_CHUNK_BASIC_CHUNK_STREAM_ID_MASK	(0x3f)

#define RTMP_CHUNK_BASIC_FORMAT_TYPE0			(0x00)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE1			(0x40)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE2			(0x80)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE3			(0xc0)

#define RTMP_CHUNK_BASIC_FORMAT_TYPE0_SIZE		(11)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE1_SIZE		(7)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE2_SIZE		(3)
#define RTMP_CHUNK_BASIC_FORMAT_TYPE3_SIZE		(0)

#define RTMP_EXTEND_TIMESTAMP					(0x00ffffff) 
#define RTMP_EXTEND_TIMESTAMP_SIZE				(4) 			//sizeof(uint)

#define RTMP_MIN(a,b)							(a<b ? a : b)
#define RTMP_MAX(a,b)							(a>b ? a : b)

// CHUNK STREAM ID
#define RTMP_CHUNK_STREAM_ID_URGENT				(2)
#define RTMP_CHUNK_STREAM_ID_CONTROL			(3)
#define RTMP_CHUNK_STREAM_ID_MEDIA				(8)

// MESSAGE ID
#define RTMP_MSGID_SET_CHUNKSIZE				(1)
#define RTMP_MSGID_ABORT_MESSAGE				(2)
#define RTMP_MSGID_ACKNOWLEDGEMENT				(3)
#define RTMP_MSGID_USERCONTROL_MESSAGE			(4)
#define RTMP_MSGID_WINDOWACKNOWLEDGEMENT_SIZE	(5)
#define RTMP_MSGID_SET_PEERBANDWIDTH			(6)
#define RTMP_MSGID_AUDIO_MESSAGE				(8)
#define RTMP_MSGID_VIDEO_MESSAGE				(9)
#define RTMP_MSGID_AMF3DATAMESSAGE				(15)
#define RTMP_MSGID_AMF3COMMANDMESSAGE			(17)
#define RTMP_MSGID_AMF0_DATA_MESSAGE			(18)
#define RTMP_MSGID_AMF0_COMMAND_MESSAGE			(20)
#define RTMP_MSGID_AGGREGATE_MESSAGE			(22)

// USER CONTROL MESSAGE ID
#define RTMP_UCMID_STREAMBEGIN					(0)
#define RTMP_UCMID_STREAMEOF					(1)
#define RTMP_UCMID_STREAMDRY					(2)
#define RTMP_UCMID_SETBUFFERLENGTH				(3)
#define RTMP_UCMID_STREAMISRECORDED				(4)
#define RTMP_UCMID_PINGREQUEST					(6)
#define RTMP_UCMID_PINGRESPONSE					(7)
#define RTMP_UCMID_BUFFEREMPTY					(31)
#define RTMP_UCMID_BUFFERREADY					(32)

// COMMAND TRANSACTION ID
#define RTMP_CMD_TRID_NOREPONSE					(0.0)
#define RTMP_CMD_TRID_CONNECT					(1.0)
#define RTMP_CMD_TRID_CREATESTREAM				(2.0)
#define RTMP_CMD_TRID_RELEASESTREAM				(2.0)
#define RTMP_CMD_TRID_DELETESTREAM				RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_CLOSESTREAM				RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_PLAY						RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_PLAY2						RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_SEEK						RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_PAUSE						RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_RECEIVEAUDIO				RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_RECEIVEVIDEO				RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_PUBLISH					RTMP_CMD_TRID_NOREPONSE
#define RTMP_CMD_TRID_FCPUBLISH 				(3.0)
#define RTMP_CMD_TRID_FCSUBSCRIBE				(4.0)
#define RTMP_CMD_TRID_FCUNSUBSCRIBE				(5.0)
#define RTMP_CMD_TRID_FCUNPUBLISH				(5.0)

// COMMAND NAME
#define RTMP_CMD_NAME_CONNECT					("connect")
#define RTMP_CMD_NAME_CREATESTREAM				("createStream")
#define RTMP_CMD_NAME_RELEASESTREAM				("releaseStream")
#define RTMP_CMD_NAME_DELETESTREAM				("deleteStream")
#define RTMP_CMD_NAME_CLOSESTREAM				("closeStream")
#define RTMP_CMD_NAME_PLAY						("play")
#define RTMP_CMD_NAME_ONSTATUS					("onStatus")
#define RTMP_CMD_NAME_PUBLISH					("publish")
#define RTMP_CMD_NAME_FCPUBLISH 				("FCPublish")
#define RTMP_CMD_NAME_FCUNPUBLISH 				("FCUnpublish")
#define RTMP_CMD_NAME_ONFCPUBLISH 				("onFCPublish")
#define RTMP_CMD_NAME_ONFCUNPUBLISH 			("onFCUnpublish")
#define RTMP_CMD_NAME_CLOSE  				  	("close")
#define RTMP_CMD_NAME_SETCHALLENGE              ("setChallenge")
#define RTMP_CMD_DATA_SETDATAFRAME			    ("@setDataFrame")
#define RTMP_CMD_NAME_ONCLIENTLOGIN				("onClientLogin")
#define RTMP_CMD_DATA_ONMETADATA			    ("onMetaData")
#define RTMP_ACK_NAME_RESULT					("_result")
#define RTMP_ACK_NAME_ERROR						("_error")
#define RTMP_ACK_NAME_BWDONE					("onBWDone")
#define RTMP_PING								("ping")

//RtmpStream/RtmpPublish 
#define RTMP_H264_I_FRAME_TYPE					(0x17) 
#define RTMP_H264_P_FRAME_TYPE					(0x27) 
#define RTMP_DEFAULT_ACKNOWNLEDGEMENT_SIZE		(2500000)
#define RTMP_DEFAULT_PEER_BANDWIDTH				(2500000)
#define RTMP_DEFAULT_CHUNK_SIZE					(128)

#define RTMP_SEQUENCE_DATA_TYPE					(0x00)
#define RTMP_FRAME_DATA_TYPE					(0x01) 
#define RTMP_VIDEO_DATA_MIN_SIZE				(5) // contdrol(1) + sequece(1) + offsettime(3)

#define RTMP_AUDIO_CONTROL_HEADER_INDEX			(0)
#define RTMP_AAC_AUDIO_SEQUENCE_TYPE_INDEX		(1)
#define RTMP_AAC_AUDIO_DATA_MIN_SIZE			(2) // contdrol(1) + sequece(1)
#define RTMP_AAC_AUDIO_FRAME_INDEX				(2)
#define RTMP_SPEEX_AUDIO_FRAME_INDEX			(1)
#define RTMP_MP3_AUDIO_FRAME_INDEX				(1)
#define RTMP_SPS_PPS_MIN_DATA_SIZE 				(14)

#define RTMP_VIDEO_CONTROL_HEADER_INDEX			(0)
#define RTMP_VIDEO_SEQUENCE_TYPE_INDEX			(1)
#define RTMP_VIDEO_COMPOSITION_OFFSET_INDEX		(2)
#define RTMP_VIDEO_FRAME_SIZE_INDEX				(5)
#define RTMP_VIDEO_FRAME_INDEX					(9)
#define RTMP_VIDEO_FRAME_SIZE_INFO_SIZE			(4)

#define RTMP_UNKNOWN_DEVICE_TYPE_STRING			("unknown_device_type")
#define RTMP_DEFAULT_CLIENT_VERSION     		("rtmp client 1.0")//"afcCli 11,0,100,1 (compatible; FMSc/1.0)"
#define RTMP_DEFULT_PORT 						(1935)

//====================================================================================================
// chunk_header 구조체
//====================================================================================================
struct RtmpChunkHeader
{
public :
	RtmpChunkHeader()
	{
		Init();
	}

	void Init()
	{
		basic_header.format_type 		= 0;
		basic_header. chunk_stream_id 	= 0;

		type_0.timestamp 				= 0;
		type_0.body_size 				= 0;
		type_0.type_id 					= 0;
		type_0.stream_id 				= 0;
	}

public :
	struct
	{
		uint8_t		format_type;
		uint32_t	chunk_stream_id;				// 0,1,2 are reserved
	} basic_header;

	union
	{
		struct
		{
			uint32_t	timestamp;
			uint32_t	body_size;			// msg len
			uint8_t		type_id;			// msg type id
			uint32_t	stream_id;			// msg stream id
		} type_0;
		//
		struct
		{
			uint32_t	timestamp_delta;
			uint32_t	body_size;
			uint8_t		type_id;
		} type_1;
		//
		struct
		{
			uint32_t	timestamp_delta;
		} type_2;
	};
};

//===============================================================================================
// Rtmp Encoder Type
//===============================================================================================
typedef enum eRTMP_ENCODER_TYPE
{
	RTMP_CUSTOM_ENCODER_TYPE = 0, 	// 일반 Rtmp 클라이언트(기타 구분 불가능 Client 포함)
	RTMP_XSPLIT_ENCODER_TYPE,		// XSplit
	RTMP_OBS_ENCODER_TYPE,			// OBS
	RTMP_LAVF_ENCODER_TYPE, 		// Libavformat (lavf)
	RTMP_MAX_ENCODER_TYPE,
	
}tRTMP_ENCODER_TYPE;

//===============================================================================================
// 프레임 타입 문자 
//===============================================================================================
static char g_rtmp_encoder_type_string[RTMP_MAX_ENCODER_TYPE][10]=
{
	"custom",	// RTMP_CUSTOM_ENCODER_TYPE,
	"xsplit",	// RTMP_XSPLIT_ENCODER_TYPE
	"obs",		// RTMP_OBS_ENCODER_TYPE
	"ffmpeg",	// RTMP_LAVF_ENCODER_TYPE
}; 

//===============================================================================================
//프레임 타입 
//===============================================================================================
typedef enum eRTMP_FRAME_TYPE
{
	RTMP_VIDEO_I_FRAME_TYPE = 'I', // VIDEO I Frame
	RTMP_VIDEO_P_FRAME_TYPE = 'P', // VIDEO P Frame
	RTMP_AUDIO_FRAME_TYPE	= 'A', // AUDIO Frame
}tRTMP_FRAME_TYPE;

//===============================================================================================
//지원 코덱 타입 
//===============================================================================================
typedef enum eRTMP_CODEC_TYPE
{
	RTMP_UNKNOWN_CODEC_TYPE,
	RTMP_H264_VIDEO_CODEC_TYPE,	//	H264/X264 avc1(7)
	RTMP_AAC_AUDIO_CODEC_TYPE,	//	AAC          mp4a(10) 
	RTMP_MP3_AUDIO_CODEC_TYPE,  //	MP3(2) 
	RTMP_SPEEX_AUDIO_CODEC_TYPE,//	SPEEX(11) 
	RTMP_MAX_CODEC_TYPE
}tRTMP_CODEC_TYPE;

//===============================================================================================
// 프레임 타입 문자 
//===============================================================================================
static char g_rtmp_codec_type_string[RTMP_MAX_CODEC_TYPE][10]=
{
	"unknown",	// RTMP_UNKNOWN_CODEC_TYPE,
	"h264",		// RTMP_H264_VIDEO_CODEC_TYPE
	"aac",		// RTMP_AAC_AUDIO_CODEC_TYPE
	"mp3",		// RTMP_MP3_AUDIO_CODEC_TYPE
	"speex",	// RTMP_SPEEX_AUDIO_CODEC_TYPE

}; 

//===============================================================================================
// 프레임 정보 
//===============================================================================================
struct RtmpFrameInfo
{
	uint32_t			timestamp; 
	int					composition_time_offset;
	tRTMP_FRAME_TYPE 	frame_type;
	int					frame_size; 
	char * 				frame; 
};

//===============================================================================================
// Rtmp Handshake State
//===============================================================================================
typedef enum eRTMP_HANDSHAKE_STATE
{
	RTMP_HANDSHAKE_READY_STATE = 0,
	RTMP_HANDSHAKE_C0_STATE,
	RTMP_HANDSHAKE_C1_STATE,
	RTMP_HANDSHAKE_S0_STATE,
	RTMP_HANDSHAKE_S1_STATE,
	RTMP_HANDSHAKE_S2_STATE,
	RTMP_HANDSHAKE_C2_STATE,
	RTMP_HANDSHAKE_COMPLETE_STATE

}tRTMP_HANDSHAKE_STATE;

//===============================================================================================
// 스트림 정보 
//===============================================================================================
struct RtmpMediaInfo
{
public :
	RtmpMediaInfo()
	{
		has_video 			= false;
		has_aduio 			= false;

		// 비디오 정보
		video_codec_type 	= RTMP_UNKNOWN_CODEC_TYPE;
		video_width			= 0;
		video_height		= 0;
		video_framerate		= 0;
		video_bitrate		= 0;

		// 오디오 정보
		audio_codec_type  	= RTMP_UNKNOWN_CODEC_TYPE;
		audio_channels		= 0;
		audio_bits			= 0;
		audio_samplerate	= 0;
		audio_sampleindex	= 0;
		audio_bitrate		= 0;

		timestamp_scale 	= RTMP_TIME_SCALE;
		encoder_type 		= RTMP_CUSTOM_ENCODER_TYPE;

		//h.264 AVC 헤더 관련 설정 정보
		avc_sps 			=  std::make_shared<std::vector<uint8_t>>();
		avc_pps 			=  std::make_shared<std::vector<uint8_t>>();
	}

public :
	bool				has_video;
	bool   				has_aduio;

	// 비디오 정보
	tRTMP_CODEC_TYPE 	video_codec_type;
	int					video_width;
	int					video_height;
	float				video_framerate;
	int					video_bitrate;

	// 오디오 정보
	tRTMP_CODEC_TYPE 	audio_codec_type;
	int					audio_channels;
	int					audio_bits;
	int					audio_samplerate;
	int					audio_sampleindex;
	int					audio_bitrate;

	uint32_t			timestamp_scale;
	tRTMP_ENCODER_TYPE 	encoder_type;

	//h.264 AVC 헤더 관련 설정 정보
	std::shared_ptr<std::vector<uint8_t>> avc_sps;
	std::shared_ptr<std::vector<uint8_t>> avc_pps;

};

#pragma pack()


