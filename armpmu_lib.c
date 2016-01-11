#include "armpmu_lib.h"

uint32_t read_pmn(uint32_t counter)
{
	uint32_t result;
	// Only four bits are valid, rest is reserved.
	counter &= 0xf;
	// Select the given counter.
	MCR_PMU(counter, PMSELR);
	// Read the register.
	MRC_PMU(result, PMXEVCNTR);
	return result;
}

void reset_pmn()
{
	uint32_t cr;
	// Read the control register.
	MRC_PMU(cr, PMCR);
	// Set the "Event counter reset" bit 1.
	cr |= (1 << 1);
	// Write the control register back.
	MCR_PMU(cr, PMCR);
}

void reset_ccnt()
{
	uint32_t cr;
	// Read the control register.
	MRC_PMU(cr, PMCR);
	// Set the "Cycle counter reset" bit 2.
	cr |= (1 << 2);
	// Write the control register back.
	MCR_PMU(cr, PMCR);
}
