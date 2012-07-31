/*
 * BBB HTML5 Video Adapter
 * Copyright (C) 2012 BigBlueButton Inc
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef GSS_PROGRAM_BBB_H
#define GSS_PROGRAM_BBB_H

typedef struct _GssProgram GssProgram;
typedef struct _GssStream GssStream;

void gss_program_add_bbb_video_stream(GssProgram *program, int type,
		int width, int height, int bitrate, const char *url);

void gss_stream_create_bbb_video_pipeline(GssStream *stream);

#endif /* GSS_PROGRAM_BBB_H */
