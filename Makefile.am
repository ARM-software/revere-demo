bin_PROGRAMS = revere-vfio-demo

revere_vfio_demo_SOURCES = \
	cmdline.c \
	main.c \
	platform.c \
	revere_dev.c

if VFIO
revere_vfio_demo_SOURCES += \
	vfio.c
endif
