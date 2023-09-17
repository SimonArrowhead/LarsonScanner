const int led_pin_1 = 11;
const int led_pin_2 = 10;
const int led_pin_3 = 9;
const int led_pin_4 = 6;
const int led_pin_5 = 5;
const int led_pin_6 = 3;

int brightness_mid = 255;
int brightness_sides = 25;
int led_off = 0;

int led_array[] = {led_pin_1, led_pin_2, led_pin_3, led_pin_4, led_pin_5, led_pin_6};
const size_t len = sizeof(led_array)/sizeof(led_array[0]); // Determine the size of the array in bytes and then divide by the size of one element (4 bytes)

int wait = 80;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin_1, OUTPUT); 
  pinMode(led_pin_2, OUTPUT); 
  pinMode(led_pin_3, OUTPUT);
  pinMode(led_pin_4, OUTPUT); 
  pinMode(led_pin_5, OUTPUT); 
  pinMode(led_pin_6, OUTPUT);
}

void loop() {
  // Animation loop
  for (int i = 0; i < len; i++) {
    // The following conditions are written in the order in which the animation runs
    analogWrite(led_array[i], brightness_mid); // Turns on the main LED with full brightness.
    if (i > 2) analogWrite(led_array[i-3], led_off); // First checks if there is a LED that can be turned off. If so, it turns it off.
    if (i > 1) analogWrite(led_array[i-2], brightness_sides-20); // First checks if there is a LED that can be turned on as a side LED with a brightness of 5.
    if (i == 0) analogWrite(led_array[i+3], led_off); // Turns off LEDs lit in the previous iteration to improve animation smoothness.
    if (i == 1) analogWrite(led_array[i+1], led_off); // Turns off LEDs lit in the previous iteration to improve animation smoothness.
    if (i > 0) analogWrite(led_array[i-1], brightness_sides); // First checks if there is a LED that can be turned on as a side LED with a brightness of 25.
    // The following lines were intended to create a shadow on both sides of the brightest LED, but it should only be on one side, like with bulbs.
    // if (i < len - 1) analogWrite(led_array[i+1], brightness_sides); // First checks if there is a LED that can be turned on as a side LED with a brightness of 25.
    // if (i < len - 2) analogWrite(led_array[i+2], brightness_sides-20); // First checks if there is a LED that can be turned on as a side LED with a brightness of 5.
    // if (i < len - 3) analogWrite(led_array[i+3], led_off); // First checks if there is a LED that can be turned off. If so, it turns it off.
    if (i < len-1) {
      delay(wait);
    } else reverseArr(0, len-1, led_array); // Reverses the array after the last iteration of the loop to make the animation go in the other direction.
  }
}

// Reverses the array
void reverseArr(int start, int end, int arr[]) {
  if (start >= end) {
    return;
  }

  int c = arr[start];
  arr[start] = arr[end];
  arr[end] = c;
  reverseArr(start+1, end-1, arr);
}

// Helper function for debugging the array values
void printArray(int arr[], size_t arr_size) {
  for (int i = 0; i < arr_size; i++) {
    Serial.print("Value at position ");
    Serial.print(i); 
    Serial.print(" is: ");   
    Serial.println(arr[i]);   
  }
}
