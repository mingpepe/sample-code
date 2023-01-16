#include <linux/gpio.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main()
{
    struct gpiochip_info info;
    int err = 0;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open gpiochip.\n");
        return 1;
    }

    struct gpiohandle_request req = {
        .lineoffsets[0] = 17,
        .lines = 1,
        .flags = GPIOHANDLE_REQUEST_OUTPUT,
        .consumer_label = "blinker",
    };

    err = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    if (err < 0)
    {
        printf("Failed to get gpio handler.\n");
        return err;
    }

    struct gpiohandle_data data;
    while (1)
    {
        data.values[0] = 1;
        err = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
        if (err < 0)
        {
            printf("Failed to set gpio output as high.\n");
            return err;
        }
        sleep(1);
        data.values[0] = 0;
        err = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
        if (err < 0)
        {
            printf("Failed to set gpio output as low.\n");
            return err;
        }
        sleep(1);
    }
    return 0;
}