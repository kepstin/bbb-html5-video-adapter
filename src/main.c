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

#include <gss/gss-server.h>
#include <gst/gst.h>

#include <stdio.h>

#define STREAM_BASE_DIRECTORY "/html5-video"
#define SERVER_NAME "localhost"

GssConfigDefault config_defaults[] = {
	{"enable_streaming", "on"},
	{NULL, NULL}
};

static void add_program(GssServer *server, const gchar *source)
{
	GssProgram *program;

	program = gss_server_add_program(server, "test");
	gss_program_add_bbb_video_stream(program, GSS_STREAM_TYPE_WEBM,
			320, 240, 500000, source);

	g_print("Program location: %s\n", program->location);
}

int main(int argc, char *argv[])
{
	GssServer *server;
	GMainLoop *loop;

	gst_init(&argc, &argv);

	server = gss_server_new();
	gss_server_set_server_name(server, SERVER_NAME);

	gss_config_load_defaults(server->config, config_defaults);

	add_program(server, "rtmp://192.168.22.140/oflaDemo/avatar-vp6.flv");

	loop = g_main_loop_new(NULL, TRUE);
	
	g_main_loop_run(loop);

	g_main_loop_unref(loop);
	loop = NULL;

	g_object_unref(server);
	server = NULL;

	gss_server_deinit();
	gst_deinit();
	
	return 0;
}
