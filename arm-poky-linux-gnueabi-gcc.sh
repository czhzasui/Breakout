#!/bin/bash
if [ "$1" != "-cc1" ]; then
    /opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/i686-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc --sysroot /opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi "$@"
else
    # target/triple already spelled out.
    /opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/i686-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc "$@"
fi
