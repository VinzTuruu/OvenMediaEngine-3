//==============================================================================
//
//  RtmpProvider
//
//  Created by Jaejong Bong
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once

#ifndef WIN32

#include <base/ovlibrary/ovlibrary.h>
#define OV_LOG_TAG "RtmpProvider"
#define RTMP_CHUNK_LOG(str)				logtd str
#define RTMP_CHUNK_INFO_LOG(str)		logti str
#define RTMP_CHUNK_DEBUG_LOG(str)		logtd str
#define RTMP_CHUNK_ERROR_LOG(str)		logte str
#define RTMP_CHUNK_WARNING_LOG(str)		logtw str

#else

#define RTMP_CHUNK_LOG(str)				printf str
#define RTMP_CHUNK_INFO_LOG(str)		printf str
#define RTMP_CHUNK_DEBUG_LOG(str)		printf str
#define RTMP_CHUNK_ERROR_LOG(str)		printf str
#define RTMP_CHUNK_WARNING_LOG(str)		printf str

#endif 

#pragma pack()


