Revere VFIO demo
================

Principles
----------

The Revere VFIO demo is a standalone example using a Revere device from
userspace through VFIO. It establishes a connection with a hardware inversion
"accelerator". Data is exchanged with the accelerator through Revere messages.

License
-------

This code is licensed under the open source BSD, clause 3 license. See LICENSE
for more information.

Build
-----

To build:

```
  $ ./autogen.sh
  $ ./configure
  $ make
```

Run
---

Run the demo as root to avoid permissions issues.

To run:

```
  #  modprobe vfio_iommu_type1 allow_unsafe_interrupts=1
  #  modprobe vfio-pci ids=13b5:ff81
  #  revere-vfio-demo --vfio-group /dev/vfio/2 --device 0000:00:03.0
```

Note: you need to adapt the vfio group and device to those corresponding to the
Revere PF on your platform.

Details
-------

Details of the files for this demo:

```
  +-- autogen.sh
  +-- cmdline.c
  +-- cmdline.h
  +-- configure.ac
  +-- LICENSE
  +-- main.c ............. Demo top level
  +-- Makefile.am
  +-- README
  +-- revere_dev.c ....... Function for Revere setup
  +-- revere_dev.h
  +-- revere.h ........... Revere-AMU generated header
  +-- revere_hw.c ........ Functions to access 64b registers
  +-- revere_hw.h
  +-- vfio.c ............. VFIO functions
  `-- vfio.h
```

The demo goes through the following steps:

1. Allocate memory for all i/o buffers, which are shared with the Revere device.
2. Open the device with VFIO and map memory into Revere IOVA space. Also, map
   BAR0 into our process address space and turn on BME.
3. Setup the Revere device: setup Revere management interface, then using the
   management interface, setup the AMI-HWs in the accelerator, an AMI-SW and
   connect them with sessions.
4. Exchange data with the inversion agent and verify that it has been inverted.
5. Teardown everything and exit.

Here is the Revere setup configured by the demo (omitting the management
interface):

```
  Rings in memory
                                           +-----------------------+
 .---------------.                         | Inversion accelerator |
 |  +-+-+-+-+-+  |                         |       (AHA 0)         |
 `->| | | | | |--'                         |                       |
    +-+-+-+-+-+       AMI-SW 0             |  AMI-HW 0             |
         |         +-----------+   ASN 0   +-----------+           |
         `........>| TX AMS 0  @---------->@  RX AMS 0 |--.        |
                   |           |           +-----------+  |        |
                   |           |           |             Invert    |
                   |           |           +-----------+  |        |
         ..........| RX AMS 0  @<----------@  TX AMS 0 |<-'        |
         V         +-----------+   ASN 1   +-----------+           |
    +-+-+-+-+-+                            |  AMI-HW 1             |
 .->| | | | | |--.                         +-----------------------+
 |  +-+-+-+-+-+  |
 `---------------'
```

See Also
--------

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/Documentation/vfio.txt

Git
---

Commit id 430439a0e6640c20c171fbb7cc9a7ac3b2fbb842
