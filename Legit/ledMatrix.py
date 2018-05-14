import spidev

class apa102cMatrix:

    def __init__(self, xLen, yLen, spiBus, spiDevice, spiMaxSpeed):
        print("Start __init__")
        self.test = "test"
        
        self.spi = spidev.SpiDev()
        self.spi.open(spiBus, spiDevice)
        self.spi.max_speed_hz = 1000000

        self.ledArray = [[[[0]*4] * yLen] * xLen]

    def test(self):
        print("Start test")
        print(self.test)

        
        self.spi.xfer([0b11100001, 0, 0, 0])
    
        self.spi.xfer([0b11100001, 255, 0, 0])
        self.spi.xfer([0b11100001, 255, 0, 0])
        self.spi.xfer([0b11100001, 255, 0, 0])
        self.spi.xfer([0b11100001, 255, 0, 0])
        
        self.spi.xfer([1, 1, 1, 1])

    def shutdown(self):
        self.spi.close()
