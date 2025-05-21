# Communication Protocols

The code is for Arduino. Only needed library is `LiquidCrystal`.

The maximum message size that can be sent is 16 characters, however it can be easily changed in code by changing the size of `rx_message` char array. 16 is chosen because LCD that is used in this project can only disply 16 characters in one row.

HDLC is a widely known protocol, which was earlier used for Ethernet, and is still used in many applications for its reliability and speed. My goal is to set up the standard HDLC protocol with Manchester encoding (if possible on Arduino), from complete scratch.

First synchronous serial communication between two Arduinos was set up, inspired form Ben Eater. Then instead of using `utf-8` encoding that is used in standard communication, I established communication in Morse code, with clock. This posed many subtle challenges, for example, the bit length of each character wasn't fixed in standard Morse protocol. It could range from 3 to 16 unlike `utf-8`, in which each character is 8 bits or one byte long. Initially I was planning on creating an asynchronous version of this project before turning it into synchronous, but gave up on that idea after making the transmitter because I felt it was unnecessary, since HDLC will have a clock anyways. This project served as a bridge between serial and HDLC communication, since it is a tamer version of HDLC, building on the serial communication foundation, inculcating extras of HDLC like use of delimiters and variable message lengths. HDLC still requires much more than Morse, for example, bit stuffing.

---
> * Serial communication between 2 Arduino Nano's completed.
> * Morse communication between 2 Arduino Nano's completed.
---
> * HDLC implementation is ongiong.
---
