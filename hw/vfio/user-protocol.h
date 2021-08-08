#ifndef VFIO_USER_PROTOCOL_H
#define VFIO_USER_PROTOCOL_H

/*
 * vfio protocol over a UNIX socket.
 *
 * Copyright © 2018, 2021 Oracle and/or its affiliates.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Each message has a standard header that describes the command
 * being sent, which is almost always a VFIO ioctl().
 *
 * The header may be followed by command-specfic data, such as the
 * region and offset info for read and write commands.
 */

typedef struct {
    uint16_t id;
    uint16_t command;
    uint32_t size;
    uint32_t flags;
    uint32_t error_reply;
} VFIOUserHdr;

/* VFIOUserHdr commands */
enum vfio_user_command {
    VFIO_USER_VERSION                   = 1,
    VFIO_USER_DMA_MAP                   = 2,
    VFIO_USER_DMA_UNMAP                 = 3,
    VFIO_USER_DEVICE_GET_INFO           = 4,
    VFIO_USER_DEVICE_GET_REGION_INFO    = 5,
    VFIO_USER_DEVICE_GET_REGION_IO_FDS  = 6,
    VFIO_USER_DEVICE_GET_IRQ_INFO       = 7,
    VFIO_USER_DEVICE_SET_IRQS           = 8,
    VFIO_USER_REGION_READ               = 9,
    VFIO_USER_REGION_WRITE              = 10,
    VFIO_USER_DMA_READ                  = 11,
    VFIO_USER_DMA_WRITE                 = 12,
    VFIO_USER_DEVICE_RESET              = 13,
    VFIO_USER_DIRTY_PAGES               = 14,
    VFIO_USER_MAX,
};

/* VFIOUserHdr flags */
#define VFIO_USER_REQUEST       0x0
#define VFIO_USER_REPLY         0x1
#define VFIO_USER_TYPE          0xF

#define VFIO_USER_NO_REPLY      0x10
#define VFIO_USER_ERROR         0x20


/*
 * VFIO_USER_VERSION
 */
typedef struct {
    VFIOUserHdr hdr;
    uint16_t major;
    uint16_t minor;
    char capabilities[];
} VFIOUserVersion;

#define VFIO_USER_MAJOR_VER     0
#define VFIO_USER_MINOR_VER     0

#define VFIO_USER_CAP           "capabilities"

/* "capabilities" members */
#define VFIO_USER_CAP_MAX_FDS   "max_msg_fds"
#define VFIO_USER_CAP_MAX_XFER  "max_data_xfer_size"
#define VFIO_USER_CAP_MIGR      "migration"

/* "migration" member */
#define VFIO_USER_CAP_PGSIZE    "pgsize"

#define VFIO_USER_DEF_MAX_FDS   8
#define VFIO_USER_MAX_MAX_FDS   16

#define VFIO_USER_DEF_MAX_XFER  (1024 * 1024)
#define VFIO_USER_MAX_MAX_XFER  (64 * 1024 * 1024)


/*
 * VFIO_USER_DEVICE_GET_INFO
 * imported from struct_device_info
 */
typedef struct {
    VFIOUserHdr hdr;
    uint32_t argsz;
    uint32_t flags;
    uint32_t num_regions;
    uint32_t num_irqs;
    uint32_t cap_offset;
} VFIOUserDeviceInfo;


/*
 * VFIO_USER_DEVICE_GET_REGION_INFO
 * imported from struct_vfio_region_info
 */
typedef struct {
    VFIOUserHdr hdr;
    uint32_t argsz;
    uint32_t flags;
    uint32_t index;
    uint32_t cap_offset;
    uint64_t size;
    uint64_t offset;
} VFIOUserRegionInfo;


/*
 * VFIO_USER_DEVICE_GET_IRQ_INFO
 * imported from struct vfio_irq_info
 */
typedef struct {
    VFIOUserHdr hdr;
    uint32_t argsz;
    uint32_t flags;
    uint32_t index;
    uint32_t count;
} VFIOUserIRQInfo;


/*
 * VFIO_USER_DEVICE_SET_IRQS
 * imported from struct vfio_irq_set
 */
typedef struct {
    VFIOUserHdr hdr;
    uint32_t argsz;
    uint32_t flags;
    uint32_t index;
    uint32_t start;
    uint32_t count;
} VFIOUserIRQSet;


/*
 * VFIO_USER_REGION_READ
 * VFIO_USER_REGION_WRITE
 */
typedef struct {
    VFIOUserHdr hdr;
    uint64_t offset;
    uint32_t region;
    uint32_t count;
    char data[];
} VFIOUserRegionRW;


#endif /* VFIO_USER_PROTOCOL_H */
