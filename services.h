#ifndef SERVICES_
#define SERVICES_

#define SET_BIT(REG, BIT) (REG |= (1<<BIT))
#define TOG_BIT(REG, BIT) (REG ^= (1<<BIT))
#define CLR_BIT(REG, BIT) (REG &= ~(1<<BIT))

#endif