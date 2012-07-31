ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = src/bbb-stream-pusher

src_bbb_stream_pusher_SOURCES = \
	src/gss-program-bbb.c \
	src/main.c
src_bbb_stream_pusher_CFLAGS = $(GSS_CFLAGS)
src_bbb_stream_pusher_LDADD = $(GSS_LIBS)
