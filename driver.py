import camino
import time
import numpy as np

con = camino.SerialConnection(port="/dev/ttyACM0", baud=9600)

arduino = camino.Arduino(con)

hopfield_patterns = [
  np.array([[1, 1, 1], [1, -1, 1], [-1, -1, -1]]),
  np.array([[-1, 1, -1], [1, 1, 1], [-1, 1, -1]]),
  np.array([[-1, -1, -1], [-1, 1, -1], [1, 1, 1]]),
]

def print_hopfield_pattern(pattern):
  output = np.copy(pattern)
  output[output > 0] = 1
  output[output < 0] = 0

  led_pattern = output.astype(int).flatten().tolist()
  arduino.set_pattern(*led_pattern) 

W = np.zeros((9,9)) # weights

#train
print("training...")
for pattern in hopfield_patterns:
  print_hopfield_pattern(pattern)
  W += np.outer(pattern.flatten(), pattern.flatten())
  time.sleep(0.7)

np.fill_diagonal(W, 0)
arduino.set_pattern(0,0,0,0,0,0,0,0,0) 


time.sleep(1)

# testing
test = np.array([[-1, -1, -1], [1, 1, 1], [1, -1, 1]])

activations = np.copy(test)
for _ in range(5):
  print_hopfield_pattern(activations)
  activations = 0.5 * np.dot(W, activations.reshape(-1, 1))
  time.sleep(1)

time.sleep(5) 
  
