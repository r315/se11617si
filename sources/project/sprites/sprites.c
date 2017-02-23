#include <inttypes.h>
#include "sprites.h"

const uint16_t pal1[]={0,
 0xBFFF,0xFA40,0xFFE4,0x06DF,0xF800,0x07E0,0x5DF6,0x3A2F
};

//-----------------------------------------------------------------------------
// Map Aliens0
//-----------------------------------------------------------------------------
const uint8_t Aliens0[]={
0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,
0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,
0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03
}; 

//-----------------------------------------------------------------------------
// Map Aliens1
//-----------------------------------------------------------------------------
const uint8_t Aliens1[]={
0x04,0x04,0x04,0x04,0x04,0x04,
0x04,0x04,0x04,0x04,0x04,0x04,
0x05,0x05,0x05,0x05,0x05,0x05,
0x05,0x05,0x05,0x05,0x05,0x05,
0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06
}; 

//-----------------------------------------------------------------------------
// Map Misc
//-----------------------------------------------------------------------------
const uint8_t Misc[]={
0x07,0x08,0x09,0x0A
}; 

//-----------------------------------------------------------------------------
// spcinv
// Count 10
//-----------------------------------------------------------------------------
const uint8_t spcinv[] ={
/* spcinv Tile 0 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x02,0x02,0x00,0x02,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x02,0x02,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
/* spcinv Tile 1 */
0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x03,0x00,0x03,0x03,0x03,0x00,0x03,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x03,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
/* spcinv Tile 2 */
0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x00,0x00,
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x00,0x04,0x04,0x04,0x00,0x00,0x00,0x04,0x04,0x04,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x00,0x00,0x00,
0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x00,
/* spcinv Tile 3 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x02,0x02,0x00,0x02,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x02,0x02,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x00,0x02,0x00,0x00,0x02,0x00,0x02,0x00,0x00,0x00,0x00,
/* spcinv Tile 4 */
0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x03,0x00,0x00,0x00,
0x00,0x00,0x03,0x03,0x03,0x00,0x03,0x03,0x03,0x00,0x03,0x03,0x03,0x00,0x00,0x00,
0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
/* spcinv Tile 5 */
0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x00,0x00,
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x04,0x04,0x00,0x04,0x04,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x00,
0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,
/* spcinv Tile 6 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,
0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
0x00,0x00,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x00,
/* spcinv Tile 7 */
0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,
0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x00,
0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
/* spcinv Tile 8 */
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x06,
0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,
0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,
/* spcinv Tile 9 */
0x00,0x00,0x00,0x00,0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,
0x00,0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,
0x00,0x05,0x05,0x00,0x05,0x05,0x00,0x05,0x05,0x00,0x05,0x05,0x00,0x05,0x05,0x00,
0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
0x00,0x00,0x05,0x05,0x05,0x00,0x00,0x05,0x05,0x00,0x00,0x05,0x05,0x05,0x00,0x00,
0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

