/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
# include	"trek.h"

/*
**  DOCK TO STARBASE
**
**	The starship is docked to a starbase.  For this to work you
**	must be adjacent to a starbase.
**
**	You get your supplies replenished and your captives are
**	disembarked.  Note that your score is updated now, not when
**	you actually take the captives.
**
**	Any repairs that need to be done are rescheduled to take
**	place sooner.  This provides for the faster repairs when you
**	are docked.
*/
void
dock(int unused)
{
	register int		i, j;
	int			ok;
	register struct event	*e;

	if (Ship.cond == DOCKED) {
	        printf("Chekov: But captain, we are already docked\n");
		return;
        }
	/* check for ok to dock, i.e., adjacent to a starbase */
	ok = 0;
	for (i = Ship.sectx - 1; i <= Ship.sectx + 1 && !ok; i++)
	{
		if (i < 0 || i >= NSECTS)
			continue;
		for (j = Ship.secty - 1; j <= Ship.secty + 1; j++)
		{
			if (j  < 0 || j >= NSECTS)
				continue;
			if (Sect[i][j] == BASE)
			{
				ok++;
				break;
			}
		}
	}
	if (!ok) {
	        printf("Chekov: But captain, we are not adjacent to a starbase.\n");
		return;
        }

	/* restore resources */
	Ship.energy = Param.energy;
	Ship.torped = Param.torped;
	Ship.shield = Param.shield;
	Ship.crew = Param.crew;
	Game.captives += Param.brigfree - Ship.brigfree;
	Ship.brigfree = Param.brigfree;

	/* reset ship's defenses */
	Ship.shldup = 0;
	Ship.cloaked = 0;
	Ship.cond = DOCKED;
	Ship.reserves = Param.reserves;

	/* recalibrate space inertial navigation system */
	Ship.sinsbad = 0;

	/* output any saved radio messages */
	dumpssradio();

	/* reschedule any device repairs */
	for (i = 0; i < MAXEVENTS; i++)
	{
		e = &Event[i];
		if (e->evcode != E_FIXDV)
			continue;
		reschedule(e, (e->date - Now.date) * Param.dockfac);
	}
}


/*
**  LEAVE A STARBASE
**
**	This is the inverse of dock().  The main function it performs
**	is to reschedule any damages so that they will take longer.
*/
void
undock(int unused)
{
	register struct event	*e;
	register int		i;

	if (Ship.cond != DOCKED) {
		printf("Sulu: Pardon me captain, but we are not docked.\n");
		return;
	}
	Ship.cond = GREEN;
	Move.free = 0;

	/* reschedule device repair times (again) */
	for (i = 0; i < MAXEVENTS; i++)
	{
		e = &Event[i];
		if (e->evcode != E_FIXDV)
			continue;
		reschedule(e, (e->date - Now.date) / Param.dockfac);
	}
}
