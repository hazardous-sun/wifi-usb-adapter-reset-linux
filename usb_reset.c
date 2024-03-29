#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>

/*
 * Use the "lsusb" command to get the bus and the id of the USB port you want to reset
 * Run "sudo ./usbreset /dev/bus/usb/BUS_NUMBER/USB_ID" to reset the specified USB port
 */

int main(int argc, char **argv) {

    const char *filename;
    int fd;
    int rc;

    // No path provided
    if (argc != 2) {
        fprintf(stderr, "Usage: usbreset device-filename\n");
        return 1;
    }

    filename = argv[1];

    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Error opening output file");
        return 2;
    }

    printf("Resetting USB device %s\n", filename);
    rc = ioctl(fd, USBDEVFS_RESET, 0);
    if (rc < 0) {
        perror("Error in ioctl");
        return 3;
    }
    printf("Reset successful\n");

    close(fd);

    return 0;
}
