 // set pin numbers (cheesy, yes, at some point this will change in a for loop, or something similar):
 const int btnPlate[ 5 ] = { 13, 12, 8, 7, 4 };
 boolean btnState[ 5 ]  = { true, true, true, true, true };
 long btnTime[ 5 ] = { 0, 0, 0, 0, 0 };

 // Arduino USB Keyboard HID
 uint8_t keybuf[8] = { 0 };

 void setup( )
 {
   pinMode(btnPlate[ 0 ], INPUT_PULLUP );
   pinMode(btnPlate[ 1 ], INPUT_PULLUP );
   pinMode(btnPlate[ 2 ], INPUT_PULLUP );
   pinMode(btnPlate[ 3 ], INPUT_PULLUP );
   pinMode(btnPlate[ 4 ], INPUT_PULLUP );
 
   //Serial.begin( 9600 );
   Keyboard.begin();
 }
 
 void loop( )
 {
   handleButton( 0 );
   handleButton( 1 );
   handleButton( 2 );
   handleButton( 3 );
   handleButton( 4 );
 }
 
 void handleButton( int _button )
 {
   if ( digitalRead( btnPlate[ _button ] ) != btnState[ _button ] )
   {
     btnState[ _button ] = digitalRead( btnPlate[ _button ] );
     if ( btnState[ _button ] && !btnTime[ _button ] )
     {
       // Send keypress, start at index 2, and write keyboard keys '1' and beyond
       keybuf[ 2 + _button ] = 0x1e + _button;
       //Serial.write( keybuf, 8 );
       //Keyboard.press( 0x1e + _button );
       Keyboard.print( (_button + 1) );
       btnTime[ _button ] = millis();
     }
   }
   if ( btnTime[ _button ] && ( btnTime[ _button ] + 500 < millis() ) )
   {
     keybuf[ 2 + _button ] = 0x00;
     btnTime[ _button ] = 0;
     //Serial.write( keybuf, 8 );
     //Keyboard.release( 0x1e + _button );
   }
 }
 /*
 void releaseKey() 
 {
     keybuf[0] = 0;
     keybuf[2] = 0;
     Serial.write( keybuf, 8 );
 }
 */
 
