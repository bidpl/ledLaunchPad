import ledMatrix
import time

time.sleep(1)



matrix = ledMatrix.apa102cMatrix(4, 1, 0, 0, 1000000)

matrix.setPixel(0, 0, 255, 0, 0)
matrix.setPixel(1, 0, 0, 255, 0)
matrix.setPixel(2, 0, 0, 0, 255, 20)

matrix.showMatrix();

matrix.test()

matrix.shutdown()
