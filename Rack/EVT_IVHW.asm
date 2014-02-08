/* =============================================================================
 *
 *   Description: This is the Interrupt Service Routine called EVT_IVHW_Entry
 *
 * -----------------------------------------------------------------------------
 *  Comments: 
 *
 * ===========================================================================*/

#include "VDK.h"
.file_attr prefersMemNum="30";
.file_attr prefersMem="internal";
.file_attr ISR;

.section/doubleany data1;
/* declare external globals */

/* declare locals */

.section/doubleany program;

/******************************************************************************
 * EVT_IVHW_Entry
 */

/* ISR entry point */
.GLOBAL     EVT_IVHW_Entry;
EVT_IVHW_Entry:

/* Insert Your Assembly Code HERE for nesting disabled */

    [--SP] = RETI; /* Pushing the RETI register re-enables nested interrupts */

/* Insert Your Assembly Code HERE for nesting enabled */

    RETI = [SP++]; /* restore pushed RET contents prior to RTI */

    RTI;
.EVT_IVHW_Entry.end:

/* ========================================================================== */
