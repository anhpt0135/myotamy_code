####Section 1:
###(BBB Web interface)

SYSFS is file system, we will use lots of 'c' applications to access peripherals via SYSFS,
like LCD, EEPROM, I2C, sensor, 7segment display, SPI, ADC...

Example:
/sys/class # ls
bdi          graphics     mdio_bus     mtd          sar_adc_cls  ubi
dma          i2c-adapter  mem          net          spi_master   usb_device
firmware     i2c-dev      misc         pwm          spidev
gpio         ieee80211    mmc_host     rfkill       tty
/sys/class # cd gpio
/sys/class/gpio # ls
export      gpio34      gpio42      gpio46      gpio58      gpiochip32
gpio13      gpio36      gpio43      gpio47      gpio59      unexport
gpio27      gpio39      gpio44      gpio48      gpio60
gpio28      gpio40      gpio45      gpio49      gpiochip0

/sys/class/gpio # ls -la
drwxr-xr-x    2 root     root             0 Jan  1  1970 .
drwxr-xr-x   24 root     root             0 Jan  1  1970 ..
--w-------    1 root     root          4096 Jan  1  1970 export
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio13 -> ../../devices/platform/ftgpio010.0/gpio/gpio13
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio27 -> ../../devices/platform/ftgpio010.0/gpio/gpio27
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio28 -> ../../devices/platform/ftgpio010.0/gpio/gpio28
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio34 -> ../../devices/platform/ftgpio010.1/gpio/gpio34
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio36 -> ../../devices/platform/ftgpio010.1/gpio/gpio36
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio39 -> ../../devices/platform/ftgpio010.1/gpio/gpio39
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio40 -> ../../devices/platform/ftgpio010.1/gpio/gpio40
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio42 -> ../../devices/platform/ftgpio010.1/gpio/gpio42
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio43 -> ../../devices/platform/ftgpio010.1/gpio/gpio43
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio44 -> ../../devices/platform/ftgpio010.1/gpio/gpio44
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio45 -> ../../devices/platform/ftgpio010.1/gpio/gpio45
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio46 -> ../../devices/platform/ftgpio010.1/gpio/gpio46
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio47 -> ../../devices/platform/ftgpio010.1/gpio/gpio47
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio48 -> ../../devices/platform/ftgpio010.1/gpio/gpio48
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio49 -> ../../devices/platform/ftgpio010.1/gpio/gpio49
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio58 -> ../../devices/platform/ftgpio010.1/gpio/gpio58
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio59 -> ../../devices/platform/ftgpio010.1/gpio/gpio59
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpio60 -> ../../devices/platform/ftgpio010.1/gpio/gpio60
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpiochip0 -> ../../devices/platform/ftgpio010.0/gpio/gpiochip0
lrwxrwxrwx    1 root     root             0 Jan  1  1970 gpiochip32 -> ../../devices/platform/ftgpio010.1/gpio/gpiochip32

/sys/class/gpio # cd gpio13
/sys/devices/platform/ftgpio010.0/gpio/gpio13

echo '1' > trigger  => '1' hoan toan la 1 string

echo "$a"        | apple       | variables are expanded inside ""
echo '$a'        | $a          | variables are not expanded inside ''

####Section 2
###Functional block

####Section 3: Beaglebone Linux Booting Process

###15: What do we need to successfully boot linux on BBB ?
##Linux Boot requirement:
1. ROM Boot Loader: la mot phan ma de chay tren mot SOC khi cap nguon. ROM Boot Loader duoc viet boi nha san xuat va luu trong
ROM trong qua trinh san xuat chip nay. Khong the thay doi no.
==> Nhiem vu cua ROM Boot Loader la de khoi chay stage boot loader thu 2 la SPL/MLO

2. SPL/MLO (Secondary Program Loader/Memory Loader): duoc dua vao internal SRAM, ==> de load va thi hanh stage boot loader thu 3 
la U-boot.

3.U-boot(duoc load vao DDR memory of the board): duoc dung de load va run the Linux Kernel 

4. Linux Kernel: ==> duoc load vao DDR memory of the board de sau do mount RFS into RAM.

5. RFS(Root FIle System): trong SD/Flash/Network/RAM/e-MMC

==> De boot Linux thanh cong thi ta can it nhat tu 1-5 thanh phan o phia tren.

===> Dung busy-box de tao ra your own root file system (RFS)


###20: Booting RBL and MLO on BBB

RBL copies MLO tu external memory device (MMC card, USB, NAND, ...) vao internal SRAM cua AM3359.
De thuc hien viec boot thi micro SD card can phan vung 2 partitions:
partition 1 o dinh dang FAT chua boot: MLO, U-boot
partition 2 o dinh dang ext3/ext4 (la dinh dang file systems mac dinh cua LINUX tieng anh goi la linux native file systems) chua va linux-kernel image (uImage) va RFS

Cong viec cua U-boot la khoi tao peripherals va sau do load Kernel vao DDRAM.

###24: Decoding U-boot header of uImage Manually
MMC0 interface ==> microSD card
MMC1 interface ==> e-MMC

U-boot command:
de load a file from FAT based file system in to memory use : fatload
de load a file from any file system : load

example:
fatload usb 0:2 0x82000000 uImage
fatload mmc 0:2 0x88000000 initramfs
load mmc 0:2 0x88000000 uImage


####Section 12: U-boot (bao gom SPL/MLO, U-boot image)

1. Download U-boot:
git clone -b sunxi https://github.com/linux-sunxi/u-boot-sunxi.git

