import Adafruit_DHT

# Set the sensor type and pin number
sensor = Adafruit_DHT.DHT22
pin = 4

# Get the temperature and humidity
humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

# Check if the sensor reading was successful
if humidity is not None and temperature is not None:
    print(f'Temperature: {temperature:.1f} °C')
else:
    print('Failed to retrieve temperature data')
