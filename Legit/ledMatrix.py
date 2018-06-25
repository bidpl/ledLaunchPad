import spidev
import numpy as np

class apa102cMatrix:
    def __init__(self, xLen, yLen, spiBus, spiDevice, spiMaxSpeed):
        print("Start __init__")
        
        self.spi = spidev.SpiDev()
        self.spi.open(spiBus, spiDevice)
        self.spi.max_speed_hz = 1000000

        self.ledArray = np.zeros( (xLen, yLen, 4), dtype=np.int16 )

        self.ledArray[..., ..., 3] = 1

    def test(self):
        print("Start test")
        print(self.spi.max_speed_hz)
        
        self.showLedArray()

    def setPixel(self, xPos, yPos, red, blue, green, *brightness):
        self.ledArray[xPos][yPos][0] = min(255, red)
        self.ledArray[xPos][yPos][1] = min(255, blue)
        self.ledArray[xPos][yPos][2] = min(255, green)

        if len(brightness) > 0:
            self.ledArray[xPos][yPos][3] = min([31, max([1, brightness[0]])])

    def showLedArray(self):
        print(self.ledArray)

    def showMatrix(self):
        #Opening frame
        self.spi.xfer([0, 0, 0, 0])
        for row in range(self.ledArray.shape[0]):
            for column in range(self.ledArray.shape[1]):
                #Led Frame
                led = self.ledArray[row][column]
                self.spi.xfer( [int(224 +led[3])] )
                self.spi.xfer( [int(led[0])] )
                self.spi.xfer( [int(led[2])] )
                self.spi.xfer( [int(led[3])] )

        #Closing Frame
        self.spi.xfer([255, 255, 255, 255])

    def shutdown(self):
        self.spi.close()
