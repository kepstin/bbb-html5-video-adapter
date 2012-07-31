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

#include "gss-program-bbb.h"

#include <gss/gss-program.h>
#include <gss/gss-server.h>
#include <gss/gss-stream.h>

void gss_program_add_bbb_video_stream(GssProgram *program, int type,
		int width, int height, int bitrate, const char *url)
{
	GssStream *stream;

	stream = gss_program_add_stream_full(program, type,
			width, height, bitrate, NULL);
	stream->follow_url = g_strdup(url);

	gss_stream_create_bbb_video_pipeline(stream);

	gst_element_set_state(stream->pipeline, GST_STATE_PLAYING);
}

void gss_stream_create_bbb_video_pipeline(GssStream *stream)
{
	GstElement *pipe, *e;
	GString *pipe_desc;
	GError *error;

	pipe_desc = g_string_new("");

	g_string_append(pipe_desc, "rtmpsrc name=src do-timestamp=true ! ");

	/*
	 * We actually have to re-encode the video from Flash's VP6 to VP8
	 * and re-mux it into a WebM container. Note that the BBB stream is
	 * video-only; audio will be handled separately.
	 */
	g_string_append(pipe_desc, "flvdemux ! ffdec_vp6f ! ");
	/* TODO: pick good encoding parameters */
	g_string_append(pipe_desc, "vp8enc ! webmmux streamable=true ! ");

	/* Is the parser actually needed? */
	/* g_string_append(pipe_desc, "matroskaparse name=parse ! "); */

	g_string_append(pipe_desc, "queue ! ");
	g_string_append_printf(pipe_desc, "%s name=sink ",
			gss_server_get_multifdsink_string());

	g_print("pipeline: %s\n", pipe_desc->str);

	error = NULL;
	pipe = gst_parse_launch(pipe_desc->str, &error);
	g_string_free(pipe_desc, TRUE);
	if (error != NULL) {
		g_print("pipeline parse error: %s\n", error->message);
		return;
	}

	e = gst_bin_get_by_name(GST_BIN(pipe), "src");
	g_object_set(e, "location", stream->follow_url, NULL);
	g_object_unref(e);

	e = gst_bin_get_by_name(GST_BIN(pipe), "sink");
	gss_stream_set_sink(stream, e);
	g_object_unref(e);

	stream->pipeline = pipe;

	/* TODO: Handle pipeline bus messages */
}
