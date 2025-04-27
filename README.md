# Communication Protocols

The code is for Arduino. Only needed library is `LiquidCrystal`.

The maximum message size that can be sent is 16 characters, however it can be easily changed in code by changing the size of `rx_message` char array. 16 is chosen because LCD that is used in this project can only disply 16 characters in one row.

---
> * Serial communication between 2 Arduino Nano's completed.
> * Morse communication between 2 Arduino Nano's completed.
---
> * HDLC implementation is ongiong.

HDLC is a widely known protocol, which was earlier used for Ethernet, and is still used in many applications for its reliability and spped. My goal is to set up the standard HDLC protocol with Manchester encoding (if possible on Arduino), from complete scratch.
