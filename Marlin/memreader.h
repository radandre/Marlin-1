/* -*- c++ -*- */

#ifndef MEMREADER_H
#define MEMREADER_H

static char *ScriptName[5] = { "", "Calib. piano", "2", "3", "4" };

//Length=13 ( 1 in meno dello 0 finale )
/*static uint8_t LEVEL_PLATE[] = { 'M', '7', '1', ' ', '(', 'p', 'i', 'p', 'p', 'o', ')', 0xd, 0x0d, 0x00 };*/

#include "sc_level_plate.h"

static uint8_t *Script[5] = { 0,
                              LEVEL_PLATE,
                              0,
                              0,
                              0 };
                              
// Utilities program length
static uint32_t ScriptLength[5] = { -1,
                                     LEVEL_PLATE_LENGTH,
                                     0,
                                     0,
                                     0 };

class MemReader
{
public:
  MemReader();
  
  void startMemprint(const uint8_t nr);
  void getStatus();
  void printingHasFinished();

  FORCE_INLINE bool eof() { return pos>=ScriptLength[program]; };
  FORCE_INLINE int16_t get() {  if ( pos<=ScriptLength[program] ) 
                                  return (int16_t)Script[program][pos++];
                                else
                                  return -1;
                             };
  FORCE_INLINE uint8_t percentDone(){if(!isprinting) return 0; return pos/((ScriptLength[program]+99)/100); };

public:
  bool isprinting;  

private:
  uint8_t program;
  uint32_t pos;

};
extern MemReader utility;
#endif
