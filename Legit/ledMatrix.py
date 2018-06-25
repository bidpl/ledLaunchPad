import spidev
import numpy

class apa102cMatrix:
    def __init__(self, xLen, yLen, spiBus, spiDevice, spiMaxSpeed):
        print("Start __init__")
        
        self.spi = spidev.SpiDev()
        self.spi.open(spiBus, spiDevice)
        self.spi.max_speed_hz = 1000000

        self.ledArray = [[[0]*4]*yLen]*xLen

    def test(self):
        print("Start test")
        print(self.spi.max_speed_hz)
        
        self.showLedArray()

        self.ledArray[1][0][0] = 100
               
        
        self.showLedArray()

    def setPixel(self, xPos, yPos, red, blue, green, *brightness):
        self.ledArray[xPos][yPos][0] = red
        self.ledArray[xPos][yPos][1] = blue
        self.ledArray[xPos][yPos][2] = green

        if len(brightness) > 0:
            self.ledArray[xPos][yPos][3] = min([31, max([1, brightness[0]])])

    def showLedArray(self):
        print(self.ledArray)

    def showMatrix(self):
        #Opening frame
        self.spi.xfer([0, 0, 0, 0])
        for row in self.ledArray:
            for led in row:
                #Led Frame
                self.spi.xfer([0b11100001])
                self.spi.xfer([led[0]])
                self.spi.xfer([led[1]])
                self.spi.xfer([led[2]])

        #Closing Frame
        self.spi.xfer([255, 255, 255, 255])

    def shutdown(self):
        self.spi.close()
