/* =============================================================================
 *
 *   Description: This is the Interrupt Service Routine called EVT_IVG7_Entry
 *
 * -----------------------------------------------------------------------------
 *  Comments: 
 *
 * ===========================================================================*/

#include "VDK.h"
#include <stddefine.h>
#include <RS232>

.file_attr prefersMemNum="30";
.file_attr prefersMem="internal";
.file_attr ISR;

.section/doubleany data1;
/* declare external globals */

/* declare locals */

.section/doubleany program;

/******************************************************************************
 * EVT_IVG7_Entry
 */

/* ISR entry point */
.GLOBAL     EVT_IVG7_Entry;
EVT_IVG7_Entry:


    //[--SP] = RETI; /* Pushing the RETI register re-enables nested interrupts */

    ISR_RS232_SERVICE();

    //RETI = [SP++]; /* restore pushed RET contents prior to RTI */

    RTI;
.EVT_IVG7_Entry.end:

/* ========================================================================== */
