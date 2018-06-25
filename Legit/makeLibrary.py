import ledMatrix
import time

time.sleep(1)


matrix = ledMatrix.apa102cMatrix(4, 1, 0, 0, 1000000)

matrix.test()

matrix.shutdown()
