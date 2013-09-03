/* -*- c++ -*- */

#ifndef MEMREADER_H
#define MEMREADER_H

//Length=13 ( 1 in meno dello 0 finale )
/*static uint8_t LEVEL_PLATE[] = { 'M', '7', '1', ' ', '(', 'p', 'i', 'p', 'p', 'o', ')', 0xd, 0x0d, 0x00 };*/

#include "sc_level_plate.h"
#include "sc_load_left.h"
#include "sc_load_right.h"
#include "sc_unload_left.h"
#include "sc_unload_right.h"

static uint8_t *Script[6] = { 0,
                              LEVEL_PLATE,
                              LOAD_LEFT,
                              UNLOAD_LEFT,
#if EXTRUDERS > 1
                              LOAD_RIGHT,
                              UNLOAD_RIGHT
#else
                              0,0
#endif
};
                              
// Utilities program length
static uint32_t ScriptLength[6] = { -1,
                                     LEVEL_PLATE_LENGTH,
                                     LOAD_LEFT_LENGTH,
				     UNLOAD_LEFT_LENGTH,
#if EXTRUDERS > 1
                                     LOAD_RIGHT_LENGTH,
                                     UNLOAD_RIGHT_LENGTH
#else
                                     -1,-1
#endif
};

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
