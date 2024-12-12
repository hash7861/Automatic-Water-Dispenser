# Automatic-Water-Dispenser
Personal project from ECE 2360 taken in Autumn 2024
// Project Code Overview: We created a seamless, automatic water dispenser. While there is no object in front of
// the hrs04 sensor, the red LED stays HIGH, the serial monitor outputs the distance (cm), no object detected,
// the water pump stays OFF, and the LCD screen prints "Not Filling". As soon as the sensor senses an object within
// 8 cm, the green LED turns on, and the water pours into the object. The serial monitor only then outputs object 
// is detected and the LCD prints the message "Filling Up". Hence the water pump stays ON until the object is out of range.
