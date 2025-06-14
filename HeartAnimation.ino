#include "Arduino_LED_Matrix.h"  

ArduinoLEDMatrix matrix; 

uint32_t frame[] = {   
  0x3184a444,   
  0x42081100,   
  0xa0040000 
};  

void setup() {   
  Serial.begin(9600);   
  matrix.begin(); 
  Serial.println("Please enter one of the Commands : "); 
  Serial.println("On");     
  Serial.println("Off");     
  Serial.println("Swap");    
  Serial.println("Left");
  Serial.println("Right");  
}     

String HexBin(uint32_t* image) {
    String binpart2 = "";
    for (int b = 0; b < 3; b++) {
        String temp = String(image[b], BIN);
        while (temp.length() < 32) temp = "0" + temp;  // Ensure 32 bits
        binpart2 += temp;
    }
    return binpart2;
}

void BinHex(String binparts, uint32_t* output) {
    for (int i = 0; i < 3; i++) {
        String chunk = binparts.substring(i * 32, (i + 1) * 32);
        output[i] = strtoul(chunk.c_str(), NULL, 2);
    }
}

void Animate_Right(uint32_t* image) {
  String binpart = HexBin(image);
  String newBinpart = "";

  for(int row=0; row<8; row++) {

    // 12x8 Grid Grid, Grab first 12 Char, take Right most and put end of Left (Right Shift)
    // Then add to full binary Sequence
    String cur_row = binpart.substring(row*12,(row+1) * 12);
    String new_row = cur_row.charAt(11) + cur_row.substring(0,11);
    newBinpart += new_row;

  }
  BinHex(newBinpart,image);

}

void Animate_Left(uint32_t* image) {
  String binpart = HexBin(image);
  String newBinpart = "";

  for(int row=0; row<8; row++) {

    // 12x8 Grid Grid, Grab first 12 Char, take Right most and put end of Left (Right Shift)
    // Then add to full binary Sequence
    String cur_row = binpart.substring(row*12,(row+1) * 12);
    String new_row =  cur_row.substring(1) + cur_row.charAt(0);
    newBinpart += new_row;

  }
  BinHex(newBinpart,image);
  
}

void loop() {


  // Variables
  String binpart = "";        
  String userInput = Serial.readString();        
  userInput.trim();  
  uint32_t parts[3];
  binpart = "";          
    

    // Turns on the preset Image
    if (userInput.equalsIgnoreCase("on")){       
                  
      matrix.loadFrame(parts);
      
      //Binary Operations
      binpart = HexBin(frame);  
      Serial.println("Full binary: " + binpart);
      
      // Re-Organize Array and Convert back to Hex
      BinHex(binpart,parts);
      
      // Load Matrix
      matrix.loadFrame(parts);          
    }    

    // Turns off matrix
    if (userInput.equalsIgnoreCase("off")){     
      matrix.clear();
    }

    // Inverts Image
    if (userInput.equalsIgnoreCase("swap")){       
      
      binpart = HexBin(frame);  

        // reverse all values of leds
        int length = binpart.length();      
        for(int i=0; i < length; i++){              
          if(binpart.charAt(i) == '0'){         
            binpart.setCharAt(i, '1');       
          }       
          else{         
            binpart.setCharAt(i, '0');       
          }       
        }      
        // Finish loop and create heximage
        BinHex(binpart,parts);
        // Load image
      matrix.loadFrame(parts); 
      }       
      
      // Animation
        
        // Keep shifting Image right untill other input given
    if(userInput.equalsIgnoreCase("right")){ 

      Serial.println("Type anything to stop");
      while(Serial.available() <= 0){
      Animate_Right(parts);
      matrix.loadFrame(parts);
      delay(200);

      }
    }

      // Keep shifting Image left aswell
    else if(userInput.equalsIgnoreCase("left")){
                
      Serial.println("Type anything to stop");
      while(Serial.available() <= 0){
      Animate_Left(parts);
      matrix.loadFrame(parts);
      delay(200);
      }

  } 
}