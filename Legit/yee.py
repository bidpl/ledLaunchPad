import spidev
import time
import ledMatrix

time.sleep(1)

spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 1000000

for i in range(4):
    spi.xfer([0])

spi.xfer([0b11100001,255,0,0])

spi.xfer([0b11100001,0,255,0])

spi.xfer([0b11100001,255,0,0])

spi.xfer([0b11100001,255,0,0])

for i in range(4):
    spi.xfer([255])


time.sleep(1)

spi.close()
