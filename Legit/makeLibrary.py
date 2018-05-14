import ledMatrix
import time

time.sleep(1)


matrix = ledMatrix.apa102cMatrix(4, 1, 0, 0, 1000000)

#matrix.test()

matrix.setPixel(0, 0, 255, 0, 0, 1)
matrix.setPixel(1, 0, 0, 255, 0, 1)
matrix.setPixel(2, 0, 0, 0, 255, 1)
##matrix.setPixel(3, 0, 255, 0, 0, 14)

##matrix.showMatrix()
print(matrix.ledArray)

matrix.shutdown()
